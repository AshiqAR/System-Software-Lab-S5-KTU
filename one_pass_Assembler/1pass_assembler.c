#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
	FILE *fin,*fsym,*fopt,*finter;
	char la[20],mne[20],op[20],n[20],name[20];
	char symop[20],symad[20],symrd[20];
	char opmne[20],opcode[20];
	char intad[20],intcode[20];
	int locctr,startadd,op1,flag1,flag2,flag3,pos,len,l,i;

	fin=fopen("input.txt","r");
	fsym=fopen("symtab.txt","w+");
	finter=fopen("inter.txt","w+");

	fscanf(fin,"%s%s%x",la,mne,&op1);
	if(strcmp(mne,"START")==0){
		strcpy(name,la);
		startadd=op1;
		locctr=op1;
	}
	else{
		locctr=0;
	}


	while(1){
		fscanf(fin,"%s%s%s",la,mne,op);
		strcpy(n,op);
		if(strcmp(la,"-")!=0){
			flag1=0;
			fseek(fsym,0,SEEK_SET);
			while(1){
				fscanf(fsym,"%s%s",symop,symad);
				if(strcmp(la,symop)==0){
					flag1=1;
					break;
				}
				if(strcmp(symad,"*")==0){
					fscanf(fsym,"%s",symrd);
					while(strcmp("-",symrd)!=0){
						fscanf(fsym,"%s",symrd);
					}
				}
				if(feof(fsym))
					break;
			}

			if(flag1==1){
			if(strcmp("*",symad)==0){
				pos=ftell(fsym);
				strcpy(symrd,symad);
				while(strcmp("-",symrd)!=0){

					fseek(finter,0,SEEK_SET);
					while(1){
						fscanf(finter,"%s%s",intad,intcode);
						if(strcmp(symrd,intad)==0)
						{
						fseek(finter,-4,SEEK_CUR);
						fprintf(finter,"%x",locctr);
						fseek(fsym,-4,SEEK_CUR);
						fprintf(fsym,"    ");
						break;
						}
						if(feof(finter))
						break;
					}
					fscanf(fsym,"%s",symrd);
				}
			fseek(fsym,-1,SEEK_CUR);
			fprintf(fsym," ");
			fseek(fsym,pos-1,SEEK_SET);
			fprintf(fsym,"%x",locctr);
			}
			}
			else{
				fseek(fsym,0,SEEK_END);
				fprintf(fsym,"%s\t%x\t",la,locctr);
				fprintf(fsym,"                  \n");
			}
		}




		fopt=fopen("optab.txt","r");
		flag2=0;
		while(1){
			fscanf(fopt,"%s%s",opmne,opcode);
			if(strcmp(opmne,mne)==0){
				flag2=1;
				break;
			}
			if(feof(fopt)){
				break;
			}
		}


		if(flag2==1){
			fseek(fsym,0,SEEK_SET);
			flag3=0;
			while(1){
				fscanf(fsym,"%s%s",symop,symad);
				if(strcmp(op,symop)==0){
					flag3=1;
					break;
				}
				if(strcmp(symad,"*")==0){
					fscanf(fsym,"%s",symrd);
					while(strcmp("-",symrd)!=0)
					{
					fscanf(fsym,"%s",symrd);
					}
				}
				if(feof(fsym))
					break;
			}

			if(flag3==1){
				if(strcmp("*",symad)==0){
					fscanf(fsym,"%s",symrd);
					while(strcmp("-",symrd)!=0)
					{
					fscanf(fsym,"%s",symrd);
					}
					fseek(fsym,-1,SEEK_CUR);
					fprintf(fsym,"%x\t%s",locctr,"-");
					fprintf(finter,"%x\t%s%s\n",locctr,opcode,"0000");
				}
				else{
					fprintf(finter,"%x\t%s%s\n",locctr,opcode,symad);
				}
			}
			else{
				fseek(fsym,0,SEEK_END);
				fprintf(fsym,"%s\t%s\t%x\t%s                 \n",op,"*",locctr,"-");
				fprintf(finter,"%x\t%s%s\n",locctr,opcode,"0000");
			}

			locctr=locctr+3;
		}
		else if(strcmp(mne,"WORD")==0){
			fseek(finter,0,SEEK_END);
			fprintf(finter,"\n%x\t00000%s",locctr,op);
			locctr=locctr+3;
		}
		else if(strcmp(mne,"RESW")==0){
			op1=atoi(op);
			locctr=locctr+(3*op1);
		}
		else if(strcmp(mne,"RESB")==0){
			op1=atoi(op);
			locctr=locctr+op1;
		}
		else if(strcmp(mne,"BYTE")==0){
			l=strlen(op);
			fseek(finter,0,SEEK_END);
			fprintf(finter,"%x\t",locctr);
			for(i=2;i<l;i++){
				fprintf(finter,"%d",op[i]);
			}
			if(n[0]=='X'){
				locctr=locctr+1;
			}
			else{
				len=strlen(op)-2;
				locctr=locctr+len;
			}
		}
		if(feof(fin))
			break;
	}



	printf("H^%s^%x^%x\n",name,startadd,locctr-startadd);
	printf("T^%x",startadd);
	fseek(finter,0,SEEK_SET);
	i=0;
	while(1){

		fscanf(finter,"%s%s",intad,intcode);
		if(i>60){
			i=i-60;
			printf("\nT^%x",locctr);
		}
		i=i+strlen(intcode);
		printf("^%s",intcode);
		if(feof(finter))
			break;

	}
	printf("\nE^00%x\n",startadd);
	fclose(fsym);
	fclose(fin);
}
