#include <stdio.h>
#include "btree.h"
#include <time.h>

int main(){

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for(int i=0; i<100; i+=10){
        int value = i + 2;
        insert(i,value);
        end = clock();
        cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
        printf("time taken for insert ---- %f \n", cpu_time_used);
    };

    

    print_bpt();
    genNode *h = find(7);
    return 0;

};
