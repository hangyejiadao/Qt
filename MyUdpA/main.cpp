#include <iostream>
#include"udp.h"
using namespace std;

int main(int argc,char**args)
{
    if(argc>1){
        udp instance;
        char buf[1024]={0};
        while(1){
            memset(buf,0,sizeof(buf));
            gets(buf);
            instance.socket_send(args[1],buf,strlen(buf));
            if(strncmp(buf,"exit",4)==0)
                break;
        }

    }else{
        udp instance;
        char buf[1024]={0};
        if(instance.socket_bind(8080)>-1){
            char ip[100]={0};
            while(1){
                memset(buf,0,sizeof(buf));
                memset(ip,0,sizeof(ip));
                instance.socket_recv( buf,sizeof(buf),ip);
                if( strncmp(buf,"exit",4)==0)
                    break;
                    cout<<buf<<endl;
                    cout<<ip<<endl;
                }
            }
        }
        return 0;
    }

