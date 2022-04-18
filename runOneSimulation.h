#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef signed short int status;

typedef struct iData {
  int count;
  float averageWaitTime;
  int maxWaitTime;
  int clearanceTime;
} iData;

typedef struct data {
  struct iData left;
  struct iData right;
} data;

typedef struct node {
  int arrival;
  struct node *next;
} node;

typedef struct queue {
  node *head;
  node *tail;
  int count;
  int waitTime;
  int maxWaitTime;
} queue;

data *runOneSimulation(double, int, double, int);
queue *createQueue();
int isEmpty(queue *);
void push(queue *, int);
void pop(queue *);
void printQueue(queue *);

#endif