#include <poll.h>
#include "Define.h"
#include "unp.h"
/*
 *int poll(struct pollfd, *fdarray, unsigned long nfds, int timeout);
 *返回:若有就绪描述符, 则为其数目, 若超时, 则为0, 出错为-1
 *struct pollfd{
 *		int 	fd;      //descriptor to check
 *		short   events;  //events of interest on fd
 *		short   revents; //events that occurred on fd
 *	}
 *	
 *timeout值:
 *    INFTIM      永远等待//定义在sys/stropts.h
 *    0			  立即返回,不阻塞进程
 *    >0  		  等待指定的毫秒数
 *
 *	              events    revents
 *	POLLIN     |   yes    |   yes        普通或优先级带数据可读
 *	POLLRDNORM |   yes	  |   yes		 普通数据可读
 *	POLLRDBAND |   yes	  |   yes		 优先级带数据可读
 *	POLLPRI	   |   yes	  |   yes		 高优先级带数据可读
 *	--------------------------------
 *	POLLOUT    |   yes    |   yes		 普通数据可写
 *	POLLWRNORM |   yes    |   yes		 普通数据可写
 *	POLLWRBAND |   yes    |   yes		 带优先级数据可写
 *	--------------------------------
 *	POLLERR    |          |   yes		 发生错误
 *	POLLHUP    |  		  |   yes		 错误挂起
 *	POLLNVAL   |		  |   yes		 描述符不是一个打开的文件
 * */

class Poll
{
public:
	Poll();
	~Poll();

    int Init();
	int open();


};
