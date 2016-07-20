#include "Poll.h"

Poll::Poll()
{

}

Poll::~Poll()
{


}

int Poll::Init()
{
	int i, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	char buf[4096];
	socklen_t clilen, servlen;
	struct sockaddr_in cliaddr, servaddr;
	struct pollfd client[OPEN_MAX];
	servlen = sizeof(servaddr);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *)& servaddr, servlen);
	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;
	for(i = 0; i < OPEN_MAX; ++i)
	{
		client[i].fd = -1;
	}
	maxi = 0;


	return 0;
	

}

int Poll::open()
{

	return 0;
}
