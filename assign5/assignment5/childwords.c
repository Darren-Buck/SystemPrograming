#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#define BUFSIZE 4096   

char buffer[BUFSIZE]; 
FILE *datafile = NULL;

bool wordcount(const char * fileName){
  
  char *token;
  const char delim[]= " \n\r";
  int count = 0; 
  
  datafile = fopen(fileName, "r");
  memset(buffer,0,BUFSIZE);
  
  while (fgets(buffer, BUFSIZE, datafile) != NULL){
    token = strtok(NULL,delim);
    count += sizeof(token);
  }
  printf("Child process for %s: word count is %d", fileName,count);
  
  return true;
}
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
int main (int argc, char ** argv) {

  long lForkPid;        // PID of child
  int iExitStatus = 0;  // Used by parent to get status of child
  long lWaitPid;        // PID of child that terminated

  int totalfiles = (argc -1);
  int success = 0;
  int i;
  int count = 0; 
  for (i=1; i<=argc; i++){
    
       // create a child process
    lForkPid= fork();
     // Both the parent and first child continue here
    switch(fork()) {
      case -1:
         errExit("fork failed: %s", strerror(errno));
         break;
      case 0: // child process
        return !wordcount(argv[i]);
       
      default: // parent process - the writer
        
        break;
        }
    }    
   // make parrent wait for all children to close count the number of successful closes 
  while(wait(&iExitStatus) != -1){
    
    if (WIFEXITED(iExitStatus) != 0)
      printf("Child terminated normally: %d\n", WEXITSTATUS(iExitStatus));
    if (WIFSIGNALED(iExitStatus) != 0)
      printf("Child terminated due to uncaught signal: %d\n", WTERMSIG(iExitStatus));
    
    success += 1;
  }
  return 0;
}
