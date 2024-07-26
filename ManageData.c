#include "file.h"

Machine* GetNameAndInitialize(void)
{   
    Machine *student=allocmemachine(STUDENT_N);
    FILE* file=Open(DATA_FILE_NAME,"r");
    char tmpstr[MAX];
    int i = 0,k=0;
    int numero;
    char name[MAX];
    char all_prenames[MAX],*prename;
    int j,end,length;
    int start = 0;
    int prename_index = 0;

    while (fgets(tmpstr, MAX, file) != NULL && i < STUDENT_N) 
    {
        // Retirer le caractère de nouvelle ligne si présent
        if (tmpstr[strlen(tmpstr) - 1] == '\n')
            tmpstr[strlen(tmpstr) - 1] = '\0';

        // Lire les données de l'étudiant
 
        sscanf(tmpstr, "%d#%49[^#]#%99[^\n]", &numero, name, all_prenames);

        // Initialiser le numéro
        student[i].numero = numero;
        // Allouer et copier le name
        student[i].name = allocAndCopy(name, strlen(name));
        // Compter le namebre de prénames
        student[i].n_prename = 1; // Au moins un préname
        for ( j = 0; all_prenames[j] != '\0'; j++) 
        {
            if (all_prenames[j] == ',')
                student[i].n_prename++;
        }
       
        // Allouer la mémoire pour les prénames
        student[i].prename = allocmemchar(student[i].n_prename, 60);
        start = 0;
        prename_index = 0;
        // Séparer et copier les prénames manuellement
        for (j = 0; all_prenames[j] != '\0'; j++) 
        {
            if (all_prenames[j] == ',' || all_prenames[j + 1] == '\0') 
            {
                // Calculer la longueur du préname actuel
                length = j - start;
                // Copier le préname actuel dans le tableau de prénames
                prename = allocChar1(length +1); // +1 pour le '\0'
                for ( k = 0; k < length; k++) 
                {
                    prename[k] = all_prenames[start + k];
                }
                prename[length] = '\0'; // Ajouter le caractère de fin de chaîne
                // Assigner le préname copié au tableau de prénames
                student[i].prename[prename_index] = prename;
                // Passer au prochain préname
                prename_index++;
                start = j + 1;
            }
        }
        strcpy(student[i].presence,"ABSENT");
        i++;
    }
    fclose(file);
    return(student);
}
void LoadData(Machine* student)
{   
    char tmpstr[MAX];
    int i=0,l,n,h,m,s,u,found=0;
    FILE* file= Open(FILE_NAME_Saveforprogram,"r+");
    struct tm *now_tm=GetTime();
    struct tm time_tm;
    char date[30];
    sprintf(date,"%04d-%02d-%02d",
            now_tm->tm_year + 1900,
            now_tm->tm_mon + 1,
            now_tm->tm_mday);
    while (fgets(tmpstr, MAX, file) != NULL) 
    {  
        // Retirer le caractère de nouvelle ligne si présent
        if (tmpstr[strlen(tmpstr)-1]=='\n')
                tmpstr[strlen(tmpstr)-1]='\0';
        if (strcmp(tmpstr, date) == 0) 
                found = 1; // La date a été trouvée
        if ((found==1 && strcmp(tmpstr, date) != 0) || (found==1 && strcmp(tmpstr,"9999999999999")!=0)) 
        {    
            sscanf(tmpstr,"%d#%d#%02d:%02d:%02d",&n, &u, &time_tm.tm_hour, &time_tm.tm_min, &time_tm.tm_sec);
            for ( i = 0; i < STUDENT_N; i++)
            {
                if (student[i].numero==n)
                {
                    student[i].numero=n;
                    student[i].utilisation=u;
                    student[i].t.tm_hour=time_tm.tm_hour;
                    student[i].t.tm_min=time_tm.tm_min;
                    student[i].t.tm_sec=time_tm.tm_sec;
                    DoPresence(&student[i]);
                }
            
            } 
        }  
    }
    fclose(file);
}

