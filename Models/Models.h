
struct patient{
    char name[255];
    char vmonth[255];
    int date,year,month;
};

struct link{
    patient zero;
    link *next,*prev;
};
