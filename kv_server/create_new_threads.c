#include <pthread.h>

void create_new_threads(){
    pthread_t t_id[data.THREAD_POOL_GROWTH];
    for(int i=0;i<data.THREAD_POOL_GROWTH;i++){
        int chk=pthread_create(&t_id[i],NULL,worker_thread,(void *)(i+1+batch_size));
        if(chk>0){
            perror("\nCaanot Create Thread\n");
        }
    }
    for(int i=0;i<data.THREAD_POOL_GROWTH;i++){
        int chk=pthread_detach(t_id[i]);
        if(chk>0){
            perror("\nCaanot Create Thread\n");
        }
    } 

}
