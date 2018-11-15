#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct userdb
{
    int score;
    int no_of_ques;
    char uname[15];
}getuser={0,0,"NULL"},f_user;

void practice(FILE *);        //done
void showstats(FILE *); //done
void leaderboard(void);  // done
int match(int);            //done
int scoreupdate(FILE *);   //done
void showques(void);        //done
void showans(void);     //done
void welcome(void);     //done
FILE* login(void);  //done
FILE *getpos(void); //done

char username[15];
int qnum=0;

int main()
{
    int choice;
    char flag='y';
    FILE *pos;
    system("rm sol.c;rm sol;rm output.txt;touch userdata.dat");
    system("clear");
    welcome();
    pos=login();
    showstats(pos);
    do{
        printf("\n\n 1.) Practice\n "
                "2.) Show Leaderboard\n "
                "3.) Logout\n "
                "0.) Exit\n\n "
                "Your Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: practice(pos);
                    break;
            case 2: leaderboard();
                    break;
            case 3: main();
                    break;
            case 4: return 0;
            default: printf(" Incorrect Input!!!\n");
        }
 /*       printf("\n Want to continue?(y/n): ");
        scanf("%c",&flag);*/
    }while(1);
    return 0;
}

void practice(FILE *pos)
{
    char ch='y';
    int choice,val,comp=0,exec=0;
        printf("\n File ptr in practice beg: %ld\n",ftell(pos));
        showques();
        printf("\n !!!---Press enter to open nano text editor---!!!\n");
        getchar();
        getchar();
        system("nano sol.c");
    do{
        printf("%s","\n 1.) View question again\n "
                        "2.) Open text editor again\n "
                        "3.) Compile\n "
                        "4.) Run with custom input\n "
                        "5.) Submit your code\n "
                        "6.) Show answer\n "
                        "0.) Go Back\n\n "
                        "Your Choice: ");
        scanf("%d",&choice);
        pos=getpos();
        printf("\n File ptr in practice do while: %ld\n",ftell(pos));
        switch(choice)
        {
            case 1: showques();
                    break;
            case 2: system("nano sol.c");
                    break;
            case 3: val=system("gcc sol.c -o sol");
                    if(!val)
                    {
                        printf("\n Compilation Successful.\n");
                        comp=1;
                    }
                    else
                    {
                        printf("\n GCC returned error %d.\n Compilation unsuccessful.\n",val);
                        comp=0;
                    }
                    break;
            case 4: 
                    if(!comp)
                    {
                        printf("\n You need to successfully compile your program first!!!");
                        exec=0;
                    }
                    else
                    {
                        printf("\n Provide your Input here(if any).\n\n");
                        val=system("./sol");
                        if(val)
                        {
                            printf("\n Execution unsuccessful.\n Error %d.\n",val);
                            exec=0;
                        }
                        else
                        {
                            printf("\n Executed successfull!!!");
                            exec=1;
                        }
                    }
                    break;
            case 5: if(exec==1 || comp==1)
                    {
                        system("./sol > output.txt"); 
                        val=match(qnum);
                        if(!val)
                        {
                            printf("\n Answer matched!!!");
                            if(!scoreupdate(pos))
                                printf("\n Score Updated!");
                            qnum++;
                        }
                    }
                    else
                    {
                        printf("\n You should at least try to compile your program first!!!");
                    }
                    break;
            case 6: showans();
                    break;
            case 0: return ;
            default: printf("\n Please provide a valid input.");
        }
    }while(1);
}

FILE* login(void)
{
    int flag=0,i=0;
    FILE *fptr;
    char readname[15];
  /*  printf(" Enter username: ");
    getchar();
    scanf("%[^\n]s",readname);      */
    printf("\n\n Enter Username: ");

    scanf("%s",readname);
  //                                  printf("\n read string : %s",readname);

    strcpy(getuser.uname,readname);
 //                                  printf("\ncopied to getuser.uname");
    fptr=fopen("userdata.dat","r+b");
    while(!feof(fptr))
    {
        fread(&f_user,sizeof(f_user),1,fptr);
        if(!strcmp(f_user.uname,getuser.uname))
        {
            printf("\n Welcome Back %s\n",getuser.uname);
            flag=1;
            break;
        }
    }
    if(!flag)
    {
     //   fwrite(&getuser,sizeof(getuser),1,fptr);
        fwrite(&getuser,sizeof(getuser),1,fptr);
        printf("\n New Profile created!!\n");
    }
    fseek(fptr,-sizeof(getuser),SEEK_CUR);
    return fptr;
}