int choicefunction(Machine*student)
{   
    Machine*studentAr=NULL;
    int choice=-1,subchoice=-1,a=-1,b=-1;
    char*dateArchive;
    while(1)
    {   
        system("clear"); 
        menu_display(&choice);
        switch (choice)
        {
            case 1:
                system("clear");
                searchAndCheck(student);
                break;
            case 2:
                system("clear");
                a=-1;
                do 
                {   
                    displaySubchoice(&subchoice,a);
                    if (subchoice<6 && subchoice>=0)
                    {
                        display(student,subchoice,initializeLaunchDate());
                        b=subchoice;
                        
                    }
                    if(subchoice==7 && a==1)
                    {   
                        system("clear");
                        FileGenerator(student,b,initializeLaunchDate());
                        a=-1;
                    }
                    if (subchoice !=7 )
                    {
                        a=1;
                        b=subchoice;   
                    }

                }while (subchoice!=6);
                break;
            case 3:
                system("clear");
                do 
                {     
                    dateArchive=GetDateForDisplayArchive();
                    if (dateArchive!=NULL)
                    {   
                        studentAr=GetArchive(dateArchive);
                        if(studentAr!=NULL)
                        {   
                        system("clear");
                            printf("Donnée correspondant a la date trouvée\n"); 
                            a=-1;    
                                while(1)
                                {                
                                        displaySubchoice(&subchoice,a);
                                        if (subchoice<6 && subchoice>=0)
                                        {
                                            display(studentAr,subchoice,dateToString(dateArchive));
                                            b=subchoice;
                                            
                                        }
                                        if(subchoice==7 && a==1)
                                        {   
                                            system("clear");
                                            FileGenerator(studentAr,b,dateToString(dateArchive));
                                            a=-1;
                                        }
                                        if (subchoice !=7)
                                        {
                                            a=1;
                                            b=subchoice;   
                                        }
                                        if(subchoice==6)
                                        {   
                                            system("clear");
                                            freemem(studentAr);
                                            break;
                                        }
                                }
                        }
                        else
                        {
                            errorDisplay();
                        }
                    }
                }while(dateArchive!=NULL);
                break;
            default:
                break;
        }
        if (choice==4 || choice==5)
        {   
            Final_Display(&subchoice);
            if(subchoice==1)
            {
                break;
            }
        }
    }

    return(choice);
}

