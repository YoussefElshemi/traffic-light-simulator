#define _XOPEN_SOURCE // needed for some reason
#include "runOneSimulation.c"

int main(int argc, char *argv[]) {
  srand48(time(0));

  float pLeft = atof(argv[1]);
  int lTrafficPeriod = atoi(argv[2]);
  float pRight = atof(argv[3]);
  int rTrafficPeriod = atoi(argv[4]);

  float leftCount = 0;
  float leftWaitingTime = 0;
  float leftMaxTime = 0;
  float leftClearanceTime = 0;

  float rightCount = 0;
  float rightWaitingTime = 0;
  float rightMaxTime = 0;
  float rightClearanceTime = 0;

  // calculate averages
  for (int i = 0; i < 100; i++) {
    data *simulationData = runOneSimulation(pLeft, lTrafficPeriod, pRight, rTrafficPeriod);

    leftCount += (float) simulationData->left.count;
    leftWaitingTime += (float) simulationData->left.averageWaitTime;
    leftMaxTime += (float) simulationData->left.maxWaitTime;
    leftClearanceTime += (float) simulationData->left.clearanceTime;

    rightCount += (float) simulationData->right.count;
    rightWaitingTime += (float) simulationData->right.averageWaitTime;
    rightMaxTime += (float) simulationData->right.maxWaitTime;
    rightClearanceTime += (float) simulationData->right.clearanceTime;

    free(simulationData);
  }


  printf(
  "Parameter values :\n"
  "  from left :\n"
  "    traffic arrival rate : %f\n"
  "    traffic light period : %d\n"
  "  from right :\n"
  "    traffic arrival rate : %f\n"
  "    traffic light period : %d\n"
  "Results ( averaged over 100 runs ):\n"
  "  from left :\n"
  "    number of vehicles : %f\n"
  "    average waiting time : %f\n"
  "    maximum waiting time : %f\n"
  "    clearance time : %f\n"
  "  from right :\n"
  "    number of vehicles : %f\n"
  "    average waiting time : %f\n"
  "    maximum waiting time : %f\n"
  "    clearance time : %f\n",
  pLeft, lTrafficPeriod, pRight, rTrafficPeriod,
  leftCount / 100, leftWaitingTime / 100, leftMaxTime / 100, leftClearanceTime / 100,
  rightCount / 100, rightWaitingTime / 100, rightMaxTime / 100, rightClearanceTime/ 100
  );

  return 0;
}
