#include<winsock2.h>
#include<stdio.h>
#include<string.h>


int socket_send(const char *IP){
    //初始化socket
    DWORD ver;
    WSADATA wsaData;
    ver=MAKEWORD(1,1);//在调用wsaStartUp要告诉windows我用什么版本的socket
    WSAStartup(ver,&wsaData);
    //window要求 只要用socket 第一步 必须调用这个函数


    //初始化socket完成 第一个参数是指定socket要用哪个协议 AF_INET代表要用tcp/ip协议
    //第二个参数socket_DGRAM 意识是要用udp协议
    //第三个参数一般默认填0
    SOCKET st=socket(AF_INET,SOCK_DGRAM,0);//建立一个socket ,第一个参数是指定socket要用哪个协议
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family=AF_INET;//代表要使用一个TCP/IP的地址
    addr.sin_port=htons(8080);//host to net short
    addr.sin_addr.s_addr=inet_addr(IP);//设置成
    //    unsigned long laddr=inet_addr("192.168.6.200");
    //    unsigned char*p=&laddr;
    //    printf("%u,%u,%u,%u\n",*(p),*(p+1),*(p+2),*(p+3));

    char buf[1024]={0};
     size_t rc;
    while(1){
        memset(buf,0,sizeof(buf));
        gets(buf);
        if(buf[0]=='0')//作为循环的退出条件
            break;
        //发送udp数据
          rc=  sendto(st,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));

    }
    closesocket(st);//使用完socket要将其关闭
    WSACleanup();//释放win socket内部的相关资源
    return rc;
}


int socket_recv(){
    //初始化socket
    DWORD ver;
    WSADATA wsaData;
    ver=MAKEWORD(1,1);//在调用wsaStartUp要告诉windows我用什么版本的socket
    WSAStartup(ver,&wsaData);
    //window要求 只要用socket 第一步 必须调用这个函数


    //初始化socket完成 第一个参数是指定socket要用哪个协议 AF_INET代表要用tcp/ip协议
    //第二个参数socket_DGRAM 意识是要用udp协议
    //第三个参数一般默认填0
    SOCKET st=socket(AF_INET,SOCK_DGRAM,0);//建立一个socket ,第一个参数是指定socket要用哪个协议
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family=AF_INET;//代表要使用一个TCP/IP的地址
    addr.sin_port=htons(8080);//host to net short
    addr.sin_addr.s_addr=htonl(INADDR_ANY);//做为接收方 不需要指定具体的ip地址 接收的主机是什么ip 我就在什么ip上收数据
    //    unsigned long laddr=inet_addr("192.168.6.200");
    //    unsigned char*p=&laddr;
    //    printf("%u,%u,%u,%u\n",*(p),*(p+1),*(p+2),*(p+3));
    int rc=0;
    if( bind(st,(struct sockaddr *)&addr,sizeof(addr))>-1)  ;//将端口号和程序绑定
    {
        char buf[1024]={0};
        struct sockaddr_in sendaddr;
        memset(&sendaddr,0,sizeof(sendaddr));
        int len=sizeof(sendaddr);
        while(1){
            memset(buf,0,sizeof(buf));
            //接收udp数据
            rc=  recvfrom(st,buf,sizeof(buf),0,(struct sockaddr*)&sendaddr,&len);
            //inet_ntoa(sendaddr.sin_addr);//这个函数是不可重入函数
            printf("%s:%s\n",inet_ntoa(sendaddr.sin_addr),buf);
        }

    }
    closesocket(st);//使用完socket要将其关闭
    WSACleanup();//释放win socket内部的相关资源
    return rc;
}
