#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    FILE *f1,*f2,*f3,*f4;

    f1 = fopen("input.txt","r");
    f2 = fopen("optab.txt","r");
    f3 = fopen("symtab.txt","w");
    f4 = fopen("inter.txt","w");
    char la[10],mn[10],op[10],opt[10];
    int locctr=0,startaddr=0,temp;

    fscanf(f1,"%s\t%s",la,mn);
    if(strcmp(mn,"START") == 0){
        fscanf(f1,"%x",&locctr);
        fprintf(f4,"%x\t%s\t%s\t%x\n",locctr,la,mn,locctr);
        printf("%x\t%s\t%s\t%x\n",locctr,la,mn,locctr);
        startaddr = locctr;
    }
    else
        fseek(f1,0,SEEK_SET);

    do{
        fscanf(f1,"%s\t%s\t%s",la,mn,op);
        printf("%x\t%s\t%s\t%s\n",locctr,la,mn,op);
        fprintf(f4,"%x\t%s\t%s\t%s\n",locctr,la,mn,op);

        if(strcmp(la,"-") != 0){
            fprintf(f3,"%s\t%x\n",la,locctr);
        }        
        fseek(f2,0,SEEK_SET);
        do{
            fscanf(f2,"%s\t%x",opt,&temp);
            if(strcmp(opt,mn) == 0){
                locctr += 3;
                break;
            }
        }while(!feof(f2));

        if(strcmp(mn,"WORD") == 0){
            locctr += 3;
        }
        else if(strcmp(mn,"RESW") == 0){
            locctr += (atoi(op)*3);
        }
        else if(strcmp(mn,"BYTE") == 0){
            if(op[0] == 'X')
                locctr += 1;
            else 
                locctr += (strlen(op) - 2);
        }
        else if(strcmp(mn,"RESB") == 0){
            locctr += atoi(op);
        }
    }while(!feof(f1));
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    FILE *p = fopen("plen.txt","w");
    fprintf(p,"%x\n",locctr-startaddr);
    fclose(p);
}