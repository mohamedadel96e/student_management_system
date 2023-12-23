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
void addStudent(struct Student students[], int* count); // Add students manually
void addStudents_db(struct Student students[],int* count);// add students from csv formated file
void displayAllStudents(const struct Student students[],int* count);// to display all students in the array
void searchStudent(const struct Student students[],int *count);// to search for a student in the array
void searchStudentByName(const struct Student students[],const int *count);
int  searchStudentById(const struct Student students[],const int *count);
void saveAllStudents(const struct Student students[],int* count);// to save the process in a file
void update_data(struct Student students[],int* count);// to update data of a student
void delete_student(struct Student students[],int* count);// delete a student from the array
void sort(struct Student students[],int* count);// sort the students array
void name_sort(struct Student students[],int* count);// sort by Name
void grade_sort(struct Student students[],int* count);//sort by grade
int isNumeric(const char str[]);// check if the inputed ID is numeric
void display_student(struct Student); // to display one student
int check_ID(const struct Student students[],int* count,const char ID[]);// to check if the inputed ID is exist or not
int main()
{
    struct Student students[MAX_STUDENTS]; // array of structs to save students data
    int studentCount = 0; // to count number of the students
    int choice;

    do{
        printf("\n\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\tStudent Database Management System\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\t| 1. Add Student                 |\n");
        printf("\t\t\t\t\t| 2. Add Students From CSV file  |\n");
        printf("\t\t\t\t\t| 3. Display All Students        |\n");
        printf("\t\t\t\t\t| 4. update student Data         |\n");
        printf("\t\t\t\t\t| 5. Delete Student              |\n");
        printf("\t\t\t\t\t| 6. Search For Student          |\n");
        printf("\t\t\t\t\t| 7. Sort Students               |\n");
        printf("\t\t\t\t\t| 8. Save Process                |\n");
        printf("\t\t\t\t\t| 9. Exit                        |\n");
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
                update_data(students,&studentCount);
                system("cls");
                break;
            case 5:
                system("cls");
                delete_student(students,&studentCount);
                system("cls");
                break;
            case 6:
                system("cls");
                searchStudent(students,&studentCount);
                system("cls");
                break;
            case 7:
                system("cls");
                sort(students,&studentCount);
                system("cls");
                break;
            case 8:
                system("cls");
                saveAllStudents(students,&studentCount);
                system("cls");
                break;
            case 9:
                system("cls");
                printf("\n\n\n\t\t\t\t\tExiting program. Goodbye!\n");
                break;
            default:
                system("cls");
                printf("\n\n\n\t\t\t\t\tInvalid choice. please enter a valid number!!\n");
                sleep(1);
                system("cls");
        }

    }while(choice != 9);
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
        if(check_ID(students,count,newStudent.id))
        {
            printf("\t\t\t\t\tThis ID is already exist!!!\n");
            sleep(2);
            return;
        }
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
        if(newStudent.grade < 0)
        {
            printf("\t\t\t\t\tInvalid Grade , must be positive!");
            return;
        }
        students[*count] = newStudent;
        (*count)++;
        printf("\n\n\t\t\t\t\tStudent added successfully! \n");
        printf("\t\t\t\t\tThe Number Of empty spaces = %d",MAX_STUDENTS - (*count));
        sleep(1);
    }else{
        printf("\t\t\t\t\tStudent database is full. Cannot add more students.\n");
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
    printf("\n\t\t\t\t\t==========================================    \n");
    printf("\t\t\t\t\t            Add Student Info\n");
    printf("\t\t\t\t\t==========================================    \n");
    printf("\n\t\t\t\t\tEnter The name Of the file\"FileName.csv\":\n\t\t\t\t\t ");
    scanf("%s",file_name);
    FILE * csv_file = fopen(file_name,"r");
    if(csv_file == NULL){
        fprintf(stderr,"\n\t\t\t\t\tError opening file!\n");
        sleep(2);
        return;
    }

    do
    {
        read = fscanf(csv_file,"%14[^,],%49[^,],%d,%f\n",new_student.id,new_student.name,&new_student.age,&new_student.grade);

        if(check_ID(students,count,new_student.id))
        {
            printf("/t/t/t/t/tThere is an Id already exist With index %d in program!\n",*(count - 1));
            continue;
        }
        if(new_student.grade < 0)
        {
            printf("\t\t\t\t\tInvalid Grade , must be positive!");
            continue;
        }
        if (read == 4 )
        {
            students[*count] = new_student;
            (*count)++;
            records++;
        }

        if(read != 4 )
        {
            printf("\n\t\t\t\t\tFile format incorrect.\n");
            fclose(csv_file);
            sleep(3);
            return;
        }
        if(ferror(csv_file))
        {
            printf("\n\t\t\t\t\tError Reading file.\n");
            fclose(csv_file);
            sleep(3);
            return;
        }

    }while(!feof(csv_file));
    printf("\t\t\t\t\tThe Number Entered = %d\n",records);
    printf("\t\t\t\t\tThe Number Of empty spaces = %d",MAX_STUDENTS - (*count));
    sleep(3);
    fclose(csv_file);

    }



