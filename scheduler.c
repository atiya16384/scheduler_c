/**
 * Implementation of the scheduler module.
 * Note - All time is in minutes.
 *
 * @author Atiya Mahboob
 */

#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

// Function implementations

Act *initAct(int length)
{
    Act *pAct = (Act *)malloc(sizeof(Act));
    pAct->length = length;
    pAct->start = -1;
    pAct->end = -1;
    return pAct;
}

void printAct(const Act *act)
{
    printf("%3d minutes long, starts at ", act->length);
    printTime(act->start);
    printf(" and ends at ");
    printTime(act->end);
    printf("\n");
}

void scheduleAct(Act *act, int start)
{
    act->start = start;
    act->end = start + act->length;
}

void printTime(int time)
{
    printf("%02d:%02d", time / 60, time % 60);
}

ActNode *insert(ActNode *headAct, int length, int priority)
{
    ActNode *temp = (ActNode *)malloc(sizeof(ActNode));
    temp->priority = priority;
    temp->data = initAct(length);
    temp->next = NULL;

    if (isempty(headAct) || priority < headAct->priority)
    {
        temp->next = headAct;
        return temp;
    }

    ActNode *current = headAct;
    while (current->next != NULL && current->next->priority <= priority)
    {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;

    return headAct;
}

int isempty(const ActNode *headAct)
{
    return headAct == NULL;
}

void traverse(const ActNode *headAct)
{
    const ActNode *temp = headAct;
    int i = 1;

    while (temp != NULL)
    {
        printf("Event No. %d     ", i);
        printAct(temp->data);
        temp = temp->next;
        i++;
    }
}

Scheduler *initScheduler()
{
    Scheduler *pscheduler = (Scheduler *)malloc(sizeof(Scheduler));
    pscheduler->numActs = 0;
    pscheduler->gap = 0;
    pscheduler->startTime = 0;
    pscheduler->headAct = NULL;
    return pscheduler;
}

void loadActs(Scheduler *pScheduler, FILE *data)
{
    int length = 0, priority = 0;
    for (int i = 0; i < pScheduler->numActs; i++)
    {
        fscanf(data, "%d %d\n", &length, &priority);
        pScheduler->headAct = insert(pScheduler->headAct, length, priority);
    }
}

void loadScheduler(Scheduler *scheduler, const char *fileName)
{
    FILE *data = fopen(fileName, "r");

    if (data == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fscanf(data, "%d %d %d\n", &scheduler->startTime, &scheduler->gap, &scheduler->numActs);
    loadActs(scheduler, data);
    setActTimes(scheduler);
    fclose(data);
}

void setActTimes(Scheduler *scheduler)
{
    int startTime = scheduler->startTime;
    int gap = scheduler->gap;
    ActNode *temp = scheduler->headAct;
    while (temp != NULL)
    {
        scheduleAct(temp->data, startTime);
        startTime = temp->data->end + gap;
        temp = temp->next;
    }
}

void printScheduler(const Scheduler *scheduler)
{
    printf("Start time: ");
    printTime(scheduler->startTime);
    printf("\nNumber of acts: %d\n", scheduler->numActs);
    printf("Gap: %d\n", scheduler->gap);
    traverse(scheduler->headAct);
}

void storeSchedule(const Scheduler *scheduler, const char *fileName)
{
    FILE *data = fopen(fileName, "w");
    if (data == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    if (scheduler->numActs == 0)
    {
        printf("Event has no acts.\n");
        return;
    }

    fprintf(data, "                 Schedule  \n");
    fprintf(data, "Event will begin at: ");
    fprintf(data, "%02d:%02d", scheduler->startTime / 60, scheduler->startTime % 60);
    fprintf(data, "\n");

    fprintf(data, "Number of events: %d\n", scheduler->numActs);
    fprintf(data, "Gap between events: %d\n", scheduler->gap);
    fprintf(data, "\n");

    ActNode *temp = scheduler->headAct;
    int i = 1;
    while (temp != NULL)
    {
        fprintf(data, "Event No. %2d --- ", i);
        fprintf(data, "Start time: %02d:%02d", temp->data->start / 60, temp->data->start % 60);
        fprintf(data, " End time: %02d:%02d\n", temp->data->end / 60, temp->data->end % 60);
        i++;
        temp = temp->next;
    }
    fclose(data);
}

void addAct(Scheduler *scheduler, int length, int priority)
{
    scheduler->headAct = insert(scheduler->headAct, length, priority);
    scheduler->numActs++;
    setActTimes(scheduler);
}
