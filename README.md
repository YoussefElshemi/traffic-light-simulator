## ECM2433 - Temporary Traffic Light Simulator

### Installation
First, ensure you have these following files:
- runSimulations.c
- runOneSimulation.c
- runOneSimulation.have
- compileSim

### Compliation
Next use the following command in a linux terminal to be able to execute the compileSim file:
```
$ chmod +x ./compileSim
```

Next, we can compile the simulator using the command below, which should produce a file called runSimulations:
```
$ ./compileSim
```

### Execution
We can use the simulator as demonstrated below:
```
$ ./runSimulations <P_LEFT> <T_LEFT> <P_RIGHT> <T_RIGHT>
```

Where:
- P_LEFT: Probability of a car arriving from the left hand side
- T_LEFT: How many time steps for the left traffic lane to be open for
- P_RIGHT: Probability of a car arriving from the right hand side
- T_RIGHT: How many time steps for the right traffic lane to be open for
 
### Output
This will produce an output in the following format with the results of 100 simulations avereged with the parameters provided by the user:

```
Parameter values :
  from left :
    traffic arrival rate : XXX
    traffic light period : XXX
  from right :
    traffic arrival rate : XXX
    traffic light period : XXX
Results ( averaged over 100 runs ):
  from left :
    number of vehicles : XXX
    average waiting time : XXX
    maximum waiting time : XXX
    clearance time : XXX
  from right :
    number of vehicles : XXX
    average waiting time : XXX
    maximum waiting time : XXX
    clearance time : XXX
```