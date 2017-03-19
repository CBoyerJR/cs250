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
		printf("Please Make sure input was IP, then Port\n");
		return 0;
	}
	
	char *IP = argv[1];
	int port = atoi(argv[2]);
	
	printf("Given IP : %s\n", IP);
	printf("Given port : %d\n", port);
	
	
    int sock;
    struct sockaddr_in server;
    char filename[1000] , server_reply[2000];
     
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
     
		memset(filename,'\0',1000);
		memset(server_reply,'\0',2000);
        printf("Name of File?: ");
        scanf("%s" , filename);
        if( send(sock , filename , strlen(filename) , 0) < 0)
        {
            printf("Failure on Send");
            return 1;
        }
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            printf("Failure on Receipt");
            return 1;
        }
        char fail[]="File not Found";
        if(strcmp(server_reply, fail)==1){
			printf("File does not exist");
			return 1;
		}
        FILE *f = fopen(filename, "w");
        if (f == NULL)
		{
			printf("Error opening file!\n");
			exit(1);
		}
        fprintf(f, "%s",server_reply);
        fclose(f);
        printf("The file has been made in this directory.\n");
		
    close(sock);
    return 0;
}

