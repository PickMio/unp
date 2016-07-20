const int EOF = 0;  // 1. 接收到FIN的TCP连接会返回0
const int ERROR = -1;  // 1. TCP连接会返回错误

const int MAXLINE = 4096;  // 1. TCP发送的最大数据量
const int OPEN_MAX = 1000; // 2. POLL最大打开的连接数 
const int SERV_PORT = 10010; // 3. 服务器的端口号
