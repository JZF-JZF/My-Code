#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#define     PORT    6000
#define     IPSTR   "127.0.0.1"

int connect_to_ser();
void recv_file(int sockfd, char* name);
int main()
{
    int sockfd = connect_to_ser();
    if ( sockfd == -1 )
    {
        printf("connect to ser failed!\n");
        return 0;
    }

    while( 1 )
    {
        char buff[128] = {0};

        printf("Connect>>");
        fflush(stdout);

        fgets(buff,128,stdin);//  ls, rm a.c , get a.c ,sdfg , exit
        buff[strlen(buff)-1] = 0;

        if ( buff[0] == 0 )
        {
            continue;
        }

        char sendbuff[128] = {0};
        strcpy(sendbuff,buff);

        int i = 0;
        char * myargv[10] = {0};
        char * s = strtok(buff," ");
        while( s != NULL )
        {
            myargv[i++] = s;
            s = strtok(NULL," ");
        }

        if ( myargv[0] == NULL )
        {
            continue;
        }

        if ( strcmp(myargv[0],"exit") == 0 )
        {
            break;
        }
        else if ( strcmp(myargv[0],"get") == 0 )
        {
            if ( myargv[1] == NULL )
            {
                continue;
            }
            send(sockfd,sendbuff,strlen(sendbuff),0);//get a.c
            recv_file(sockfd,myargv[1]);
        }
        else if ( strcmp(myargv[0],"put") == 0 )
        {

        }
        else
        {
            send(sockfd,sendbuff,strlen(sendbuff),0);

            char readbuff[4096] = {0};
            recv(sockfd, readbuff,4095,0);
            if ( strncmp(readbuff,"ok#",3) != 0 )
            {
                printf("err");
                continue;
            }

            printf("%s\n",readbuff+3);

        }
    }

    close(sockfd);
}

void recv_file(int sockfd, char* name)
{
    char buff[128] = {0};
    if ( recv(sockfd,buff,127,0) <= 0 )
    {
        return;
    }

    if ( strncmp(buff,"ok#",3) != 0 )//ok#345
    {
        printf("Error:%s\n",buff+3);
        return;
    }

    int size = 0;
    printf("file size:%s\n",buff+3);
    sscanf(buff+3,"%d",&size);

    if( size == 0 )
    {
        send(sockfd,"err",3,0);
        return;
    }

    int fd = open(name,O_WRONLY|O_CREAT,0600);
    if ( fd == -1 )
    {
        send(sockfd,"err",3,0);
        return;
    }

    send(sockfd,"ok",2,0);

    char recvbuff[1024] = {0};

    int num = 0;
    int curr_size = 0;

    while( ( num = recv(sockfd,recvbuff,1024,0)) > 0 )
    {
        write(fd,recvbuff,num);
        curr_size += num;

        float f = curr_size * 100.0 / size ;
        printf("下载:%.2f%%\r",f);
        fflush(stdout);

        if ( curr_size >= size )
        {
            break;
        }
    }

    printf("\n文件下载完成!\n");
    close(fd);

}

int connect_to_ser()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if ( sockfd == -1 )
    {
        return -1;
    }

    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = inet_addr(IPSTR);

    int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if ( res == -1 )
    {
        return -1;
    }

    return sockfd;
}