void searchAndCheck(Machine *eleve)
{	
    char chaine[MAX];
    int* found=NULL;
    int indexN=0;
    int i;
    int n,p=0,c,choice,t;
    int start,end;
    time_t now;
    system("clear");
    while (1)
     {  
        t=0;
        printf("\n\n\n\t\t🔴 Enter the number or the name or the prename of the student or tap 'quit' to quit:");
        read_input("",STRING,chaine);
        
            if(strcmp(chaine,"quit")==0)
                break;
            
            
            if(sscanf(normalize_string(chaine),"%d-%d",&start,&end)==2 && start<=STUDENT_N && start >=1 && end<=STUDENT_N && end>=1)
            {
                for ( i = 0; i < STUDENT_N ; i++)
                {
                    if (eleve[i].numero<=end && eleve[i].numero>=start)
                    {
                        searchDisplay(&eleve[i]);
                    }                       
                }
                displayChoiceSearch(&c);
                for ( i = 0; i < STUDENT_N; i++)
                {
                    if (eleve[i].numero<=end && eleve[i].numero>=start)
                    {
                        eleve[i].utilisation=c;
                        DoPresence(&eleve[i]);
                        AttributeTime(&eleve[i]);
                    }  
                }  
                t=1;
            }

            else
            {
                found=search1(eleve,chaine,&indexN);
                if (found != NULL) 
                {     
                    for ( i = 0; i < indexN; i++)
                    {
                        eleve[found[i]].utilisation = 0; 
                        searchDisplay(&eleve[found[i]]); 
                    }
                    if(indexN >1)
                    {   
                        n=-1; 
                        while (1)
                        {
                            read_input("\n\n\t\t\t\t==>Tap the num of the student who you want to check or 0 to search another one:",INT,&p);
                            for ( i = 0; i < indexN; i++)
                            {
                                if(eleve[found[i]].numero==p)
                                    n=found[i];
                            }
                            if(n!=-1 || p==0)
                                break;
                            else
                            {
                                printf("Choose between number: ");
                                for ( i = 0; i < indexN; i++)
                                {   
                                    printf("%d,",eleve[found[i]].numero);
                                }
                            }
                            
                        }
                        if (p!=0)
                        {
                        searchDisplay(&eleve[n]);
                        }
                    }
                    else 
                    {
                    n=found[0];
                    p=1;
                    }


                    if (p!=0)
                    {   
                        choice=1;
                        if (strcmp(eleve[n].presence,"ABSENT")!=0)
                        {   
                            printf("\n\t\t\thas already checked %s at %2d:%2d:%2d are you sure to change here(his) checking?❌\n",eleve[n].presence,eleve[n].t.tm_hour,eleve[n].t.tm_min,eleve[n].t.tm_sec);
                            while (1)
                            {   
                                read_input("\t\t\t==>Tap 1 for Yes or 2 for No:",INT,&choice);
                                if (choice==1 ||choice ==2)
                                    break;
                                else
                                {
                                    printf("❌❌ It's easy to choose or tap on 2 or 1 !!!!!!\n");
                                } 
                            }   
                        }
                        if(choice == 1)
                        {
                            displayChoiceSearch(&eleve[n].utilisation);
                            if (eleve[n].utilisation!=0)
                            {
                                AttributeTime(&eleve[n]);
                            }
                            DoPresence(&eleve[n]);
                        }
                    }
                    t=1;
                }
                free(found);
            }
        system("clear");
        if(t!=1 && strcmp(chaine,"quit")!=0)
        {
            printf("\n❌ Student not found,try again\n");
        }
     }
}
void DoPresence(Machine* student)
{     
        switch (student->utilisation)
        {
        case OUI:
            strcpy(student->presence,"OUI");
            break;
        case NON:
            strcpy(student->presence,"NON");
            break;
        case PERSO:
            strcpy(student->presence,"PERSO");
            break;
        default:
            strcpy(student->presence,"ABSENT");
            break;
        }

}
void AttributeTime(Machine* student)
{   
    time_t rawtime;
     if (student->utilisation==OUI||student->utilisation==NON|| student->utilisation==PERSO)
        {  
            time(&rawtime);
            student->t=*localtime(&rawtime);
        }
}

Machine* GetArchive(char *date)
{   
    
    Machine* studentAr=GetNameAndInitialize();
    printf("%s\n",date);
    char tmpstr[MAX];
    int i=0,l,n,h,m,s,u,po=0,found=0;
    struct tm time_tm;
    FILE* file= Open(FILE_NAME_Saveforprogram,"r");
    while (fgets(tmpstr, MAX, file) != NULL) 
    {  
        // Retirer le caractère de nouvelle ligne si présent
        if (tmpstr[strlen(tmpstr)-1]=='\n')
                tmpstr[strlen(tmpstr)-1]='\0';

        if (strcmp(tmpstr, date) == 0) 
                found = 1; // La date a été trouvée

        if(strcmp(tmpstr,"9999999999999")==0)
                found = 0;

        if (found==1 && strcmp(tmpstr, date) != 0) 
        {   
            po=1;   
            l=sscanf(tmpstr,"%d#%d#%02d:%02d:%02d",&n, &u, &time_tm.tm_hour, &time_tm.tm_min, &time_tm.tm_sec);
            if (l!=5)
            {
                printf("Erreur de lecture de donnée dans %s\n",FILE_NAME_Saveforprogram);
                exit(1);
            } 
            for ( i = 0; i < STUDENT_N; i++)
            {
            if (studentAr[i].numero==n)
            {
                studentAr[i].numero=n;
                studentAr[i].utilisation=u;
                studentAr[i].t.tm_hour=time_tm.tm_hour;
                studentAr[i].t.tm_min=time_tm.tm_min;
                studentAr[i].t.tm_sec=time_tm.tm_sec;
                DoPresence(&studentAr[i]);
            }
            
            } 
        }  
    }
    fclose(file);
    if (po==1)
    {
        return(studentAr);
        printf("\n📂 Data corresponding to the date %s found\n",date); 
    }
    else
    {
        return(NULL);
    } 
    
}
int removeLine(const char *filename, int n) 
{
    FILE *file = Open(filename, "r");
    // Lire tout le contenu du fichier
    char **lines = NULL;
    char line[MAX];
    int total_lines = CountLine(file);
    int i=0,j=0;
    int lines_to_keep;

    // Allouer la mémoire pour le tableau de lignes
    lines = allocmemchar2(total_lines);

    // Lire les lignes du fichier
    while (fgets(line, sizeof(line), file))
    {   
        lines[j]=allocChar1(strlen(line)+1);
        i = 0;
        while (line[i] != '\0') 
        {
            lines[j][i] = line[i];
            i++;
        }
        lines[j][i] = '\0';
        j++;
        //total_lines++;
    }

    fclose(file);

    // Calculer le namebre de lignes à conserver
    lines_to_keep = total_lines - n;
    if (lines_to_keep < 0) 
        lines_to_keep = 0;

    // Réécrire le fichier avec les lignes conservées
    file = Open(filename, "w");
    for ( i = 0; i < lines_to_keep; i++) 
    {
        fputs(lines[i], file);
    }

    freeTabLine(lines,lines_to_keep);
    fclose(file);
    return 0;
}

