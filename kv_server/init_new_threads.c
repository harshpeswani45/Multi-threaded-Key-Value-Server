
void init_new_threads(){
    int num_of_threads=total_threads+data.THREAD_POOL_GROWTH;
    epollfd=(int*) realloc(epollfd,num_of_threads*sizeof(int));
    cv=(pthread_cond_t *) realloc(cv,num_of_threads*sizeof(pthread_cond_t));
    m=(pthread_mutex_t *) realloc(m,num_of_threads*sizeof(pthread_mutex_t));
    cv_create=(pthread_cond_t *) realloc(cv,num_of_threads*sizeof(pthread_cond_t));
    m_create=(pthread_mutex_t *) realloc(m,num_of_threads*sizeof(pthread_mutex_t));
    cnt_clients=(int *) realloc(cnt_clients,num_of_threads*sizeof(int));
    created=(int *) realloc(cnt_clients,num_of_threads*sizeof(int));
    int i=total_threads;
    total_threads+=data.THREAD_POOL_GROWTH;
    for(;i<total_threads;i++){
        pthread_cond_init(&cv[i],NULL);
        pthread_mutex_init(&m[i],NULL);
        pthread_cond_init(&cv_create[i],NULL);
        pthread_mutex_init(&m_create[i],NULL);
        cnt_clients[i]=0;
        created[i]=0;

    }
}