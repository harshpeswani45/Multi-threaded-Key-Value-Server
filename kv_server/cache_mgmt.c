#include <string.h>

struct node{
    char* key;
    char *value;
    long used;
    struct node* next;
};


int cnt_elem=1;

struct node* head=NULL;

struct node* create_node(char* key, char* value){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->key=key;
    temp->value=value;
    temp->used=0;
    temp->next=NULL;
    return temp;
    
}


struct node* insert_node(struct node *head,struct node* new){
    if(head==NULL){
        head=new;
        return head;
    }    
    new->next=head;
    head=new;
    cnt_elem++;
    return head;
}

struct node* find_entry(struct node* head,char* key){
    struct node *temp=head;
    while(temp!=NULL){
        if(!strcmp(temp->key,key)){
            return temp;
        }
        temp=temp->next;
    }
    return temp;
}

struct node* LFU_replace(struct node* head,struct node* new){
   
    long min_curr=head->used;
    struct node* tmp=head;
    struct node* min_tmp=head;
    struct node* min_tmp_prev=NULL;
    while(tmp->next!=NULL){
        if(tmp->next->used < min_curr){
            min_curr=tmp->next->used;
            min_tmp=tmp->next;
            min_tmp_prev=tmp;
        }
        tmp=tmp->next;
    }
    struct node* to_del=min_tmp;
    if(min_tmp==head){
        new->next=head->next;
        head=new;
        free(to_del);
    }else{
        new->next=min_tmp->next;
        min_tmp_prev->next=new;
        free(to_del);
    }
   
    return head;

}

struct response find_in_cache(struct request req){
    struct node* tmp=NULL;
    struct response res;
    pthread_mutex_lock(&m_cache);
    tmp=find_entry(head,req.key);
    pthread_mutex_unlock(&m_cache);
    
    if(req.api==1){
        if(tmp==NULL){
            res.code=100;
        }else{
            res.code=200;
            pthread_mutex_lock(&m_cache);
            res.value=tmp->value;
            if(tmp->used==__LONG_MAX__){

            }else{
                tmp->used++;
            }
            pthread_mutex_unlock(&m_cache);
        }
    }else if(req.api==2){
        if(tmp==NULL){
            struct node* new=create_node(req.key,req.value);
            pthread_mutex_lock(&m_cache);
            if(cnt_elem == max_cache){
                head=LFU_replace(head,new);
               
        
            }else{

               // struct node* new=create_node(req.key,req.value);
                head=insert_node(head,new);
               
            }
             pthread_mutex_unlock(&m_cache);
        }else{
            res.code=200;
            pthread_mutex_lock(&m_cache);
            tmp->value=req.value;
            if(tmp->used==__LONG_MAX__){

            }else{
                tmp->used++;
            }
            pthread_mutex_unlock(&m_cache);
        }  
    }
    return res;
}

struct response delete_in_cache(struct request req){
    struct node* tmp=NULL;
    struct response res;
    pthread_mutex_lock(&m_cache);
    tmp=find_entry(head,req.key);
    pthread_mutex_unlock(&m_cache);
    if(tmp==NULL){
        res.code=100;
    }else{
        pthread_mutex_lock(&m_cache);
        struct node* temp=head;
        if(tmp==head){
            head=head->next;
            free(tmp);
        }else{
            while(temp->next!=NULL){
                if(temp->next==tmp){
                    struct node* to_del=tmp;
                    temp->next=temp->next->next;
                    free(to_del);
                    break;
                }
                temp=temp->next;
            }
        }
        cnt_elem--;
        pthread_mutex_unlock(&m_cache);
        res.code=200;   
    }
    return res;

}



