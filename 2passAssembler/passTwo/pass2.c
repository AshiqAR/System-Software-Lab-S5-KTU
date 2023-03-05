#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
    FILE *inter,*symtab,*optab,*plen;
    inter = fopen("inter.txt","r");
    symtab = fopen("symtab.txt","r");
    optab = fopen("optab.txt","r");
    plen = fopen("plen.txt","r");

    char loc[10],la[10],mn[10],op[10],temp[10],opt[10],t1[10];
    int f = 0,i,j;
    char str[10];
    fscanf(inter,"%s\t%s\t%s\t%s",loc,la,mn,op);
    fscanf(plen,"%s",temp);

    printf("H^%s^00%s^%s\n",la,op,temp);
    strcpy(str,op);
    printf("T^00%s^%s",op,temp);

    do{
        f = 0;
        fscanf(inter,"%s\t%s\t%s\t%s",loc,la,mn,op);
        fseek(optab,0,SEEK_SET);
        do{
            fscanf(optab,"%s\t%s",opt,temp);
            if(strcmp(opt,mn) == 0){
                f = 1;
                break;
            }
        }while(!feof(optab));

        if(strcmp(mn,"BYTE") == 0 ){
            if(op[0] == 'X'){
                for(i=2,j=0;i<strlen(op);i++,j++){
                    temp[j] = op[i];
                }
                temp[j] = '\0';
            }
            else if(op[0] == 'C'){
                printf("^");
                for(i=2;i<strlen(op);i++)
                    printf("%x",op[i]);
            }
        }
        else if(strcmp(mn,"WORD") == 0){
            printf("^00000%s",op);
        }

        if(f == 1){
            fseek(symtab,0,SEEK_SET);
            do{
                fscanf(symtab,"%s\t%s",opt,t1);
                if(strcmp(opt,op) == 0){
                    break;
                }
            }
            while(!feof(symtab));

            printf("^%s%s",temp,t1);
        }
    }
    while(!feof(inter));
    printf("\nE^00%s\n",str);
}