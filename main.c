#include "lib/Dict.c"
#include "lib/Http_Server.c"



Http_Server server;
HashTable routes;


void close_server_execution( int sig )
{
    if ( close_Http_Server( &server ) != 0 ) {
        fprintf( stderr, "Error on Signal ctrl+c on close http server.\n" );
    }

    if ( del_Hash_Table( &routes ) ) {
        fprintf( stderr, "Error on Signal ctrl+c on delelte hash table.\n" );
    }

    exit(0);
}

void response_function( int socket, char* request, int request_lenght )
{
    struct { char method[128]; char route[256]; char version[128]; } request_header;
    sscanf( request, "%s %s %s", request_header.method, request_header.route, request_header.version );
    char* result = search_Hash_Table( &routes, request_header.route );
    if ( result != NULL ) {
        FILE* file = fopen( result, "r" );
        if ( file == NULL ) {
            fprintf( stderr, "Error to open file %s", result );
            return ;
        }
        int bytes_reads = fread( request, sizeof(char), 4096, file );
        send( socket, request, bytes_reads, 0 );
    }
}


int main( int argc, char* argv[] )
{
    if ( init_Http_Server( &server, 80 ) != 0 ) {
        fprintf( stderr, "Error during init http server.\n" );
        close_Http_Server( &server );
        return -1;
    }

    if ( init_Hash_Table( &routes, 13, 65.0 ) ) {
        fprintf( stderr, "Error during init hash table.\n" );
        close_Http_Server( &server );
        del_Hash_Table( &routes );
        return -1;
    }

    if ( signal(SIGINT, close_server_execution) == SIG_ERR ) {
        printf("Error in setting signal handler.\n");
        close_Http_Server( &server );
        del_Hash_Table( &routes );
        return 1;
    }

    if ( insert_Hash_Table( &routes, "/", "views/index.html" ) != 0 ) {
        fprintf( stderr, "Error on insert route %s.\n", "/" );
    }

    return listen_Http_Server( &server, 10, response_function );
}