void Save_for_program(Machine*student)
{   
    int i;
    struct tm* now_tm=GetTime();
    FILE* file=Open(FILE_NAME_Saveforprogram,"a+");
    fprintf(file,"%04d-%02d-%02d\n",
           now_tm->tm_year + 1900,
           now_tm->tm_mon + 1,
           now_tm->tm_mday);
    for ( i = 0; i < STUDENT_N; i++)
    {
        fprintf(file,"%d#",student[i].numero);
        fprintf(file,"%d#%02d:%02d:%02d\n",student[i].utilisation,student[i].t.tm_hour,
                                             student[i].t.tm_min, student[i].t.tm_sec);
    }
    fprintf(file,"9999999999999\n");
    fclose(file);
    
}

char* initializeLaunchDate() 
{
    time_t rawtime;
    struct tm *timeinfo;
    static char tmpstr[100];  // Utiliser static pour une durée de vie plus longue

    // Obtenir le temps actuel
    time(&rawtime);
    // Convertir en temps local
    timeinfo = localtime(&rawtime);

    // Formater la date et l'heure en chaîne de caractères
    strftime(tmpstr, sizeof(tmpstr), "%A %d %B %Y", timeinfo);

    // Allouer dynamiquement la mémoire pour la chaîne retournée
    char* result = malloc(strlen(tmpstr) + 1);
    if (result) 
    {
        strcpy(result, tmpstr);
    }
    return (result);
}

struct tm* GetTime()
{
    time_t rawtime;
    struct tm *timeinfo;
    // Obtenir le temps actuel
    time(&rawtime);
    // Convertir en temps local
    timeinfo = localtime(&rawtime);

    return(timeinfo);
}