void displayAllStudents( const struct Student students[],int* count)
{
    // TODO

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

int searchStudentById(const struct Student students[],const int* count)
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
        if(strcmp(searchID ,students[i].id) == 0)
        {
            system("cls");
            display_student(students[i]);
            return i;
        }
    }
    printf("\t\t\t\t\tThis Student is not exist!!\n");
    sleep(2);
    return -1;

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
    printf("\n\t\t\t\t\t press any key to continue.\n");
    getch();
}

void searchStudent(const struct Student students[],int *count)
{
    //TODO
    int choice ;
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t     Search Student\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        1-Search by ID \n");
    printf("\t\t\t\t\t        2-Search by name\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\tEnter Your choice: ");
    scanf("%d",&choice) ;
    switch(choice)
    {
        case 1:
            system("cls");
            searchStudentById(students,count);
            system("cls");
            break ;

        case 2:
            system("cls");
            searchStudentByName(students,count);
            system("cls");
            break;

        default :
            printf("\t\t\t\t\t Invalid choice\n");
            printf("\t\t\t\t\t==================================    \n");
            sleep(2);
            system("cls");
            return searchStudent(students,count);
    }
}
void searchStudentByName(const struct Student students[],const int *count)
{
    //TODO
    char name[50];
    int name_flag = 0;
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Search By Name\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\tEnter The name to search: ");
    fflush(stdin);
    gets(&name);
    for(int i =0 ; i< *count; i++)
    {
        if(!strcmp(name,students[i].name))
        {
            if(name_flag == 0)
                system("cls");
            name_flag++;
            display_student(students[i]);
        }
    }
    if(name_flag == 0)
    {
        printf("\t\t\t\t\t This student is not exist!!\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\n\t\t\t\t\t press any key to back.\n");
        getch();
    }
    }

void update_data(struct Student students[],int* count)
{
    //TODO
    int index ;
    int choice;
    struct Student newStudent;
    index = searchStudentById(students,&count);
    if(index >= 0)
    {
        printf("\n\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\t        Update Student data\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\twhat is the data do want to update: \n");
        printf("\t\t\t\t\t 1.ID \n");
        printf("\t\t\t\t\t 2.Name\n");
        printf("\t\t\t\t\t 3.Age\n");
        printf("\t\t\t\t\t 4.Grade\n");
        printf("\t\t\t\t\t==================================    \n");
        printf("\t\t\t\t\tEnter Your Choice: ");
        scanf("%d",&choice) ;
        newStudent = students[index];
        switch(choice)
        {
            case 1:

                printf("\t\t\t\t\tEnter the New ID: ");
                scanf("%s",newStudent.id );
                if(check_ID(students,count,newStudent.id))
                {
                    printf("\t\t\t\t\tThis ID is already exist!");
                    return;
                }
                students[index] = newStudent;
                break;
            case 2:
                printf("\t\t\t\t\tEnter the New Name: ");
                scanf("%s",newStudent.name);
                students[index] = newStudent;
                break;
            case 3:
                printf("\t\t\t\t\tEnter the New Age: ");
                scanf("%d",&newStudent.age);
                students[index] = newStudent;
                break;
            case 4:
                printf("\t\t\t\t\tEnter the New Grade: ");
                scanf("%f",&newStudent.grade);
                if(newStudent.grade < 0)
                {
                    printf("\t\t\t\t\tInvalid Grade , must be positive!");
                    return;
                }
                students[index] = newStudent;
                break;
            default:
                printf("\t\t\t\t\t Invalid Choice!!!!!!");
                sleep(3);
                return;
        }
    }


}
void sort(struct Student students[],int* count)
{
    //TODO
    int choice;
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Sorting Data\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\twhat is the data do want to sort by: \n");
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        1-Name \n");
    printf("\t\t\t\t\t        2-Grade\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\tEnter Your Choice: ");
    scanf("%d",&choice) ;
    switch(choice)
    {

        case 1:
            name_sort(students,count);
            break;
        case 2:
            grade_sort(students,count);
            break;
        default:
            printf("\t\t\t\t\t Invalid Choice!!!!!!");
            sleep(3);
            return;
    }
}

