#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    FILE *inter,*optab,*symtab,*plen;
    inter = fopen("inter.txt","r");
    optab = fopen("optab.txt","r");
    symtab = fopen("symtab.txt","r");
    plen = fopen("plen.txt","r");

    char loc[10],la[10],mn[10],op[10],startadd[10],len[10],opt[10],temp1[10],temp2[10];

    int f ,i,j;

    fscanf(inter,"%s\t%s\t%s\t%s",loc,la,mn,op);
    fscanf(plen,"%s",len);
    printf("H^%s^00%s^%s\n",la,op,len);
    strcpy(startadd,op);
    printf("T^00%s^%s",op,len);

    do{
        f = 0;
        fscanf(inter,"%s\t%s\t%s\t%s",loc,la,mn,op);
        fseek(optab,0,SEEK_SET);
        do{
            fscanf(optab,"%s\t%s",opt,temp1);
            if(strcmp(opt,mn) == 0){
                f = 1;
                break;
            }
        }while(!feof(optab));

        if(strcmp(mn,"BYTE") == 0){
            if(op[0] == 'X'){
                printf("^");
                for(i=2,j=0;i<strlen(op);i++,j++){
                    printf("%c",op[i]);
                }
            }
            else if(op[0] == 'C'){
                printf("^");
                for(i=2;i<strlen(op);i++){
                    printf("%x",op[i]);
                }
            }
        }
        else if(strcmp(mn,"WORD") == 0){
            printf("^00000%s",op);
        }

        if(f==1){
            fseek(symtab,0,SEEK_SET);
            do{
                fscanf(symtab,"%s\t%s",opt,temp2);
                if(strcmp(op,opt) == 0){
                    break;
                }
            }while(!feof(symtab));

            printf("^%s%s",temp1,temp2);
        }
        
    }while(!feof(inter));
    printf("\nE^00%s\n",startadd);

}