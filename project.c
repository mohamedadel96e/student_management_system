#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STUDENTS 100
// structure to represent a student
struct Student {
    char id[15];
    char name[50];
    int age;
    float grade;
}Student;
// Function prototypes
void addStudent(struct Student students[], int* count);
void addStudents_db(struct Student students[],int* count);
void displayAllStudents(const struct Student students[],int* count);
void searchStudent(const struct Student students[],int *count);// New
void searchStudentByName(const struct Student students[],int *count);//New
void searchStudentById(const struct Student students[],int *count);
void saveAllStudents(const struct Student students[],int* count);
void update_data(struct Student students[],int* count);//New
void delete_student(struct Student students[],int* count);
void sort(struct Student students[],int* count);//New
void ID_sort(struct Student students[],int* count);//New
void name_sort(struct Student students[],int* count);//New
void grade_sort(struct Student students[],int* count);//New
int isNumeric(const char str[]);
void display_student(struct Student);
int main()
{
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do{
        printf("\n\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\tStudent Database Management System\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\t| 1. Add Student                 |\n");
        printf("\t\t\t\t\t| 2. Add Students From CSV file  |\n");
        printf("\t\t\t\t\t| 3. Display All Students        |\n");
        printf("\t\t\t\t\t| 4. Search Student By ID        |\n");
        printf("\t\t\t\t\t| 5. Save Process                |\n");
        printf("\t\t\t\t\t| 6. Exit                        |\n");
        printf("\t\t\t\t\t|  Enter your choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                system("cls");
                addStudent(students,&studentCount);
                system("cls");
                break;
            case 2:
                system("cls");
                addStudents_db(students,&studentCount);
                system("cls");
                break;
            case 3:
                system("cls");
                displayAllStudents(students,&studentCount);
                system("cls");
                break;
            case 4:
                system("cls");
                searchStudentById(students,&studentCount);
                system("cls");
                break;
            case 5:
                system("cls");
                saveAllStudents(students,&studentCount);
                system("cls");
                break;
            case 6:
                system("cls");
                printf("\n\n\n\t\t\t\t\tExiting program. Goodbye!\n");
                break;
            default:
                system("cls");
                printf("\n\n\n\t\t\t\t\tInvalid choice. please enter a valid number!!\n");
                return 1;
        }

    }while(choice != 6);
    return 0;
}

void addStudent(struct Student students[], int* count)
{
    // TODO

    if(*count < MAX_STUDENTS)
    {
        struct Student newStudent;
        printf("\n\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\t        Add Student Info\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\n\t\t\t\t\tEnter Student ID   : ");
        scanf("%s",&newStudent.id);
        if(!isNumeric(newStudent.id))
        {
            printf("\n\t\t\t\t\tError, Invalid ID!!!");
            sleep(2);
            return;
        }
        fflush(stdin);
        printf("\n\t\t\t\t\tEnter Student name : ");
        gets(&newStudent.name);
        printf("\n\t\t\t\t\tEnter Student age  : ");
        scanf("%d",&newStudent.age);
        printf("\n\t\t\t\t\tEnter student grade: ");
        scanf("%f",&newStudent.grade);
        students[*count] = newStudent;
        (*count)++;
        printf("\n\n\t\t\t\t\tStudent added successfully! \n");
        sleep(1);
    }else{
        printf("Student database is full. Cannot add more students.\n");
        sleep(1);
    }

}

void addStudents_db(struct Student students[],int* count)
{
    // TODO

    int read = 0;
    unsigned short records = 0;
    struct Student new_student;
    char file_name[50];
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Add Student Info\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\n\t\t\t\t\tEnter The name Of the file\"FileName.csv\": ");
    scanf("%s",file_name);
    FILE * csv_file = fopen(file_name,"r");
    if(csv_file == NULL){
        fprintf(stderr,"Error opening file!\n");
        sleep(2);
        return;
    }
    /*char buffer[1024];
    if (fgets(buffer, sizeof(buffer), csv_file) == NULL) {
        perror("Error reading file");
        sleep(2);
        fclose(csv_file);
        return;
    }*/
    do
    {
        read = fscanf(csv_file,"%14[^,],%49[^,],%d,%f\n",new_student.id,new_student.name,&new_student.age,&new_student.grade);

        if (read == 4 )
        {
            students[*count] = new_student;
            (*count)++;
            records++;
        }

        if(read != 4 )
        {
            printf("File format incorrect.\n");
            fclose(csv_file);
            sleep(3);
            return;
        }
        if(ferror(csv_file))
        {
            printf("Error Reading file.\n");
            fclose(csv_file);
            sleep(3);
            return;
        }

    }while(!feof(csv_file));
    printf("The Number Entered = %d\n",records);
    printf("The Number Of empty spaces = %d",MAX_STUDENTS - (*count));
    sleep(5);
    fclose(csv_file);

    }



