#define _LARGEFILE64_SOURCE
#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

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
void send_file(int c, char * name);

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
        else if ( strcmp(myargv[0],"get") == 0 )	//下载文件
        {
            if ( myargv[1] == NULL )
            {
                continue;
            }
            send(sockfd,sendbuff,strlen(sendbuff),0);//发送get a.c到服务器
            recv_file(sockfd,myargv[1]);//接收文件
        }
        else if(strcmp(myargv[0],"rm") == 0)
        {
            if(myargv[1] == NULL)
            {
                continue;
            }
            send(sockfd,sendbuff,strlen(sendbuff),0);
        }
        else if ( strcmp(myargv[0],"put") == 0 )
        {
			if ( myargv[1] == NULL )
		    {
		        continue;
		    }
		    send(sockfd,sendbuff,strlen(sendbuff),0);//发送put a.c到服务器
		    send_file(sockfd,myargv[1]);	//响服务器发送文件
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

void recv_file(int sockfd, char* name)	//下载文件
{


    int d_fd = open(name,O_WRONLY | O_LARGEFILE);
    if(d_fd != -1)	//说明本地有此文件
    {
        char d_buff[128] = {0};
        if(recv(sockfd,d_buff,127,0) <= 0)      //接收服务器端文件大小
        {
            return;
        }
        if(strncmp(d_buff,"ok#",3) != 0)
        {
            printf("Error!!!\n");
            return;
        }
        long long d_size = 0;

        
        sscanf(d_buff+3,"%lld",&d_size); //得到服务器文件大小
        if(d_size == 0)	
        {
            send(sockfd,"err_size",8,0);
            return;
        }
        long long fd_size = lseek64(d_fd,0,SEEK_END);	//得到本地文件大小

        if(d_size == fd_size)
        {
            printf("本地已存在该文件！！！\n");
        }
        if(d_size != fd_size)
        {
            printf("local file size:%lld\n",fd_size);	//输出本地文件大小
            char d_res_buff[128] = {0};
            sprintf(d_res_buff,"ok#size#%lld",fd_size);//不存在文件发送ok# 存在发送ok#size#

            send(sockfd,d_res_buff,strlen(d_res_buff),0);	//把本地文件大小发送到服务器
            char d_recvbuff[1024] = {0};

            long long d_num = 0;
            long long d_curr_size = fd_size;	//从末尾接收服务器发送的文件
            while((d_num = recv(sockfd,d_recvbuff,1024,0)) > 0)
            {
                write(d_fd,d_recvbuff,d_num);	//从d_revbuff处接收文件
                d_curr_size += d_num;	//更新末尾位置
                float d_f = d_curr_size * 100.0 / d_size;
                printf("继续下载下载进度*:%.2f%%\r",d_f);
                fflush(stdout);
                if(d_curr_size >= d_size)	
                {
                    break;
                }
            }
            printf("文件下载完成\n");
        }
        send(sockfd,"finish！！！",5,0);
        close(d_fd);
        return;
    }

    char buff[128] = {0};
    if ( recv(sockfd,buff,127,0) <= 0 )
    {
        return;
    }
    if ( strncmp(buff,"ok#",3) != 0 )//ok#345
    {
        printf("No This File!!!\n");
        return;
    }

    long long size = 0;
    printf("file size:%s\n",buff+3);
    sscanf(buff+3,"%lld",&size);

    if( size == 0 )
    {
        printf("no this file!!!\n");
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

    long  num = 0;
    long curr_size = 0;

    while( ( num = recv(sockfd,recvbuff,1024,0)) > 0 )
    {
        write(fd,recvbuff,num);
        curr_size += num;

        float f = curr_size * 100.0 / size ;
        printf("*下载进度*:%.2f%%\r",f);
        fflush(stdout);

        if ( curr_size >= size )
        {
            break;
        }
    }

    printf("\n文件下载完成!\n");
    close(fd);
    return;
}


void send_file(int c, char * name)	//上传文件
{
    if ( name == NULL )
    {
        send(c,"err#no name",11,0);
        return;
    }
    //=============================================
    char m_buff[128] = {0};
    sprintf(m_buff,"./my.sh %s",name);	
    system(m_buff);	//计算文件MD5值并写入md5.c文件中
    //=============================================
    int md_fd = open("md5.c",O_RDONLY | O_CREAT);
    if(md_fd == -1)
    {
        printf("md_fd err\n");
        return;
    }
    char md_res_buff[128] = {0};
    read(md_fd,md_res_buff,128);	//读取文件内容

    char * s = strtok(md_res_buff,"\n");    //分割得到文件MD5值
    char buff[128] = {0};

    close(md_fd);
    system("rm md5.c"); //得到文件MD5值后就删除MD5.c文件

    sprintf(buff,"ok#%s",s);
    send(c,buff,strlen(buff),0);	//把ok#MD5值发送给服务器
    char p[128] = {0};
    if(recv(c,p,127,0) <= 0)
    {
        return;
    }
    if(strncmp(p,"#samefile#",10) == 0)	//如果服务器回复samefile，则说明服务器有该文件
    {
        printf("文件已存在！\n");
        printf("秒传成功！！！\n");
        return;
    }

    int fd = open(name,O_RDONLY);
    if ( fd == -1 )
    {
        send(c,"err",3,0);
        return;
    }

    long long size = lseek(fd,0,SEEK_END);	//得到文件大小
    lseek(fd,0,SEEK_SET);
    if(size==0)
    {
        send(c,"err",3,0);
        return;
    }

    char res_buff[128] = {0};
    sprintf(res_buff,"ok#%lld",size);

    send(c,res_buff,strlen(res_buff),0);    //发送ok#文件大小

    char cli_status[64] = {0};
    if ( recv(c,cli_status,63,0) <= 0 )
    {
        close(fd);
        return;
    }

    if ( strncmp(cli_status,"ok",2) != 0 )
    {
        close(fd);
        return;
    }
    /*
    long long num = 0;
    char sendbuff[1024] = {0};
    while( (num = read(fd,sendbuff,1024)) > 0 )
    {
        send(c,sendbuff,num,0);
    }
    */
    long long num = 0;
    long long curr_size = 0;
    char sendbuff[1024] = {0};
    printf("文件大小:%d\n",size);
    while((num = read(fd,sendbuff,1024)) > 0)
    {   
        send(c,sendbuff,num,0);
        curr_size += num;
        float f = curr_size * 100.0 /size;
        printf("\033[?25l*上传进度*:%.2f%%\r",f);
        fflush(stdout);
    }
    printf("\n文件上传完成!\n");

    close(fd);

    return;
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
