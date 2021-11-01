#include <stdio.h>
#include <stdlib.h>
//#include "global.h"

struct config_data read_config(){
    struct config_data data_return;
    FILE *fptr;
    fptr=fopen("config","r");
    if(fptr==NULL){
        perror("\nCannot Open File Try Again Latter\n");
        exit(1);
    }
    char *garbage=(char *)malloc(30);
    
    fscanf( fptr," %s %d",garbage,&data_return.LISTENING_PORT);
    fscanf(fptr," %s %d",garbage,&data_return.CLIENTS_PER_THREAD);
    fscanf(fptr," %s %d",garbage,&data_return.CACHE_SIZE);
    fscanf(fptr," %s %d",garbage,&data_return.CACHE_REPLACEMENT);
    fscanf(fptr," %s %d",garbage,&data_return.THREAD_POOL_SIZE_INITIAL);
    fscanf(fptr," %s %d",garbage,&data_return.THREAD_POOL_GROWTH);
    
    free(garbage);
    return data_return;
}