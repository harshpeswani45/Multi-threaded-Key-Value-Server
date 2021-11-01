#include "req_mgmt.c"
#include "res_mgmt.c"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
char* GET(char* key){
    if(strlen(key)>256){
        return "Key length is greater than 256Bytes";
    }
    char msg[513];
    bind_msg_get(msg,key);
    write(con.sockfd,msg,513);

    char response_buffer[513];
    read(con.sockfd,response_buffer,513);
    return unbind_msg(response_buffer);
    
}

char* PUT(char* key, char* value){
    if(strlen(key)>256){
        return "Key length is greater than 256Bytes";
    }
    if(strlen(value)>256){
        return "Value length is greater than 256Bytes";
    }
    char msg[513];
    bind_msg_put(msg,key,value);
    write(con.sockfd,msg,513);
    
    char response_buffer[513];
    read(con.sockfd,response_buffer,513);
    return unbind_msg(response_buffer);

}

char* DEL(char* key){
    if(strlen(key)>256){
        return "Key length is greater than 256Bytes";
    }
    char msg[513];
    bind_msg_del(msg,key);
    write(con.sockfd,msg,513);

    char response_buffer[513];
    read(con.sockfd,response_buffer,513);
    return unbind_msg(response_buffer);

}