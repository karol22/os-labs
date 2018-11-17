/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    char operation;
    int values[10];
    int size;
} query;

int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int answer, i;
	query q;

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    answer=connect(sockfd, (struct sockaddr *)&address, len);

    if(answer == -1) {
        perror("Error: client1");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    
    if (argc < 2) {
        printf("No arguments passed");
        return -1;
    }
    
    q.operation = *argv[1];
    for (i = 2; i < argc; i++)
    {
        q.values[i-2] = atoi(argv[i]);
        printf("client send: %d \n", q.values[i-2]);
    }
    q.size = i - 2;
    int ans;
    write(sockfd, &q, sizeof(q));
    read(sockfd, &ans, sizeof(ans));
    printf("client recieved: %i \n", ans);
    close(sockfd);
    exit(0);
}
