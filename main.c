#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
#include "functions.h"

int main()
{
    int i=0;
    user u[100];
    book b[100];
char o1[10];
    int No_of_books = Load(b) ;
    FILE *f1=fopen("credentials.txt","a");
    fclose(f1);
    f1=fopen("credentials.txt","r");
    if(f1!=NULL)
    {
        while(!feof(f1))
        {
            fscanf(f1,"%s%s",u[i].name,u[i].pass);
            i++;
        }
    }
    else
    {
        printf("FILE NOT FOUND !");
        return;
    }
    fclose(f1);
    printf("1.LOGIN\n");
    SetColor(12);
    printf("2.QUIT\n");
    SetColor(15);
    do{
        printf("Please choose a valid option: ");
        gets(o1);
    }while(strcmp(o1,"1")!=0&&strcmp(o1,"2")!=0);
    if(strcmp(o1,"1")==0)
      {Login(i,u);
        menu(No_of_books,b);}

    else if (strcmp(o1,"2")==0) exit(1);

}

void Login(int i,user u[i])
{
    int j;
    char un[40],psw[10];
    int pass=0;

        printf("Please enter username: ");
        gets(un);
        printf("Please enter password: ");
        gets(psw);
        for(j=0; j<i; j++)
        {
            if(strcmp(un,u[j].name)==0)
            {
                if(strcmp(psw,u[j].pass)==0)
                {
                    pass=1;
                    system("cls");
                    SetColor(10);
                    printf("Login successful!\n\n");
                    SetColor(15);

                }
            }
        }if (pass==0)
        { SetColor(12);
        system("cls");
        printf("Please enter valid data!\n");
        SetColor(15);
      main();}
    }
