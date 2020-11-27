#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Models/Models.h"
#include "../Controller/Controller.h"

int main(){
    int cureT,patientT;
    link *head;
   patient toAdd;
    scanf("%d %d",&patientT,&cureT);
    getchar();
   while(patientT--){
       do{
        scanf("%d %s %d - %[^\n]",&toAdd.date,toAdd.vmonth,&toAdd.year,toAdd.name);
        getchar();}while(!parseInt(toAdd.vmonth));
        head=push(toAdd,head);
    }
    while(head&&cureT--){
        head=pop(head);
    }
    if(!head){
        printf("All patients get the cure, %d cure left\n",cureT);
    }else{
        printf("Need %d more cure\n",patientT);
        printAll(head);
    }
    while(head){
        head=pop(head);
    }
    return 0;
}
