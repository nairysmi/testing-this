/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */
#include "readwritehelper.h"
#include "portNUMS_defined.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void get_power(struct device * gp, int SD)
{ char power[100];int ret=0;
  
  //printf("before sprintf!!!!%d %d \n ", ret,gp->power);
  ret=sprintf(power, "%d", gp->power); 
  //printf("power:%s and length %d \n",power,ret); 
  writehelp(SD,power, ret+1);
}

void get_variable(struct device * gv, int SD)
{
  char message[100]="power is off. turn power on to get data\n";
  
  
  if(gv->power == 1) {
    char var[100];
    int ret;
    ret= sprintf(var, "%d", gv->variable);
    writehelp(SD, var,ret+1 ); 
  } else
    writehelp(SD,message ,strlen(message)+1); 
}

void set_power(struct device *spo, int p,int SD)
{ spo->power=p;
  char s[100];int ret;
  ret= sprintf(s,"power is now: %d\n", spo->power);
  write(SD,s,ret+1);
}

void set_variable(struct device * sv, int SD)
{
  char input[100];
  char message[100]="enter new number:";
  int intinput;
  writehelp(SD, message, strlen(message)+1);
  readhelp(SD, input, 10);
  intinput=atoi(input);
  //printf("INT changed: %d \n", intinput);
  sv->variable=intinput;
}
int takecommands(char * command, struct device *sp, int SD)
{
  //sp->power=sp->power+1;
  //  sp->variable=sp->variable-1;
  if(strcmp(command, "GET_POWER")==0)
    {
      get_power(sp,SD);
    }
  else if(strcmp(command, "GET_TEMP")==0 | strcmp(command, "GET_WATT")==0 | strcmp(command, "GET_CHANNEL")==0)
    {
      get_variable(sp,SD);
    }
  else  if(strcmp(command, "SET_POWER_ON")==0)
    {
      set_power(sp,1,SD);
    }
  else  if(strcmp(command, "SET_POWER_OFF")==0)
    {
      set_power(sp,0,SD);
    }
  else if(strcmp(command, "SET_TEMP")==0 | strcmp(command, "SET_WATT")==0 | strcmp(command, "SET_CHANNEL")==0)
    {
      set_variable(sp,SD);
    }
  else  if(strcmp(command, "EXIT")==0)
    {
      printf("exiting!\n");
      return -1;
    }
  else
    {char  message[100]="invalid command \n";
      write(SD,message , strlen(message)+1);
    }
  return 1;
}
