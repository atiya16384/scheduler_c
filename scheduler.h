/**
 * Header file for scheduler module
 *
 * @author Atiyah Mahboob
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>

// Structure declarations
typedef struct Act
{
    int length;
    int start;
    int end;
} Act;

typedef struct ActNode
{
    int priority;
    Act *data;
    struct ActNode *next;
} ActNode;

typedef struct Scheduler
{
    int startTime;
    int numActs;
    int gap;
    ActNode *headAct;
} Scheduler;

// Function declarations for acts
Act *initAct(int length);
void printAct(const Act *act);
void scheduleAct(Act *act, int start);
void printTime(int time);

// Function declarations for scheduler
Scheduler *initScheduler();
void loadScheduler(Scheduler *scheduler, const char *fileName);
void loadActs(Scheduler *pScheduler, FILE *data);
void printScheduler(const Scheduler *scheduler);
void setActTimes(Scheduler *scheduler);
void storeSchedule(const Scheduler *scheduler, const char *fileName);
void addAct(Scheduler *scheduler, int length, int priority);

// Priority queue functions
int isempty(const ActNode *headAct);
void traverse(const ActNode *headAct);
ActNode *insert(ActNode *headAct, int length, int priority);

#endif // SCHEDULER_H
