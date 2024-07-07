#include "header_ms.h"
#include "def.h"
int ls_cmd(int);
int ps_cmd(int);
int g_cmd(char* a,char* b,int c,int d);
int mv_cp_cmd(int c,int b,char* r, char* s);
void source_file_ptr(char* a);
void destin_file_ptr(char* a);
int main(){
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
		  
		   	char token_arr[10][100]={{0}};
			char* token;
			int i=0;
			token = strtok(command_name, " ");
			while (token != NULL) {
				  int j=0;
				  while(token[j]!='\0'){
					  token_arr[i][j]=token[j];
					//  printf("token[%d]=%c ",j,token[j]);
					  j++;
				 }
				  token_arr[i][j]='\0';
				  //puts("");
				//printf("%d-i %s\n",i, token_arr[i]);
					token=strtok(NULL," "); //gone to next token from where it left last token
					i++;
					//printf("space\n");
			  }
			  
			 //printf("%d-i\n",i); printf("%s\n",token_arr[1]);
			  if(strcmp(ls,token_arr[0])==0){
			  	//printf("yes\n");
			  int a=0;
			  if(strcmp(ls1,token_arr[1])==0 && i==2){a=1;}
			  if(strcmp(ls2,token_arr[1])==0 && i==2){a=2;}
			  if(strcmp(ls3,token_arr[1])==0 && i==2){a=3;}
			  if(strcmp(ls4,token_arr[1])==0 && i==2){a=4;}
			  if(i==1){a=5;}
			 //  printf("a=%d\n",a);
			
			 ls_cmd(a);     
			  }
			  int b=0; int j=0;int k=0;
			  if(strcmp(cp,token_arr[0])==0){
			  if(token_arr[1][0]=='-'){
			  	if((strcmp(cp1,token_arr[1])==0 || strcmp(cp2,token_arr[1])==0 || strcmp(cp3,token_arr[1])==0 || strcmp(cp4,token_arr[1])==0)==0){
			  		printf("invalid option\n");       	
			  	}
			  	else{
			  		  if(strcmp(cp1,token_arr[1])==0){b=1;}
					  if(strcmp(cp2,token_arr[1])==0 ){b=2;}
					  if(strcmp(cp3,token_arr[1])==0 ){b=3;}
					  if(strcmp(cp4,token_arr[1])==0 ){b=4;}
					  j=i-3;  //no.of sourcefiles      	
			  	}
			  }
			  else{ b=5;	j=i-2; }
				  
				  for(int p=i-2;p>=i-j-1;p--){		   
				   // destin_file_ptr(token_arr[i-1]);
				 	  //source_file_ptr(token_arr[p]); 
				 	  mv_cp_cmd(0,b,token_arr[p],token_arr[i-1]);
				 	  	//printf("p in loop -%d j-%d i-%d\n",p,j,i);
				 	  }	  	 	
			  	}
		  	
		  	int c=0;
		  	if(strcmp(mv,token_arr[0])==0){
			   if(token_arr[1][0]=='-'){
			  	if((strcmp(mv1,token_arr[1])==0 || strcmp(mv2,token_arr[1])==0 || strcmp(mv3,token_arr[1])==0 || strcmp(mv4,token_arr[1])==0)==0){
			  		printf("invalid option\n");       	
			  	}
			  	else{
					  if(strcmp(mv1,token_arr[1])==0){c=1;}
					  if(strcmp(mv2,token_arr[1])==0 ){c=2;}
					  if(strcmp(mv3,token_arr[1])==0 ){c=3;}
					  if(strcmp(mv4,token_arr[1])==0 ){c=4;}
					  j=2;
					 }
					}
					  else{c=5;j=1;}
						 //destin_file_ptr(token_arr[i-1]);
					 	 for(int p=i-2;p>=i-j-1;p--){				   			 
						 	  //source_file_ptr(token_arr[p]);  
						 	  mv_cp_cmd(c,0,token_arr[p],token_arr[i-1]);  	
				  	}
				  	
				}

			 
			  if(strcmp(g,token_arr[0])==0){
			  int d=0;
			  //printf("yes\n");
			  
			   if(token_arr[1][0]=='-'){
			  	if((strcmp(g1,token_arr[1])==0 || strcmp(g2,token_arr[1])==0 || strcmp(g3,token_arr[1])==0 || strcmp(g4,token_arr[1])==0)==0){
			  		printf("invalid option\n");       	
			  	}
			  	else{ j=2;
					  if(strcmp(g1,token_arr[1])==0 ){d=1;}
					  if(strcmp(g2,token_arr[1])==0 ){d=2;}
					  if(strcmp(g3,token_arr[1])==0 ){d=3;}
					  if(strcmp(g4,token_arr[1])==0 ){d=4;}
					  
						  
					  }
					}
				
				 else{d=5; j=1;}
					   //printf("a=%d\n",a);
					   
					   if(token_arr[j][0] == '"' ) { //changed here
					  	//char *str = "Hello, world!";
					  	char str_req[100]; int k=1;
						while(token_arr[2][k]!='"'){
						 	str_req[k]=token_arr[2][k];
						 	k++;					
						}
						str_req[k]='\0';
						
					   for(int k=j+1;k<i;k++){
					//   printf("%d\n",k);
						g_cmd(str_req,token_arr[k],d,i-j-1);       
					   }
					}
					else{
					
					for(int k=j+1;k<i;k++){
					//   printf("%d\n",k);
						g_cmd(token_arr[j],token_arr[k],d,i-j-1); 
					
					}
					
		  			  }
		  		}
		  		
		  		if(strcmp(ps,token_arr[0])==0){
			  	//printf("yes\n");
			  	if(token_arr[1][0]=='-'){
			  	if((strcmp(ps1,token_arr[1])==0 || strcmp(ps2,token_arr[1])==0 || strcmp(ps3,token_arr[1])==0 || strcmp(ps4,token_arr[1])==0)==0){
			  		printf("invalid option\n");       	
			  	}}
			  int e=0;
			  if(strcmp(ps1,token_arr[1])==0){e=1;printf("PID\tSPID\tTTY\tTIME\tCMD\n");}
			  if(strcmp(ps2,token_arr[1])==0){e=2;printf("PID\tTTY\tTIME\tCMD\n");}
			  if((strcmp(ps3,token_arr[1])==0) || (strcmp(ps4,token_arr[1]))==0){e=3;printf("PID\tSPID\tTTY\tTIME\tCMD\n");}
			  
			  if(i==1){e=5;}
			 ps_cmd(e); 
			 }
		
			/*if(strcmp(command_name,exit)==0){
			printf("exitting from shell\n");
			return 0;
			}*/
			
			if(strcmp(command_name,help)==0){
			system("bash -c help");
			}
			


	 }
}
