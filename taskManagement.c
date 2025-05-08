#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
void updateTask(int id);
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
        case 3:
            showTodaysTasks();
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
        printf("3. Show Todays Tasks.\n");
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
    // printf("d");
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
    printf("Enter Deadline: (YYYY-MM-DD) ");
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

    int choice;
    printf("Do you want to update a task? (1: Yes, 0: No): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        int id;
        printf("Enter Task ID to update: ");
        scanf("%d", &id);
        updateTask(id);
    }
}

void showTodaysTasks()
{
    FILE *file = fopen(FILENAME_TASKS, "r");
    if (file == NULL)
    {
        printf("No Task found!\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char today[11];
    sprintf(today, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    Task tsk;
    int found = 0;
    printf("\nToday's Tasks (%s):\n", today);
    printf("\n%-5s %-12s %-12s %-10s\n", "ID", "Task Title", "Status", "Deadline");
    printf("%-5s %-12s %-12s %-10s\n", "--", "----------", "------", "---------");

    while (fscanf(file, "%d %d %10s %s", &tsk.id, &tsk.status, tsk.deadline, tsk.title) != EOF)
    {
        if (strcmp(tsk.deadline, today) == 0)
        {
            printf("%-5d %-12s %-12s %-10s\n", tsk.id, tsk.title, getStatus(tsk.status), tsk.deadline);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No tasks due today.\n");
    }

    fclose(file);

    int choice;
    printf("Do you want to update a task? (1: Yes, 0: No): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        int id;
        printf("Enter Task ID to update: ");
        scanf("%d", &id);
        updateTask(id);
    }
}

void updateTask(int id)
{
    FILE *file = fopen(FILENAME_TASKS, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    Task tsk;
    int found = 0;
    while (fscanf(file, "%d %d %10s %s", &tsk.id, &tsk.status, tsk.deadline, tsk.title) != EOF)
    {
        if (tsk.id == id)
        {
            found = 1;
            int choice;
            do
            {
                printf("\n*** Updating Task: ID - %d ***\n", id);
                printf("1. Update Status\n");
                printf("2. Update Deadline\n");
                printf("3. Update Title\n");
                printf("4. Save and Exit\n");
                printf("0. Cancel Update\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                if (choice == 1)
                {
                    printf("Current Status: %s\n", getStatus(tsk.status));
                    printf("Enter new status (0: Pending, 1: In-Progress, 2: Done): ");
                    scanf("%d", &tsk.status);
                }
                else if (choice == 2)
                {
                    printf("Current Deadline: %s\n", tsk.deadline);
                    printf("Enter new deadline (YYYY-MM-DD): ");
                    scanf("%s", tsk.deadline);
                }
                else if (choice == 3)
                {
                    printf("Current Title: %s\n", tsk.title);
                    printf("Enter new Title: ");
                    scanf("%s", tsk.title);
                }
                else if (choice == 4)
                {
                    printf("Saving updates...\n");
                    break; // লুপ থেকে বের হবে এবং সেভ করবে
                }
                else if (choice == 0)
                {
                    printf("Update canceled.\n");
                    fclose(file);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
                else
                {
                    printf("Invalid choice. Try again.\n");
                }

            } while (1);
        }

        fprintf(temp, "%d %d %s %s\n", tsk.id, tsk.status, tsk.deadline, tsk.title);
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME_TASKS);
    rename("temp.txt", FILENAME_TASKS);

    if (found)
        printf("Task updated successfully!\n");
    else
        printf("Task with ID %d not found!\n", id);
}
