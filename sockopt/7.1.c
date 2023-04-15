#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);

    int tcp_send_buf_size;
    int tcp_recv_buf_size;
    int udp_send_buf_size;
    int udp_recv_buf_size;

    socklen_t optlen;

    optlen = sizeof(tcp_send_buf_size);
    getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, &tcp_send_buf_size, &optlen);
    optlen = sizeof(tcp_recv_buf_size);
    getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, &tcp_recv_buf_size, &optlen);
    optlen = sizeof(udp_send_buf_size);
    getsockopt(udp_sock, SOL_SOCKET, SO_SNDBUF, &udp_send_buf_size, &optlen);
    optlen = sizeof(udp_recv_buf_size);
    getsockopt(udp_sock, SOL_SOCKET, SO_RCVBUF, &udp_recv_buf_size, &optlen);

    printf("TCP send buffer size: %d\n", tcp_send_buf_size);
    printf("TCP receive buffer size: %d\n", tcp_recv_buf_size);
    printf("UDP send buffer size: %d\n", udp_send_buf_size);
    printf("UDP receive buffer size: %d\n", udp_recv_buf_size);

    return 0;
}