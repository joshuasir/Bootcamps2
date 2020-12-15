#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	node *alph[95];
	int isComplete;
};
node *addNode(){
	node *toAdd=(node *)malloc(sizeof(node));
	toAdd->isComplete=0;
	for(int i=0;i<95;i++){
		toAdd->alph[i]=NULL;
	}	
	return toAdd;
}

void addWord(char *str,node *curr){

	for(int i=0;i<strlen(str);i++){
		if(!curr->alph[str[i]-31]){
			curr->alph[str[i]-31]=addNode();
		}
		curr=curr->alph[str[i]-31];	
	}
	if(curr->isComplete){
		printf("Already added!\n");
	}else{
		printf("Successfully added!\n");
		curr->isComplete=1;
	}
}

void delWord(char *str,node *curr){

	for(int i=0;i<strlen(str);i++){
		if(!curr->alph[str[i]-31]){
			printf("Unavailable!\n");
			return;
		}
		curr=curr->alph[str[i]-31];	
	}
	if(curr->isComplete){
		curr->isComplete=0;
		printf("Successfully deleted!\n");
	}else{
		printf("Unavailable!\n");
	}
	
}


int main(){
	int many,choose;
	char text[255];
	node *root=addNode();
	scanf("%d",&many);
	getchar();
	while(many--){
	scanf("%[^\n]",text);
	getchar();
	do{
	printf("1. add word\n2. delete word\n>>");
	scanf("%d",&choose);
	getchar();
	switch(choose){
		case 1:
			addWord(text,root);
		break;
		case 2:
			delWord(text,root);
	}
	}while(choose<1||choose>2);
	getchar();
	text[0]='\0';
	}
	
}
