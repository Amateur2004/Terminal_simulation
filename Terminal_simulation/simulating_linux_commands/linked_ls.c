#include "header_ms.h"

int no_dig(int a){
	int count=1;
	while(a/10!=0){
		a=a/10;
		count++;
	}
return count; 
}


int m_time_comp(const void* a, const void* b) {
 const struct fileprop* file_a = (const struct fileprop*) a; // casting a pointer 'a' of type 'void*' to a pointer of type 'const struct file_prop*'. The resulting pointer is stored in the variable 'file_a'.
    const struct fileprop* file_b = (const struct fileprop*) b;
    return file_b->metadata.st_mtime - file_a->metadata.st_mtime;
}
int a_time_comp(const void* a, const void* b) {
	 const struct fileprop* file_a = (const struct fileprop*) a; 
	 const struct fileprop* file_b = (const struct fileprop*) b;
	 return file_b->metadata.st_atime - file_a->metadata.st_atime;
}

int file_name_comp(const void* a, const void* b) {
	 const struct fileprop* file_a = (const struct fileprop*) a; 
	 const struct fileprop* file_b = (const struct fileprop*) b;
	 return strcasecmp(file_a->file_name,file_b->file_name);
   }
   
int ls_cmd(int a){
DIR * curr_dir = opendir(".");
	if(curr_dir==NULL){
	printf("unable to access the directory");
	}
	
	int count=0;
	struct dirent *rd_dir;	
	//reads complete inf abt it so uses structure to read name,time,etc
	//1st while to count no.of files
	  while((rd_dir=readdir(curr_dir))!=NULL){
	  	 if((rd_dir->d_name[0])!='.'){
	  		count++;
	  	}
	  }
	    //2nd opening to get data feeded into the strucure
	   rewinddir(curr_dir);
	 // struct statvfs fs_prop;
	  //long b_size=fs_prop.f_bsize;
	  //printf("b_size=%ld\n",b_size);
	struct fileprop file_prop[count];
	  struct passwd *usr[count];
	  struct group *grp[count];
	//  struct stat metadata[count];
	  time_t time[count];
	
	  int counter=0;
	 long max_size=0;
	 long total_mem=0;
 while((rd_dir=readdir(curr_dir))!=NULL){
	  	 if((rd_dir->d_name[0])!='.'){
	  		stat(rd_dir->d_name,&file_prop[counter].metadata);  //storing metadata in the structure using filename	  		
	  		strcpy(file_prop[counter].file_name,rd_dir->d_name);
	  		total_mem=file_prop[counter].metadata.st_size+total_mem;
	  		//printf("%ld-m   ",metadata[counter].st_size);
	  		if(max_size<file_prop[counter].metadata.st_size){
	  			max_size=file_prop[counter].metadata.st_size;
	  			//printf("%ld-max  ",max_size); 
	  			}
	  	counter++;	
	  	} 	
	  	
	 } 
	 closedir(curr_dir);
	 
	// -l 
	 if(a==1){
	qsort(file_prop,count,sizeof(struct fileprop),file_name_comp);
	for(int i=0;i<count;i++){
	  	//1.filetype
	  		if(S_ISREG(file_prop[i].metadata.st_mode)){
	  		printf("-"); 
	  		}
	  		if(S_ISDIR(file_prop[i].metadata.st_mode)){
	  		printf("d");
	  		}
	  		if(S_ISCHR(file_prop[i].metadata.st_mode)){
	  		printf("c");
	  		}
	  		if(S_ISBLK(file_prop[i].metadata.st_mode)){
	  		printf("b");
	  		}
	  		if(S_ISFIFO(file_prop[i].metadata.st_mode)){
	  		printf("p");
	  		}
	  		if(S_ISLNK(file_prop[i].metadata.st_mode)){
	  		printf("l");
	  		}
	  		if(S_ISSOCK(file_prop[i].metadata.st_mode)){
	  		printf("s");
	  		}
	  	//2.permissions
	  		printf((file_prop[i].metadata.st_mode & S_IRUSR)? "r" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IWUSR)? "w" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IXUSR)? "x" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IRGRP)? "r" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IWGRP)? "w" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IXGRP)? "x" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IROTH)? "r" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IWOTH)? "w" : "-");
	  		printf((file_prop[i].metadata.st_mode & S_IXOTH)? "x" : "-");
	      //3.hardlinks
	       printf(" %ld",file_prop[i].metadata.st_nlink);	
              //4.owner
              usr[i]=getpwuid(file_prop[i].metadata.st_uid);
              printf(" %s",usr[i]->pw_name);
              //5.group
              grp[i]=getgrgid(file_prop[i].metadata.st_gid);
              printf(" %s",grp[i]->gr_name);
              //6.size
            for(int j=0;j<no_dig(max_size)-no_dig(file_prop[i].metadata.st_size);j++){
              	printf(" ");
              }
              	printf(" %ld",file_prop[i].metadata.st_size);
              
             //7.time
              time[i]=file_prop[i].metadata.st_mtime;
             struct tm *tm_attr=localtime(&time[i]);
             char mod_time[13];
             strftime(mod_time,sizeof(mod_time),"%b %d %H:%M",tm_attr);
             printf(" %s",mod_time);
              
              //8.filename
              
              printf(" %s",file_prop[i].file_name);
	   
	  // i++;
	  printf("\n");
	 } 	
	  }
	//-t 
	if(a==2) { 
		for(int i=0;i<count;i++){
		 qsort(file_prop,count,sizeof(struct fileprop),m_time_comp);
	 	  printf("%s\n",file_prop[i].file_name);
	 	  }puts("");
	 }
        // -u	 
        	if(a==3) { 
		 	for(int i=0;i<count;i++){
			 qsort(file_prop,count,sizeof(struct fileprop),a_time_comp);
		 	  printf("%s\n",file_prop[i].file_name);
		 	  }	  
	 	  puts("");
	 	  }
	 //-U	  
	 	if(a==4) {
		 for(int i=0;i<count;i++){
		 	  printf("%s\n",file_prop[i].file_name);
		 	 }
		 	puts("");
	 	  }
   // only ls 
   		if(a==5){
	   	for(int i=0;i<count;i++){
			 qsort(file_prop,count,sizeof(struct fileprop),file_name_comp);
		 	  printf("%s\n",file_prop[i].file_name);
		 	 }
		 	 puts("");
	  }
	  
	 if(a==0){
	  printf("not in the list of commands\n");
	  }
  return 0;
	 }