void Save_for_human(Machine *eleve)
{
 FILE *file = Open(FILE_NAME_Saveforhuman,"a+");
    int i,j;
    int abs,oui,non,perso,pres;
    char all_prenames[WIDTH_prenames];
    fprintf(file,"<HTML>\n"
                    "<HEAD>\n"
                        "<TITLE>"
                            "Liste"
                        "</TITLE>\n"
                        "<style>"
                            "table{"
                                "border: 1 solid black;"
                                "border-collapse: collapse;"
                                "background-color: #bbbbbb;"
                                "opacity: .85;"
                                "}"
                            ".present{"
                                "color: #005;"
                                "}"
                            ".abs{"
                                "color: #900;"
                                "border: 1 solid black;"
                                "}"
                            ".perso{"
                                "color: purple;"
                            "}"
                        "</style>"
                    "</HEAD>"
                    "<BR>");
    fprintf (file,"<BODY background='/home/christian/Bureau/Projet/pray.jpg'><CENTER><I><FONT face=times-roman COLOR='#1bbbee' size=16>Date :%s</FONT></I></CENTER>",initializeLaunchDate());
    fprintf(file, "<CENTER><TABLE border=4><TR><TD>%-*s</TD><TD>%-*s</TD><TD>%-*s</TD><TD>%*s</TD><BR>",WIDTH_num, "<FONT COLOR=GREEN>NUM</FONT>",WIDTH_name, "<FONT COLOR=GREEN>NAME</FONT>", WIDTH_prenames, "<FONT COLOR=GREEN>PRENAMES</FONT>", WIDTH_DATA, "<FONT COLOR=GREEN>DATA</FONT>");
    fprintf(file,"<TD>%s</TD></TR><BR>","<FONT COLOR=GREEN>TIME</FONT>");
    // Écrire les données
    for (i = 0; i < STUDENT_N; i++) 
    {
        // Écrire le name
        fprintf(file, "<TR><TD>%-*d</TD><TD>%-*s</TD>", WIDTH_num, eleve[i].numero, WIDTH_name, eleve[i].name);
        strcpy(all_prenames, "");
        for ( j = 0; j < eleve[i].n_prename; j++) 
        {
            strcat(all_prenames, eleve[i].prename[j]);
            if (j < eleve[i].n_prename - 1) 
            {
                strcat(all_prenames, " ");
            }
        }
        fprintf(file, "<TD>%-*s</TD>", WIDTH_prenames, all_prenames);
        // Écrire la donnée variable
        fprintf(file, "<TD  class=\"%s\"> %-*s</TD><TD>%02d:%02d:%02d</TD</TR><BR>", !strcmp(eleve[i].presence, "ABSENT")?"abs":!strcmp(eleve[i].presence, "PERSO")?"perso":"present", WIDTH_DATA, eleve[i].presence, eleve[i].t.tm_hour, eleve[i].t.tm_min, eleve[i].t.tm_sec);
    }
    
    Countstudent(eleve,&abs,&oui,&non,&perso,&pres);
    fprintf(file,"</CENTER></TABLE>");
    fprintf(file,"<BR>Total number of student:%d<BR>",STUDENT_N);
    fprintf(file,"<B><FONT COLOR=blue>Present number</FONT></B>:\t%d<BR><B><FONT COLOR=red>Absent number</FONT></B>:\t%d<BR><B><FONT COLOR=green>Student number depending on usage type:</FONT></B><BR>",pres,abs);
    fprintf(file,"OUI:%d\tNON:%d\tPERSO:%d<BR>",oui,non,perso);
    fprintf(file,"</BODY>" "</HTML>");
    fprintf(file,"--------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}
void Countstudent(Machine*student,int *abs,int*oui,int*non,int*perso,int*pres)
{
    int i;
     *abs=0;
     *oui=0;
     *non=0;
     *perso=0;
     *pres=0;
    for ( i = 0; i < STUDENT_N; i++)
    {
        switch (student[i].utilisation)
        {
        case ABSENT:
            (*abs)++;
            break;
        case OUI:
            (*oui)++;
            (*pres)++;
            break;
        case NON:
            (*non)++;
            (*pres)++;
            break;
        case PERSO:
            (*perso)++;
            (*pres)++;
            break;
        default:
            break;
        }
    }
    
}


char *dateToString(const char *date_str) 
{
    char *formatted_date=allocChar1(50);
    int y,m,d;
    char month[20];

    sscanf(date_str,"%04d-%02d-%02d",&y,&m,&d);
    switch (m)
    {
    case 1:
        strcpy(month,"January");
        break;
    case 2:
        strcpy(month,"February");
        break;
    case 3:
        strcpy(month,"March");
        break;
    case 4:
        strcpy(month,"April");
        break;
    case 5:
        strcpy(month,"May");
        break;
    case 6:
        strcpy(month,"June");
        break;
    case 7:
        strcpy(month,"July");
        break;
    case 8:
        strcpy(month,"August");
        break;
    case 9:
        strcpy(month,"September");
        break;
    case 10:
        strcpy(month,"October");
        break;
    case 11:
        strcpy(month,"November");
        break;
    case 12:
        strcpy(month,"December");
        break;
    default:
        break;
    }
    sprintf(formatted_date,"%d %s %d",d,month,y);
    return formatted_date;
}


void FileGenerator(Machine*eleve,Utilisation p,char*Date)
{
        int i,j,oui,non,perso,pres,abs;
        char *filename,* mode;
        filename=GenerateFileName(p,Date);
        mode=UtilisationToStr(p);
        FILE*file=Open(filename,"w");
        fprintf (file,"LIST OF '%s'\t\t\t\tDate:%s\n",mode,Date);
        fprintf(file,"%-*s|%-*s|%-*s|%-*s",WIDTH_num,"NUM",WIDTH_name, "NAME", WIDTH_prenames, "PRENAMES", WIDTH_DATA, "DATA");
        fprintf(file,"|%s\n","TIME");
        Countstudent(eleve,&abs,&oui,&non,&perso,&pres);
        j=-1;
        switch (p)
        {
            case ALL:
            {
                for (i = 0; i < STUDENT_N; i++) 
                {
                    fdisplayByMain(&eleve[i],file);
                }
                fprintf(file,"\nTotal number of student:%d\n",STUDENT_N);
                fprintf(file,"Present number:%d\tAbsent number:%d\nStudent number depending on usage type:\n",pres,abs);
                fprintf(file,"OUI:%d\tNON:%d\tPERSO:%d\n\n",oui,non,perso);
                break;
            }
            case PRESENT:
            {
                for (i = 0; i < STUDENT_N; i++)            
                {
                    if(eleve[i].utilisation>ABSENT && eleve[i].utilisation<ALL)
                        {
                            fdisplayByMain(&eleve[i],file);
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
                            fdisplayByMain(&eleve[i],file);
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
                        fdisplayByMain(&eleve[i],file);
                        j++;
                    }

                }
                break;
            }
        }
        if(p!=ALL)
            {
                fprintf(file,"\nStopped the list at %d students\n",j);
            }
    fprintf(file,"--------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n📁 file '%s' container of the list of '%s' created successfully\n\n",filename,mode);
    free(filename);
    free(mode);
    fclose(file);
}

char* GenerateFileName(Utilisation p,const char *Date)
{       
    char *filename=allocChar1(50);
    strcpy(filename,"FileCreated/");
    strcat(filename,Date);   
        switch (p)
        {
        case OUI:
            strcat(filename,"-OUI.txt");
            break;
        case NON:
            strcat(filename,"-NON.txt");
            break;
        case PERSO:
            strcat(filename,"-PERSO.txt");
            break;
        case ABSENT:
            strcat(filename,"-ABSENT.txt");
            break;
        case PRESENT:
            strcat(filename,"-PRESENT.txt");
            break;
        case ALL:
            strcat(filename,"-TOUS_LES-ELEVES.txt");
            break;
        }
        return(filename);

}
char* UtilisationToStr(Utilisation p)
{    
    char *str=allocChar1(11);  
        switch (p)
        {
        case OUI:
            strcpy(str,"OUI");
            break;
        case NON:
            strcpy(str,"NON");
            break;
        case PERSO:
            strcpy(str,"PERSO");
            break;
        case ABSENT:
            strcpy(str,"ABSENT");
            break;
        case PRESENT:
            strcpy(str,"PRESENTS");
            break;
        case ALL:
            strcpy(str,"ALL_STUDENTS");
            break;
        }

        return(str);

}

void fdisplayByMain(Machine*eleve,FILE*file)
{   
    char all_prenames[WIDTH_prenames];
    int j;
    fprintf(file,"%-*d|%-*s|",WIDTH_num,eleve->numero, WIDTH_name, eleve->name);
    strcpy(all_prenames, "");
    for ( j = 0; j < eleve->n_prename; j++) 
    {
        strcat(all_prenames, eleve->prename[j]);
        if (j < eleve->n_prename - 1) 
            {
                strcat(all_prenames, " ");
            }
    }
    fprintf(file,"%-*s|", WIDTH_prenames, all_prenames);

   // Écrire la donnée variable
    fprintf(file,"%-*s|%02d:%02d:%02d\n", WIDTH_DATA, eleve->presence, eleve->t.tm_hour, eleve->t.tm_min, eleve->t.tm_sec);
}

int CountLine(FILE* file)
{   
    char str[MAX];
    int count=0;
    while (fgets(str,MAX,file)!=NULL)
        count++;
    rewind(file);
    return (count);  
    
}

void to_lowercase(char *str) 
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') 
        {
            str[i] = str[i] + ('a' - 'A');
        }
    }
}

