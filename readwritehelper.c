/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#include "readwritehelper.h"
#include <stdio.h>
#include <string.h>

//ASSURES COMPLETE READING
//TAKES A FILE DESCRIPTOR, A STRING TO STORE WHAT YOU READ, AND MAX LENGTH TO READ
//RETURNS THE STRING WITH THE READ MATERIAL
char * readhelp(int SD, char *string, int max)
{
  int counter=0; int error;  char c;
  while (counter<=max) {
    if (error=read(SD,&c,1) < 0)
      printf("READING ERROR\n");
    else
      {
        if (c==0){         
          string[counter]=c;
          return string;
        }
        else if(c=='\n') { 
              string[counter]=0;
              return string;
            }
          else {
            string[counter]=c;
            counter++;
          }
      }
  }
  if (error==-1)
    printf("error in reading");
  return string;
}
//ASSURES COMPLETE WRITING
//TAKES A FILE DESCRIPTOR, A STRING TO WRITE, THE NUMBER OF BYTES TO WRITE
writehelp(int SD, char * string, int len)
{
  int counter=0;
  while( counter<=len){
    if (string[counter]==NULL){
      write(SD,&(string[counter]),1);
      return;
      }
    else {
      if( write(SD,&(string[counter]),1)!=1)
        printf("error in writing\n");
      counter++;
    }
  }
}