void leaderboard(void)
{
    FILE *readptr;
    char exp_level[13];
    readptr=fopen("userdata.dat","rb");
    printf(" Name\t\tScore\tExp Level\tQuestions\n");
    while(fread(&f_user,sizeof(f_user),1,readptr))
    {
        switch(f_user.no_of_ques)
        {
            case 0: strcpy(exp_level,"Unranked"); break;
            case 1: strcpy(exp_level,"Beginner"); break;
            case 2: strcpy(exp_level,"Intermediate"); break;
            case 3: strcpy(exp_level,"Advanced"); break;
            case 4: strcpy(exp_level,"Ace"); break;
            default: strcpy(exp_level,"Legendary"); break;
        }
        printf("\n %s\t\t%d\t%s\t\t%d",f_user.uname,f_user.score,exp_level,f_user.no_of_ques);
    }
    fclose(readptr);
}


int scoreupdate(FILE *pos)
{
    FILE *fptr;
    fptr=fopen("userdata.dat","r+b");
    fptr=pos;
    printf("\n File ptr in scoreupd: %ld\n",ftell(fptr));
//    fseek(fptr,-sizeof(f_user),SEEK_CUR);
    fread(&f_user,sizeof(f_user),1,fptr);
    f_user.score+=10;
    f_user.no_of_ques+=1;
    fseek(fptr,-sizeof(f_user),SEEK_CUR);
    fwrite(&f_user,sizeof(f_user),1,fptr);
    fclose(fptr);
    return 0;
}

FILE *getpos()
{
    FILE *fptr;
    fptr=fopen("userdata.dat","r+b");
    while(!feof(fptr))
    {
        fread(&f_user,sizeof(f_user),1,fptr);
        if(!strcmp(f_user.uname,getuser.uname))
        {
            break;
        }
    }
    fseek(fptr,-sizeof(getuser),SEEK_CUR);
    return fptr;  
}

int match(int solnum)
{
    int ret;
    switch(solnum)
    {
        case 0: ret=system("diff -Z output.txt s0.txt");
                break;
        case 1: ret=system("diff -Z output.txt s1.txt");
                break;
        case 2: ret=system("diff -Z output.txt s2.txt");
                break;
        case 3: ret=system("diff -Z output.txt s3.txt");
                break;
        case 4: ret=system("diff -Z output.txt s4.txt");
                break;
        default: printf("\n Limit Exceeded!!\n");
    }
    return ret;
}

void showques()
{
    switch(qnum)
    {
        case 0: system("cat q0.txt");
                break;
        case 1: system("cat q1.txt");
                break;
        case 2: system("cat q2.txt");
                break;
        case 3: system("cat q3.txt");
                break;
        case 4: system("cat q4.txt");
                break;
        default: printf("\n Sorry we do not have anymore questions for you!!\n");
    }
}

void showans(void)
{
    switch(qnum)
    {
        case 0: system("firefox https://www.programiz.com/c-programming/examples/print-sentence");
                break;
        case 1: system("firefox https://www.programiz.com/c-programming/examples/print-integer");
                break;
        case 2: system("firefox https://www.programiz.com/c-programming/examples/factorial");
                break;
        case 3: system("cat q3.txt");
                break;
        case 4: system("cat q4.txt");
                break;
        default: printf("\n Sorry we do not have anymore questions for you!!\n");
    }
}

void showstats(FILE *pos)
{
    char exp_level[13];
    FILE *fptr;
    fptr=fopen("userdata.dat","rb");
    fptr=pos;
    fread(&f_user,sizeof(f_user),1,fptr);
    switch(f_user.no_of_ques)
    {
        case 0: strcpy(exp_level,"Unranked"); break;
        case 1: strcpy(exp_level,"Beginner"); break;
        case 2: strcpy(exp_level,"Intermediate"); break;
        case 3: strcpy(exp_level,"Advanced"); break;
        case 4: strcpy(exp_level,"Ace"); break;
        default: strcpy(exp_level,"Legendary"); break;
    }
    qnum=f_user.no_of_ques;
    printf("\n Username: %s\n Questions solved: %d\n Score: %d\n Programmer Level: %s\n\n",f_user.uname,f_user.no_of_ques,f_user.score,exp_level);
    fclose(fptr);
}

void welcome(void)
{
    printf("\t##  ##  ###### ##      ##   #####  #####  #####   ######\n"
           "\t## ##   ##       ##  ##    ##     ##    # ##   #  ##    \n"
           "\t###     ####       ##      ##     ##    # ##    # ####  \n"
           "\t## ##   ##         ##      ##     ##    # ##   #  ##    \n" 
           "\t##  ##  ######     ##       #####  #####  #####   ######\n");
}
