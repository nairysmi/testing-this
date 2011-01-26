/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */

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
#include "portNUMS_defined.h"

takeclient(struct sockaddr_in, int, struct device*);


int main(int argc, char *argv[])
{
  int SDfromClient; int checknum=0;
  int DefaultPort=8080;
  int port;
  
    // int test=light;
  //if(test==8000)
  // printf("light defined \n" );
  // else
  // printf("light not defined\n");
  struct device *specs=(struct device *)malloc(sizeof(struct device));
  

  printf("before anything\n");
  // printf("argc: %d\n", argc);
  if(argc==1)//no inputs
    {
      printf("you are dumb! you forgot a device name!!!restart...\n");
      return 0;
    }
  else if(argc==2)
    {
      specs->power=5;
      specs->variable=-5;
      specs->name=argv[1];
      specs->id=1;
      port=portnumhelper(specs->name, specs->id);
      if (port!=-1)
	printf("PORT: %d \n", port);
      else
	return 0;
      
      // printf("STORED name=%s   %d \n", specs.name,specs.id);
    }
  else
    {printf("got into here \n");
      specs->power=5;
      specs->variable=-5;
      specs->name=argv[1];
      printf("after assignments\n");
      specs->id=atoi(argv[2]);
      printf("after assignment of atoi\n");
      port=portnumhelper(specs->name, specs->id);
      if (port != -1)
        printf("PORT: %d \n", port);
      else
        return 0;
    }
  
  umask(0000);
  struct sockaddr_in destination;
  memset(&destination, 0, sizeof(destination));
  destination.sin_family=AF_INET;
  destination.sin_port=htons(port);
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
  
  while(1){// i think this allows for multiple clients and I can delete it later
    printf(" spec.power: %d and specs.variable: %d \n", specs->power, specs->variable);
    takeclient(destination, SDfromClient,specs);
    printf(" spec.power: %d and specs.variable: %d \n", specs->power, specs->variable);
  }
  
  shutdown(SDfromClient, SHUT_RDWR);
  
  return 1;
}

takeclient(struct sockaddr_in destination, int SDfromClient, struct device *SPEC)
{
  int newSD;
  int f;
  char messageFromClient[255]; char messageToClient[255];
  


  if ( (newSD=accept(SDfromClient, NULL, NULL)) < 0  ) {
    printf ("accept failed\n");
    return 0;} 
  else {
    printf("Accepting connections...\n"); 
    
    // while(1){
    strcpy(&messageFromClient,(char *)readhelp(newSD,&messageFromClient,255));
    printf("Message from client: %s\n", messageFromClient);
    // specs.power=specs.power;
    // specs.variable=specs.variable;      
    // int b=0;
    // if(b=
    takecommands(messageFromClient,SPEC,newSD);//<0)
    //break;
    //  } 
    
    
    close(newSD);
  }
  
}
