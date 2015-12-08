#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main()
{ 
    int listen_sock, conn_sock,sockfd;
    struct sockaddr_in svr_addr, client_addr;
    socklen_t addr_len;
    int client_array[64];
    fd_set rset, allset;
    char buf[64];
    int ret = 0;
    int maxi,maxfd,i,nready;


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

    maxfd = listen_sock;
    maxi = -1;
    for (i =0; i< 64; ++i)
            client_array[i] = -1;

    FD_ZERO(&allset);
    FD_SET(listen_sock, &allset);

    for (;;)
    {

        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0)
        {
            printf("select error\n");
            return -1;
        }
        if (FD_ISSET(listen_sock, &rset))
        {
            addr_len = sizeof(client_addr);
            conn_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addr_len);
            if (conn_sock < 0)
            {
                printf("accept error\n");
                return -1;
            }
            for (i=0; i < 64; ++i)
            {
                    if (client_array[i] < 0)
                    {
                        client_array[i] = conn_sock;
                        break;
                    }
            }
            if (i == 64)
            {
                    printf("too many client\n");
                    return -1;
            }

            printf("new client-%d: port=%u\n", i, client_addr.sin_port);
            FD_SET(conn_sock, &allset);
            if(conn_sock > maxfd)
                    maxfd = conn_sock;
            if (i > maxi)
                    maxi = i;

            if (--nready <= 0)
                    continue;
        }

        for (i=0; i <= maxi; i++)
        {
                if ((sockfd = client_array[i]) < 0)
                        continue;
                if (FD_ISSET(sockfd, &rset))
                { 
                        ret = read(sockfd, buf, 63);
                        if (ret < 0)
                        {
                                printf("read error\n");
                                return -1;
                        }
                        else if(ret == 0)
                        {
                                printf("client-%d leave\n", i);
                                close(sockfd);
                                FD_CLR(sockfd, &allset);
                                client_array[i] = -1;
                        } 
                        else
                        {
                        buf[ret] = 0;
                        printf("read from client-%d: %s\n", i, buf);
                        ret = write(sockfd, buf, ret);
                        if (ret < 0)
                        {
                                printf("write error\n");
                                return -1;
                        }
                            printf("write to client-%d:%s\n",i, buf);
                        }
                        if (--nready <= 0)
                                break;
                }
        }
    }
    return 0;
}
