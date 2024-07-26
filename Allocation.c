#include "file.h"

FILE* Open(const char *str,const char opt[2])
{
    FILE* file=fopen(str,opt);
    if(file==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        exit (EXIT_FAILURE);
    }
    return(file);
}
char *allocAndCopy(const char *src, int length) 
{
    char *dest = malloc((length + 1) * sizeof(char)); // +1 pour le '\0'
    int i;
    for (i = 0; i < length; i++) 
    {
        dest[i] = src[i];
    }
    dest[length] = '\0';
    return dest;
}

Machine* allocmemachine(int n)
{   int i=0;
    Machine* A=NULL;
    A=(Machine*)malloc(n*sizeof(Machine));
    if (A==NULL)
    {
        printf("Erreur d'Allocation memoire\n");
        exit (1);
    }
    return(A);
}



char** allocmemchar(int n,int p)
{   int i=0;
    char **A=NULL;
    A=(char**)malloc(n*sizeof(char*));
    if (A==NULL)
    {
        printf("Erreur d'Allocation memoire\n");
        exit (1);
    }
    for (i;i<n;i++)
    {
        A[i]=(char*)malloc(p*sizeof(char));
        if (A[i]==NULL)
        {
            printf("Erreur Allocation memoire numero %d\n",i);
            exit(EXIT_FAILURE);
        }
    }
    return(A);

}
char** allocmemchar2(int n)
{
    char **A=NULL;
    A=(char**)malloc(n*sizeof(char*));
    if (A==NULL)
    {
        printf("Erreur d'Allocation memoire\n");
        exit (1);
    }
    return(A);
}
char* allocChar1(int n)
{   
    char* A=NULL;
    A=(char*)malloc(n*sizeof(char));
        if (A==NULL)
        {
            printf("Erreur Allocation memoire\n");
            exit(EXIT_FAILURE);
        }
    return(A);
}



void freemem(Machine* student)
{
for (int i = 0; i < STUDENT_N; i++) 
    {
        if (student[i].prename != NULL)
        {
            for (int j = 0; j < student[i].n_prename; j++) 
            {
                free(student[i].prename[j]);
            }
            free(student[i].prename);
        }
    }
    free(student);
}

void freeTabLine(char ** Tab,int l)
{
    int i;
    for (i=0;i<l;i++)
    {
        free(Tab[i]);
    }
    free(Tab);
}