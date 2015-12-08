#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

int main()
{ 
    int client_socket;
    struct sockaddr_in svr_addr;
    char buf[64];
    int ret = 0;
    int flags = 0;
    fd_set rset;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
	    printf("create socket error\n");
	    return -1;
    }

    memset(&svr_addr, 0, sizeof(sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(6693);
    inet_pton(AF_INET, "192.168.1.1", &svr_addr.sin_addr);

    flags = fcntl(client_socket, F_GETFL, 0);
    ret = fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);
    ret = connect(client_socket, (struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        if (errno != EINPROGRESS)
        {
            printf("connect error\n");
            return -1;
        }
    }

    if (ret == 0)
        goto done;

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    FD_ZERO(&rset);
    FD_SET(client_socket, &rset);
    ret = select(client_socket+1, &rset, NULL, NULL, &tv);
    if (ret < 0)
    {
            printf("select failed\n");
            return -1;
    }
    else if (ret == 0)
    {
            printf("connect timeout\n");
            return 0;
    }

done:
    while(fgets(buf, sizeof(buf), stdin) != NULL)
    {
    ret = write(client_socket, buf, strlen(buf));
    if (ret < 0)
    {
        printf("write error\n");
        return -1;
    }
    ret = read(client_socket, buf, 64);
    if (ret < 0)
    {
        printf("read error\n");
        return -1;
    }
    buf[ret] = 0;
    printf("read:%s\n", buf);
    }
    return 0;
}
