#include "udp.h"



udp::udp()
{
#ifndef MYLINUX
    //初始化socket
    DWORD ver;
    WSADATA wsaData;
    ver=MAKEWORD(1,1);
    WSAStartup(ver,&wsaData);
    //初始化socket完成
    //建立一个socket 第一个参数是指定socket要用哪个协议 AF_INET代表要用TCP/IP协议
    //第二个参数SOCKT_DGRAM意思是要用UDP协议
    //第三个参数一般默认0
    st=socket(AF_INET,SOCK_DGRAM,0);//定义一个socket
#endif
}


udp::~udp(){
#ifdef MYLINUX
    close(st);
#else
    closesocket(st);
    WSACleanup();//释放win socket内部的相关资源
#endif
}

udp::socket_bind(short port){

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);//host to net short
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int rc=0;
    return bind(st,(struct sockaddr*)&addr,sizeof(addr));

}


int udp::socket_send(const char *IP, const char *buf, int len){
    st=socket(AF_INET,SOCK_DGRAM,0);//定义一个socket
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family=AF_INET;//代表要使用一个TCP/IP的地址
    addr.sin_port=htons(8080);//host to net short
    addr.sin_addr.s_addr=inet_addr(IP);
    size_t rc=0;
    //发送u'dp数据
    rc=sendto(st,buf,len,0,(struct sockaddr *)&addr,sizeof(addr));
    return rc;

}
int udp::socket_recv(char *buf, int len,char *srcIP)
{
    struct sockaddr_in sendaddr;
    memset(&sendaddr,0,sizeof(sendaddr));
#ifdef MYLINUX
    socklen_t addrlen;
#else
    int addrlen;
#endif
    addrlen=sizeof(sendaddr);
    memset(buf,0,len);

    int   rc=recvfrom(st,buf,len,0,(struct sockaddr* )&sendaddr,&addrlen);
    if(srcIP)
        strcpy(srcIP,inet_ntoa(sendaddr.sin_addr));

    return rc;
}
udp::udp(const udp &it){

}
