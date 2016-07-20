#include "unp.h"
#include "NetSock.h"
#include "Select.h"

static void sig_alrm(int)
{
    cout << "catch the signal!" << endl;


}
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
			close(connfd);
			cout << "Parent conn has been closed" << endl;
			continue;
		}
		char addr[1024];
		memset(addr, 0, sizeof(addr));
		if(false == inet_ntop(AF_INET, (void*)&cliaddr.sin_addr, addr, sizeof(addr)))
		{
			err_quit("Cli addr is error", __FUNCTION__, __FILE__, __LINE__);
		}

		cout << "connection come from " << addr << endl;
		cout << "son pid is " << getpid() << endl;
		(signal(SIGPIPE, sig_alrm) == SIG_ERR);

		Beater(connfd);
		close(connfd);
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
			//	n = Written(connfd, "You must touch me in 5 seconds", 100);
				{
					//err_quit("Client is Closed! ", __FUNCTION__, __FILE__, __LINE__);			
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
void GameSvr()
{
    NetSock svr;
	svr.Init(10010);
	svr.Open();
}
void SelectSvr()
{
	Select sl;
	cout << "Before sleep for 5 secends!" << endl;
    int ret = sl.sleep(5);
	cout << "select has returned, ret is " << ret << endl;
	sl.init();

}
int main(int argc, char*argv[])
{
	//server();
    //GameSvr();
    SelectSvr();
	return 0;
}
