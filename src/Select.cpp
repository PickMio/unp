#include "Select.h"
//int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);
//返回值:有就绪描述符则为其数目,若超时则为0, 出错为-1.
//sturct timeval{
//	long tv_sec;
//	long tv_usec;
//}
//forever NULL
//wait some time, time
//no wait, 0
//可能返回EINTR
//
//void FD_ZERO(fd_set *fdset);
//void FD_SET(int fd, fd_set *fdset);
//void FD_CLR(int fd, fd_set *fdset);
//void FD_ISSET(int fd, fd_set *fdset);
Select::Select()
{


}
Select::~Select()
{


}

int Select::init()
{
	fd_set set;
	FD_ZERO(&set);
	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serv;
	serv.sin_family = AF_INET; 
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(10011);
	socklen_t len = sizeof(serv);
	Bind(sockfd, (SA *)&serv, len);
	Listen(sockfd, 5);
	{
		sockaddr_in cliaddr;
		socklen_t clilen;
		clilen = sizeof(cliaddr);
		int connfd = -1;
		connfd = Accept(sockfd, (SA *)&cliaddr, &clilen);
		for(;;)
		{
			fd_set readset;
			FD_ZERO(&readset);
			FD_SET(connfd, &readset);
			FD_SET(3, &readset);
			int ret = -1;
			select(max(3, connfd)+1, &readset, NULL, NULL, NULL);
			char buf[1024] = {0};
			if(FD_ISSET(connfd, &readset))
			{
				cout << "Get Client msg" << endl;
				ret = Readline(connfd, buf, 1024);
				if(0 == ret)
				{
					cout << "client closed" << endl;
					close(connfd);
					err_quit("client has been closed!", __FUNCTION__, __FILE__, __LINE__);
				}else if( ret < 0 )
				{
					cout << "an error occured! error id:" << errno << endl;
					err_quit("an erro occured!", __FUNCTION__, __FILE__, __LINE__);
				}else
				{
					cout << buf << endl;
					fgets(buf,50, stdin);
					Written(connfd, buf, sizeof(buf));
				}


			}
			if(FD_ISSET(0, &readset))
			{
				cout << "Get Keyboard msg" << endl;
			}
		}


	}

}

int Select::open()
{


}

int Select::sleep(int sec)
{
	struct timeval tm;
	tm.tv_sec = sec;
	tm.tv_usec = 0;
	int ret = 0;
	ret = select(0 ,NULL, NULL, NULL, &tm);	
	return ret;

}