void name_sort(struct Student students[],int* count)
{
    //TODO
    struct Student temp;
    for(int i = 0;i < *count; i++)
    {
        for(int j = 0; j < (*count) - i - 1;j++)
        {
            if(strcmp(students[j].name , students[j + 1].name) > 0)
            {
                temp = students[j];
                students[j]= students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    if(*count > 0)
    {
        printf("\t\t\t\t\tStudents Sorted Now.\n");
        sleep(2);
    }
    else{
        printf("\t\t\t\t\tThere are no students!!\n");
        sleep(2);
    }

    return;
}
void grade_sort(struct Student students[],int* count)
{
    //TODO
    int sort_type;
    struct Student temp;
    printf("\t\t\t\t\tEnter sort type\n\t\t\t\t\t1.ASC\n\t\t\t\t\t2.DESC\n ");
    printf("\t\t\t\t\tEnter your choice: ");
    scanf("%d",&sort_type);
    switch(sort_type)
        {

        case 1:
            for (int i = 0; i < *count; i++)
            {
                for(int j = 0; j < (*count)- 1 - i;j++)
                {
                    if(students[j].grade > students[j + 1].grade)
                    {
                        temp = students[j];
                        students[j] = students[j + 1];
                        students[j + 1] = temp;
                    }
                }
            }
            if(*count > 0)
            {
                printf("\t\t\t\t\tStudents Sorted Now.\n");
                sleep(2);
            }
            else{
                printf("\t\t\t\t\tThere are no students!!\n");
                sleep(2);
            }
            break;
        case 2:
            for (int i = 0; i < *count; i++)
            {
                for(int j = 0; j < (*count)- 1 - i;j++)
                {
                    if(students[j].grade < students[j + 1].grade)
                    {
                        temp = students[j];
                        students[j] = students[j + 1];
                        students[j + 1] = temp;
                    }
                }
            }
            if(*count > 0)
            {
                printf("\t\t\t\t\tStudents Sorted Now.\n");
                sleep(2);
            }
            else{
                printf("\t\t\t\t\tThere are no students!!\n");
                sleep(2);
            }
            break;
        default:
            printf("\t\t\t\t\tINVALID Input!!!\n");
            return;
        }

}
void delete_student(struct Student students[],int* count)
{
    char ID[15];
    printf("\n\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\t        Delete Data\n");
    printf("\t\t\t\t\t==================================    \n");
    printf("\t\t\t\t\tEnter The ID of the Student: ");
    scanf("%s",ID);
    for(int i = 0;i < *count;i++)
    {
        if(!strcmp(ID,students[i].id))
        {
            for (int j = i;j < (*count) - 1;j++)
            {
                if(j < (*count) -1)
                {
                    students[j] = students[j + 1];
                }
            }
            (*count)--;
            printf("\t\t\t\t\tData has been Deleted Successfully.\n");
            sleep(3);
            return;
        }
    }
    printf("\t\t\t\t\tThis ID is not exist!!");
    sleep(3);

}
int check_ID(const struct Student students[],int* count,const char ID[])
{
    if((*count) == 0)
    {
        return 0;
    }
    for( int i = 0; i < (*count); i++)
    {
        if(strcmp(ID,students[i].id) == 0)
        {
            return 1;
        }
    }
    return 0;
}

