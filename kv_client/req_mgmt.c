#include<string.h>
void bind_msg_get(char* msg,char* key){
    for(int i=0;i<513;i++){
        msg[i]='\0';
    }
    
    msg[0]='1';
    memcpy(msg+1,key,256);
    int flag=0;
    for(int i=0;i<513;i++){
        if(msg[i]=='\0'){
            flag=1;
        }
        if(flag==1){
            msg[i]='\0';
        }
    }
    
    
    
}

void bind_msg_put(char* msg,char* key,char* value){
    for(int i=0;i<513;i++){
        msg[i]='\0';
    }
    msg[0]='2';
    memcpy(msg+1,key,256);
    int flag=0;
    for(int i=0;i<257;i++){
        if(msg[i]=='\0'){
            flag=1;
        }
        if(flag==1){
            msg[i]='\0';
        }
    }
    memcpy(msg+257,value,256);
    flag=0;
    for(int i=257;i<513;i++){
        if(msg[i]=='\0'){
            flag=1;
        }
        if(flag==1){
            msg[i]='\0';
        }
    }
}

void bind_msg_del(char* msg,char* key){
    for(int i=0;i<513;i++){
        msg[i]='\0';
    }
    msg[0]='3';
    memcpy(msg+1,key,256);
    int flag=0;
    for(int i=0;i<513;i++){
        if(msg[i]=='\0'){
            flag=1;
        }
        if(flag==1){
            msg[i]='\0';
        }
    }
    
    
}