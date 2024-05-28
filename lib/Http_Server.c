#include "Http_Server.h"

int init_Http_Server( Http_Server* server, unsigned short port )
{
    server->socket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( server->socket == -1 ) {
        fprintf( stderr, "Error creation socket.\n" );
        return -1;
    }

    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons( port ),
        .sin_addr.s_addr = INADDR_ANY
    };

    if ( bind( server->socket, (struct sockaddr *) &server_address, sizeof(server_address) ) == -1 ) {
        fprintf( stderr, "Error binding socket.\n" );
        close( server->socket );
        return -1;
    }

    return 0;
}

int close_Http_Server( Http_Server* server )
{
    if ( close( server->socket ) == -1 ) {
        fprintf( stderr, "Error closing socket.\n" );
        return -1;
    }

    return 0;
}

int listen_Http_Server( Http_Server* server, int bufflenght, void (*func_handler)(int,char*,int) )
{
    if ( listen( server->socket, bufflenght ) != 0 ) {
        fprintf( stderr, "Error listen socket.\n" );
        return -1;
    }

    for ( ; ; ) {

        char buffer[4096] = {0};

        struct sockaddr_in client_address;
        int client_addrlen = sizeof(client_address);
        int client_socket = accept( server->socket, (struct sockaddr*)&client_address, (socklen_t*)&client_addrlen );

        // TODO: parse request

        int bytes_recived = recv( client_socket, buffer, 4096, 0 );

        func_handler( client_socket, buffer, bytes_recived );

        close( client_socket );
    }

    return 0;
}