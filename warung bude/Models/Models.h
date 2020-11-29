struct dish{
char name[255];
int price,quant;
};

struct link{
    dish food;
    link *next,*prev;
}*head,*tail,*curr;

struct customer{
    link *fhead,*ftail,*fcurr;
    char name[255];
    customer *next,*prev;
}*tables[SIZE];
