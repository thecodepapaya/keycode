#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct userdb
{
    int score;
    int no_of_ques;
    int exp_level;
    char uname[15];
}getuser={0,0,0,"NULL"},f_user;

void practice(FILE *);        //done
void showstats(FILE *); //done
void leaderboard(void);
void acheivements(void);                    
int match(void);            //done
int scoreupdate(FILE *);   //done
void showques(void);        //dones
void showans(void);     //done
void welcome(void);     //done
FILE* login(void);  //done
void updatestats(FILE*);

char username[15];

int main()
{
    int choice;
    char flag='y';
    FILE *pos;
    system("clear");
    welcome();
    pos=login();
    showstats(pos);
    do{
        printf(" 1.) Practice\n "
                "2.) Show Leaderboard\n "
                "3.) Your Acheivements\n "
                "4.) Logout\n "
                "5.) Exit\n\n "
                "Your Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: practice(pos);
                    break;
            case 2: leaderboard();
                    break;
            case 3: acheivements();
                    break;
            case 4: main();
                    break;
            case 5: return 0;
            default: printf(" Incorrect Input!!!\n");
                     break;
        }
        printf("\n Want to continue?(y/n): ");
        scanf("%c",&flag);
    }while(flag=='y' || flag=='Y');
    return 0;
}

void practice(FILE *pos)
{
    char ch='y';
    int choice,val,comp,exec;
    
        showques();
        printf("\n !!!---Press enter to open nano text editor.---!!!\n");
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
                        "0.) Exit\n\n "
                        "Your Choice: ");
        scanf("%d",&choice);
        comp=0;
        exec=0;
        switch(choice)
        {
            case 1: showques();
                    break;
            case 2: system("nano sol.c");
                    break;
            case 3: val=system("gcc sol.c -o sol");
                    if(val)
                    {
                        printf("\n GCC returned error %d.\n Compilation unsuccessful.\n",val);
                    }
                    else
                    {
                        comp=1;
                    }
                    break;
            case 4: printf("\n Provide your Input here(if any).\n\n");
                    val=system("sol");
                    if(!comp)
                    {
                        printf("\n You need to successfully compile your program first!!!");
                    }
                    else
                    {
                        if(val)
                        {
                            printf("\n Execution unsuccessful.\n Error %d.\n",val);
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
                        system("sol > output.txt"); 
                        val=match();
                        if(!val)
                        {
                            printf("\n Answer matched!!!");
                            if(!scoreupdate(pos))
                                printf("\n Score Updated!");

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
    int flag=0;
    FILE *fptr;
    char readname[15];
  /*  printf(" Enter username: ");
    getchar();
    scanf("%[^\n]s",readname);      */
    printf("\n\n Enter Username: ");
    getchar();
    scanf("%[^\n]s",getuser.uname); 
    fptr=fopen("userdata.dat","ab+");
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
        fwrite(&getuser,sizeof(getuser),1,fptr);
        printf("\n New Profile created!!\n");
    }
    fseek(fptr,-sizeof(getuser),SEEK_CUR);
    return fptr;
}
/*
void leaderboard(void)
{
    FILE *fptr;
    fptr=fopen("userdata.dat","rb");
    while(fptr!=NULL)
    {
        fread(&f_user,sizeof(f_user),1,fptr);

    }
}
*/

int scoreupdate(FILE *pos)
{
    FILE *fptr;
    fptr=fopen("userdata.dat","rtb");
    fptr=pos;
    fread(&f_user,sizeof(f_user),1,fptr);
    f_user.score+=10;
    fseek(fptr,-sizeof(f_user),SEEK_CUR);
    fwrite(&f_user,sizeof(f_user),1,fptr);
    fclose(fptr);
    return 0;
}

void leaderboard(void)
{
    printf("\n Oops! This function is currently under development!");
}

void acheivements(void)
{
    printf("\n Oops! This function is currently under development!");
}


int match(void)
{
    int ret;
    ret=system("diff output.txt solution.txt");
    return ret;
}

void showques(void)
{
    system("cat question.txt");
}

void showans(void)
{
    system("firefox https://www.hackerrank.com/domains/c?filters%5Bstatus%5D%5B%5D=unsolved&badge_type=c");
}

void showstats(FILE *fptr)
{
//    fptr=fopen("userdata.dat","r");
    printf("\n Username: %s\n Questions solved: %d\n Score: %d\n\n",f_user.uname,f_user.no_of_ques,f_user.score);
}

void welcome(void)
{
    printf("\t##  ##  ###### ##      ##  #####  #####  #####   ######\n"
           "\t## ##   ##       ##  ##   ##     ##    # ##   #  ##    \n"
           "\t###     ####       ##     ##     ##    # ##    # ####  \n"
           "\t## ##   ##         ##     ##     ##    # ##   #  ##    \n" 
           "\t##  ##  ######     ##      #####  #####  #####   ######\n");
}
