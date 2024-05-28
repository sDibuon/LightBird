#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "Dict.h"


typedef struct {
    int socket;
} Http_Server;


int init_Http_Server( Http_Server* server, unsigned short port );


int close_Http_Server( Http_Server* server );


int listen_Http_Server( Http_Server* server, int bufflenght, void (*func_handler)(int,char*,int) );


#endif // __HTTP_SERVER_H__