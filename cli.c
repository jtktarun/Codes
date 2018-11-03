#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	int sockfd, portno, n, len;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bzero((char *)&serv_addr,sizeof(serv_addr));
	portno = atoi(argv[2]);
	server = gethostbyname(argv[1]);
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);
	//connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	scanf("%s",buffer);
	n = sendto(sockfd,buffer,sizeof(buffer),MSG_CONFIRM,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	n = recvfrom(sockfd,buffer,256,MSG_WAITALL,(struct sockaddr *)&serv_addr,&len);
	printf("%s\n",buffer);
	close(sockfd);
	return 0;
}