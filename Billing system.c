#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void input();
void writefile();
void search();
void output();
struct date
{
    int month;
    int day;
    int year;
};
struct account
{
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
} customer;
int tl, sl, ts;
void main()
{
    int i, n;
    char ch;
    clrscr();
    _setcursortype(_NOCURSOR);
    printf(" CUSTOMER BILLING SYSTEM USING C BY OMPRAKASH AND VIGNESH \n\n");
    printf("**************************************************************\n");
    printf("\nPRESS 1 FOR ADD ACCOUNT ON LIST\n");
    printf("PRESS 2 FOR SEARCH CUSTOMER ACCOUNT\n");
    printf("PEESS 3 FOR QUIT\n");
    printf("\n**************************************************************\n");
    do
    {
        printf("\nSELECT WHAT DO YOU WANT TO DO?");
        ch = getche();
    } while (ch <= '0' || ch > '3');
    switch (ch)
    {
    case '1':
        clrscr();
        printf("\nHOW MANY CUSTOMER ACCOUNTS NEEDS TO STORE?");
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            input();
            if (customer.payment > 0)
                customer.acct_type = (customer.payment < 0.1 * customer.oldbalance) ? 'O' : 'D';
            else
                customer.acct_type = (customer.oldbalance > 0) ? 'D' : 'C';
            customer.newbalance = customer.oldbalance - customer.payment;
            writefile();
        }
        main();
    case '2':
        clrscr();
        printf("SEARCH BY ? \n");
        printf("\nPRESS 1 FOR SEARCH BY CUSTOMER NUMBER\n");
        printf("PRESS 2 SEARCH BY CUSTOMER NAME\n");
        search();
        ch = getche();
        main();
    case '3':
        clrscr();
        delay(700);
        textcolor(RED);
        gotoxy(25, 25);
        cprintf("\nPROJECT DONE BY OMPRAKASH ");
        delay(3000);
        exit(1);
    }
}
void input()
{
    FILE *fp = fopen("bidur.dat", "rb");
    fseek(fp, 0, SEEK_END);
    tl = ftell(fp);
    sl = sizeof(customer);
    ts = tl / sl;
    fseek(fp, (ts - 1) * sl, SEEK_SET);
    fread(&customer, sizeof(customer), 1, fp);
    printf("\nCUSTOMER NUMBER:%d\n", ++customer.number);
    fclose(fp);
    printf(" ACCOUNT NUMBER: ");
    scanf("%d", &customer.acct_no);
    printf("\n NAME: ");
    scanf("%s", customer.name);
    printf("\n MOBILE NUMBER: ");
    scanf("%f", &customer.mobile_no);
    printf(" STREET: ");
    scanf("%s", customer.street);
    printf(" CITY: ");
    scanf("%s", customer.city);
    printf(" PREVIOUS BALANCE: ");
    scanf("%f", &customer.oldbalance);
    printf(" CURRENT PAYMENT: ");
    scanf("%f", &customer.payment);
    printf(" PAYMENT DATE(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &customer.lastpayment.month, &customer.lastpayment.day, &customer.lastpayment.year);
    return;
}
void writefile()
{
    FILE *fp;
    fp = fopen("bidur.dat", "ab");
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
    return;
}
void search()
{
    char ch;
    char nam[100];
    int n, i, m = 1;
    FILE *fp;
    fp = fopen("bidur.dat", "rb");
    do
    {
        printf("\nENTER YOUR CHOICE: ");
        ch = getche();
    } while (ch != '1' && ch != '2');
    switch (ch)
    {
    case '1':
        fseek(fp, 0, SEEK_END);
        tl = ftell(fp);
        sl = sizeof(customer);
        ts = tl / sl;
        do
        {
            printf("\nCHOOSE CUSTOMER NUMBER: ");
            scanf("%d", &n);
            if (n <= 0 || n > ts)
                printf("\nENTER CORRECT\n");
            else
            {
                fseek(fp, (n - 1) * sl, SEEK_SET);
                fread(&customer, sl, 1, fp);
                output();
            }
            printf("\n\nNEED TO CONTINUE?(y/n): ");
            ch = getche();
        } while (ch == 'y');
        fclose(fp);
        break;
    case '2':
        fseek(fp, 0, SEEK_END);
        tl = ftell(fp);
        sl = sizeof(customer);
        ts = tl / sl;
        fseek(fp, (ts - 1) * sl, SEEK_SET);
        fread(&customer, sizeof(customer), 1, fp);
        n = customer.number;
        do
        {
            printf("\nENTER THE NAME: ");
            scanf("%s", nam);
            fseek(fp, 0, SEEK_SET);
            for (i = 1; i <= n; i++)
            {
                fread(&customer, sizeof(customer), 1, fp);
                if (strcmp(customer.name, nam) == 0)
                {
                    output();
                    m = 0;
                    break;
                }
            }
            if (m != 0)
                printf("\n\nDOESN'T EXIST\n");
            printf("\nANOTHER?(y/n)");
            ch = getche();
        } while (ch == 'y');
        fclose(fp);
    }
    return;
}
void output()
{
    printf("\n\n CUSTOMER NO :%d\n", customer.number);
    printf(" NAME :%s\n", customer.name);
    printf(" MOBILE NO :%.f\n", customer.mobile_no);
    printf(" ACCOUNT NUMBER :%d\n", customer.acct_no);
    printf(" STREET :%s\n", customer.street);
    printf(" CCITY :%s\n", customer.city);
    printf(" OLD BALANCE :%.2f\n", customer.oldbalance);
    printf(" CURRENT PAYMENT:%.2f\n", customer.payment);
    printf(" NEW BALANCE :%.2f\n", customer.newbalance);
    printf(" PAYMENT DATE :%d/%d/%d\n\n", customer.lastpayment.month, customer.lastpayment.day, customer.lastpayment.year);
    printf(" ACCOUNT STATUS :");
    textcolor(128 + RED);
    switch (customer.acct_type)
    {
    case 'C':
        cprintf("CURRENT\n\n");
        break;
    case 'O':
        cprintf("OVERDUE\n\n");
        break;
    case 'D':
        cprintf("DELINQUENT\n\n");
        break;
    default:
        cprintf("ERROR\\n\n");
    }
    textcolor(WHITE);
    return;
}
