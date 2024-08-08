/**
 * Menu and tester class for scheduler project
 *
 * @author Atiya Mahboob
 */

#include "scheduler.h"
#include <stdio.h>

void printMenu();

int main()
{
    const char *inFileName = "data.txt";
    const char *outFileName = "Schedule.txt";
    Scheduler *sc = initScheduler();
    printf("An empty event has been created.\n");

    int choice, length, priority;
    do
    {
        printMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("\n\n\n");
        switch (choice)
        {
        case 1:
            loadScheduler(sc, inFileName);
            printf("Schedule loaded.\n");
            break;
        case 2:
            printf("Enter the length of the act (in minutes): ");
            scanf("%d", &length);
            printf("Enter the priority of the act (1 being the highest and 20 the lowest): ");
            scanf("%d", &priority);
            addAct(sc, length, priority);
            printf("Act added.\n");
            break;
        case 3:
            printScheduler(sc);
            break;
        case 4:
            storeSchedule(sc, outFileName);
            printf("Schedule stored in Schedule.txt.\n");
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");

    return 0;
}

void printMenu()
{
    printf("\n\n");
    printf("Choose from one of the following options:\n");
    printf("1. Load acts from a file (data.txt).\n");
    printf("2. Add acts.\n");
    printf("3. Print Schedule.\n");
    printf("4. Store Schedule in text file.\n");
    printf("0. Exit.\n");
}
