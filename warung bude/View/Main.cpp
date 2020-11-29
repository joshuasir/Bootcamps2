#include "../Controller/Controller.h"

int main(){
    int choose,many;
    dish toAdd;
    customer alsoAdd;
    do{
    system("cls");
    printf("System: %s\n%s\n1. Add Dish\n2. Remove Dish\n3. Add Customer\n4. Search Customer\n5. View Warteg\n6. Order\n7. Payment\n8. Exit Warteg\n>>",detectOS(),getDate());
    scanf("%d",&choose);
    getchar();
    switch(choose){
        case 1:
        do{
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]",toAdd.name);
        getchar();
        }while(valName(toAdd.name)||findDish(toAdd.name));

        do{
        printf("Insert the price of the dish [1000...50000]: ");
        scanf("%d",&toAdd.price);
        getchar();
        }while(toAdd.price<1000||toAdd.price>50000);

        do{
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d",&toAdd.quant);
        getchar();
        }while(toAdd.quant<1||toAdd.quant>999);

        printf("The dish has been added!\nPress enter to continue...");
        getchar();
        newDish(toAdd);
        break;
        case 2:
        if(head){
        viewDish();
        do{
        printf("Insert dish's name to be deleted: ");
        scanf("%[^\n]",toAdd.name);
        getchar();
        }while(!findDish(toAdd.name));
        printf("The dish has been removed!\nPress enter to continue...\n");
        getchar();
        deleteDish(findDish(toAdd.name));}
        break;
        case 3:
        do{
        printf("Insert the customer's name[Without space]: ");
        scanf("%[^\n]",toAdd.name);
        getchar();}while(valcName(toAdd.name));
        printf("Customer has been added!\nPress enter to continue...\n");
        getchar();
        newCust(toAdd.name);
        break;
        case 4:
        printf("Insert the customer's name to be searched: ");
        scanf("%[^\n]",toAdd.name);
        getchar();
        if(findCust(toAdd.name)){
            printf("%s is available.\n",toAdd.name);
        }else{
            printf("%s is not present.\n",toAdd.name);
        }
        printf("Press enter to continue...\n");
        getchar();
        break;
        case 5:
        printf("Customer's List\n");
        viewCust();
        printf("Press enter to continue...\n");
        getchar();
        break;
        case 6:
        do{
        printf("Insert the customer's name: ");
        scanf("%[^\n]",alsoAdd.name);
        getchar();}while(!findCust(alsoAdd.name));
        printf("Insert the amount of dish: ");
        scanf("%d",&many);
        getchar();
        for(int i=1;i<=many;i++){
            printf("[%d] Insert the dish's name and quantity: ",i);
            scanf("%[^x]x%d",toAdd.name,&toAdd.quant);
            getchar();
            toAdd.name[strlen(toAdd.name)-1]='\0';
            if(findDish(toAdd.name)&&findDish(toAdd.name)->food.quant>=toAdd.quant){
                addOrder(findCust(alsoAdd.name),findDish(toAdd.name),toAdd.quant);
            }else{
                i--;
            }
        }
        printf("Order success!\nPress enter to continue...\n");
        getchar();
        break;
        case 7:
        do{
        printf("Insert the customer's name: ");
        scanf("%[^\n]",toAdd.name);
        getchar();}while(!findCust(toAdd.name));
        payment(findCust(toAdd.name));
        printf("Press enter to continue...\n");
        getchar();
        break;
        case 8:
        printf("Please expand your terminal to fullscreen!\nPress enter to continue...\n");
        getchar();
        splashFile();
    }
    }while(choose!=8);
}