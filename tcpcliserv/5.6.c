    #include	"unp.h"

    void p_sigpipe(int signo)
    {
        printf("SIGPIPE caught %d", signo);
    }

    int
    main(int argc, char **argv)
    {
        int					sockfd;
        struct sockaddr_in	servaddr;

        if (argc != 2)
            err_quit("usage: tcpcli <IPaddress>");

        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(13);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        signal(SIGPIPE, p_sigpipe);

        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

        sleep(2);

        write(sockfd, "hello world", 11);

        sleep(2);

        write(sockfd, "hello world", 11);

        exit(0);
    }