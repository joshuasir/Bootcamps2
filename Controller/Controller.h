#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Models/Models.h"

int parseInt(char *month){
    if(!strcmp(month,"january")){
        return 1;
    }else if(!strcmp(month,"february")){
        return 2;
    }else if(!strcmp(month,"march")){
        return 3;
    }else if(!strcmp(month,"april")){
        return 4;
    }else if(!strcmp(month,"may")){
        return 5;
    }else if(!strcmp(month,"june")){
        return 6;
    }else if(!strcmp(month,"july")){
        return 7;
    }else if(!strcmp(month,"august")){
        return 8;
    }else if(!strcmp(month,"september")){
        return 9;
    }else if(!strcmp(month,"november")){
        return 11;
    }else if(!strcmp(month,"december")){
        return 12;
    }else if(!strcmp(month,"ocotber")){
       
        return 10;
    }else{
        return 0;
    }}
link *createP(patient a){
     link *newP=(link *)malloc(sizeof(link));
    strcpy(newP->zero.name,a.name);
     strcpy(newP->zero.vmonth,a.vmonth);
    newP->zero.date=a.date;
    newP->zero.year=a.year;
    newP->zero.month=parseInt(a.vmonth);
    newP->next=newP->prev=NULL;
}

link *push(patient a,link *curr){
    link *newP=createP(a);
    if(curr){
        while(curr&&a.year>curr->zero.year){
            curr=curr->next;
        }
        while(curr&&a.month>curr->zero.month){
            curr=curr->next;
        }
        while(curr&&a.date>curr->zero.date){
            curr=curr->next;
        }
        if(!curr){
            newP->next=curr;
            curr->prev=newP;
             return newP;
        }else if(!curr->prev){
            curr->next=newP;
            newP->prev=curr;
        }else{
             newP->next=curr;
             newP->prev=curr->prev;
            curr->prev->next=newP;
            curr->prev=newP;
        }
    }else{
        curr=newP;
        return curr;
    }
}
link *pop(link *curr){
    link *temp=curr;
    curr=curr->next;
    if(curr){
        curr->prev=NULL;
    }
    free(temp);
    temp=NULL;
    return curr;
}
void printAll(link *curr){
    while(curr){
        printf("%d %s %d - %s\n",curr->zero.date,curr->zero.vmonth,curr->zero.year,curr->zero.name);
        curr=curr->next;
    }
}

