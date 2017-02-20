/*CharlesBoyer
 The following website was used as reference for this homework. http://www.binarytides.com/server-client-example-c-sockets-linux/
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
	
	if (argc!= 3){
		printf("Please Make sure input was Port, then IP address\n");
		return 0;
	}
	
	int port = atoi(argv[1]);
	char *IP = argv[2];
	printf("Given port : %d\n", port);
	printf("Given IP : %s\n", IP);
	
	
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Failure on Socket");
    }
    printf("Socket: Success\n");
     
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Failure on Connection");
        return 1;
    }
     
    printf("Connection: Success\n");
     
    
    while(1)
    {
		memset(message,'\0',1000);
		memset(server_reply,'\0',2000);
        printf("Enter message : ");
        scanf("%s" , message);
         
        
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            printf("Failure on Send");
            return 1;
        }
         
        
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            printf("Failure on Receipt");
            break;
        }
         
        printf("Server reply :");
        puts(server_reply);
    }
     
    close(sock);
    return 0;
}
