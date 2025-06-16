#include "tcp.h"

int Tcp_ServerInit(int Port)
{
    //创建TCP网络套接字
    int ser_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(ser_fd < 0){
        perror("TCP_socket_open");//出错提示
        return -1;
    }
    int option = 1;
    setsockopt(ser_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//IPV4协议族
    addr.sin_port = htons(Port);//端口(网络字节序)
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");//IP(网络字节序)

    int ret = bind(ser_fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0){
        perror("TCP_socket_bind");
        return -1;
    }

    listen(ser_fd, 5);
    return ser_fd;
}

int Tcp_ConnectToServer(char *IP, int Port)
{
    //创建TCP网络套接字
    int cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(cli_fd < 0){
        perror("TCP_socket_open");//出错提示
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//IPV4协议族
    addr.sin_port = htons(Port);//端口(网络字节序)
    addr.sin_addr.s_addr = inet_addr(IP);//IP(网络字节序)

    int ret = connect(cli_fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret < 0){
        perror("TCP_socket_connect");
        return -1;
    }

    return cli_fd;
}

int Tcp_WaitNewConnection(int S_fd)
{
    int cli_fd = accept(S_fd, NULL, NULL);
    if(cli_fd < 0){
        perror("TCP_socket_accept");
        return -1;
    }
    return cli_fd;
}

#define SEND_TIMEOUT_SECONDS 5  

int Tcp_Send(int fd, void *Buf, int Count) {
    fd_set write_fds;
    struct timeval timeout;
    FD_ZERO(&write_fds);
    FD_SET(fd, &write_fds);
    // 设置超时时间
    timeout.tv_sec = SEND_TIMEOUT_SECONDS;
    timeout.tv_usec = 0;

    int select_ret = select(fd + 1, NULL, &write_fds, NULL, &timeout);
    if (select_ret == -1) {
        perror("select in Tcp_Send");
        return -1;
    } else if (select_ret == 0) {
        // 超时，没有成功写入数据的机会，返回错误码（这里假设返回 -2 表示发送超时，可自定义合适的错误码）
        fprintf(stderr, "Tcp_Send timeout, unable to send data within the specified time.\n");
        return -2;
    }

    // 有机会写入数据，执行write操作
    int ret = write(fd, Buf, Count);
    if (ret < 0) {
        perror("Tcp_Send");
        return -1;
    }
    return ret;
}
int Tcp_Recv(int fd, void *Buf, int Count)
{
    fd_set read_fds;
    struct timeval timeout;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);
    // 设置超时时间为100毫秒（0.1秒）
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;
    int ret = select(fd + 1, &read_fds, NULL, NULL, &timeout);
    if (ret == -1) {
        perror("select");
        return -1;
    } else if (ret == 0) {
        // 超时，没有数据可读
        //printf("Tcp_Recv timeout, no data available.\n");
        return 0;
    }
    // 有数据可读，进行读取操作
    return read(fd, Buf, Count);
}


int Tcp_Close(int fd)
{
    if(close(fd) < 0)
    {
        perror("TCP_close_cli");
        return -1;
    }
    return 0;
}
