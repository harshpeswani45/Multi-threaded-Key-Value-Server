#include<pthread.h>
#include<sys/epoll.h>

void* worker_thread(void* rank){
    rank=(int)rank;
    int event_count=0;
    //MAIN'S WORK
    if(rank==0){
        struct epoll_event event;
        event.events=EPOLLIN|EPOLLET;
        event.data.fd=con_fd;
        //printf("1\n");
        pthread_mutex_lock(&m[turn]);
         if(cnt_clients[turn] >= data.CLIENTS_PER_THREAD){
             
            if(flag_check==0){
                flag_check=1;
                batch_size=batch_size+data.THREAD_POOL_SIZE_INITIAL;
            }else{
                batch_size=batch_size+data.THREAD_POOL_GROWTH;
            }
            init_new_threads();
            create_new_threads();
            pthread_mutex_unlock(&m[turn]);
            turn=0;
            assign_work(total_threads);
            jump_check=1;
            return;
            //MAKE NEW THREADS AND INITIALIZE IT
        }
        pthread_mutex_unlock(&m[turn]);
         //printf("2\n");
        pthread_mutex_lock(&m_create[turn]);
        while(created[turn]==0){
            pthread_cond_wait(&cv_create[turn],&m_create[turn]);
        }
        pthread_mutex_unlock(&m_create[turn]);
         //printf("3\n");
        pthread_mutex_lock(&m[turn]);
        if(epoll_ctl(epollfd[turn], EPOLL_CTL_ADD, con_fd, &event)){
            perror("Failed to add file descriptor to epoll\n");
            close(epollfd);
            pthread_mutex_unlock(&m[turn]);
            return 1;
        }
        //MAIN THREAD and Create Event Struct
       
        cnt_clients[turn]++;
        
        pthread_mutex_unlock(&m[turn]);
        pthread_cond_signal(&cv[turn]);
        return;
    }
    //MAIN'S WORK COMPLETE

    int i=rank-1;
    pthread_mutex_lock(&m[i]);
    epollfd[i]=epoll_create1(0);
    if(epollfd[i]==-1){
        perror("\nCannot Create Epoll\n");
        exit(1);
    }
    pthread_mutex_unlock(&m[i]);

    pthread_mutex_lock(&m_create[i]);
    created[i]=1;
    pthread_mutex_unlock(&m_create[i]);
    pthread_cond_signal(&cv_create[i]);

    pthread_mutex_lock(&m[i]);
    if(epollfd[i]==-1){
        perror("\nCannot Create Epoll\n");
        exit(1);
    }
    while(cnt_clients[i]<=0){
        pthread_cond_wait(&cv[i],&m[i]);
        
    }
    pthread_mutex_unlock(&m[i]);
    struct epoll_event events[20];
    while(1){
        event_count=epoll_wait(epollfd[i],events,20,30000);
        
        for(int i=0;i<event_count;i++){
            //DO ALL WORK 
            char read_buffer[513];
            int cnt=1;
            struct request req;
            struct response res;
            while(cnt!=0){
                cnt=read(events[i].data.fd,read_buffer,513);
                //printf("%d \n",(int)rank);
                /*if(cnt!=0){
                    printf(" %d %s\n",cnt,read_buffer);
                }*/ // DO MAKE USE MAY CONTAIN BUGS
                if(cnt!=0){
                    req=parse_request(read_buffer);
                    if(req.api==1){
                        if(req.key[strlen(req.key)-1]=='\n'){
                            req.key[strlen(req.key)-1]='\0';
                        }
                        
                        res=GET(req);
                        bind_res_get(res,events[i].data.fd);
                        //MAKE RES PACKET AND THEN WRITE
                    }if(req.api==2){
                        if(req.value[strlen(req.value)-1]=='\n'){
                            req.value[strlen(req.value)-1]='\0';
                        }
                        
                        res=PUT(req);
                        bind_res_put(res,events[i].data.fd);
                        //MAKE RES PACKET AND THEN WRITE
                    }if(req.api==3){
                        if(req.key[strlen(req.key)-1]=='\n'){
                            req.key[strlen(req.key)-1]='\0';
                        }
                        
                        res=DEL(req);
                        bind_res_del(res,events[i].data.fd);
                    }
                }    

                    /*if(read_buffer[0]=='1' ||read_buffer[0]=='3'){
                        int api=read_buffer[0]-'0';
                        cnt=read(events[i].data.fd,read_buffer,256);
                        if(cnt!=0){
                            req=parse_request(read_buffer,api);
                            if(req.api==1){
                                res=GET(req);
                                //MAKE RES PACKET AND THEN WRITE
                            
                            }if(req.api==3){
                                res=DEL(req);
                            }

                        }

                    }else{
                        cnt=read(events[i].data.fd,read_buffer,512);
                        if(cnt!=0){
                            req=parse_request(read_buffer,2);
                            res=PUT(req);
                        }
                    }*/
                
                
                /*if(cnt!=0){
                    printf(" %d %s\n",cnt,read_buffer);
                }*/ // DO MAKE USE MAY CONTAIN BUGS
                                
            }
            
            //lseek(events[i].data.fd,0,SEEK_END);
        }
    }

}