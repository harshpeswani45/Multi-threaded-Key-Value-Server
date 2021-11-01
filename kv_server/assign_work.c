#include <pthread.h>

void assign_work(int num_of_threads){
    if(flag_check==0){
        turn=(turn)%num_of_threads;    
        worker_thread((void *)0);
        if(jump_check==1){
            jump_check=0;
            return;
        }
        turn=(turn+1)%num_of_threads;
    }else{
        turn=turn%data.THREAD_POOL_GROWTH;
        turn=turn+batch_size;
        worker_thread((void *)0);
        if(jump_check==1){
            jump_check=0;
            return;
        }
        turn=turn-batch_size;
        turn=(turn+1)%data.THREAD_POOL_GROWTH;
    }

}