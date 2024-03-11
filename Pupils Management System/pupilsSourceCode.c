#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct StudentRecord{
    char regNum[50];
    char studentFirstname[50];
    char studentMiddlename[50];
    char studentLastname[50];
    char studentGrade[50];
    char date[12];
}sr;

FILE *filePointer;


int main() {


    int choice;

    while(1){
        system("cls");
        printf("                ======== PUPILS DATABASE MANAGEMENT SYSTEM =======\n");
        printf("\n1.  Add New Student\n");
        printf("2.  Show Student Records\n");
        printf("3.  Delete Student Record\n");
        printf("0.  Exit\n\n");
        printf("Enter your choice: (Eg. '1' to add new student) \n");
        scanf("%d", &choice);

        switch(choice){
        case 0:
            exit(0);

        case 1:
            AddStudent();
            break;

        case 2:
        studentRecords();
        break;

         case 3:
            del();
             break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}

void AddStudent(){
    system("cls");
    printf("                ======== ADD NEW STUDENT RECORD =======\n\n");
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(sr.date, myDate);

    filePointer = fopen("records.txt", "ab");

    printf("Enter Your Registration Number: \n");
    fflush(stdin);
    gets(sr.regNum);

    printf("\nEnter Your First Name: \n");
    fflush(stdin);
    gets(sr.studentFirstname);

    printf("\nEnter Your Middle Name: \n");
    fflush(stdin);
    gets(sr.studentMiddlename);

    printf("\nEnter Your Last Name: \n");
    fflush(stdin);
    gets(sr.studentLastname);

    printf("\nEnter Your Grade: \n");
    fflush(stdin);
    gets(sr.studentGrade);

    printf("        Your Informations are Successfully Submitted! \n");

    fwrite(&sr, sizeof(sr), 1, filePointer);
    fclose(filePointer);

}


void studentRecords(){

    system("cls");
    printf("                ======== REGISTERED STUDENT RECORDS =======\n\n");
    printf("%-20s %-15s %-15s %-15s %-15s %s\n\n", "REG_NUMBER", "LAST_NAME", "FIRST_NAME", "MIDDLE_NAME", "GRADE", "DATE_REGISTERED");

    filePointer = fopen("records.txt", "rb");
    while(fread(&sr, sizeof(sr), 1, filePointer) == 1){
    printf("%-20s %-15s %-15s %-15s %-15s %s\n\n", sr.regNum, sr.studentLastname, sr.studentFirstname, sr.studentMiddlename, sr.studentGrade, sr.date);
    }

    fclose(filePointer);
}

void del(){
    char regNum[50];
    int f =0;
    system("cls");
    printf("<== REMOVE STUDENT RECORDS ==>\n\n");
    printf("Enter Student Registration Number: \n");
    scanf("%s", &regNum);

    FILE *ft;

    filePointer = fopen("records.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&sr, sizeof(sr), 1, filePointer) == 1){
        if(strcmp(regNum, sr.regNum ) == 0){
            f=1;
        }else{
            fwrite(&sr, sizeof(sr), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully. \n");
    }else{
        printf("\n\nRecord Not Found ! \n");
    }

    fclose(filePointer);
    fclose(ft);

    remove("records.txt");
    rename("temp.txt", "records.txt");

}

