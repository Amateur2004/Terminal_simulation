#include "header_ms.h"

char pattern[100];
int n;
 
int g_cmd(char* pattern,char* source,int d,int k ){
	int f_source1;
	f_source1=open(source,O_RDONLY,0); //f_source is the file descriptor which is like an ID to the file
	if(f_source1==-1){
		printf("grep : %s : unable to open the file\n",source);
		return 0;
	}
	char line[400];	
	char ch;
	
	int line_matched =0; int line_no=0;
	while(1){
	//printf("%ld\n",bytes_read);
	ssize_t bytes_read = read(f_source1, &ch, sizeof(ch));
	if(bytes_read<0){
			printf("grep : %s :couldn't read the file properly\n",source);
		        return 0;
		}
		if(bytes_read==0){
			//printf("end of the file\n");
			break;
		}
			
		int i=0; 
		//printf("i=%d\n",i);
		while(ch!='\n'){
			 line[i] = ch;
		     	 i++;
		       bytes_read = read(f_source1, &ch, sizeof(ch));  //to move to next char
            }
             line[i]='\0';
             if(i!=0){
             line_no++;
             }
		
		  char* check = strstr(line, pattern);
		  if(check != NULL){		  
		     //grep
		     if(d==5 && k >1){
		     		printf("%s:%s\n",source,line);
		     }
		     if(k==1){
				printf("%s\n",line);
		     }
		      //grep -c //count no.of lines
		      
		  	line_matched++;
		      //grep -h
		      if(d==2){
		      	printf("%s\n",line);
		      }
		      //grep -l
		      if(d==3){
		     		printf("%s\n",source);
		     	}
		      //grep -n
		      if(d==4){
		      	printf("%s:%d:%s\n",source,line_no,line);
		      }
		      
		  	
	}
		
    }
   		 if(d==1){
  			printf("%s:%d\n",source,line_matched);
  		  	}
			fflush(stdout);
    close(f_source1);
 }


