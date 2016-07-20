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
		err_quit("sock fail ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	int n = 0;
    if((n = connect(sockfd, servaddr, addrlen)) < 0)
	{
		err_quit("connect fail ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
	int n = 0;
    if((n = bind(sockfd, myaddr, addrlen)) < 0)
	{
		err_quit("bind fail ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}

int Listen(int sockfd, int backlog)
{
	int n = 0;
    if((n = listen(sockfd, backlog)) < 0)
	{
		err_quit("listen fail ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;

}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int confd = -1;
    if((confd = accept(sockfd, cliaddr, addrlen)) < 0)
	{
		err_quit("accept fail ", __FUNCTION__, __FILE__, __LINE__);
	}

	return confd;/*返回监听套接字*/
}
/*
int Close(int sockfd)
{
	int n = 0;
    if((n = close(sockfd)) < 0)
	{
		err_quit("close fail, ", __FUNCTION__, __FILE__, __LINE__);
	}

	return n;
}
*/
void err_quit(string msg, string func, string file, long line)
{
	string date;
	cur_time(date);
    cout << date << "FILE[" << file <<"] " << " LINE[" <<line << "] " << "FUNCTION::" << func << " MSG[" << msg << "] " << "ERRNO[" << errno <<"]" <<" HINT["<< strerror(errno)<<"]"<< endl;
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

int Readline(int fd, void const *vptr, size_t maxlen)
{
	int n = 0;
    if(fd < 0)
	{
		err_quit("Readn fd is less than 0.", __FUNCTION__, __FILE__, __LINE__);
	}

    char c, *ptr;
	size_t rc = 0;
	ptr = (char*)vptr;	
	if(NULL == vptr)
	{
		err_quit("vptr is NULL!", __FUNCTION__, __FILE__, __LINE__);
	}

	for(n = 1; n < maxlen; ++n)
	{
		if( 1 == (rc = read(fd, &c, 1)))
		{
			*ptr++ = c;
			if('\n' == c)
			{
				break;
			}
		}
		else if( 0 == rc)
		{
			*ptr = '\0';
			return (n - 1); //EOF
		}
		else
		{
			if(EINTR == errno)
			{
				--n;
				continue;
			}
			cout << "Readn an error occoured! id is " << errno << endl;
			return -1;
		}
	
	}

	*ptr = 0;
	return (n);
}

int Written(int fd, void const *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	char *ptr;

	ptr = (char*)vptr;
	nleft = n;
	for(nleft = n; nleft > 0;)
	{
		if( (nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if(nwritten < 0 && EINTR == errno)
			{
				nwritten = 0;
			}
			else
			{
				cout << "Written an error occoured! id is " << errno << endl;
				return (-1); //error
			}
		}

		nleft -= nwritten;
		ptr += nwritten;
	
	}

	return (n);



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


