#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TASKS 100
#define FILENAME_TASKS "tasks.txt"

typedef struct
{
    int id;
    char title[50];
    char addingDate[10];
    char deadline[10];
    char status[10];
} Task;

// Prototypes
void addTask();
void editTask();
void showAllTasks();
void showTodaysTasks();
void deleteTask();
int menu();
int generateTaskId();

int main()
{

    int input = menu(0);
    // printf("Input from Main Function: %d\n", input);
    switch (input)
    {
    case 1:
        addTask();
        break;

    default:
        break;
    }

    return 0;
}

int menu(int current)
{
    int choice;
    do
    {
        printf("\n*** Main Menu ***\n");
        printf("1. Add Task.\n");
        printf("2. Show All Tasks.\n");
        printf("3. Show Todays Tasks.(Under Construction)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting program.\n");
            exit(0);
        }
        else if (choice > 4)
        {
            printf("Invalid choice. Try again.\n");
        }
        else
            return choice;

    } while (choice > 4);
}

int generateTaskId()
{
    FILE *file = fopen(FILENAME_TASKS, "r");
    printf("d");
    if (file == NULL)
        return 1;

    printf("dd");
    Task tsk;
    while (fscanf(file, "%d %s %s %s %s", &tsk.id, &tsk.title, &tsk.addingDate, &tsk.deadline, &tsk.status) != EOF)
    {
    }
    fclose(file);
    printf("ddd");
    return tsk.id + 1;
}

void addTask()
{
    Task task;
    int id = generateTaskId();

    printf("Enter Title: ");
    scanf("%49s", task.title);
    printf("Enter Deadline: ");
    scanf("%49s", task.deadline);

    FILE *file = fopen(FILENAME_TASKS, "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %s %s %s\n", id, task.title, "12-02-2025", "14-02-2025", "Pending");
    fclose(file);
    printf("Task added successfully!\n");
}
