#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define STUDENT_N 75
#define MAX 200
#define N_CHAR 100
#define DATA_FILE_NAME "name1.csv"
#define FILE_NAME_Saveforhuman "ELEVEMACHINE.html"
#define FILE_NAME_Saveforprogram "et.csv"

enum WIDTH
{
WIDTH_num=3,
WIDTH_name=30,
WIDTH_prenames=50, 
WIDTH_DATA=10,
WIDTH_time=10
};
enum DataType
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
};
enum Utilisation
{   
    ABSENT,
    OUI,
    NON,
    PERSO,
    ALL,
    PRESENT
    
};
struct Machine 
{   
    int numero;
    char *name;
    char **prename;
    int utilisation;
    char presence[10];
    int n_prename;
    struct tm t;
};

typedef enum Utilisation Utilisation;   // Pour differencier l 'utilisation OUI ou NON ou PERSO du machine 
typedef struct Machine Machine;
typedef enum DataType DataType;

// Fonction pour initialiser la date de lancement
Machine* GetNameAndInitialize(void);//on prend les donner dans le fichier name.csv et le copier dans le tableau de structure Machine student
char* initializeLaunchDate();
void searchAndCheck(Machine *eleve);
void LoadData(Machine* student);
int choicefunction(Machine*student);
void menu_display(int *c);
void Save_for_human(Machine *eleve); //sauvegarder les données dans un fichier
void Save_for_program(Machine*student);

////////////////////////////////////////////////////////////////////

char *allocAndCopy(const char *src, int length); 
Machine* allocmemachine(int n);//ON alloue en memoire un tableau de une dimension de machine 
char** allocmemchar(int n,int p);//ON alloue en memoire un tableau de deux dimensions de char 
FILE* Open(const char *str,const char opt[2]);
int CountLine(FILE* file);// compter les lignes d un fichier
void searchDisplay(const Machine*eleve);
int removeLine(const char* filename,int n_lines_to_rm);
void DoPresence(Machine* student);
void display (Machine *eleve,Utilisation p,char*Date); //final display
void displayByMain(Machine*eleve);
void displaySubchoice(int *c,int a);
void freemem(Machine* student);  //liberer le memoire occupé par le Machine
void freeTabLine(char ** Tab,int l);
void read_input(const char *label,DataType type, void *variable); 
struct tm* GetTime();
char** allocmemchar2(int n);
char* allocChar1(int n);
void AttributeTime(Machine* student);
void Final_Display(int *c);
void Countstudent(Machine*student,int *abs,int*oui,int*non,int*perso,int*pres);
Machine* GetArchive(char *date);
char* GetDateForDisplayArchive(void);
void errorDisplay(void);
char *dateToString(const char *date_str); 
char* GenerateFileName(Utilisation p,const char *Date);
void FileGenerator(Machine*eleve,Utilisation p,char*Date);
char* UtilisationToStr(Utilisation p);
void fdisplayByMain(Machine*eleve,FILE*file);
void remove_spaces(char *str);
void to_lowercase(char *str);
char *normalize_string(const char *str);
int *search1(Machine *student, const char *critere, int *found_count);
void trim_spaces(char *str);
void displayChoiceSearch(int *c);
void tabulation(void);
