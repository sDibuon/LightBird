#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    int socket;
} Http_Server;


int init_Http_Server( Http_Server* server, unsigned short port );
int close_Http_Server( Http_Server* server );