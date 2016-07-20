#include "NetSock.h"

NetSock::NetSock()
{
	m_OnlineCount = 0;


}
NetSock::~NetSock()
{


}

int NetSock::Init(short port)
{
	if(port <= 0 )
	{
		err_quit("Port is not right!", __FUNCTION__, __FILE__, __LINE__);
	}
	m_ListenPort = port;

	m_Sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(m_ListenPort);
	Bind(m_Sockfd, (SA *)&serv, sizeof(serv));
	Listen(m_Sockfd, 1024);

	return m_Sockfd;
}

int NetSock::Open()
{
	time_t t, stamp = 0;
	{
		struct sockaddr_in cli;
		memset(&cli, 0, sizeof(cli));
		socklen_t cliSize = sizeof(cli);
        
		if(m_OnlineCount >= MAX_CONNECTION)
		{
			err_quit("The server is full!", __FUNCTION__, __FILE__, __LINE__);
		}

		int curConnfd = -1;
		curConnfd = Accept(m_Sockfd, (SA *)&cli, &cliSize);
		for(;;)
		{
			m_ConList[m_OnlineCount++] = curConnfd;

			t = time(NULL);
			if(t - stamp <= 5)
				continue;
			stamp = t;

			char buff[1024];
			memset(buff, 0, sizeof(buff));

			char str[100] = "Good Job\n";
			m_Stream.Write(curConnfd, str, strlen(str) + 1);
			int ret = m_Stream.Read(curConnfd, buff, sizeof(buff));
			if(0 == ret)
			{
				err_quit("Client has been closed!", __FUNCTION__, __FILE__, __LINE__);
			}
			cout << curConnfd << ". Client Says:" << buff << endl;
		}
	
	}
}

int NetSock::Close()
{
	close(m_Sockfd);
	return 0;
}

int IOStream::Read(int fd, void const *vptr, size_t len)
{

	int ret = 0;
	ret = Readline(fd, vptr, len);
	return ret;
}

int IOStream::Write(int fd, void const *vptr, size_t len)
{
	int ret = 0;
    ret = Written(fd, vptr, len);
	return ret;
}
