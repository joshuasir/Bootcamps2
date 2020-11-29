#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctime>
#define SIZE 2000
#include "../Models/Models.h"


int hashkey(char *str){
    unsigned long key =5381;
    int a;
    while(a=*str++){
        key=((key<<5)+key)+a;
    }
    return key%SIZE;
}
customer *createCustom(char *name){
    customer *newcust=(customer *)malloc(sizeof(customer));
    strcpy(newcust->name,name);
    newcust->ftail=newcust->fhead=NULL;
    newcust->next=newcust->prev=NULL;
    return newcust;
}
const char* detectOS() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN32
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}
const char* getDate(){
   time_t rawtime;
   struct tm *info;
   time( &rawtime );
   info = localtime( &rawtime );
   return asctime(info);
}
link *createDish(dish a){
    link *newdish=(link *)malloc(sizeof(link));
    strcpy(newdish->food.name,a.name);
    newdish->food.price=a.price;
    newdish->food.quant=a.quant;
    newdish->next=newdish->prev=NULL;
    return newdish;
}
void newCust(char *name){
    customer *newC=createCustom(name),*temp;
    int key=hashkey(name);
    if(tables[key]){
        temp=tables[key];
        while(temp->next){
            temp=temp->next;
        }
        temp->next=newC;
        newC->prev=temp;
    }else{
        tables[key]=newC;
    }
}
customer *findCust(char *name){
    int key=hashkey(name);
    if(tables[key]){
        customer *temp=tables[key];    
        while(temp->next&&strcmp(name,temp->name)){
            temp=temp->next;
        }
        if(!strcmp(name,temp->name)){
            return temp;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}
void deleteDish(link *toDel){
    if(head==tail){
        head=tail=NULL;
        free(head);
    }else if(head){
        if(toDel==head){
            head=head->next;
            head->prev=head->prev->next=NULL;
        }else if(toDel==tail){
            curr=tail;
            tail=tail->prev;
            tail->next=tail->next->prev=NULL;
        }else{
            toDel->prev->next=toDel->next;
            toDel->next->prev=toDel->prev;
            toDel->next=toDel->prev=NULL;
        }
        free(toDel);
        toDel=NULL;
    }
}
void addOrder(customer *temp,link *dish,int quant){
    if(temp&&dish&&dish->food.quant>=quant){
        if(!temp->fhead){
            link *newD=createDish(dish->food);
            newD->food.quant=quant;
            temp->fhead=temp->ftail=newD;
        }else{
        curr=temp->fhead;
        while(curr->next&&strcmp(curr->food.name,dish->food.name)){
            curr=curr->next;
        }
        if(!strcmp(curr->food.name,dish->food.name)){
            curr->food.quant+=quant;
        }else{
           link *newD=createDish(dish->food);
           newD->food.quant=quant;
           temp->ftail->next=newD;
           newD->prev=temp->ftail;
           temp->ftail=newD;
        }
        dish->food.quant-=quant;
        if(!dish->food.quant){
            deleteDish(dish);
        }
    }
}}
void deleteCust(customer *guy){
    int key=hashkey(guy->name);
    if(guy->next||guy->prev){

    if(!guy->next){
        guy->prev=guy->prev->next=NULL;
    }else if(!guy->prev){
        tables[key]=guy->next;
        guy->next=guy->next->prev=NULL;
    }else{
        guy->prev->next=guy->next;
        guy->next->prev=guy->prev;
        guy->prev=guy->next=NULL;
    }}else{
        tables[key]=NULL;
    }
    free(guy);
    guy=NULL;
}
void payment(customer *guy){
    if(guy){
    guy->fcurr=guy->fhead;
    int num=1,sum=0;
    while(guy->fcurr){
        printf("[%d] %s x%d\n",num,guy->fcurr->food.name,guy->fcurr->food.quant);
        sum+=(guy->fcurr->food.price*guy->fcurr->food.quant);
        num++;
        curr=guy->fcurr;
        guy->fcurr=guy->fcurr->next;
        if(guy->fcurr){
        guy->fcurr->prev=guy->fcurr->prev->next=NULL;}
        free(curr);
        curr=NULL;
    }
    printf("Total: Rp%d\n",sum);
    deleteCust(guy);}
}

void viewCust(){
    customer *temp;
    for(int i=0;i<SIZE;i++){
        if(tables[i]){
        temp=tables[i];
        while(temp){
            printf("%d. %s\n",i,temp->name);
            temp=temp->next;
        }}
    }
}
void newDish(dish a){
    link *newD=createDish(a);
    if(head){
    if(strcmp(newD->food.name,head->food.name)<=0){
        newD->next=head;
        head->prev=newD;
        head=newD;
    }else if(strcmp(newD->food.name,tail->food.name)>=0){
        tail->next=newD;
        newD->prev=tail;
        tail=newD;
    }else{
        curr=head;
        while(curr->next&&strcmp(curr->food.name,newD->food.name)<0){
            curr=curr->next;
        }
        newD->prev=curr->prev;
        newD->next=curr;
        curr->prev->next=newD;
        curr->prev=newD;
    }}else{
        head=tail=newD;
    }
}
link *findDish(char *name){
    if(head){
        curr=head;
        while(curr->next&&strcmp(curr->food.name,name)<0){
            curr=curr->next;
        }
        if(!strcmp(name,curr->food.name)){
            return curr;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}
void viewDish(){
    if(head){
    curr=head;
    char num='1';
    printf("        Bude's Menu\n===========================\n");
    printf("%-2s %-5s %-10s %-5s\n","No.","Name","Quantity","Price");
    
    while(curr){
        printf("%c.%-5s   %03d   Rp%d\n",num,curr->food.name,curr->food.quant,curr->food.price);
        curr=curr->next;
        num++;
    }
    printf("===========================\n");}
}

int valName(char *str){
    for(int i=0;i<strlen(str);i++){
        if(str[i]<'a'||str[i]>'z'){
            return 1;
        }
    }
    return 0;
}
int valcName(char *str){
    for(int i=0;i<strlen(str);i++){
        if(str[i]==' '){
            return 1;
        }
    }
    return 0;
}
void splashFile(){
    char str[255];
    FILE *ptr=fopen("../splash-screen.txt","r");
    if(ptr){
        while(fscanf(ptr,"%[^\n]\n",str)!=EOF){
            printf("%s\n",str);
        }
    }
    fclose(ptr);
}