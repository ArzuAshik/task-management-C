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
    char deadline[11];
    int status;
} Task;

// Prototypes
void addTask();
void editTask();
void showAllTasks();
void showTodaysTasks();
void deleteTask();
int menu();
int generateTaskId();
const char *getStatus();

int main()
{

    int input = 0;
    // printf("Input from Main Function: %d\n", input);
    do
    {
        input = menu(0);
        switch (input)
        {
        case 0:
            printf("Exiting The Program.");
            exit(0);
        case 1:
            addTask();
            break;
        case 2:
            showAllTasks();
            break;

        default:
            printf("Invalid Input");
            break;
        }
    } while (input > 0);

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
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting program.\n");
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

    Task tsk;
    while (fscanf(file, "%d %d %s %s", &tsk.id, &tsk.status, &tsk.title, &tsk.deadline) != EOF)
    {
    }
    fclose(file);
    return tsk.id + 1;
}

const char *getStatus(int status)
{
    switch (status)
    {
    case 0:
        return "Pending";
    case 1:
        return "In-Progress";
    case 2:
        return "Done";
    default:
        return "Invalid Status";
    }
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
    fprintf(file, "%d %d %s %s\n", id, 0, task.deadline, task.title);
    fclose(file);
    printf("Task added successfully!\n");
}

void showAllTasks()
{
    // printf("hsldfh");
    FILE *file = fopen(FILENAME_TASKS, "r");
    if (file == NULL)
    {
        printf("No Task found!\n");
        return;
    }

    Task tsk;
    printf("\n%-5s %-12s %-12s %-10s\n", "ID", "Task Title", "Status", "Deadline");
    printf("%-5s %-12s %-12s %-10s \n", "--", "----------", "------", "------");

    while (fscanf(file, "%d %d %10s %s", &tsk.id, &tsk.status, &tsk.deadline, &tsk.title) != EOF)

        printf("%-5d %-12s %-12s %-5s\n", tsk.id, tsk.title, getStatus(tsk.status), tsk.deadline);

    fclose(file);
}