#include "file.h"

int main ()
{   
    Machine*student=NULL;
    int choice;
    student=GetNameAndInitialize();
    LoadData(student);
    choice=choicefunction(student); //le vrai cerveau 
    if (choice==4)
    {   
        removeLine(FILE_NAME_Saveforhuman,STUDENT_N+9);
        removeLine(FILE_NAME_Saveforprogram,STUDENT_N+2);
        Save_for_human(student);
        Save_for_program(student);
    }
    freemem(student);
    return 0;
}
///////////////////////////////////////////////////