void displayAllStudents( const struct Student students[],int* count)
{
    // Mohammed El Shafey

    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Display All Students\n");
    printf("\t\t\t\t\t==================================    \n");

    for(int i = 0;i < *count; i++)
    {
       printf("\n\t\t\t\t\t student ID    : %s",students[i].id);
       printf("\n\t\t\t\t\t student name  : %s",students[i].name);
       printf("\n\t\t\t\t\t student age   : %d",students[i].age);
       printf("\n\t\t\t\t\t student grade : %.2f",students[i].grade);
       printf("\n\t\t\t\t\t__________________________________\n");

    }
    printf("\n\t\t\t\t\t press any key to back.\n");
    getch();
}

void searchStudentById(const struct Student students[],int* count)
{
    // TODO
    char searchID[15];
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Search student by ID\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\tEnter student ID to search: ");
    scanf("%s",searchID);

    for(int i = 0; i < *count;i++)
    {
        if(!strcmp(searchID ,students[i].id))
        {
            display_student(students[i]);
            return;
        }
    }
    printf("This Student is not exist!!\n");
    sleep(2);

}

void saveAllStudents(const struct Student students[],int* count)
{
    // TODO
    char fileName[50];
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Save Students\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\n\t\t\t\t\tEnter File Name (\"filename.csv\"):\n\t\t\t\t\t");
    scanf("%s",fileName);
    FILE * csv_file = fopen(fileName,"w");
    if(csv_file == NULL)
    {
        fprintf(stderr,"\n\t\t\t\t\tError Opening file!!");
        return;
    }
    // CSV file format: ID,Name,Age,Grade
    // Write CSV header
    //fprintf(csv_file, "ID,Name,Age,Grade\n");
    // Write each struct to the CSV file
    for(int i = 0;i < *count; i++)
    {
        fprintf(csv_file,"%s,%s,%d,%.2f\n",students[i].id,students[i].name,students[i].age,students[i].grade);
    }
    //close the file
    fclose(csv_file);
    printf("\n\n\t\t\t\t\tStudents Saved successfully! \n");
    sleep(1);
}

int isNumeric(const char str[]) {
    // Check if each character in the string is a digit
    for(int i = 0; i < strlen(str);i++)
    {
        if(!isdigit(str[i]))
        return 0;//not a digit

    }
    return 1; // is a digit
}
void display_student(struct Student student)
{
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Display Student\n");
    printf("\t\t\t\t\t==================================    \n");


    printf("\n\t\t\t\t\t student ID    : %s",student.id);
    printf("\n\t\t\t\t\t student name  : %s",student.name);
    printf("\n\t\t\t\t\t student age   : %d",student.age);
    printf("\n\t\t\t\t\t student grade : %.2f",student.grade);
    printf("\n\t\t\t\t\t__________________________________\n");


    printf("\n\t\t\t\t\t press any key to back.\n");
    getch();
}

void searchStudent(const struct Student students[],int *count)
{
    //TODO
}
void searchStudentByName(const struct Student students[],int *count)
{
    //TODO
}
void update_data(struct Student students[],int* count)
{
    //TODO
}
void sort(struct Student students[],int* count)
{
    //TODO
}
void ID_sort(struct Student students[],int* count)
{
    //TODO
}
void name_sort(struct Student students[],int* count)
{
    //TODO
}
void grade_sort(struct Student students[],int* count)
{
    //TODO
}
