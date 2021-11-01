#include <pthread.h>

void create_thread(int num_of_threads){
    pthread_t t_id[num_of_threads];
    for(int i=0;i<num_of_threads;i++){
        int chk=pthread_create(&t_id[i],NULL,worker_thread,(void *)(i+1));
        if(chk>0){
            perror("\nCaanot Create Thread\n");
        }
    }
    for(int i=0;i<num_of_threads;i++){
        int chk=pthread_detach(t_id[i]);
        if(chk>0){
            perror("\nCaanot Create Thread\n");
        }
    } 

}
