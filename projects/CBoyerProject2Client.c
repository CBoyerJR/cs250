#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFLEN 512

int main(int argc , char *argv[])
{
	
	if (argc!= 3){
		printf("Please Make sure input was IP, then Port\n");
		return 0;
	}
	
	char *IP = argv[1];
	unsigned int port = atoi(argv[2]);
	
	struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
	
	printf("Given IP : %s\n", IP);
	printf("Given port : %d\n", port);
	
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
	{
		printf("Fail on Socket\n");
		exit(1);
	}
	else
		printf("Socket Successful\n");
	
	memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

	if (inet_aton(IP , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
	
	while(1)
	{
		
		printf("Enter Message : ");
		scanf("%s" , message);
		
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            printf("Failed on Message Sending\n");
            exit(1);
        }
        else
			printf("Message Sent");
		
		memset(buf, '\0', BUFLEN);
		memset(message, '\0', BUFLEN);
		
		if(timeout_recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) > 0, 1) 
		{
			if (buf != message)
			{
				printf("Server Reply : ");
				puts(buf);
			}
		}
		else
		printf("Listening for Reply\n"); 
	}
	
	close(s);
	return 0;
}

int timeout_recvfrom (int sock, char *buf, int *length, struct sockaddr_in *connection, int timeoutinseconds)
{
    fd_set socks;
    struct timeval t;
    FD_ZERO(&socks);
    FD_SET(sock, &socks);
    t.tv_sec = timeoutinseconds;
    if (select(sock + 1, &socks, NULL, NULL, &t) &&
        recvfrom(sock, buf, *length, 0, (struct sockaddr *)connection, length)!=-1)
        {
        return 1;
        }
    else
        return 0;
}
