/*
Code by Harry Adkins
Assignment 19
*/
//Question 1
/*
The program will have to loop through the pages multiple times in order to purposefully
increase the time it takes so that a timer can be more accurate, or so it can at least provide distinguishable results.
*/
//Question 2
/*

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

    

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for(size_t i = 0; i < totalEntries; i += jump){
        pageArray[i] = 1;
    }
    for(int j = 0; j < trials; j++){
        for(int i = 0; i < totalEntries; i += jump){
            pageArray[i] += 1;
        }
    }

    gettimeofday(&end, NULL);
    
    printf("pageSize: %ld bytes\n", pageSize);
    printf("pages: %d\n", pages);
    printf("Time for %d trials: %f seconds\n", trials, ((end.tv_sec - start.tv_sec) * 1E6 + end.tv_usec - start.tv_usec) / (trials * pages));

    free(pageArray);
    return 0;
}