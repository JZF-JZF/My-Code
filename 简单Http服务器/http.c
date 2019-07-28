#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define IPADDR "127.0.0.1" 	// 	服务器的IP地址
#define PORT 80 			// 	http默认端口为80 
#define SIZE 100 			//	接收缓冲区的大小
//创建套接字
int create_socket(); 

int main()
{
	//获取创建的套接字描述符 
	int sockfd = create_socket();
	assert(sockfd != -1);
	while (1)
	{
		struct sockaddr_in caddr;
		int len = sizeof(caddr);
		//接收新连接
		int c = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t *)&len);
		//若有新连接则继续循环监听
		if (c <= 0) 
		{
			continue;
		}
		char buff[SIZE] = { 0 };
		int n = recv(c, buff, SIZE - 1, 0);
		printf("recv(%d):\%s\n", n, buff);

		//HTTP请求报文的构造
		char* s = strtok(buff, " ");
		if (s == NULL)
		{
			close(c);
			continue;
		}
		//拿到method方法
		printf("method:%s\n", s);
		s = strtok(NULL, " ");

		//构造跳转目标URL
		char path[128] = { "/home/JZF/Desktop/mycode/http" };
		if (strcmp(s, "/") == 0)
		{
			/如果没有目标URL 则返回默认的页面
			strcat(path, "/index.html"); 
		}
		else
		{
			//如果有目标URL 则将请求的目标页面返回 
			strcat(path, s); 
		}
		//打开目标资源文件
		int fd = open(path, O_RDONLY);
		//如果打开错误 则报出404错误的响应报文
		if (fd == -1)
		{
			char err_buff[256] = { "HTTP/1.1 404 Not Found\r\n" };
			strcat(err_buff, "Server: myhttp\r\n");
			strcat(err_buff, "Content-Length: 3\r\n");
			strcat(err_buff, "\r\n");
			strcat(err_buff, "404\r\n");
			
			//将错误报文返回客户端
			send(c, err_buff, strlen(err_buff), 0);
			close(c);
			continue;
		}
		//请求成功时报出200
		//将文件指针定位到文件末尾获取文件大小，返回的SEEK_CUR指针，即文件的大小
		int size = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET); //得到文件大小后，需要将文件指针置回文件起始位置
		
		char suc_buff[128] = { "HTTP/1.1 200 OK\r\n" };
		strcat(suc_buff, "Server: myhttp\r\n");
		sprintf(suc_buff + strlen(suc_buff), "Content-Length: %d\r\n", size);
		strcat(suc_buff, "\r\n");
		
		// 将成功的200响应报文发送给客户端
		send(c, suc_buff, strlen(suc_buff), 0);
	
		//在服务器端进行打印响应报文
		printf("\nsend:\n%s\n", suc_buff);

		char send_buff[1024] = { 0 };
		//将客户端请求的资源文件发送给浏览器，若是网页则由浏览器进行执行
		int num = 0;
		while ((num = read(fd, send_buff, 1024)) > 0)
		{
			send(c, send_buff, num, 0);
		}
		close(fd); 		// 关闭资源文件描述符fd
		close(c);	 	// 关闭连接套接字c
	}

}
//创建套接字
int create_socket()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		return -1;
	}
	//设置地址信息
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr(IPADDR);
	//命名套接字 将地址信息绑定到创建的sockfd上
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	if (res == -1)
	{
		return -1;
	}
	//创建监听队列
	listen(sockfd, 20);
	//返回创建好的socket
	return sockfd;
}
