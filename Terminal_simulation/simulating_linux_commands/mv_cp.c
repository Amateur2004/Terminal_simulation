#include "header_ms.h"
char source_file_path[100];
char destin[100];
/*void source_file_ptr(char* a){
int i=0;
  while(a[i]!='\0'){
 	source_file_path[i] =a[i];
 	i++;
  }
  source_file_path[i] ='\0';
}
void destin_file_ptr(char* a){
int i=0;
  while(a[i]!='\0'){
 	destin[i] =a[i];
 	i++;
  }
 }*/

int mv_cp_cmd(int c,int b,char* source_file_path,char* destin){

struct stat metadata_s,metadata_d;
unsigned int mode;
	if(stat(source_file_path,&metadata_s)==0){   //can stat store based on filepath also? name is less unique than this 
	mode= metadata_s.st_mode & 0777;
	}

	int count_s=0;
	while(source_file_path[count_s]!='\0'){
	count_s++;
	}
	int length_s=count_s+1;
	int i_s=0;
	while(source_file_path[count_s]!='/' &&count_s >=0){
	i_s++; count_s--;
	}
	char file_name[i_s];
		for(int j=0;j<i_s;j++){	
			file_name[i_s-1-j]=source_file_path[length_s-1-j];	
		}
  
int f_source;
	f_source=open(source_file_path,O_RDONLY,0); //f_source is the file descriptor which is like an ID to the file
	//printf("source in cp %s\n",source_file_path);
	if(f_source==-1){
		printf("%s : unable to open the file\n",source_file_path);
		return 0;
	}

	else{
	
	long size= lseek(f_source,0,SEEK_END); //to move fileptr to end;
	lseek(f_source,0,SEEK_SET); //to move to start
	void * content_sourcefile=malloc(size);
	ssize_t file_read= read(f_source,content_sourcefile,size);
	char final_file_path[500];
	
		DIR *dir=opendir(destin);
		//printf("destin in cp-%s\n",destin);
	if(dir){
		 sprintf(final_file_path,"%s/%s",destin,file_name);//need to do this for same folder and other options //filename not provided
	}
/*	if(k==0 && dir!=NULL){
			sprintf(final_file_path,"%s",destin);			
	}
		else if(k>0 && dir ==NULL){
			printf("directory is unavailable\n");
		}
	*/
	/*if(dir!=NULL){
		sprintf(final_file_path,"%s",destin);
	}*/
	else{
		sprintf(final_file_path,"%s",destin);
	}
	//mv -i cv -i
	if(c==1 || b==1){
	char permission;
 	if(access(final_file_path,F_OK)!=-1){
 		if(c==1){
			printf("mv overwrite '%s' ? ",final_file_path);	
		}
		if(b==1){
			printf("cp overwrite '%s' ? ",final_file_path);	
		}
			scanf(" %c",&permission);
	  	
	  	
		if(permission=='y' || permission=='Y'){
		int f_destin=open(final_file_path,O_WRONLY|O_CREAT,mode);
			if(f_destin==-1){
			printf("%s : unable to write the file to destination\n",final_file_path);
			}		
			write(f_destin, content_sourcefile ,size);
			 close(f_destin);
			 if(c==1){
			 	remove(source_file_path);}
		}
	 }
	 else{
	 	int f_destin=open(final_file_path,O_WRONLY|O_CREAT,mode);
						if(f_destin==-1){
						printf("%s : unable to write the file to destination\n",final_file_path);
						}		
			write(f_destin, content_sourcefile ,size);
			close(f_destin);
			if(c==1){
				remove(source_file_path);
			}
	 }
 }	
	// mv -u cv -u
	if(c==2 || b==2){
		if(access(final_file_path,F_OK)!=-1){
		 stat(final_file_path,&metadata_d);	
		} 	
			if(access(final_file_path,F_OK)!=-1 && metadata_s.st_mtime > metadata_d.st_mtime || access(final_file_path,F_OK)==-1){
				int f_destin=open(final_file_path,O_WRONLY|O_CREAT,mode);	
				if(f_destin==-1){
				printf("%s : unable to write the file to destination\n",final_file_path);
				}	
				write(f_destin, content_sourcefile ,size); 
				if(c==1){
					remove(source_file_path);
				}
				close(f_destin);	
			} 
	}
	
	
	
	// cp -v b==3; cp -f b==4; cp b==5;
	if(c==3 || c==4 || c==5 || b==4 || b==5 || b==3){
		int f_destin=open(final_file_path,O_WRONLY|O_CREAT,mode);	
		if(f_destin==-1){
		printf("%s : unable to write the file to destination\n",final_file_path);
		}	//printf("destin in cp-%s\n",destin);
		write(f_destin, content_sourcefile ,size);
		//printf("destin in cp-%s\n",destin);
		if(c==3 || c==4 || c==5){		
			 remove(source_file_path);
		}
		close(f_destin);
	}
	if(c==3 || b==3){
	//printf("destin in cp-%s\n",destin);
		printf("'%s' -> '%s'\n",source_file_path,final_file_path);
	}
	
	// cp -f is similar to cp also mv -f is similar to mv
	close(f_source);
	}
	return 0;
    }

