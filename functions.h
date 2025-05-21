#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <string.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        wColor=(csbi.wAttributes&0xF0)+(ForgC&0x0F);
        SetConsoleTextAttribute(hStdOut,wColor);
    }
    return;
}
char month[12][20]= {"January","February","March","April","May","June","July","August","September","October","November","December"};
typedef struct
{
    char name[40];
    char pass[10];
} user;
typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char ISBN [14];
    char title [100];
    char Author_name [30];
    int quantity;
    float price;
    date publish_date;
} book;




int Load ( book b[100])
{
    int i=0,No_of_books;

    FILE *f2;
    f2=fopen("books.txt","a");
    fclose(f2);
    f2=fopen("books.txt","r");
    if(f2!=NULL)
    {
        while(!feof(f2))
        {
            fscanf(f2,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n",b[i].ISBN,b[i].title,b[i].Author_name,&b[i].quantity,&b[i].price,&b[i].publish_date.month,&b[i].publish_date.year);
            i++;
        }
    }
    else
    {
        SetColor(4);
        printf("FILE NOT FOUND!");
        SetColor(15);
        return;
    }
    No_of_books = i;
    return No_of_books;
}
void Search_ISBN(int No_of_books,  book b[No_of_books])
{
    int i,flag=0;
    char isbn[100];
    getchar();
    SetColor(11);
    printf("Please enter a valid ISBN for the required book: ");
    SetColor(15);
    gets(isbn);
    if(isvalid(isbn,3))
    {
        for(i=0; i<No_of_books; i++)
        {
            int z;
            if(strcmp(isbn,b[i].ISBN)==0)
            {
                printf("ISBN:%s\n",isbn);
                printf("Title:%s\n",b[i].title);
                printf("Author:%s\n",b[i].Author_name);
                printf("Quantity:%d\n",b[i].quantity);
                printf("Price:%0.2f$\n",b[i].price);
                z=b[i].publish_date.month;
                printf("Published:%s %d\n",month[z-1],b[i].publish_date.year);
                printf("-----------------------\n");

                flag=1;

            }
        }
    }
    if (flag==0)
    {
        SetColor(12);
        printf("NO MATCHES FOUND!\n\n");
        SetColor(15);
    }

}
void AdvSearch(int No_of_books, book b[No_of_books])
{
    int i;
    char keyword [50];
    char *p;
    int flag=0;
    SetColor(11);
    printf("Please enter a keyword: ");
    SetColor(15);
    scanf("%s",keyword);


    for(i = 0 ; i < No_of_books ; i++)
    {
        p=strstr(b[i].title,keyword);
        if(p)
        {
            int z;
            printf("ISBN:%s\n", b[i].ISBN);
            printf("Title:%s\n",b[i].title);
            printf("Author:%s\n",b[i].Author_name);
            printf("Quantity:%d\n",b[i].quantity);
            printf("Price:%0.2f$\n",b[i].price);
            z=b[i].publish_date.month;
            printf("Published:%s %d\n",month[z-1],b[i].publish_date.year);
            printf("-------------------------------\n");
            flag=1;
        }
    }
    if (flag == 0)
    {
        SetColor(12);
        printf("No matches are found !\n\n");
        SetColor(15);
    }
}
void menu(int No_of_books,  book b[No_of_books])
{
    char no[25];
    int flag=0;
    do
    {
        SetColor(13);
        printf("Select one of the following:\n");
        SetColor(15);
        printf("1.ADD\n2.DELETE\n3.MODIFY\n4.SEARCH\n5.ADVANCED SEARCH\n6.PRINT\n7.SAVE\n8.QUIT\n");
        SetColor(11);
        printf("Please enter the desired option number: ");
        SetColor(15);
        scanf("%s",no);
        system("cls");
        if(strcmp(no,"1")==0)
        {
            No_of_books = Add(No_of_books, b);
            menu(No_of_books, b);
        }
        else if (strcmp(no,"2")==0)
        {
            No_of_books=delete_book(No_of_books,b);
            menu(No_of_books, b);
        }
        else if (strcmp(no,"3")==0)
        {
            modify(No_of_books, b);
            menu(No_of_books, b);
        }
        else if(strcmp(no,"4")==0)
        {
            Search_ISBN(No_of_books,b);
            menu(No_of_books, b);
        }
        else if(strcmp(no,"5")==0)
        {
            AdvSearch(No_of_books, b);
            menu(No_of_books, b);
        }
        else if(strcmp(no,"6")==0)
        {
            Print(No_of_books, b);
            menu(No_of_books, b);

        }
        else if (strcmp(no, "7") == 0)
        {
            save(No_of_books, b);
            menu(No_of_books, b);
        }
        else if(strcmp(no,"8")==0)
        {
            quit(No_of_books, b);
        }
        else
        {
            SetColor(12);
            printf("Please enter a valid option! \n\n");
            SetColor(15);
            flag=1;

        }

    }
    while(flag==1);
}
void Print(int No_of_books, book b[No_of_books])
{
    int flag = 0, i,z;
    char op[25];
    printf("1.Data sorted by TITLE\n");
    printf("2.Data sorted by DATE\n");
    printf("3.Data sorted by PRICE\n\n");
    getchar();
    while(!flag)
    {
        SetColor(11);
        printf("Please choose a valid option :");
        SetColor(15);
        gets(op);
        if (strcmp(op, "1") == 0)
        {
            flag = 1;
            system("cls");
            SetColor(3);
            printf("BOOKS SORTED BY TITLE ASCENDINGLY: \n");
            SetColor(15);
            sort_by_title(No_of_books, b);
        }
        else if (strcmp(op, "2") == 0)
        {
            system("cls");
            SetColor(3);
            printf("BOOKS SORTED BY DATE FROM NEWEST TO OLDEST: \n");
            SetColor(15);
            flag = 1;
            sort_by_date(No_of_books, b);
        }
        else if (strcmp(op, "3") == 0)
        {
            flag = 1;
            system("cls");
            SetColor(3);
            printf("BOOKS SORTED BY PRICE FROM CHEAPEST TO MOST EXPENSIVE: \n");
            SetColor(15);
            sort_by_price(No_of_books, b);
        }
    }
    for ( i = 0 ; i < No_of_books ; i++)
    {
        printf("\n");
        printf("ISBN:%s\n",b[i].ISBN);
        printf("Title:%s\n",b[i].title);
        printf("Author:%s\n",b[i].Author_name);
        printf("Quantity:%d\n",b[i].quantity);
        printf("Price:%0.2f$\n",b[i].price);
        z=b[i].publish_date.month;
        printf("Published:%s %d\n",month[z-1],b[i].publish_date.year);
        printf("-----------------------\n");

    }
}
void sort_by_title(int No_of_books,  book b[No_of_books])
{
    int pass, i, sorted = 0;
    book temp;
    for (pass = 1;pass < No_of_books && !sorted ; pass ++)
    {
        sorted = 1;
        for ( i = 0 ; i < No_of_books - pass ; i ++)
        {
            if (strcmp(b[i].title, b[i + 1].title) == 1)
            {
                temp = b[i];
                b[i] =  b[i + 1];
                b[i + 1] = temp ;
                sorted = 0;
            }
        }
    }
}
void sort_by_date(int No_of_books,  book b[No_of_books])
{
    int pass, j, sorted = 0;
    book temp;
    for (pass = 1 ; pass < No_of_books&& !sorted  ; pass ++)
    {
        sorted = 1;
        for ( j = 0 ; j < No_of_books - pass ; j ++)
        {
            if (b[j].publish_date.year < b[j + 1].publish_date.year)
            {
                temp = b[j];
                b[j] =  b[j + 1];
                b[j + 1] = temp ;
                sorted = 0;
            }
            else if (b[j].publish_date.year == b[j + 1].publish_date.year)
            {
                if (b[j].publish_date.month < b[j + 1].publish_date.month)
                {
                    temp = b[j];
                    b[j] =  b[j + 1];
                    b[j + 1] = temp ;
                    sorted = 0;
                }
            }
        }
    }
}
void sort_by_price(int No_of_books,  book b[No_of_books])
{
    int pass, j, sorted = 0;
    book temp;
    for (pass = 1 ; pass < No_of_books&& !sorted  ; pass ++)
    {
        sorted = 1;
        for ( j = 0 ; j < No_of_books - pass ; j ++)
        {
            if (b[j].price > b[j + 1].price)
            {
                temp = b[j] ;
                b[j] = b[j + 1];
                b[j + 1] = temp ;
                sorted = 0;
            }
        }
    }
}
void quit(int No_of_books,  book b[No_of_books])
{
    char ans[25];
    SetColor(12);
    printf("WARNING!\n");
    SetColor(15);
    printf("Your data will not be saved if you want to quit\nDo you want to continue ?\n1.YES\n2.NO and Return\n");
    do
    {
        printf("Choose a valid option: ");
        scanf("%s", ans);
    }
    while (strcmp(ans, "1") != 0 && strcmp(ans, "2") != 0);
    if (strcmp(ans, "1") == 0)
        exit(1);
    else menu(No_of_books, b);
}
int isvalid(char m[100], int n)
{
    int i,x, l,flag=0;
    for(i = 0 ; i < strlen(m);  i++)
    {
        if(!isdigit(m[i]))
            return 0;
    }
    if(n == 1)
    {
        x = atoi(m);
        if(x >= 1 && x <= 12)
            return 1;
        else
            return 0;
    }
    else if (n == 2)
    {
        x = atoi(m);
        if(x > 0 && x <= 2022)
            return 1;
        else
            return 0;
    }
    else if (n == 3)
    {
        l = strlen(m);
        if (l == 13)
            return 1;
        else
            return 0;
    }
    else if(n==4)
    {
int pass=0;
        for(i=0; i<strlen(m); i++)
        {
            if(isdigit(m[i]))
           {
               pass=1;
           }
            else break;

        }
         if(pass==0)
         return 0;
         else return 1;
    }

}

void save(int No_of_books, book b[No_of_books])
{
        int i;
        FILE *f1;
        f1=fopen("books.txt","w");
        for(i=0; i<No_of_books; i++)
        {
            fprintf(f1,"%s,%s,%s,%d,%.2f,%d-%d\n",b[i].ISBN,b[i].title,b[i].Author_name,b[i].quantity,b[i].price,b[i].publish_date.month,b[i].publish_date.year);
        }
        fclose(f1);
        SetColor(10);
        printf("YOUR DATA IS SAVED SUCCESSFULLY!\n\n");
        SetColor(15);
}
void modify(int no_of_books, book b[no_of_books])
{
        int i,flag=0;
        char str[100],mo[50],ye[50],q[10];

        printf("Enter a valid ISBN of book to be modified: ");
        scanf("%s",str);
        if(!isvalid(str,3))
            {
            SetColor(12);
            printf("NO MATCHES ARE FOUND! \n\n");
            SetColor(15);
            }
            else
                {
        for(i=0; i<no_of_books; i++)
        {
            if(strcmp(b[i].ISBN,str)==0)
            {
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            SetColor(12);
            printf("NO MATCHES ARE FOUND!\n\n");
            SetColor(15);
        }
        else
        {
            printf("Enter modified title: ");
            getchar();
            gets(b[i].title);
            printf("Enter modified author name: ");
            gets(b[i].Author_name);
        do{
                printf("Enter modified quantity: ");
                gets(q);
           } while(!isvalid(q,4));
            b[i].quantity=atoi(q);
            printf("Enter modified price: ");
            scanf("%f",&b[i].price);
            getchar();
            do
            {
                printf("Enter publication date:\nEnter month: ");
                gets(mo);
                printf("Enter year: ");
                gets(ye);
            }while(!isvalid(mo, 1) || !isvalid(ye, 2));
            SetColor(10);
            printf("BOOK IS MODIFIED SUCCESSFULLY!\n\n");
            SetColor(15);
        }
                }

}
int delete_book(int No_of_books,book b[No_of_books])
{
        int flag=1,i,l,j;
        char isbn[100];
        getchar();
        printf("please enter a valid ISBN :");
        gets(isbn);
        if(isvalid(isbn, 3))
        {
            for(i=0; i<No_of_books; i++)
            {
                if(strcmp(b[i].ISBN,isbn)==0)
                {
                    for(j=i; j<No_of_books-1; j++)
                    {
                        strcpy( b[j].ISBN, b[j+1].ISBN);
                        strcpy( b[j].title, b[j+1].title);
                        strcpy( b[j].Author_name, b[j+1].Author_name);
                        b[j].quantity=b[j+1].quantity;
                        b[j].price=b[j+1].price;
                        b[j].publish_date.month = b[j+1].publish_date.month;
                        b[j].publish_date.year = b[j+1].publish_date.year;
                    }
                    No_of_books--;
                    flag=0;
                    break;
                }
            }
        }

        if(!flag)
        {
            SetColor(10);
            printf("book deleted succesfully \n");
            SetColor(15);
        }
        else
        {
            SetColor(12);
            printf ("No matches are found!\n");
            SetColor(15);
            printf("\n");
        }
        int x=No_of_books;
        return x;
}
int Add(int No_of_books,book b[No_of_books])
{
        int i=0,flag=0,l;
        char isbn [15],mo[50],ye[50];
        SetColor(11);
        printf("Please enter book details: \n\n");
        SetColor(15);
        getchar();
        do
        {
            printf("Please enter a valid ISBN: ");
            gets(isbn);
        }while(!isvalid(isbn, 3));
        for(i=0; i<No_of_books; i++)
        {
            if(strcmp(b[i].ISBN,isbn)==0)
            {
                (b[i].quantity)++;
                flag=1;
                SetColor(10);
                printf("Book quantity increased\n\n");
                SetColor(15);
                break;
            }
        }
        if(flag==0)
        {
            b[No_of_books].quantity=1;
            strcpy(b[No_of_books].ISBN,isbn);
            printf("Enter title: ");
            gets(b[No_of_books].title);
            printf("Enter author name: ");
            gets(b[No_of_books].Author_name);
            printf("Enter price: ");
            scanf("%f", &b[No_of_books].price);
            getchar();
            do
            {
                printf("Enter publication date:\nEnter month: ");
                gets(mo);
                printf("Enter year: ");
                gets(ye);
            }while(!isvalid(mo, 1) || !isvalid(ye, 2));
            b[No_of_books].publish_date.month = atoi(mo);
            b[No_of_books].publish_date.year = atoi(ye);
            No_of_books++;
            SetColor(10);
            system("cls");
            printf("BOOK ADDED SUCCESSFULY !\n\n");
            SetColor(15);
        }
        return No_of_books;
}

#endif // FUNCTIONS_H_INCLUDED
