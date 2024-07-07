#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<ctype.h> //isspace fn
#include<dirent.h>
#include<sys/stat.h>
#include<sys/statvfs.h> //for blocksize contains inf of filesystem
#include<pwd.h> //contains inf abt user
#include<grp.h>
#include<time.h>
#include<string.h>
#include<dirent.h>
#include<fcntl.h> //for different flags O_RDONLY,etc
/*qsort(file_prop,count,sizeof(struct fileprop),m_time_comp);
qsort(file_prop,count,sizeof(struct fileprop),a_time_comp);
qsort(file_prop,count,sizeof(struct fileprop),file_name_comp);*/
int m_time_comp(const void* a, const void* b);
int a_time_comp(const void* a, const void* b);
int file_name_comp(const void* a, const void* b);
void printfiledetails(void);
struct fileprop{
 struct stat metadata;
 char file_name[100];
};





