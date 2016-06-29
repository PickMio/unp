#include "unp.h"
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

/**
 *family   AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY 
 *type     SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW
 *protocol IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP
 */
int Socket(int family, int type, int protocol)
{



	return 0;
}

int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{

	return 0;
}

int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{

	return 0;
}

int Listen(int sockfd, int backlog)
{

	return 0;
}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{

	return 0;
}

int Close(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen)
{

	return 0;
}

void err_quit(string msg, string func, long line)
{
	string date;
	cur_time(date);
    cout << date << "FUNCTION::" <<func << " LINE[" <<line << "] "<< msg << endl;
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
