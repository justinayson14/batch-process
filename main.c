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
		}
		printf("\n\n");
	}
	return;
}


//*************************************************************
void getParams() {
	// declare local variables
	// last column holds "if done" field  
	// prompt for total number of processes
	printf("Enter total number of processes: ");
	scanf("%d",&numProc);
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
	}
	// print contents of table 
	printTable();
	return;		
}	
		

//*************************************************************
void scheduleFIFO() {
	// declare (and initilize when appropriate) local variables 
	// for each process, reset "done" field to 0 
	// while there are still processes to schedule 	
		// initilize the earliest arrival time to INT_MAX (largest integer value) 
		// for each process not yet scheduled 
			// check if process has earlier arrival time than current earliest and update 	
		// set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time        	
		// update current cycle time and increment number of processes scheduled 
	// print contents of table 
	return;		
}	


//*************************************************************
void scheduleSJG() {
	// declare (and initilize when appropriate) local variables 
	// for each process, reset "done" field to 0 
	// while there are still processes to schedule 	
		// initilize the lowest total cycle time to INT_MAX (largest integer value) 
		// for each process not yet scheduled 
			// check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update 	
		// set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time        	
		// update current cycle time and increment number of processes scheduled 
	// print contents of table 
	return;		
}	
        	

//*************************************************************
void scheduleSRT() {
	// declare (and initilize when appropriate) local variables 
	// for each process, reset "done", "total_remaining" and "already_started" fields to 0 
	// while there are still processes to schedule 	
		// initilize the lowest total remaining time to INT_MAX (largest integer value) 
		// for each process not yet scheduled 
			// check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update 	
		// check if process already partially-scheduled 
			// if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time        	
		// set end time, turnaround time of process with lowest (and available) total remaining cycle time 
		// decrement total remaining time of process with lowest (and available) total remaining cycle time 
		// if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes
	// print contents of table 
	return;		
}	
        	

//*************************************************************
void delTable() {
	// free the schedule table if not NULL 
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
        printf("\nBatch scheduling\n");
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
            printf("Entering parameters...\n");
			getParams();
            break;
        case 2:
            printf("Scheduleing processes with FIFO...\n");
            break;
        case 3:
            printf("Scheduling processes with SJF...\n");
            break;
        case 4:
            printf("Scheduling processes with SRT...\n");
            break;
        case 5:
            printf("Quitting and freeing memory...\n");
            break;
        default:
            printf("INVALID INPUT. Please try again.\n");
            break;
        }	
	// while loop 
    } while (choice != 5);
	 return 1; // indicates success 
} // end of procedure 
