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
#include <netinet/in.h>
#include <netdb.h>



int main(/*int argc, char *argv[]*/)
{
  
 int SDfromClient; int checknum=0;
  int DefaultPort=8080;
  int port;

  //SET UP THE SOCKADDR_IN STRUCT TO CONNECT TO THE CLIENT
  struct device *specs=(struct device *)malloc(sizeof(struct device));
  umask(0000);
  struct sockaddr_in destinationCC;
  memset(&destinationCC, 0, sizeof(destinationCC));
  destinationCC.sin_family=AF_INET;
  destinationCC.sin_port=htons(DefaultPort);
  destinationCC.sin_addr.s_addr=htonl(INADDR_ANY);
  SDfromClient=socket(AF_INET,SOCK_STREAM,0);
  if (SDfromClient<0){
    printf("socket failed\n"); return 0;}
  // else printf("socket worked \n", SDfromClient);
  if ( (checknum = bind(SDfromClient, (struct sockaddr *) &destinationCC, sizeof(destinationCC))) < 0) {
    printf("bind failed\n");  return 0;} 
  // else { printf("Successful bind\n"); }
  if ( (checknum=listen(SDfromClient, 2)) < 0 ) {
    printf("listen failed\n");  return 0; }
  // else {printf("Listening on INADDR_ANY\n");}

  //MAKE CONNECTIONS TO THE CLIENT
  while(1){
    int newSD;
    if ( (newSD=accept(SDfromClient, NULL, NULL)) < 0  ) {
      printf ("accept failed\n");return 0;} 
    else {
      //printf("Accepting connections...\n"); 
      
      //SET UP STRUCTS TO WORK WITH APPLIANCES
      struct hostent * host;
      host=gethostbyname("127.0.0.1");
      int SDtoServer;
      struct sockaddr_in destination;
      umask(0000);
      memset(&destination, 0, sizeof(destination));
      destination.sin_family=AF_INET;
      memcpy((char*)&destination.sin_addr.s_addr, (char *)host->h_addr, host->h_length);
      
      //TAKE THE MESSAGE FROM THE CLIENT AND SPLIT IT INTO A NAME, AN ID, AND A MESSAGE
      char *command = (char *) malloc(255 * sizeof(char));
      strcpy(command,(char *)readhelp(newSD,command,255));
      printf("Message from client: %s\n", command);
      char * minicommands[3];
      minicommands[0]=command;
      // printf("minicommands[0]= %sSPACE\n", minicommands[0]);
      int counter=0;
      int num=1;
      while(num<3) {
        if(*command==' '){
          *command=NULL;
          command++;
          minicommands[num]=command;
          command--;  num++;
        }
        command++;
      }
      int portnumber=portnumhelper(minicommands[0], atoi(minicommands[1]));
      printf("portnumber: %d\n", portnumber);
      
      //ADDS AN APPLIANCE TO AN ARRAY
      int appliance_ports[30];
      int numappliances=0;
      if (minicommands[2]=="ADD_APPLIANCE")
        {
          appliance_ports[numappliances]=portnumber;
          numappliances++;
        }
      else
        {
          //MAKE A CONNECTION TO AN APPLIANCE 
          destination.sin_port=htons(portnumber);
          SDtoServer=socket(AF_INET,SOCK_STREAM,0);
          if (SDtoServer <0)
            printf("socket failed from client\n");
          //else printf("socket worked from client\n");
          if(connect(SDtoServer,(struct sockaddr *) &destination, sizeof(destination)) < 0)
            printf("No such appliance! \n");
          //else printf("connection worked \n");
          
          //PASSES THE MESSAGE FROM THE CENTRAL SERVER TO THE APPLIANCE AND GETS A REPLY
          char message[255];
          writehelp(SDtoServer, minicommands[2],strlen(minicommands[2])+1);
          readhelp(SDtoServer, message, 255); 
          printf("message: %s ", message);
          //ACTS ACCORDINGLY TO THE COMMAND AND PASSES ALL INFORMATION TO THE CLIENT         
          writehelp(newSD,message, strlen(message)+1);
          if (strcmp("enter new number:",message)==0)
            {
              char newtemp[255];
              readhelp(newSD, newtemp, 255);
              writehelp(SDtoServer,newtemp,strlen(newtemp)+1);
            }
          shutdown(SDtoServer, SHUT_RDWR);
        }
      close(newSD);
    }
  }
  return 1;
}


