#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

//int main(int argc,char *argv[])
int main()
{
    int serv_sock;
    int clnt_sock;
    /*
    struct sockaddr_in
    {
        sa_family_t sin_family; //地址族
        uint16_t    sin_port;   //16位TCP/UDP端口号 2字节
        struct      sin_addr;   //32位IP地址        4字节
        char        sin_zero[8];//不使用
    }

    struct in_addr
    {
        In_addr_t  s_addr;   //32位IPV4地址
    }

    */

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    char * serv_port="9190";

    char message[]="Hello World!";

    // if(argc!=2)
    // {
    //     printf("Usage : %s <port>\n",argv[0]);
    //     exit(1);
    // }

    /*
    int socket(int domain,int type,int protocol)
    domain 套接字中使用的协议族信息
            PF_INET     IPv4互联网协议族
            PF_INET6    IPv6互联网协议族
            PF_LOCAL    本地通信的UNIX协议族
            PF_PACKET   底层套接字的协议族
            PF_IPX      IPX Novell协议族
    type 套接字数据传输类型信息
            SOCK_STREAM 面向连接的套接字TCP
            SOCK_DGRAM  面向消息的套接字UDP
    protocol 计算机通信中使用的协议信息
            同一协议族中存在多个数据传输方式相同的协议
            IPPROTO_TCP  TCP套接字
            IPPROTO_UDP  UDP套接字
    */
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1)
        error_handling("socket()error");

    memset(&serv_addr,0,sizeof(serv_addr));  //将serv_addr的所有成员初始化为0
    /*
    sin_family
        AF_INET         IPV4网络协议中使用的地址族
        AF_INET6        IPV6网络协议中使用的地址族
        AF_LOCAL        本地通信中采用的UNIX协议的地址族
    
    */
    serv_addr.sin_family=AF_INET;
    /*
    网络字节序为大端序

    unsigned short htons(unsigned short);  //把short型数据从主机字节序转化为网络字节序
    unsigned short ntohs(unsigned short);  //把short型数据从网络字节序转化为主机字节序
    unsigned long htonl(unsigned long);     
    unsigned long ntohl(unsigned long);

    h表示主机(host)字节序
    n表示网络(network)字节序
    s表示short
    l表示long
    */

    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
    //serv_addr.sin_port=htons(atoi(argv[1]));
    serv_addr.sin_port=htons(atoi(serv_port));
    /*bind函数的第二个参数期望得到sockaddr结构体变量地址值，包括地址族、端口号、IP地址等
    struct sockaddr
    {
        sa_family_t sin_family;  //地址族
        char        sa_data[14]; //地址信息
    }

    */
    if(bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof(serv_addr))==-1)
        error_handling("bind() error");

    if(listen(serv_sock,5)==-1)    
        error_handling("listen() error");

        clnt_addr_size=sizeof(clnt_addr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
        if(clnt_sock==-1)
            error_handling("accept() error");
    
    /*
    ssize_t write(int fd,const void *buf,size_t nbytes); 成功时返回写入的字节数，失败时返回-1
    fd      显示数据传输对象的文件描述符
    buf     保存要传输数据的缓冲地址符 
    nbytes  要传输数据的字节数

    */
    write(clnt_sock,message,sizeof(message));
    /*
    int close(int fd)  成功时返回0，失败时返回-1
    fd   需要关闭的文件或套接字的文件描述符
    */

    close(clnt_sock);
    close(serv_sock);
    return 0;

}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}