struct response search_and_update(int hash,struct request req){
    struct response res;
    pthread_mutex_lock(&m_file[hash]);
    char read_buffer[515];
    char key_extracted[257];
    int flag=0;
    int seek=0;
   // fclose(fd[hash]);
    char str[3];
    sprintf(str, "%d", hash);
    //fd[hash] = fopen(str, "a+");
    fseek(fd[hash],0,SEEK_SET);
    while(fgets(&read_buffer,515,fd[hash])!=NULL){
        memcpy(&key_extracted,&read_buffer,256);
        key_extracted[256]='\0';
        if(!strcmp(req.key,key_extracted)){
            if(read_buffer[512]=='1'){
                flag=1;
                break;
            }
        }
        seek++;
    }
    if(flag==1){
        seek=seek*514;
        fseek(fd[hash],seek,SEEK_SET);
        char wrt[514];
        memcpy(wrt,key_extracted,256);
        memcpy((wrt+256),req.value,256);
        wrt[512]='1';
        wrt[513]='\n';
        fwrite(wrt,1,sizeof(wrt),fd[hash]);
        res.code=200;
    }else{
        res.code=100;
    }
    fseek(fd[hash],0,SEEK_SET);
    pthread_mutex_unlock(&m_file[hash]);   
    return res; 
}

struct response search_get(int hash,struct request req){
    struct response res;
    pthread_mutex_lock(&m_file[hash]);
    char read_buffer[515];
    char key_extracted[257];
    int flag=0;
    int seek=0;
   // fclose(fd[hash]);
    char str[3];
    sprintf(str, "%d", hash);
    //fd[hash] = fopen(str, "a+");
    fseek(fd[hash],0,SEEK_SET);
    while(fgets(&read_buffer,515,fd[hash])!=NULL){
        memcpy(&key_extracted,&read_buffer,256);
        key_extracted[256]='\0';
        if(!strcmp(req.key,key_extracted)){
            if(read_buffer[512]=='1'){
                flag=1;
                break;
            }
        }
        seek++;
    }
    if(flag==1){
        char value_extracted[257];
        memcpy(value_extracted,(read_buffer+256),256);
        value_extracted[256]='\0';
        res.code=200;
        res.value=value_extracted;

    }else{
        res.code=100;
        char value_extracted[257]="Key not found";
        res.value=value_extracted;
    }
    pthread_mutex_unlock(&m_file[hash]);

    return res;
}

struct response add_entry(int hash,struct request req){
    struct response res;
    int index;
    pthread_mutex_lock(&m_file[hash]);
    if(head_file[hash]!=NULL){
        index=head_file[hash]->index;
        struct free_list *tmp=head_file[hash];
        head_file[hash]=head_file[hash]->next;
        free(tmp);
        
        fseek(fd[hash],index,SEEK_SET);
        char wrt[514];
        memcpy(wrt,req.key,256);
        memcpy((wrt+256),req.value,256);
        wrt[512]='1';
        wrt[513]='\n';
        fwrite(wrt,1,sizeof(wrt),fd[hash]);
        res.code=200;
        fseek(fd[hash],0,SEEK_SET);
    }else{
        fclose(fd[hash]);
        //char hash_str[3];
        char str[3];
        sprintf(str, "%d", hash);
        fd[hash] = fopen(str, "a+");
        char wrt[514];
        memcpy(wrt,req.key,256);
        memcpy((wrt+256),req.value,256);
        wrt[512]='1';
        wrt[513]='\n';
        fwrite(wrt,1,sizeof(wrt),fd[hash]);
        res.code=200;
        fclose(fd[hash]);
        fd[hash]=fopen(str,"r+");
    }
    pthread_mutex_unlock(&m_file[hash]);
    return res;
}

struct response delete_in_file(int hash,struct request req){
    struct response res;
    pthread_mutex_lock(&m_file[hash]);
    char read_buffer[515];
    char key_extracted[257];
    int flag=0;
    int seek=0;
   // fclose(fd[hash]);
    char str[3];
    sprintf(str, "%d", hash);
    //fd[hash] = fopen(str, "a+");
    fseek(fd[hash],0,SEEK_SET);
    while(fgets(&read_buffer,515,fd[hash])!=NULL){
        memcpy(&key_extracted,&read_buffer,256);
        key_extracted[256]='\0';
        if(!strcmp(req.key,key_extracted)){
            if(read_buffer[512]=='1'){

                flag=1;
                break;
            }
        }
        seek++;
    }
    if(flag==1){
        seek=seek*514;
        char value_ex[256]="\0";
        fseek(fd[hash],seek,SEEK_SET);
        char wrt[514];
        memcpy(wrt,key_extracted,256);
        memcpy((wrt+256),value_ex,256);
        wrt[512]='0';
        wrt[513]='\n';
        fwrite(wrt,1,sizeof(wrt),fd[hash]);
        res.code=200;
        
        //ADD IN FREE LIST
        struct free_list *new_free=(struct free_list *)malloc(sizeof(struct free_list));
        new_free->index=seek;
        new_free->next=head_file[hash];
        head_file[hash]=new_free;
        //ADD_COMPLETE

    }else{
        res.code=100;
        char value_extracted[257]="Key not found";
        res.value=value_extracted;

    }
    pthread_mutex_unlock(&m_file[hash]);
    return res;
}