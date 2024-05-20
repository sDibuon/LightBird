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