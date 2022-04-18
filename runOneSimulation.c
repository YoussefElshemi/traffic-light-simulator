#include "runOneSimulation.h"

queue *createQueue() {
  queue *q = (queue *)malloc(sizeof(queue));
  if (q == NULL) abort();

  q->head = NULL;
  q->tail = NULL;
  q->count = 0;
  q->waitTime = 0;
  q->maxWaitTime = 0;
  return q;
}

int isEmpty(queue *queue) {
  return queue->head == NULL;
}

void push(queue *queue, int arrival) {
  node *newNode = malloc(sizeof(node));
  if (newNode == NULL) abort();

  newNode->next = NULL;
  newNode->arrival = arrival;

  if (isEmpty(queue)) {
    queue->head = queue->tail = newNode;
  } else {
    queue->tail->next = newNode;
    queue->tail = newNode;
  }

  queue->count++;
}

void pop(queue *queue) {
  if (isEmpty(queue)) return;
  
  node *temp;
  temp = queue->head;
  queue->head = queue->head->next;

  if(queue->head == NULL) queue->tail = NULL;
  free(temp);
}

void printQueue(queue *queue) {
  node *temp = queue->head;
  
  while(temp) {
    printf("🚗");
    temp = temp->next;
  }

  printf("\n");
}

data* runOneSimulation(double pLeft, int lTrafficPeriod, double pRight, int rTrafficPeriod) {
  int timeStep = 0;
  int leftClearanceTime = 0;
  int rightClearanceTime = 0;

  // create the two queues for the traffic simulation
  queue *leftSide = createQueue();
  queue *rightSide = createQueue();

  // start with the left side green light
  // and the right side red light

  status leftSideStatus = 1;
  status rightSideStatus = 0;

  // now run the simulation for the rest of the time
  while (1) {
    timeStep++;

    // only if we're past 500 time steps
    if (timeStep > 500) {
      if (isEmpty(leftSide) && leftClearanceTime == 0) {
        leftClearanceTime = timeStep;
      }

      if (isEmpty(rightSide) && rightClearanceTime == 0) {
        rightClearanceTime = timeStep;
      }

      if (isEmpty(leftSide) && isEmpty(rightSide)) {
        break;
      }
    }

    // around every X time steps, change the status of the lights
    if (timeStep % lTrafficPeriod == 0) {
      leftSideStatus = !leftSideStatus;
    }

    if (timeStep % rTrafficPeriod == 0) {
      rightSideStatus = !rightSideStatus;
    }

    // if a light switch occured, continue to the next time step
    if (timeStep % lTrafficPeriod == 0 || timeStep % rTrafficPeriod == 0) {
      continue;
    }

    // only add cars in if it's the first 500 time steps
    if (timeStep <= 500) {
      // around every X time steps, a car will drive from the left side
      if (drand48() <= pLeft) {
        push(leftSide, timeStep);
      }

      // around every X time steps, a car will drive from the right side
      if (drand48() <= pRight) {
        push(rightSide, timeStep);
      }
    }
    
    // if left side is open and there is a queue, first car passes through
    if (leftSideStatus && !isEmpty(leftSide)) {
      int waitTime = timeStep - leftSide->head->arrival; 
      leftSide->waitTime += waitTime;

      if (waitTime > leftSide->maxWaitTime) {
        leftSide->maxWaitTime = waitTime;
      }
      
      pop(leftSide);
    }

    // if right side is open and there is a queue, first car passes through
    if (rightSideStatus && !isEmpty(rightSide)) {
      int waitTime = timeStep - rightSide->head->arrival; 
      rightSide->waitTime += waitTime;

      if (waitTime > rightSide->maxWaitTime) {
        rightSide->maxWaitTime = waitTime;
      }
      
      pop(rightSide);
    }
  }

  if (leftClearanceTime == 0) {
    leftClearanceTime = timeStep;
  }

  if (rightClearanceTime == 0) {
    rightClearanceTime = timeStep;
  }

  // create the data structure for left and right queue
  iData *leftData = malloc(sizeof(iData));
  if (leftData == NULL) abort();

  iData *rightData = malloc(sizeof(iData));
  if (rightData == NULL) abort();

  // assign the data to the respective data structures
  leftData->count = leftSide->count;
  leftData->averageWaitTime = (float)leftSide->waitTime / leftSide->count;
  leftData->maxWaitTime = leftSide->maxWaitTime;
  leftData->clearanceTime = leftClearanceTime;
  
  rightData->count = rightSide->count;
  rightData->averageWaitTime = (float)rightSide->waitTime / rightSide->count;
  rightData->maxWaitTime = rightSide->maxWaitTime;
  rightData->clearanceTime = rightClearanceTime;

  data *simulationData = malloc(sizeof(data));
  if (simulationData == NULL) abort();

  simulationData->left = *leftData;
  simulationData->right = *rightData;

  free(leftSide);
  free(rightSide);
  free(leftData);
  free(rightData);

  return simulationData;
}