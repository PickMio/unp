#pragma once
#include "unp.h"

const int MAX_CONNECTION = 100;

class Connector
{



};

class IOStream
{
	public:
		int	Read(int fd, void const* vptr, size_t len);
		int	Write(int fd, void const* vptr, size_t len);

};
class NetSock
{
	public:
		NetSock();
		~NetSock();

		/*addr 监听地址
		 * port 监听端口
		 */
		int Init(short port);
		int Open();
		int Close();

	private:
		int m_Sockfd;
		int m_ConList[MAX_CONNECTION];
		int m_OnlineCount; 

		IOStream m_Stream;

		string m_ListenAddr;
		short m_ListenPort;

};

