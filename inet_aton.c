#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

void error_handling(char *message);

int main(int argc,char *argv[])
{
    char *addr="127.232.124.79";
    struct sockaddr_in addr_inet;


    /*
    int inet_aton(const char*string,struct in_addr *addr); 成功时返回1，失败时返回0
    string 含有需要转化的IP地址信息的字符串地址值
    addr  将保存转换结果的in_addr结构体变量的地址值

    */
    if(!inet_aton(addr,&addr_inet.sin_addr))
        error_handling("Conversion error");
    else
        printf("Network ordered integer addr: %#x \n",addr_inet.sin_addr.s_addr);
    return 0;

}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}