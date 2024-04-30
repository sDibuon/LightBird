#include "Http_Server.h"

Http_Server Create_Http_Server( unsigned short port )
{
    Http_Server server = malloc( sizeof(Http_Server_t) );

    server->socket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( server->socket == -1 ) {
        fprintf( stderr, "Error during the creation of socket.\n" );
        return NULL;
    }

    struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons( port );
	server_address.sin_addr.s_addr = INADDR_ANY;

    if ( bind( server->socket, (struct sockaddr *) &server_address, sizeof(server_address) ) == -1 ) {
        fprintf( stderr, "Error during the binding of socket.\n" );
        close( server->socket );
        return NULL;
    }

    return server;
}

int Delete_Http_Server( Http_Server* server )
{
    if ( *server != NULL ) {

        if ( close( (*server)->socket ) == -1 ) {
            fprintf( stderr, "Error closing socket.\n" );
            return -1;
        }

        free( *server );

        *server = NULL;
    }

    return 0;
}