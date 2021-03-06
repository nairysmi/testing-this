#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "readwritehelper.h"

takeclient(struct sockaddr_in, int);

int main() {
  int SDfromClient; int checknum=0;
  
  int DefaultPort=8080;
  umask(0000);
  struct sockaddr_in destination;
  memset(&destination, 0, sizeof(destination));
  destination.sin_family=AF_INET;
  destination.sin_port=htons(DefaultPort);
  destination.sin_addr.s_addr=htonl(INADDR_ANY);
  //struct sockaddr clientinfo; 
  //memset(&clientinfo, 0, sizeof(clientinfo));
  printf("before anything\n");
  
  SDfromClient=socket(AF_INET,SOCK_STREAM,0);
  if (SDfromClient<0)
    printf("socket failed\n");
  else
    printf("socket worked socketnum:%d \n", SDfromClient);

  if ( (checknum = bind(SDfromClient, (struct sockaddr *) &destination, sizeof(destination))) < 0) {
    printf("bind failed\n");
    return 0;}
  else {
    printf("Successful bind\n"); }

  if ( (checknum=listen(SDfromClient, 2)) < 0 ) {
    printf("listen failed\n");
    return 0; }
  else {
    printf("Listening on INADDR_ANY\n");}

  /////////////////////////////////////////////////  

  while(1)
    takeclient(destination, SDfromClient);
  shutdown(SDfromClient, SHUT_RDWR);
 return 1;
}

takeclient(struct sockaddr_in destination, int SDfromClient)
{
  int newSD;
  int f;
  char messageFromClient[255]; char messageToClient[255];//aka pid #
  if ( (newSD=accept(SDfromClient, NULL, NULL)) < 0  )
    {
      printf ("accept failed\n");
      return 0;
    } 
  else {
    printf("Accepting connections...\n"); 
    f=fork();
    if(f==0)//child
      {
	strcpy(&messageFromClient,(char *)readhelp(newSD,&messageFromClient,255));
	printf("Message from client: %s\n", messageFromClient);
	strcpy(&messageToClient, &messageFromClient);
	printf("messageToClient is: %s and length %d \n", messageToClient, strlen(messageToClient)+1);
	
	writehelp(newSD, messageToClient, strlen(messageToClient)+1);
	close(newSD);	
      }
    close(newSD);//because parent has a "copy" of the newSD
  }
    
}
  
  
