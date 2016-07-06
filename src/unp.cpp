#include "unp.h"
/**
 *family   AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY 
 *type     SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW
 *protocol IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP
 */
int Socket(int family, int type, int protocol)
{
	int n = 0;
    if((n = socket(family, type, protocol)) < 0)
	{
		err_quit("sock fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	int n = 0;
    if((n = connect(sockfd, servaddr, addrlen)) < 0)
	{
		err_quit("connect fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
	int n = 0;
    if((n = bind(sockfd, myaddr, addrlen)) < 0)
	{
		err_quit("bind fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Listen(int sockfd, int backlog)
{
	int n = 0;
    if((n = listen(sockfd, backlog)) < 0)
	{
		err_quit("listen fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;

}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int confd = -1;
    if((confd = accept(sockfd, cliaddr, addrlen)) < 0)
	{
		err_quit("accept fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return confd;/*返回监听套接字*/
}

int Close(int sockfd)
{
	int n = 0;
    if((n = close(sockfd)) < 0)
	{
		err_quit("close fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

void err_quit(string msg, string func, string file, long line)
{
	string date;
	cur_time(date);
    cout << date << "FILE[" << file <<"] " << " LINE[" <<line << "] " << "FUNCTION::" << func << " MSG[" << msg << "] " << endl;
	exit(0);
}

int cur_time(string& tStr)
{
	time_t t;
	time (&t);
    string tmp(ctime(&t));
	tStr.assign(tmp.begin(), tmp.end());
	return 0;

}
/*
void str_cli(FILE *fp, int sockfd)
{
	int     maxfdp1, stdineof;
	fd_set  rset;
	char    buff[MAXLINE];
	int     n;

	stdineof = 0;
	FD_ZERO(&rset);

	for( ; ; )
	{
		if(0 == stdineof)
		{
			FD_SET(fileno(fp), &rset);
		}

		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;

		Select(maxfdp1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(sockfd, &rset))
		{
			if( 0 == (n = Read(sockfd, buff, MAXLINE)))
			{
				if( 1 == stdineof)
				{
					return;
				}else
				{
					err_quit("str_cli : server terminated prematurely");
				}

				Write(fileno(fp), buff, n);

				
			}
		}

		if(FD_ISSET(fileno(fp), &rset))
		{
			if(0 == (n = Read(fileno(fp), buff, MAXLINE)))
			{
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			Writen(sockfd, buff, n);
		
		}
	}


}
*/

