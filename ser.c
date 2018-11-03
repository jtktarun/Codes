#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int sockfd, newsockfd, portno, n;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t clilen;
	char buffer[256];
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	newsockfd = sockfd;
	/*listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	*/
	int len;
	bzero(buffer,256);
	n = recvfrom(newsockfd,buffer,256,MSG_WAITALL,(struct sockaddr *)&cli_addr,&len);
	printf("%s\n",buffer);
	n = sendto(newsockfd,"ack",3,MSG_CONFIRM,(struct sockaddr *)&cli_addr,len);
	//close(newsockfd);
	close(sockfd);

	return 0;
}