#ifndef __TCP_H
#define __TCP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/select.h>

int Tcp_ServerInit(int Port);
int Tcp_WaitNewConnection(int S_fd);
int Tcp_ConnectToServer(char *IP, int Port);
int Tcp_Send(int fd, void *Buf, int Count);
int Tcp_Recv(int fd, void *Buf, int Count);
int Tcp_Close(int fd);
#endif
