#include<pthread.h>
#include<sys/epoll.h>
#include <stdlib.h>

struct free_list* add_freelist(struct free_list* head,int index){
    struct free_list* new=(struct free_list*)malloc(sizeof(struct free_list));
    new->index=index;
    new->next=NULL;
    if(head==NULL){
        head=new;
        return head;
    }
    new->next=head;
    head=new;
    return head;
}


void init_threads(int num_of_threads){
    //THREADS
    total_threads=num_of_threads;
    batch_size=0;
    flag_check=0;
    jump_check=0;
    thread_grow=data.THREAD_POOL_GROWTH;

    max_cache=data.CACHE_SIZE;
    turn=0;
    con_fd=0;
    pthread_mutex_init(&m_cache,NULL);
    epollfd=(int*) malloc(num_of_threads*sizeof(int));
    cv=(pthread_cond_t *) malloc(num_of_threads*sizeof(pthread_cond_t));
    m=(pthread_mutex_t *) malloc(num_of_threads*sizeof(pthread_mutex_t));
    cv_create=(pthread_cond_t *) malloc(num_of_threads*sizeof(pthread_cond_t));
    m_create=(pthread_mutex_t *) malloc(num_of_threads*sizeof(pthread_mutex_t));
    cnt_clients=(int *) malloc(num_of_threads*sizeof(int));
    created=(int *) malloc(num_of_threads*sizeof(int));
    for(int i=0;i<num_of_threads;i++){
        pthread_cond_init(&cv[i],NULL);
        pthread_mutex_init(&m[i],NULL);
        pthread_cond_init(&cv_create[i],NULL);
        pthread_mutex_init(&m_create[i],NULL);
        cnt_clients[i]=0;
        created[i]=0;
    }


    //FILES
    for(int i=0;i<37;i++){
        head_file[i]=NULL;
        pthread_mutex_init(&m_file[i],NULL);
        char str[3];
        sprintf(str, "%d", i);
        fd[i]=fopen(str,"a+");
        fclose(fd[i]);
        fd[i]=fopen(str,"r+");
        //Add in free list
        char read_buffer[515];
        int index=0;
        while(fgets(&read_buffer,515,fd[i])!=NULL){
            if(read_buffer[512]=='0'){
                head_file[i]=add_freelist(head_file[i],index*514);    
            }
        index++;
        }
        fseek(fd[i],0,SEEK_SET);

    }
}



