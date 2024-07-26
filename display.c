#include "file.h"

void menu_display(int *c)
{   
    //system("clear");
    int i,j,k;
    for ( i = 0; i < 12; i++)
    {
         printf("\n");
    }
    
    printf("\t\t\t\t\t\t");
    for (i = 0; i < 30; i++)
    {
        printf("◽");
    }
    j=59;
    k=50;
    printf("\n");
    tabulation();
    printf("%-*s◽\n",j,"◽");
    tabulation();
    printf("%-*s◽\n",j,"◽");
    tabulation();
    printf("◽\t%-*s◽\n",k,"1-CHECK");
    tabulation();
    printf("◽\t%-*s◽\n",k,"2-SHOW THE LIST OF TODAY");
    tabulation();
    printf("◽\t%-*s◽\n",k,"3-SHOW THE LIST OF A SPECIFIC DAY");
    tabulation();
    printf("◽\t%-*s◽\n",k,"4-QUIT AND SAVE");
    tabulation();
    printf("◽\t%-*s◽\n",k,"5-QUIT ONLY");
    tabulation();
    printf("%-*s◽\n",j,"◽");
    tabulation();
    printf("%-*s◽\n",j,"◽");
    tabulation();
    for (i = 0; i < 30; i++)
    {
        printf("◽");
    }
    printf("\n\n\n");
    tabulation();
    read_input("Enter a integer between 1 to 6:",INT,c);
}

void tabulation(void)
{   
    int i;
    for(i=0;i<6;i++)
    {
        printf("\t");
    }
}

void searchDisplay(const Machine *E) 
{   
    int i ;
    printf("\n\t\t\t⥬> %d %s ",E->numero,E->name);
    for (i= 0; i < E->n_prename; i++) 
    {
        printf("%s ", E->prename[i]);
    }
}

void display (Machine *eleve,Utilisation p,char*Date)
{       
        char* mode=UtilisationToStr(p);
        int i,j,oui,non,perso,pres,abs;
        system("clear");
        printf("\t\t\t\t\t\tLISTE OF '%s'\n\t\t\t\t\t     %s\n",mode,Date);
        printf("%-*s|%-*s|%-*s|%-*s",WIDTH_num,"NUM",WIDTH_name, "NAME", WIDTH_prenames, "PRENAMES", WIDTH_DATA, "DATA");
        printf("|%s\n","TIME");
        Countstudent(eleve,&abs,&oui,&non,&perso,&pres);
        // Écrire les données
        j=-1;
        switch (p)
        {
            case ALL:
            {
                for (i = 0; i < STUDENT_N; i++) 
                {
                    displayByMain(&eleve[i]);
                }
                printf("\nTotal number of student :%d\n",STUDENT_N);
                printf("Present number:%d\tAbsent number:%d\nStudent number depending on usage type:\n",pres,abs);
                printf("OUI:%d\tNON:%d\tPERSO:%d\n",oui,non,perso);
                break;
            }
            case PRESENT:
            {
                for (i = 0; i < STUDENT_N; i++)            
                {
                    if(eleve[i].utilisation>ABSENT && eleve[i].utilisation<ALL)
                        {
                            displayByMain(&eleve[i]);
                        }
                }
                j=pres;
                break;
            }
            case ABSENT:
            {
                for (i = 0; i < STUDENT_N; i++)            
                {
                    if(eleve[i].utilisation==0)
                        {
                            displayByMain(&eleve[i]);
                        }
                }
                j=abs;
                break;  
            }
            default:
            {   
                j=0;
                for (i = 0; i < STUDENT_N; i++) 
                {
                    if(eleve[i].utilisation==p)
                    {
                        displayByMain(&eleve[i]);
                        j++;
                    }

                }
                break;
            }
        }
        if(p!=ALL)
            {
                printf("\nStopped the list at %d students\n",j);
            }
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
}



void displaySubchoice(int *c,int a)
{       
        
        if (a==-1)
        {   
            printf("\n\n\n\t\t");  
            printf("🔎 0-ABSENT\n\t\t🔎 1-OUI\n\t\t🔎 2-NON\n\t\t🔎 3-PERSO\n\t\t🔎 4-ALL STUDENT\n\t\t🔎 5-PRESENT\n\t\t🔎 6-MENU\n");
            read_input("\n\t\t\t\t ⇰ Enter a integer between 1 to 6:",INT,c);
        }
        else if(a==1)
        {
            printf("0-ABSENT\n1-OUI\n2-NON\n3-PERSO\n4-ALL STUDENT\n5-PRESENT\n6-MENU\n7-GENERATE THIS LIST IN A FILE\n");
            read_input("Enter a integer between 1 to 7:",INT,c);
        }
        
      
    
}
void displayByMain(Machine*eleve)
{   
    char all_prenames[WIDTH_prenames];
    printf( "%-*d|%-*s|",WIDTH_num,eleve->numero, WIDTH_name, eleve->name);
    strcpy(all_prenames, "");
    for (int j = 0; j < eleve->n_prename; j++) 
    {
        strcat(all_prenames, eleve->prename[j]);
        if (j < eleve->n_prename - 1) 
            {
                strcat(all_prenames, " ");
            }
    }
    printf("%-*s|", WIDTH_prenames, all_prenames);

   // Écrire la donnée variable
    printf("%-*s|%02d:%02d:%02d\n", WIDTH_DATA, eleve->presence, eleve->t.tm_hour, eleve->t.tm_min, eleve->t.tm_sec);
}

