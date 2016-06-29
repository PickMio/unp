#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
/**
 *    family   AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY 
 *    type     SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW
 *    protocol IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP
 *    
 *    */
int Socket(int family, int type, int protocol);
int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
int Close(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
void err_quit(string msg, string func, long line);
int cur_time(string& tStr);







