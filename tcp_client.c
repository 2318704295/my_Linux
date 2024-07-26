#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len=0;

    int idx=0,read_len=0;

    if(argc!=3)
    {
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1); 
    }

    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;  //地址族 IPV4
    /*
    in_addr_t inet_addr(const char *string); 成功时返回32位大端序整数型值，失败时返回INADDR_NONE
    把字符串形式的IP地址转换成32位整数型数据,在转换类型的同时进行网络字节序转换

    实际编程中若要调用inet_addr函数，需将转换后的IP地址信息代入sockaddr_in结构体中声明的in_addr结构体变量
    而inet_aron函数则不需要此过程。原因在于若传递in_addr结构体变量地址值，函数会自动把结果填入该结构体变量。
    */
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);  //32位ip地址信息，以网络字节序保存
    serv_addr.sin_port=htons(atoi(argv[2])); //16位端口号 以网络字节序保存

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    
    // str_len=read(sock,message,sizeof(message)-1);
    // if(str_len==-1)
    //     error_handling("read() error!");
    while(read_len=read(sock,&message[idx++],1))
    {
        if(read_len==-1)
            error_handling("read() error!");
        str_len+=read_len;
    }

    printf("Message from server : %s \n", message);
    printf("Function read call count:%d \n",str_len);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}