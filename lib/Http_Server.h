#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    int socket;
} Http_Server_t;

typedef Http_Server_t* Http_Server;

Http_Server Create_Http_Server( unsigned short port );
int Delete_Http_Server( Http_Server* server );