void read_input(const char *label,DataType type, void *variable) 
{
    char input[256];
    int valid_input = 0;
    
    while (!valid_input) 
    {
        printf("%s", label);
        if (fgets(input, sizeof(input), stdin) != NULL) 
        {
            // Remplacer le caractère de nouvelle ligne par une chaîne vide
            if (input[strlen(input) - 1] == '\n') 
            {
                input[strlen(input) - 1] = '\0';
            }

            switch (type) {
                case INT: 
                {
                    int value;
                    if (sscanf(input, "%d", &value) == 1) 
                    {
                        *((int *)variable) = value;
                        valid_input = 1;
                    } else 
                    {
                        printf("Invalid input. Please enter a valid integer.\n");
                    }
                    break;
                }
                case FLOAT: 
                {
                    float value;
                    if (sscanf(input, "%f", &value) == 1) 
                    {
                        *((float *)variable) = value;
                        valid_input = 1;
                    } else 
                    {
                        printf("Invalid input. Please enter a valid float.\n");
                    }
                    break;
                }
                case DOUBLE: 
                {
                    double value;
                    if (sscanf(input, "%lf", &value) == 1) 
                    {
                        *((double *)variable) = value;
                        valid_input = 1;
                    } else 
                    {
                        printf("Invalid input. Please enter a valid double.\n");
                    }
                    break;
                }
                case CHAR: {
                    if (strlen(input) == 1) 
                    {
                        *((char *)variable) = input[0];
                        valid_input = 1;
                    } else 
                    {
                        printf("Invalid input. Please enter a single character.\n");
                    }
                    break;
                }
                case STRING: 
                {
                    strcpy((char *)variable, input);
                    valid_input = 1;
                    break;
                }
                default: 
                {
                    printf("Unknown data type.\n");
                    break;
                }
            }
        }
    }
}
void Final_Display(int *c)
{   
    int i;
    *c=-1;
    while (1)
    {   for ( i = 0; i < 15; i++)
        {
            printf("\n");
        }
    
        read_input("\t❌Are you sure to quit ?(1-Yes,2-No):",INT,c);

        if(*c==1 || *c==2)
        {
            break;
        }
        else
        {
            printf("Please chose between 1 or 2\n");
        }
    }
    system("clear");
    
    
}

char* GetDateForDisplayArchive(void)
{   
    int y,m,d,t=0;
    char *date=allocChar1(20);
    while (1)
    {
      read_input("\n\n\t\t\t🕤 Enter the year(integer positive for example 2024) or 0 to quit:",INT,&y);
      if(y>=0)
      {
        break;
      }
      else
      {
        printf("❌❌Try again, value not accepted❌❌\n");
      }
    }
    if (y==0)
    {
        return(NULL);
    }
    
     while (1)
     {
        read_input("\t\t\t🕤 Enter the month(between [1-12],1-jan,2-fev,...)or 0 to quit:",INT,&m);
        if (m>0  &&  m<13)
        {
            break;
        }
        else
        {
            printf("Choose between 1 to 12, for example  1-january,2-February...\n");
        }
        
     }
    if (m==0)
    {
        return(NULL);
    }
    
     while (1)
     {
        read_input("\t\t\t🕒Enter the day(between [1-31])or 0 to quit:",INT,&d);
        if (d>0 && d<32)
        {
            break;
        }
        else
        {
            printf("Choose between 1 to 31 coresponding to the day what you want\n");
        }
     } 
    if (d==0)
    {
        return(NULL);
    }
   t = snprintf(date, 20, "%04d-%02d-%02d", y, m, d);
    
    if (t < 0 || t >= 20) {
        printf("Erreur de snprintf\n");
        exit(1);
    }

    printf("\n\n");
     return(date);   
}

void errorDisplay(void)
{
    printf("❌Date not found Try again\n");
}

void displayChoiceSearch(int *c)
{
    read_input("\n\t\t\t\t🔹0-ABSENT\n\t\t\t\t🔹1-OUI\n\t\t\t\t🔹2-NON\n\t\t\t\t🔹3-PERSO\n\t\t\t\t======>", INT, c);
    while (*c >= 4) 
    {
                            printf("❌ Choice too large, choose between 0 to 3.\n");
                            read_input("\n\t\t\t\t🔹0-ABSENT\n\t\t\t\t🔹1-OUI\n\t\t\t\t🔹2-NON\n\t\t\t\t🔹3-PERSO\n\t\t\t\t======>", INT, c);

    }
}