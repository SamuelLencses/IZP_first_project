#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 103
/*
Samuel Lencses
xlencs00
IZP projekt 1
kontrola hesla
*/
int LenghtOfString(char s[])//zisti dlzku stringu
    {
        int i;
        for (i=0; s[i]!='\0' ;i++)
            {}
        return i;
    }
//-------------------//
int valid(char str[])//zisti, ci heslo ma maximalne 100 znakov
{
    int len = LenghtOfString(str);
    if(len > 101)
    {
        return true;
    }
    return false;
}
//-------------------//
int PorovnanieZnakov(int param,int index1,int index2,char str[])//podfunkcia pre uroven 4
{
    for(int i=0; i<param; i++)
    {
        if ((str[index1+i]) != (str[index2+i]))
        {
            return false;
        }

    }
    return true;
}
//-------------------//
int Level_1(char str[])//uroven 1
{
    int velke=0;
    int male=0;
    for (int i=0; str[i]!='\0'; i++)
        {
        if (str[i]>='A' && str[i]<='Z')
            {
                velke=1;
            }
        else if (str[i]>='a' && str[i]<='z')
            {
                male=1;
            }
        }
    if ((velke==1) && (male==1))
        {
        return false;
        }
    else
        {
        return true;
        }
}
//-------------------//

int Level_2(int x,char str[])//uroven 2
{
    int c=0;//cisla
    int sz=0;//specialne znaky
    if (x>4)//osetrenie parametru pre param>4
    {
        x=4;
    }
    for (int i=0; str[i]!='\0'; i++)
        {
        if (str[i]>='0' && str[i]<='9')
            {
                if (c==0)
                    {
                        c=1;
                    }
            }
        else if ((str[i]>=' ' && str[i]<='/') || (str[i]>=':' && str[i]<='@') || (str[i]>='[' && str[i]<='`') || (str[i]>='{' && str[i]<='~'))//kontrola znaku ci patri aspon jednemu intervalu specialnych znakov z ascii
            {
                if (sz==0)
                    {
                        sz=1;
                    }
            }
        }
    int sum=2+c+sz;//konstanta 2, lebo ak preslo heslo prvym levelom tak musi obsahovat aj velke aj male pismeno
    if (x<=sum)
        {
            return false;
        }
    return true;
}
//-------------------//
int Level_3(int param,char str[])//uroven 3
{
    if (param==1)//nema preco porovnat samostatny znak
    {
        return true;
    }
    int sucet=1;
    for (int i=0; str[i]!='\0'; i++)
    {
        if (str[i] == str[(i+1)])//porovna znak s nasledujucim
            {
                sucet+=1;
                if(sucet>=param)
                    {
                        return true;
                    }
            }
        else
            {
                sucet=1;
            }
    }
    return false;

}
//-------------------//
int Level_4(int param,char str[])//uroven 4
{
    int len;
    len=LenghtOfString(str)-1;//dlzka hesla bez znaku konca riadka
    for (int i=0; i<=len-param-1;i++)
    {
        for(int j=i+1; j<=len-param; j++)
        {
            bool b = PorovnanieZnakov(param,i,j,str);

            if(b == true)
            {
                return true;
            }
        }
    }

    return false;
}
//-------------------//
int stats_check(char argv[])//zisti ci 3. argument je naozaj "--stats"
{
    char str[]="--stats";
    for (unsigned int i=0;i<sizeof(str);i++)
    {
        if (argv[i]!=str[i])
        {
            return true;
        }
    }
    return false;
}
//-------------------//
int param_check(char argv[])//zisti, ci argument obsahuje iny znak ako znaky od 0 po 9
{
     for (int i=0;argv[i]!='\0';i++)
    {
        if (argv[i]<'0' || argv[i]>'9')
            {
                return true;
            }
    }
    return false;
}
//-------------------//
int main(int argc,char *argv[])
{
    //pomocne premenne//
    int nchars=-1;//pocet unikatnych znakov
    int asciitab[126];//vyskyt v tabulke ascii znakov
    int dlzkahesla=0;//pomocna premenna pre zistenie dlzky hesla
    int min=105;
    int pocethesiel=0;

    for (int i=0; i<127; i++)//vyplni tabulku nulami
    {
        asciitab[i]=0;
    }

    if((argc<3)||(argc>4))//spravnost poctu argumentov
    {
        fprintf(stderr,"Invalid number of arguments\n");
        return true;
    }

    if ((param_check(argv[1])==true) || (param_check(argv[2])==true))//zisti ci 1. a 2. argument neobsahuju ine znaky ako cisla
    {
        fprintf(stderr,"invalid argument");
        return true;
    }

    int level=atoi(argv[1]);
    int param=atoi(argv[2]);
    if (param<=0)//parameter musi byt kladne cislo
        {
        fprintf(stderr,"Invalid parameter value\n");
        return 1;
        }
    if (level<1 || level>4)//level musi byt v intervale <1;4>
    {
        fprintf(stderr,"Invalid level value\n");
        return 1;
    }
    if ((argc==4) && (stats_check(argv[3])==true))//pozrie ci stvrty argument je napisany spravne
    {
        fprintf(stderr,"Argument written incorrectly\n");
        return true;
    }
    char password[SIZE];//deklaracia retazca pre heslo
    while(fgets(password,SIZE,stdin)!=NULL)//nacitavanie hesiel
    {

        for (int i=0;password[i]!='\0';i++)//priradi hodnotu 1 znakom ktore sa vyskytli v hesle do asciitab
        {
            asciitab[(int)password[i]]=1;
        }
        if (valid(password)==true)
        {
            fprintf(stderr,"password too long\n");
            return 1;
        }
        pocethesiel++;
        dlzkahesla=LenghtOfString(password)-1+dlzkahesla;//spocita pocet znakov hesla
        if (LenghtOfString(password)-1<min)
        {
            min=LenghtOfString(password)-1;
        }
        //ak hesla splnia dany level, vypise ich
        if (level==1)
        {
            if(Level_1(password)==false)
                {
                    fprintf(stdout,"%s",password);
                }
        }
        if (level==2)
        {
            if((Level_1(password)==false)&&(Level_2(param,password)==false))
                {
                    fprintf(stdout,"%s",password);
                }
        }
        if (level==3)
        {
            if((Level_1(password)==false)&&(Level_2(param,password)==false)&&(Level_3(param,password)==false))
            {
                fprintf(stdout,"%s",password);
            }
        }
        if (level==4)
        {
            if((Level_1(password)==false)&&(Level_2(param,password)==false)&&(Level_3(param,password)==false)&&(Level_4(param,password)==false))
            {
                fprintf(stdout,"%s",password);
            }
        }
    }
    for (int i=0;i<127;i++)//spocita
    {
        if(asciitab[i]==1)
        {
            nchars++;
        }
    }
    if ((argc==4) && (stats_check(argv[3])==false))//vypise statistiky
    {
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n",nchars);
        printf("Minimalni delka: %d\n",min);
        printf("Prumerna delka: %.1f\n",(double)dlzkahesla/pocethesiel);
    }
    return false;
}
