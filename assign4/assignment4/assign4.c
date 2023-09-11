#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096
#define DATAFILE "courses.dat"
#define NAMESIZE 84
#define SCHEDSIZE 4
typedef struct {
  char course_Name[NAMESIZE];    //put in header
  char course_Sched[SCHEDSIZE];
  unsigned int course_Size;
  unsigned int course_Hours;
} COURSE;

char buffer[BUFSIZE]; 
FILE *datafile = NULL;
COURSE course;

int readCourse();
int createCourse();
int updateCourse();
int deleteCourse();

// we are redirecting input from typing or file to this assignment    ./assign4 < input
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

int main(int argc, char *argv[])
{

  char choice;
  
  if((datafile = fopen(DATAFILE, "rb+")) == NULL)
  {
    datafile = fopen(DATAFILE, "wb+");
		close(datafile);
		
  }
  
do {
    
  	
    printf("\nEnter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new course record\n");
    printf("U - update an existing course record\n");
    printf("R - read an existing course record\n");
    printf("D - delete an existing course record\n");
    
    if(!fgets(buffer, BUFSIZE, stdin)){ break; } 
    if(sscanf(buffer, "%c", &choice) != 1) {
  		fprintf(stderr, "ERROR: unable to parse menu choice\n");
  		return 1;
  	 }
    switch (tolower(choice))
  	 {
      case 'c':
      createCourse();
      memset(buffer,0,BUFSIZE);
      break;
      case 'u':
      updateCourse();
      memset(buffer,0,BUFSIZE);
      break;
      case 'r':
      readCourse();
      memset(buffer,0,BUFSIZE);
      break;
      case 'd':
      deleteCourse();
      memset(buffer,0,BUFSIZE);
      break;
      default: 
  		printf("\nERROR: Invalid option.\n");
      break;
    	}
  	}
  	while(!feof(stdin));
		return 0;
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
int createCourse(void)
{
  datafile = fopen(DATAFILE, "rb+");
	COURSE course;
  int courseNum;
  memset(buffer,0,BUFSIZE);
  
  printf("\nEnter course number:");
  if(!fgets(buffer, BUFSIZE, stdin)) 
  {
    printf("\nERROR: course %d does not exist.\n", courseNum);
    return 1;
  }
  if(sscanf(buffer, "%u" , &courseNum) != 1) 
  {
    fprintf(stderr, "ERROR: unable to parse course number\n");
    return 1;
  }
  memset(&course,0,sizeof(COURSE));
  fseek(datafile , courseNum * sizeof(COURSE), SEEK_SET);
  fread(&course, sizeof(COURSE), 1L, datafile);
  printf("\nCourse number: %d\n",courseNum);
    printf("Course name: %s\n",course.course_Name);
    printf("Sheduled days: %s\n",course.course_Sched);
    printf("Credit hours: %d\n",course.course_Hours);
    printf("Enrolled Students: %d\n\n",course.course_Size);
	if((course.course_Hours == 3) || (course.course_Hours == 4))
  {
  
  	printf("\nEnter course name:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Name,buffer,NAMESIZE);
    printf("Course name: %s\n",buffer);
    memset(buffer,0,BUFSIZE);
    
		printf("Enter course sheduled:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Sched,buffer,SCHEDSIZE);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter course hours:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Hours);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter enrollment:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Size);
    memset(buffer,0,BUFSIZE);

    
    printf("\nERROR: course %d not found.\n\n", courseNum);
    }
    
    else {
    printf("\nEnter course name:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Name,buffer,NAMESIZE);
    memset(buffer,0,BUFSIZE);
    
		printf("Enter course sheduled:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Sched,buffer,SCHEDSIZE);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter course hours:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Hours);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter enrollment:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Size);
    memset(buffer,0,BUFSIZE);
    
    fseek(datafile, -sizeof(COURSE), SEEK_CUR);
    fwrite(&course, sizeof(COURSE),1L,datafile);
    printf("\nCourse created\n\n");
    }
  
	fclose(datafile);	
	return 0;
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
int readCourse(void)
{
 datafile = fopen(DATAFILE, "rb+");
  COURSE course;
  int courseNum;
  memset(buffer,0,BUFSIZE);
  printf("\nEnter course number: ");
  if(!fgets(buffer, BUFSIZE, stdin)) 
  {
    printf("\nERROR: course %d does not exist.\n", courseNum);
    return 1;
  }
  if(sscanf(buffer, "%d" , &courseNum) != 1) 
  {
    fprintf(stderr, "ERROR: unable to parse course number\n");
    return 1;
  }
  
  fseek(datafile , courseNum * sizeof(COURSE), SEEK_SET);
  fread(&course, sizeof(COURSE), 1L, datafile);
  if((course.course_Hours == 3) || (course.course_Hours == 4)){
    printf("\nCourse number: %d\n",courseNum);
    printf("Course name: %s\n",course.course_Name);
    printf("Sheduled days: %s\n",course.course_Sched);
    printf("Credit hours: %d\n",course.course_Hours);
    printf("Enrolled Students: %d\n\n",course.course_Size);
  }
  else
  {
  
    printf("\nERROR: course %d not exist.\n\n", courseNum);
    return 1;
  }
  
	fclose(datafile);
	return 0;
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
int updateCourse(void)
{
datafile = fopen(DATAFILE, "rb+");
	COURSE course;
  int courseNum;
  memset(buffer,0,BUFSIZE);
  
  printf("\nEnter course number:");
  if(!fgets(buffer, BUFSIZE, stdin)) 
  {
    perror("Course does not exist.\n");
    return 1;
  }
  if(sscanf(buffer, "%u" , &courseNum) != 1) 
  {
    fprintf(stderr, "ERROR: unable to parse course number\n");
    return 1;
  }
  
  fseek(datafile , courseNum * sizeof(COURSE), SEEK_SET);
  fread(&course, sizeof(COURSE), 1L, datafile);
   
  if((course.course_Hours == 3) || (course.course_Hours == 4))
		{						 
    printf("\nEnter course name:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Name,buffer,NAMESIZE);
    memset(buffer,0,BUFSIZE);
    
		printf("Enter course sheduled:\n");
    fgets(buffer, BUFSIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(course.course_Sched,buffer,SCHEDSIZE);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter course hours:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Hours);
    memset(buffer,0,BUFSIZE);
   
	  printf("Enter enrollment:\n");
    fgets(buffer, BUFSIZE, stdin);
    sscanf(buffer,"%u", &course.course_Size);
    memset(buffer,0,BUFSIZE);
    
    fseek(datafile, -sizeof(COURSE), SEEK_CUR);
    fwrite(&course, sizeof(COURSE),1L,datafile);
    
  }
  else{
  printf("\nERROR: course %d not found.\n\n", courseNum);
	}
	
	fclose(datafile);
	return 0;
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
int deleteCourse(void)
{
  datafile = fopen(DATAFILE, "rb+");
	COURSE course;
  int courseNum;
  memset(buffer,0,BUFSIZE);
  
  printf("\nEnter course number:");
  if(!fgets(buffer, BUFSIZE, stdin)) 
  {
    printf("\nERROR: course %d does not exist.\n", courseNum);
    return 1;
  }
  if(sscanf(buffer, "%u" , &courseNum) != 1) 
  {
    fprintf(stderr, "ERROR: unable to parse course number\n");
    return 1;
  }
  
  fseek(datafile , courseNum * sizeof(COURSE), SEEK_SET);
  fread(&course, sizeof(COURSE), 1L, datafile);
	
	if((course.course_Hours > 0) && (course.course_Hours < 5)){
	  course.course_Hours = 0;
    fseek(datafile, -sizeof(COURSE), SEEK_CUR);
    fwrite(&course, sizeof(COURSE),1L,datafile);
    printf("Course %d was successfully deleted\n", courseNum);
	}
  else{
    printf("\nERROR: course %d not found.\n\n", courseNum);
  }
  
	fclose(datafile);
	return 0;
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/











