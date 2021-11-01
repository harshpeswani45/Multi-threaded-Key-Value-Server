#include <string.h>

void bind_res_get(struct response res,int fd){
    char response_buffer[513];
    response_buffer[0]=res.code;
    if(res.code==100){
        res.value="Does not exist";
    }
    memcpy(response_buffer+1,res.value,256);
    write(fd,response_buffer,sizeof(response_buffer));
}


void bind_res_put(struct response res,int fd){
    char response_buffer[513];
    response_buffer[0]=res.code;
    if(res.code==100){
        res.value="Error in Putting";
    }else{
        res.value="Success";
    }
    memcpy(response_buffer+1,res.value,256);
    write(fd,response_buffer,sizeof(response_buffer));
}

void bind_res_del(struct response res,int fd){
    char response_buffer[513];
    response_buffer[0]=res.code;
    if(res.code==100){
        res.value="Does not exist";
    }else{
        res.value="Success";
    }
    memcpy(response_buffer+1,res.value,256);
    write(fd,response_buffer,sizeof(response_buffer));
}