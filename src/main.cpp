#include "unp.h"

int server()
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[100];
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(10010);

	Bind(listenfd, (SA *)& servaddr, sizeof(servaddr));

	Listen(listenfd, 5);

	for (;;)
	{
		len = sizeof(cliaddr);
		pid_t pa, son;
		pa = getpid();
		connfd = Accept(listenfd, (SA*)&cliaddr, &len);
		cout << "parrent pid is " << getpid() << endl;
		son = fork(); //子进程中返回0, 父进程中返回子进程ID, 故只能在父进程中使用
		if(pa == getpid())
		{
			Close(connfd);
			cout << "Parent conn has been closed" << endl;
			continue;
		}
		cout << "son pid is " << getpid() << endl;
		Beater(connfd);
		Close(connfd);
		exit(0);

	}



}

void Beater(int connfd)
{
	time_t tmNow = 0;
	static time_t tmStamp = 0;

	int c = 0;
	int n = 0;
	for(;;)
	{
		tmNow = time(NULL);
		if(tmNow - tmStamp > 5)
		{
	    	++c;		
			try
			{
				if((n = write(connfd, "This is a beater msg.\n", sizeof("This is a beater msg.\n"))) < 0)
				{
					err_quit("Client is Closed! ", __FUNCTION__, __FILE__, __LINE__);			
				}
				cout << c << ". send echo success size[" << n << "]" << endl;
				tmStamp = time(NULL);
			}
			catch(exception *e)
			{
                   cout << "get an error.  n = " << n << endl;			
			
			}
		}
	}

	return;
}

int main(int argc, char*argv[])
{
	server();
	return 0;
}