// Supprimer les espaces d'une chaîne
void remove_spaces(char *str) 
{
    char *i = str;
    char *j = str;
    while(*j != 0) 
    {
        *i = *j++;
        if(*i != ' ') 
        {
            i++;
        }
    }
    *i = 0;
}

// Normaliser une chaîne en la convertissant en minuscules et en supprimant les espaces
char *normalize_string(const char *str) 
{
    int n = strlen(str);
    char *normalized = malloc((n + 1) * sizeof(char));
    strcpy(normalized, str);
    to_lowercase(normalized);
    trim_spaces(normalized);
    return (normalized);
}

// Fonction de recherche qui retourne un tableau d'index ou NULL
int *search1(Machine *student, const char *critere, int *found_count) 
{
    // Allouer de la mémoire pour stocker les index trouvés
    int *indices = malloc(STUDENT_N * sizeof(int));
    int count = 0,i,j,num,n=0;
    char *normalized_name;
    char *normalized_prename;
    char *all_prenames;
    char *name_combinated;
    // Normaliser le critère de recherche
    char *normalized_critere = normalize_string(critere);
    for ( i = 0; i < STUDENT_N; i++) 
    {    
        n=0;
        // Normaliser le name de l'étudiant
        normalized_name = normalize_string(student[i].name);
        for(j=0;j<student[i].n_prename;j++)
        {       
            n+=strlen(student[i].prename[j]);
        }
        all_prenames=allocChar1(n+2+student[i].n_prename);
        name_combinated=allocChar1(n+4+student[i].n_prename+strlen(student[i].name));
        strcpy(all_prenames,"");
        strcpy(name_combinated,"");
        strcat(name_combinated,normalized_name);
        strcat(name_combinated," ");
        // Vérifier si le name de l'étudiant contient le critère
        if (strstr(normalized_name, normalized_critere) != NULL) 
        {
            indices[count++] = i;
            free(normalized_name);
            continue;
        }
        free(normalized_name);

        // Vérifier si un des prénames de l'étudiant contient le critère
        for ( j = 0; j < student[i].n_prename; j++) 
        {
             normalized_prename = normalize_string(student[i].prename[j]);
            
            if (strstr(normalized_prename, normalized_critere) != NULL) 
            {
                indices[count++] = i;
                free(normalized_prename);
                break;
            }
            strcat(all_prenames,normalized_prename);
            strcat(name_combinated,normalized_prename);
            strcat(name_combinated," ");
            strcat(all_prenames," ");
            free(normalized_prename);
        }
    
        if (strstr(all_prenames, normalized_critere) != NULL) 
        {
            indices[count++] = i;
            free(all_prenames);
            continue;
        }
        // Vérifier si le numéro de l'étudiant correspond au critère
        if (strstr(name_combinated, normalized_critere) != NULL) 
        {
            indices[count++] = i;
            free(all_prenames);
            continue;
        }
        num = atoi(critere);
        if (num == student[i].numero) 
        {
            indices[count++] = i;
        }
        
    }

    free(normalized_critere);

    // Si aucune correspondance n'a été trouvée, retourner NULL
    if (count == 0) 
    {
        free(indices);
        *found_count = 0;
        return NULL;
    }

    // Mettre à jour le namebre de correspondances trouvées et retourner les index
    *found_count = count;
    return indices;
}

void trim_spaces(char *str) 
{
    char *start = str;
    char *end;

    // Trouver la première position non-espace
    while (*start == ' ') 
    {
        start++;
    }

    // Si la chaîne est vide après avoir supprimé les espaces de début
    if (*start == 0) 
    {
        str[0] = 0;
        return;
    }

    // Trouver la dernière position non-espace
    end = start + strlen(start) - 1;
    while (end > start && *end == ' ') 
    {
        end--;
    }

    // Écrire un caractère nul après la dernière position non-espace
    end[1] = '\0';

    // Déplacer la chaîne modifiée au début de l'original
    memmove(str, start, end - start + 2);
}


