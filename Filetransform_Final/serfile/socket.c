#include "socket.h"

#define     PORT    6000
#define     IPSTR   "127.0.0.1"
#define     LIS_MAX 5

/***************************************************
 *stu 5.9   创建套接字, 
 *
 * *************************************************/
int create_socket()
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

    int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if ( res == -1 )
    {
        return -1;
    }

    listen(sockfd,LIS_MAX);

    return sockfd;
}
