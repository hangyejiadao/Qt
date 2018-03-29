#ifndef UDP_H
#define UDP_H
#include<stdio.h>
#ifdef MYLINUX
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SOCKET int
#else
#include<winsock2.h>
#endif

class udp
{
private:
    SOCKET st;//类的内部成员一般是不暴露在外部的
public:
    udp();
    udp(const udp&it);
    ~udp();
    int socket_bind(short int port);
    int socket_send(const char*IP,const char* buf,int len);
    int socket_recv(  char* buf,int len,char *srcIP);
};

#endif // UDP_H
