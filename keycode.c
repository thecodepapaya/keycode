#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct userdb
{
    int score;
    int no_of_ques;
    char uname[15];
}getuser={0,0,"NULL"},f_user;

void practice(FILE *);         //done
void showstats(FILE *);       //done
void leaderboard(void);      //done
int match(int);            //done
int scoreupdate(FILE *);   //done
void showques(int);      //done
void showans(void);      //done
void welcome(void);     //done
FILE* login(void);     //done
FILE *getpos(void); //done

char username[15];
int qnum=0;

int main()
{
    int choice;
    char flag='y';
    FILE *pos;
    system("rm sol.c;rm sol;rm output.txt;touch userdata.dat");
    welcome();
    pos=login();
    showstats(pos);
    do{
        printf("  \033[1;35m==========================================================\033[0m\n\n"
            "\t \033[1;37m1) Practice                         3) Logout\n\n "
            "\t 2) Show Leaderboard                 4) Exit\n\n "    
            "\033[1;35m ==========================================================\033[0m\n"
            "\t\t\033[7;37mYour Choice:\033[0m ");
        scanf("%d",&choice);
        printf("  \033[1;35m==========================================================\033[0m\n");

        switch(choice)
        {
            case 1: practice(pos);
                    break;
            case 2: leaderboard();
                    break;
            case 3: main();
                    break;
            case 4: return 0;
            default: printf("\033[1;31m-----------------Incorrect Input-------------------\033[0m\n");
                     break;
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
    
        printf("\n");
        showques(qnum);
        printf("\n\033[7;37m !!!---Press enter to open nano text editor---!!!\033[0m\n");
        getchar();
        getchar();
        system("nano sol.c");
    do{
        printf("%s",    " \033[1;37m========================================================================\n"
                        "  1.) View question again             5.) Submit your code\n\n "
                        " 2.) Open text editor again          6.) Show answer\n\n"
                        "  3.) Compile                         0.) Go Back\n\n"
                        "  4.) Run with custom input\n\n"
                        "========================================================================\033[0m\n"
                        //"5.) Submit your code\n "
                        //"6.) Show answer\n "
                        //"0.) Exit\n\n "
                        "\t   \033[7;37mYour Choice:\033[0m ");
        scanf("%d",&choice);
        pos=getpos();
        printf(" \033[1;37m========================================================================\033[0m\n");
        switch(choice)
        {
            case 1: showques(qnum);
                    break;
            case 2: system("nano sol.c");
                    break;
            case 3: val=system("gcc sol.c -o sol.out");
                    if(!val)
                    {
                        printf("\n\033[1;32m-----------------Compilation Successful-----------------\033[0m\n");
                        comp=1;
                    }
                    else
                    {
                        printf("\n\t * * * * * GCC returned \033[1;31m ERROR %d \033[0m* * * * *\n \033[1;31m\t--!!Compilation unsuccessful!!--\033[0m\n",val);
                        comp=0;
                    }
                    break;
            case 4: 
                    if(!comp)
                    {
                        printf("\n //////////////YOU NEED TO SUCCESSFULLY COMPILE YOUR PROGRAM FIRST /////////////");
                        exec=0;
                    }
                    else
                    {
                        printf("\n Provide your Input here(if any).\n\n");
                        val=system("./sol.out");
                        if(val)
                        {
                            printf("\n \033[1;31mExecution unsuccessful.\n Error %d\033[0m\n",val);
                            exec=0;
                        }
                        else
                        {
                            printf("\n \033[1;32m ~ ~ ~ ~ ! ! ! ! Executed successfull ! ! ! ! ~ ~ ~ ~ \033[0m");
                            exec=1;
                        }
                    }
                    break;
            case 5: if(exec==1 || comp==1)
                    {
                        system("./sol.out > output.txt"); 
                        val=match(qnum);
                        if(!val)
                        {
                            printf("\n \033[0;32m\t\t!!!!  Answer matched  !!!!\n\t\t\033[0m\a");
                            if(!scoreupdate(pos))
                                printf("\033[1;32m~~~~~~~~~~~~! Score Updated !~~~~~~~~~~~~\n\033[0m\a");
                            qnum++;

                        }
                    }
                    else
                    {
                        printf("\n You should at least\033[1;31m try to compile \033[0myour program first!!!\n");
                    }
                    break;
            case 6: showans();
                    break;
            case 0: return ;
            default: printf("\n \033[1;31m>>>>>>>>>>>>>>>>>>>Please provide a valid input.<<<<<<<<<<<<<<<<<<<<<<\033[0m");
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
    printf("\n\n \033[1;37mEnter Username:\033[0m ");

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
            printf("\n\033[1;34m Welcome Back\033[0m \033[1;32m%s\033[0m\n",getuser.uname);
            printf("``````````````````````````````````````\n");
            flag=1;
            break;
        }
    }
    if(!flag)
    {
     //   fwrite(&getuser,sizeof(getuser),1,fptr);
        fwrite(&getuser,sizeof(getuser),1,fptr);
        printf("\n \033[1;33m:::::::::::::::::::::::::New Profile created!!:::::::::::::::::::::::::::\033[0m\n");
    }
    fseek(fptr,-sizeof(getuser),SEEK_CUR);
    return fptr;
}

void leaderboard(void)
{
    char exp_level[13];
    FILE *readptr;
    readptr=fopen("userdata.dat","rb");
    printf("===============================================================\n");
    printf(" \033[1;33mName\t\tScore\tExp Level\tQuestions\033[0m\n");
    printf("===============================================================\n");
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
        printf("\n %s\t\t%d\t%s\t\t%d\n",f_user.uname,f_user.score,exp_level,f_user.no_of_ques);
    }
    printf("===============================================================\n");
    fclose(readptr);
}


int scoreupdate(FILE *pos)
{
    FILE *fptr;
    fptr=fopen("userdata.dat","r+b");
    fptr=pos;
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

void showques(int qnum)
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
        case 0: system("cat s0.txt");
                break;
        case 1: system("cat s1.txt");
                break;
        case 2: system("cat s2.txt");
                break;
        case 3: system("cat s3.txt");
                break;
        case 4: system("cat s4.txt");
                break;
        default: printf("\n Sorry we do not have anymore questions for you!!\n");
    }
}

