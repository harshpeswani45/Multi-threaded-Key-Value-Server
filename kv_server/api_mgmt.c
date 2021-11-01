
struct response GET(struct request req){
    struct response res=find_in_cache(req);
    if(res.code==200){
        return res;
    }else{
        res=find_in_file(req);
        if(res.code==200){
            req.api=2;
            req.value=(char *)malloc(256);
            memcpy(req.value,res.value,256);
            struct response res1;
            res1=find_in_cache(req);
            
        }
        return res;
    }
}

struct response PUT(struct request req){
    struct response res=update_db(req); //Call Pers
    //MODIFY IN CACHE IF IT EXISTS
    res=find_in_cache(req);
    return res;
}

struct response DEL(struct request req){
    struct response res=delete_db(req);
    if(res.code==200){
         struct response res1=delete_in_cache(req);
    }else{
        return res;
    }
    return res;
}