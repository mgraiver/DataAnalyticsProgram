/*
Program to implement Data Analytics program 
*************************************************************** 
* Author         Dept .          Date          Notes 
***************************************************************
* Micaela G-R    Comp. Science . Nov 10 2020   Initial version .
* Micaela G-R    Comp. Science . Nov 11 2020   Check if user exists .
* Micaela G-R    Comp. Science . Nov 14 2020   Check for collaborators .
* Micaela G-R    Comp. Science . Nov 15 2020   Added error handling .
* Micaela G-R    Comp. Science . Nov 16 2020   Debug .
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	if(argc < 3){
		fprintf(stderr,"Usage ./report <csvfile> \"<student name>\" <reportfile>\n");
		return 1;
	}

	FILE *file_in= fopen(argv[1], "r");
	if (file_in == NULL){
		printf("Error, unable to open csv file %s\n", argv[1]);
		return 1;
	}

	char logline[200] = "";
	char *sname = argv[2];
	
	int found = 0;	
	
	char *IP = "";
	int i=0;

	while(fgets(logline, 200, file_in)){
	
		if(strstr(logline, sname)){
			char *token = strtok(logline,",");
			
			for (int i=0; i<6; i++){
				IP = strtok(NULL,",");
			}	
		break;
		}
		
	}
	
	if(strstr(logline,sname)==NULL){
		fprintf(stderr,"Error, unable to locate %s\n",argv[2]);
		return 1;
	}
	
	FILE *out = fopen(argv[3], "w");
	if(!out){
		fprintf(stderr,"Error, unable to open the output file %s\n",argv[3]);	
		return 1;
	}
	
	char newline[200] = "";
	char **prevCollaborators = malloc(10*sizeof(char*));

	char *cname = malloc(50);
	int k = 0;
	int cexist =0;
	int exist = 1;
	fclose(file_in);
	FILE *file2 = fopen(argv[1], "r");

	while(fgets(newline, 200, file2)){

		if(strstr(newline, IP) && !strstr(newline, sname)){
             cexist=1;
			// Contains IP and is not original name
			
			cname = strtok(newline, ",");
			
		exist =1;	
			for(int j=0; j<k; j++){			
				if(!strcmp(prevCollaborators[j], cname)){
					// if name is already in collabs
					exist = 0;
					break;
										
				}
			}
		
			if(exist){

				prevCollaborators[k] = malloc(sizeof(cname));
				strcpy(prevCollaborators[k], cname);
				fprintf(out,"%s\n",prevCollaborators[k]);
				k++;

			}
			
		}}
		if(!cexist){
			fprintf(out,"No collaborators found for %s\n",sname);
	}
	fclose(out);

	return 0;
	
}
