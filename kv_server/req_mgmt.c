#include<string.h>

struct request parse_request(char* req_str){
    struct request req;
    req.api=req_str[0]-'0';
    if(req.api==1){
        req.key=(char *)malloc(256);
        memcpy(req.key,req_str+sizeof(char),256);
        req.value=NULL;
        req.error=0;
    }else if(req.api==2){
        req.key=(char *)malloc(256);
        req.value=(char *)malloc(256);
        memcpy(req.key,req_str+sizeof(char),256);
        memcpy(req.value,req_str+257*sizeof(char),256);
        req.error=0;
    }else if(req.api==3){
        req.key=(char *)malloc(256);
        memcpy(req.key,req_str+sizeof(char),256);
        req.value=NULL;
        req.error=0;
    }else{
        req.error=1;
    }
    return req;
}