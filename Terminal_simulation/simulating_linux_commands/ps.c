#include "header_ms.h"
#include<limits.h>  //LINE_MAX is in this

 int ps_cmd(int a){
//opened proc directory to get details of processes
DIR* curr_dir= opendir("/proc");
	if(curr_dir==NULL){
		printf("couldn't open directory\n");
		return 1;
	}
 struct dirent* thru_dir;
 char* tty_name = ttyname(STDIN_FILENO);
 char tty[256];
 strcpy(tty,"/dev/");   // /dev/tty_name()
 strcat(tty,&tty_name[5]);  //tty value is found here i.e our current working terminal
 /*printf("%s\n",tty_name);
 printf("%s\n",ttyname(STDIN_FILENO));
 printf("%s\n",tty);
 */	

 	 //printf("PID\tTTY\tTIME\tCMD\n");
	 while((thru_dir=readdir(curr_dir))!=NULL){
	 	if(thru_dir->d_type == DT_DIR && strcmp(thru_dir->d_name,".") !=0 && atoi(thru_dir->d_name)!=0 && strcmp(thru_dir->d_name,"..")!=0 && isdigit(*thru_dir->d_name)){
	 	// "." , ".." cause infinite recursion in them as every directory has . , ..(child,parent) descriptor so it causes to read dirs again
	 	char tty_path[256];
            strcpy(tty_path, "/proc/");
            strcat(tty_path, thru_dir->d_name);
            strcat(tty_path, "/fd/0");   //  /proc/dir_name/fd/0
            char tty_link[256];
            int n = readlink(tty_path, tty_link, sizeof(tty_link) - 1); //reading softlink(path or ptr to the file) of terminal associated with the process 
            if (n != -1){
                tty_link[n] = '\0';
            }
           
	//comparing if both current and working terminals are same if so ps is printed
             // Compare the tty value with the name of the terminal associated with the program  
            if( ((a==1 || a==5)&& (strcmp(tty_link, tty)) == 0) || a==2 || a==3 ) {        
	 		printf("%d\t",atoi(thru_dir->d_name));}
	 		int pid=atoi(thru_dir->d_name);
	 		//spid
	 		if(a==1 ||a==3 ){
			 	int spid=getsid(pid);
			 	printf("%d\t",spid);
	 		} 	
	 		 if( ((a==1 || a==5)&&  (strcmp(tty_link, tty)) == 0) || a==2 || a==3 ) { 	
		 		 if(tty_link==NULL){
		 		 	printf("?\t");
		 		 }
		 		 else{
		 			printf("%s\t",&tty_link[5]);
	 				}
	 		}
		 	
		 	
		 	//file is opened and then read to get attributes like uptime,cmd,..
		//curr_time -- uptime
			char path[256];
		    sprintf(path,"/proc/%d/stat",pid);
		 		FILE* fp=fopen(path,"r");
		 			if(fp!=NULL){		 			
		 			
		 			char line[512];
		 			if (fgets(line, sizeof(line),fp)!= NULL) {
			 			char* token;		 				 			
			 			token= strtok(line," ");
						for (int i=1;i<13;i++) {
						    token = strtok(NULL, " ");
						}
						unsigned long utime = strtol(token, NULL, 10); 
						token = strtok(NULL, " ");
						unsigned long stime = strtol(token, NULL, 10);					
						double cpu_time= (utime+stime)/(double)sysconf(_SC_CLK_TCK);
						int H=(int)cpu_time/3600;
						int M=((int)cpu_time%3600)/60;
						int S=(((int)cpu_time%3600)%60);
						 if( ((a==1 || a==5)&&  (strcmp(tty_link, tty)) == 0) || a==2 || a==3 ) { 
							printf("%d:%d:%d\t",H,M,S);
						}
						}
		 			}
		 			else{
		 			printf("couldn't open stat file\n");
		 			}
		 			fclose(fp);	
		 	//cmd
		 	char cmdline[256];
		 	FILE* cmdline_file;
		 	char cmdline_path[256];
		 	sprintf(cmdline_path,"/proc/%d/cmdline",pid);
		 	cmdline_file=fopen(cmdline_path,"r");
		 		if(cmdline_file==NULL){
		 			printf("couldn't open commandline file\n");
		 		}
		 	fscanf(cmdline_file,"%s",cmdline); //just like reading 
		 	 if( ((a==1 || a==5)&& (strcmp(tty_link, tty)== 0)) || a==2 || a==3  ) { 
		 		printf("%s\n",cmdline);
	    	}		 	
		 }
	 }
}
