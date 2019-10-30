#include <stdio.h>
#include "btree.h"
#include <time.h>

int main(){

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    //test for insert algorithm
    for(int i=0; i<100; i+=10){
        int value = i + 2;
        insert(i,value);
        end = clock();
        cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("time taken for insert ---- %f \n", cpu_time_used);
    };

    // test for find algorithm
    for(int i=0; i<100; i+=10){
        genNode *h = find(i);
        end = clock();
        cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("time taken for find ---- %f \n", cpu_time_used);
    };

    return 0;

};
