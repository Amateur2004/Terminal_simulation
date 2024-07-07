#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<ctype.h> //isspace fn
int strcomp(char* str1,char* str2,int size){
 int count=0;
 for(int i=0;i<size;i++){
  	if(str1[i]==str2[i]){
  	count++;
  	}
  }
 	 if(count==size){
 	 return 1;
  	}
  	else{
  	return 0;
  	}
 }
int main()
{
char hostname[100];
char* username;
char path[100];
char ini_shell[400];
char help[5]="help";
char exit[5]="exit";
gethostname(hostname,sizeof(hostname));
username=getlogin();
getcwd(path,sizeof(path));
while(1){
sprintf(ini_shell,"%s@%s:%s$ ",username,hostname,path);
char* command_name=readline(ini_shell);
  int count=0;
  while(command_name[count]!='\0'){
  count++;
  }
int counter=0;	
  for(int i=0;i<count;i++){
  	if(isspace(command_name[i])){
  	counter++;
  	}
  }
 
	if( (counter!=count) && command_name[0]!='\0'){
  	add_history(command_name);
  }
  

	if(strcomp(command_name,exit,5)){
	printf("exitting from shell\n");
	return 0;
	}
	
	if(strcomp(command_name,help,5)){
	system("bash -c help");
	}
	
	else if(system(command_name)!=0){
	printf("command not found\n");
	}
	
}

}
