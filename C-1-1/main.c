// C-1: Student Achievement Management System

#include <stdbool.h>
#include <stdio.h>
#define MAX 100
#define NOT_FOUND -1
#define FILE_NAME "students.txt"

struct Student {
    int id;
    char name[20];
    float CH;
    float MA;
    float EN;
    float score;
};
typedef struct Student Stu;

// basic functions
void read(Stu *Students, int *num);
void write(Stu *Students, int num);
int findIndex(Stu *Students, int num, int id);
bool IsFull(int num);
bool IsEmpty(int num);

// menus functions
bool add(Stu *Students, int *num);
bool delete(Stu *Students, int *num);
bool alter(Stu *Students, int num);
bool search(Stu *Students, int num);
void sort(Stu *Students, int num);
void print(Stu *Students, int num);

int main() {
    int choice = -1;
    Stu Students[MAX] = {0};
    int Num = 0;
    read(Students, &Num);
    printf("Welcome to the Student Achievement Management System!\n");
    while (choice != 0) {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Alter Student\n");
        printf("4. Search Id\n");
        printf("5. Sort Students\n");
        printf("6. Print Students\n");
        printf("0. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                add(Students, &Num); // w
                break;
            }
            case 2: {
                delete(Students, &Num); // read+delete+write
                break;
            }
            case 3: {
                alter(Students, Num); // read+delete+write
                break;
            }
            case 4: {
                search(Students, Num); // read
                break;
            }
            case 5: {
                sort(Students, Num); // read+sort+write
                break;
            }
            case 6: {
                print(Students, Num); // read
                break;
            }
            case 0: {
                printf("Exiting the system.\n");
                break;
            }
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void read(Stu *Students, int *num) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    // Read student data from file
    int n = 0;
    char line[MAX];

    // 文件格式示例：1001 张三 90 88 92
    while (n < MAX && fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d %19s %f %f %f", 
            &Students[n].id, 
            Students[n].name,
            &Students[n].CH,
            &Students[n].MA, 
            &Students[n].EN) == 5
        ) {
            Students[n].score = Students[n].CH + Students[n].MA + Students[n].EN;
                n++;
        }
    }
    *num = n;
    fclose(fp);
}
void write(Stu *Students, int num) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    for (int i = 0; i < num; i++) {
        fprintf(fp, "%d %s %.2f %.2f %.2f\n", 
            Students[i].id, 
            Students[i].name,
            Students[i].CH, 
            Students[i].MA, 
            Students[i].EN);
    }
    fclose(fp);
}
int findIndex(Stu *Students, int num, int id) {
    for (int i = 0; i < num; i++) {
        if (Students[i].id == id) {
        return i;
        }
    }
    printf("Student with ID %d not found.\n", id);
    return NOT_FOUND; // Not found
}
bool IsFull(int num) { return num >= MAX; }

bool IsEmpty(int num) { return num == 0; }

//------

bool add(Stu *Students, int *num) {
    if (IsFull(*num)) {
        printf("The student list is full. Cannot add more students.\n");
        return false;
    }
    // Read student information from the user
    Stu s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter name: ");
    scanf("%19s", s.name);
    printf("Enter CH score: ");
    scanf("%f", &s.CH);
    printf("Enter MA score: ");
    scanf("%f", &s.MA);
    printf("Enter EN score: ");
    scanf("%f", &s.EN);
    s.score = s.CH + s.MA + s.EN;

    Students[*num] = s;
    (*num)++;
    write(Students, *num);
    return true;
}
bool delete(Stu *Students, int *num) {
    if (IsEmpty(*num)) {
        printf("The student list is empty. Cannot delete any students.\n");
        return false;
    }
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);
    int index = findIndex(Students, *num, id);
    if (index == NOT_FOUND) {
        return false;
    }

    for (int i = index; i < *num - 1; i++) {
        Students[i] = Students[i + 1];
    }
    (*num)--;
    write(Students, *num);
    return true;
}
bool alter(Stu *Students, int num) {
    if (IsEmpty(num)) {
        printf("The student list is empty. Cannot alter any students.\n");
        return false;
    }
    int id;
    printf("Enter the ID of the student to alter: ");
    scanf("%d", &id);
    int index = findIndex(Students, num, id);
    if (index == NOT_FOUND) {
        return false;
    }
    // Read new information for the student
    printf("Enter new id: ");
    scanf("%d", &Students[index].id);
    printf("Enter new name: ");
    scanf("%19s", Students[index].name);
    printf("Enter new CH score: ");
    scanf("%f", &Students[index].CH);
    printf("Enter new MA score: ");
    scanf("%f", &Students[index].MA);
    printf("Enter new EN score: ");
    scanf("%f", &Students[index].EN);
    Students[index].score =
        Students[index].CH + Students[index].MA + Students[index].EN;

    write(Students, num);
    return true;
}
bool search(Stu *Students, int num) {
    if (IsEmpty(num)) {
        printf("The student list is empty. Cannot search any students.\n");
        return false;
    }
    int id;
    printf("Enter the ID of the student to search: ");
    scanf("%d", &id);
    int index = findIndex(Students, num, id);
    if (index == NOT_FOUND) {
        return false;
    }
    printf("Student found: ID: %d, Name: %s, CH: %.2f, MA: %.2f, EN: %.2f, TotalScore: %.2f\n",
            Students[index].id, 
            Students[index].name, 
            Students[index].CH,
            Students[index].MA, 
            Students[index].EN, 
            Students[index].score);
    return true;
}
void sort(Stu *Students, int num) {
    if (IsEmpty(num)) {
        printf("The student list is empty. Cannot sort any students.\n");
        return;
    }
    // Simple bubble sort based on total score
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
        if (Students[j].score < Students[j + 1].score) {
            Stu temp = Students[j];
            Students[j] = Students[j + 1];
            Students[j + 1] = temp;
        }
        }
    }
    write(Students, num);
}
void print(Stu *Students, int num) {
    if (IsEmpty(num)) {
        printf("The student list is empty. Nothing to print.\n");
        return;
    }
    printf("ID\tName\tCH\tMA\tEN\tTotal\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n", 
            Students[i].id, 
            Students[i].name,
            Students[i].CH, 
            Students[i].MA, 
            Students[i].EN, 
            Students[i].score
        );
    }
}