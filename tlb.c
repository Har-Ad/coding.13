/*
Code by Harry Adkins
Assignment 19
*/
//Question 1
/*
The program will have to loop through the pages multiple times in order to purposefully
increase the time it takes so that a timer can be more accurate, or so it can at least provide distinguishable results.
*/
//Question 3
/*
It takes roughly 10k trials to start seeing numbers around the smae range.
*/
//Question 4
/*
Visualization helps to show the moments when the time suddenly jumps, showing the relative range between 
page numbers thst are within the same efficiency.
*/
//Question 5
/*
In order to make sure a loop always stays after compilation, it needs to have observable side effects, 
such as a variable that changes each iteration.
*/
//Question 6
/*
You can use the start function in the command line to force the program to run on only one cpu.
I imagine that if it swapped between cpus, the timing may change and we won't be able to get accurate readings.
*/
//Question 7
/*
Because initialization takes time, it is better to do it before we start counting so that we only count 
the time it takes to parse through the already existing arrays. We can also counterbalance by account for how long
it might take to create an array base on how many pages we create.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("./tlb [number of pages] [number of trials]\n");
        return 1;
    }

    int pages = atoi(argv[1]);
    int trials = atoi(argv[2]);

    if(pages <= 0 || trials <= 0){
        printf("Pages and trials must both be greater than 0\n");
        return 1;
    }

    long pageSize = sysconf(_SC_PAGESIZE);
    if(pageSize <= 0){
        printf("Page size is unusable\n");
        return 1;
    }

    size_t jump = (size_t)pageSize / sizeof(int);
    size_t totalEntries = (size_t)pages * jump;
    int *pageArray = calloc(pages, pageSize);

    if(pageArray == NULL){
        printf("Allocation failure\n");
        return 1;
    }

    for(size_t i = 0; i < totalEntries; i += jump){
        pageArray[i] = 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for(int j = 0; j < trials; j++){
        for(int i = 0; i < totalEntries; i += jump){
            pageArray[i] += 1;
        }
    }

    gettimeofday(&end, NULL);
    
    printf("pageSize: %ld bytes\n", pageSize);
    printf("pages: %d\n", pages);
    printf("Time for %d trials: %f seconds\n", trials, 
        ((end.tv_sec - start.tv_sec) * 1E6 + end.tv_usec - start.tv_usec) / (trials * pages));

    free(pageArray);
    return 0;
}