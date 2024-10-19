#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// declare global variables including a table structure to hold scheduling information
// optional: define a function that finds the maximum of two integers
struct table
{
	int id;
	int arrival;
	int total_cpu;
	int total_remaining;
	int done;
	int start_time;
	int already_started;
	int end_time;
	int turnaround_time;
};
struct table *processes;
int numProc;

// function declarations
void getParams();
void printTable();
void scheduleFIFO();
void scheduleSJG();
void scheduleSRT();
void delTable();

//***************************************************************
void printTable() {
	// declare local variables
	// print table header
	printf("\nPID");
	printf("\tArrival");
	printf("\tTotal");
	printf("\tStart");
	printf("\tEnd");
	printf("\tTurnaround");
	printf("\n--------------------------------------------------\n");
	// for each process 
	for(int i = 0; i < numProc; i++) {
		// print the contents (id, arrival time, total_cycles) of each field of the table's index 
		printf("%d", processes[i].id);
		printf("\t%d", processes[i].arrival);
		printf("\t%d", processes[i].total_cpu);
		// if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) 
		if(processes[i].done == 1) {
			printf("\t%d", processes[i].start_time);
			printf("\t%d", processes[i].end_time);
			printf("\t%d", processes[i].turnaround_time);
		} // end if
		printf("\n");
	} // end for
	return;
} // end printTable


//*************************************************************
void getParams() {
	// declare local variables
	// last column holds "if done" field  
	// prompt for total number of processes
	printf("Enter total number of processes: ");
	scanf("%d",&numProc);
	// clear input buffer
	while (getchar() != '\n');
	// allocate memory for table to hold process parameters
	processes = malloc(numProc * sizeof(struct table));
	// for each process 
	for(int i = 0; i < numProc; i++) {
		// prompt for arrival time, and total cycle time
		processes[i].id = i+1; // id num starts at 1
		printf("Enter arrival cycle for process %d: ", processes[i].id);
		scanf("%d", &processes[i].arrival);
		while(getchar() != '\n');
		printf("Enter total cycle for process %d: ", processes[i].id);
		scanf("%d", &processes[i].total_cpu);
		while(getchar() != '\n');
	} // end for
	// print contents of table 
	printTable();
	return;		
} // end getParams
		

//*************************************************************
void scheduleFIFO() {
	// declare (and initilize when appropriate) local variables
	int done = 0;
	int earliestArrival;
	int earliestProcess;
	int currSchedule = 0;
	// for each process, reset "done" field to 0 
	for (int i = 0; i < numProc; i++)
		processes[i].done = 0;
	// while there are still processes to schedule
	while (done < numProc) {
		/* code */	
		// initilize the earliest arrival time to INT_MAX (largest integer value)
		earliestArrival = INT_MAX;
		// for each process not yet scheduled
		for (int j = 0; j < numProc; j++) {
			// check if process has earlier arrival time than current earliest and update 	
			if (processes[j].arrival < earliestArrival && processes[j].done == 0) {
				earliestArrival = processes[j].arrival;
				earliestProcess = j;
			} // end if
		} // end for
		// set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time
		processes[earliestProcess].start_time = currSchedule;
		currSchedule += processes[earliestProcess].total_cpu;
		processes[earliestProcess].end_time =  currSchedule;
		processes[earliestProcess].turnaround_time = currSchedule - processes[earliestProcess].arrival;
		processes[earliestProcess].done = 1;
		// update current cycle time and increment number of processes scheduled
		done++;
	} // end while
	// print contents of table 
	printTable();
	return;		
} // end scheduleFIFO	


//*************************************************************
void scheduleSJF() {
	// declare (and initilize when appropriate) local variables 
	int done = 0;
	int lowestCycle;
	int lowestProcess;
	int currSchedule = 0;
	// for each process, reset "done" field to 0 
	for (int i = 0; i < numProc; i++)
		processes[i].done = 0;
	// while there are still processes to schedule
	while (done < numProc) {
		// initilize the lowest total cycle time to INT_MAX (largest integer value) 
		lowestCycle = INT_MAX;
		// for each process not yet scheduled
		for (int j = 0; j < numProc; j++) {
			// check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
			if (processes[j].done == 0 && processes[j].total_cpu < lowestCycle && processes[j].arrival <= currSchedule) {
				lowestCycle = processes[j].total_cpu;
				lowestProcess = j;
			} // end if
		} // end for
		// set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
		processes[lowestProcess].start_time = currSchedule;
		processes[lowestProcess].end_time = currSchedule + lowestCycle;
		processes[lowestProcess].turnaround_time = processes[lowestProcess].end_time - processes[lowestProcess].arrival; 
		processes[lowestProcess].done = 1;
		// update current cycle time and increment number of processes scheduled 
		currSchedule = processes[lowestProcess].end_time;
		done++;
	} // end while 	
	// print contents of table 
	printTable();
	return;		
} // end scheduleSJF
        	

//*************************************************************
void scheduleSRT() {
	// declare (and initilize when appropriate) local variables
	int lowestTime;
	int done = 0;
	int currSchedule = 0;
	int lowestProcess; 
	// for each process, reset "done" and "already_started" fields to 0, initialize total remaining to the total CPU cycle
	for (int i = 0; i < numProc; i++) {
		processes[i].done = 0;
		processes[i].total_remaining = processes[i].total_cpu;
		processes[i].already_started = 0;
	} 
	// while there are still processes to schedule 	
	while (done < numProc) {
		// initilize the lowest total remaining time to INT_MAX (largest integer value) 
		lowestTime = INT_MAX;
		// for each process not yet scheduled
		for (int j = 0; j < numProc; j++) {
			// check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update 	
			if (processes[j].done == 0 && processes[j].total_remaining < lowestTime && processes[j].arrival <= currSchedule) {
				lowestTime = processes[j].total_remaining;
				lowestProcess = j;

			} // end if
		} // end for
		// check if process hasn't started
		if (processes[lowestProcess].already_started == 0) {
			// if so, set start time to the current cycle and update already started      	
			processes[lowestProcess].start_time = currSchedule;
			processes[lowestProcess].already_started = 1;
		} // end if
		// decrement process total remaining and increment current cycle
		processes[lowestProcess].total_remaining--;
		currSchedule++;
		// if total remaining is 0, then set done to 1, update end time to current cycle, and update turn around time
		if (processes[lowestProcess].total_remaining == 0) {
			processes[lowestProcess].done = 1;
			processes[lowestProcess].end_time = currSchedule;
			processes[lowestProcess].turnaround_time = processes[lowestProcess].end_time - processes[lowestProcess].arrival;
			done++;
		} // end if
	} // end while 
	// print contents of table 
	printTable();
	return;		
} // end scheduleSRT	
        	

//*************************************************************
void delTable() {
	// free the schedule table if not NULL 
	if (processes != NULL) {
		free(processes);
		processes = NULL;
		printf("Quitting program");
	}
	return;
}


//*************************************************************
int main() {
	// declare local vars 
    int choice;
    // while user has not chosen to quit
    do {
		// print menu of options 
		// prompt for menu selection 
        printf("\n\nBatch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n\n");
		printf("Enter selection: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
		// call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
        switch (choice)
        {
        case 1:
			getParams();
            break;
        case 2:
			scheduleFIFO();
            break;
        case 3:
			scheduleSJF();
            break;
        case 4:
			scheduleSRT();
            break;
        case 5:
			delTable();
			break;
        default:
            printf("INVALID INPUT. Please try again.\n");
            break;
        }	
	// while loop 
    } while (choice != 5);
	 return 1; // indicates success 
} // end of procedure 
