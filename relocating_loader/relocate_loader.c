#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void setInput(){
    FILE* f = fopen("input.txt","r");
    FILE* inter = fopen("obj.txt","w");
    char text[100];
    int i;

    do{
        fscanf(f,"%s",text);
        for(i = 0 ;i < strlen(text) ; i++){
            if(text[i] == '^'){
                fprintf(inter," ");
            }else{
                fprintf(inter,"%c",text[i]);
            }
        }
        fprintf(inter,"\n");
    }while(!feof(f));
    fclose(f);
    fclose(inter);
}

void main(){
    setInput();
    int reladdr,ea,startaddr;
    printf("Enter the relocation address : ");
    scanf("%x",&reladdr);

    FILE *obj,*memory;
    obj = fopen("obj.txt","r");
    memory = fopen("memory.txt","w+");
    char o[10];
    int count;
    fscanf(obj,"%s",o);
    if(strcmp(o,"H") == 0){
        fscanf(obj,"%s",o);
        fscanf(obj,"%x",&startaddr);
        fscanf(obj,"%s",o);
    }

    int s,x,add,codi;
    char val[10],temp[10];
    ea = reladdr-startaddr;

    do{
        fscanf(obj,"%s",o);
        if(strcmp(o,"T") == 0){
            fscanf(obj,"%x",&s);
            fscanf(obj,"%x",&count);
            count = count/3;
            
            for(int i=0;i<count;i++){
                fscanf(obj,"%s",o);
                fprintf(memory,"%x\t%s\n",s+ea,o);
                s += 3;
            }
        }

        if(strcmp(o,"M") == 0){
            fscanf(obj,"%x%s",&s,val);
            fseek(memory,0,SEEK_SET);
            x = s-1;
            do{
                fscanf(memory,"%x %s",&add,temp);
                if(x+ea == add){
                    fseek(memory,-1*strlen(temp),SEEK_CUR);
                    fscanf(memory,"%x",&codi);
                    fseek(memory,-1*strlen(temp),SEEK_CUR);
                    int l= strlen(temp);
                    codi = codi+ea;
                    fprintf(memory,"00%x",codi);
                    fseek(memory,0,SEEK_END);
                    break;
                }
            }while(!feof(memory));
        }
    }while(!feof(obj));
    fclose(obj);


    fseek(memory,0,SEEK_SET);
    do{
        count = 3;
        fscanf(memory,"%x %s",&add,temp);
        for(int i=0;i<count;i++){
            printf("%x\t%c%c\n",add+i,temp[(2*i)],temp[((2*i)+1)]);
        }
    }while(!feof(memory));
}