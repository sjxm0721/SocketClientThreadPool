#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<iostream>
#include<stdio.h>

using namespace std;

int main()
{
    //创建监听的套接字
    int fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd==-1)
    {
        perror("socket");
        return -1;
    }

    //绑定服务器的IP port
    sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(8888);
    inet_pton(AF_INET,"192.168.71.131",&saddr.sin_addr.s_addr);
    int ret=connect(fd,(sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1)
    {
        perror("connect");
        return -1;
    }


    //通信
    int number=0;
    while(1)
    {
        char buff[1024]={0};
        gets(buff);
        //发送数据
        send(fd,buff,strlen(buff)+1,0);
        //接收数据
        memset(buff,0,sizeof(buff));
        int len=recv(fd,buff,sizeof(buff),0);
        if(len>0)
        {
            cout<<"server say: "<<buff<<endl;
        }
        else if(len==0)
        {
            cout<<"服务器已经断开了连接..."<<endl;
            break;
        }
        else
        {
            perror("recv");
            break;
        }
        sleep(1);
    }

    //关闭文件描述符
    close(fd);
    return 0;
}