void showstats(FILE *pos)
{
    FILE *fptr;
    fptr=fopen("userdata.dat","rb");
    fptr=pos;
    fread(&f_user,sizeof(f_user),1,fptr);
    qnum=f_user.no_of_ques;
    printf("\033[1;37m+-----------------------------------------------+\n");
    printf("\033[1;37m|                                               |\n");
    printf("\033[1;37m| \tUsername            :  %s             |\n"
           "| \tQuestions solved    :  %d                |\n"
           "| \tScore               :  %d               |\n\033[0m"
           "\033[1;37m|                                               |\n",f_user.uname,f_user.no_of_ques,f_user.score);
    printf("\033[1;37m+-----------------------------------------------+\033[0m\n");
}

void welcome(void)
{
    system("clear");
    printf("\t\033[1;37m##########################################################################\033[0m\n"
           "\t\033[1;37m##                                                                      ##\033[0m\n"
           "\t\033[1;37m##\033[0m\t\033[1;34m ##  ##  ###### ##      ##\033[0m   \033[1;31m#####  #####  #####   ###### \033[0m\t\033[1;37m##\033[0m\n"
           "\t\033[1;37m##\033[0m\t\033[1;34m ## ##   ##       ##  ##\033[0m    \033[1;31m##     ##    # ##   #  ##     \033[0m\t\033[1;37m##\033[0m\n"
           "\t\033[1;37m##\033[0m\t\033[1;34m ###     ####       ##\033[0m      \033[1;31m##     ##    # ##    # ####   \033[0m\t\033[1;37m##\033[0m\n"
           "\t\033[1;37m##\033[0m\t\033[1;34m ## ##   ##         ##\033[0m      \033[1;31m##     ##    # ##   #  ##     \033[0m\t\033[1;37m##\033[0m\n" 
           "\t\033[1;37m##\033[0m\t\033[1;34m ##  ##  ######     ##\033[0m       \033[1;31m#####  #####  #####   ###### \033[0m\t\033[1;37m##\033[0m\n"
           "\t\033[1;37m##                                                                      ##\033[0m\n"
           "\t\033[1;37m##########################################################################\033[0m\n");
}