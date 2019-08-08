#include "thread.h"
#include <fcntl.h>

#define     ARGC    10
#define     READ_BUFF   4096

void send_file(int c, char * name)
{
    if ( name == NULL )
    {
        send(c,"err#no name",11,0);
        return;
    }

    int fd = open(name,O_RDONLY);
    if ( fd == -1 )
    {
        send(c,"err",3,0);
        return;
    }

    int size = lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);

    char res_buff[128] = {0};
    sprintf(res_buff,"ok#%d",size);

    send(c,res_buff,strlen(res_buff),0);

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

    int num = 0;
    char sendbuff[1024] = {0};
    while( (num = read(fd,sendbuff,1024)) > 0 )
    {
        send(c,sendbuff,num,0);
    }

    close(fd);

    return;
}

void * work_thread(void * arg)
{
    int c = (int)arg;

    while( 1 )
    {
        char buff[256] = {0};
        int n = recv(c,buff,255,0);//ls, mv a.c b.c , rm a.c ,get a.c put, aa
        if ( n <= 0 )
        {
            printf("one client over\n");
            break;
        }

        int i = 0;
        char* myargv[ARGC] = {0};
        char * ptr = NULL;
        char * s = strtok_r(buff," ",&ptr);
        while( s != NULL )
        {
            myargv[i++] = s;
            s = strtok_r(NULL," ",&ptr);
        }

        char * cmd = myargv[0];//cmd 

        if ( cmd == NULL )
        {
            send(c,"err",3,0);
            continue;
        }

        if ( strcmp(cmd,"get") == 0 )
        {
            //下载
            send_file(c,myargv[1]);
        }
        else if ( strcmp( cmd, "put") == 0 )
        {
            //上传
        }
        else
        {
            int pipefd[2];
            pipe(pipefd);

            pid_t pid = fork();
            if ( pid == -1 )
            {
                send(c,"err",3,0);
                continue;
            }

            if ( pid == 0 )
            {
                dup2(pipefd[1],1);
                dup2(pipefd[1],2);
                
                execvp(cmd,myargv);
                perror("cmd err");
                exit(0);
            }

            close(pipefd[1]);
            wait(NULL);
            char readbuff[READ_BUFF] = {"ok#"};
            read(pipefd[0],readbuff+3,READ_BUFF-4);

            send(c,readbuff,strlen(readbuff),0);
            close(pipefd[0]);
        }
    }

    close(c);
}

int thread_start(int c )
{
    pthread_t id;
    int res = pthread_create(&id,NULL,work_thread,(void*)c);
    if ( res != 0  )
    {
        return -1;
    }

    return 0;
}
