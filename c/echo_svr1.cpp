#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{ 
    int listen_sock, conn_sock,epfd,sockfd;
    struct sockaddr_in svr_addr, client_addr;
    socklen_t addr_len;
    int client_array[64];
    struct epoll_event tmp_ev, event_list[20];
    char buf[64];
    int ret = 0;
    int i,nready;


    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0)
    {
	    printf("create socket error\n");
	    return -1;
    }

    memset(&svr_addr, 0, sizeof(sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_addr.sin_port = htons(6693);

    ret = bind(listen_sock, (struct sockaddr *)&svr_addr, sizeof(svr_addr));
    if (ret < 0)
    {
        printf("bind error\n");
        return -1;
    }

    ret = listen(listen_sock, 5);
    if (ret < 0)
    {
        printf("listen error\n");
        return -1;
    }

    epfd = epoll_create(1);
    if (epfd < 0)
    {
            printf("epoll create failed\n");
            return -1;
    }

    tmp_ev.data.fd = listen_sock;
    tmp_ev.events = EPOLLIN | EPOLLET;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &tmp_ev);
    if (ret < 0)
    {
            printf("epoll ctl failed\n");
            return -1;
    }
    
    for (;;)
    {

        nready = epoll_wait(epfd, event_list, 20, -1);
        if (nready < 0)
        {
                printf("epoll wait failed\n");
                return -1;
        }

        for (i=0; i<nready; ++i)
        {
                if (event_list[i].data.fd == listen_sock)
                {
                        addr_len = sizeof(client_addr);
                        conn_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addr_len);
                        if (conn_sock < 0)
                        {
                                printf("accept error\n");
                                return -1;
                        }
                        printf("new client-%d: port=%u\n", conn_sock, client_addr.sin_port);
                        tmp_ev.data.fd = conn_sock;
                        tmp_ev.events = EPOLLIN | EPOLLET;
                        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock, &tmp_ev);
                        if (ret < 0)
                        {
                                printf("epoll ctl client failed\n");
                                return -1;
                        }
                }
                else
                {
                        sockfd = event_list[i].data.fd;
                        ret = read(sockfd, buf, 63);
                        if (ret < 0)
                        {
                                printf("read error\n");
                                return -1;
                        }
                        else if(ret == 0)
                        {
                                printf("client-%d leave\n", sockfd);
                                ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                                if (ret < 0)
                                {
                                        printf("epoll ctrl del client failed\n");
                                        return -1;
                                }
                                close(sockfd);
                        } 
                        else
                        {
                            buf[ret] = 0;
                             printf("read from client-%d: %s\n", sockfd, buf);
                             ret = write(sockfd, buf, ret);
                             if (ret < 0)
                             {
                                     printf("write error\n");
                                     return -1;
                             }
                             printf("write to client-%d:%s\n",sockfd, buf);
                        }
                }
        }
    }
    return 0;
}
