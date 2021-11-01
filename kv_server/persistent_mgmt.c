
struct response update_db(struct request req){
    struct response res;
    char hash_tmp=req.key[0];
    int hash;
    if(hash_tmp >='0' && hash_tmp <='9'){
        hash=hash_tmp-'0';
    }else if(hash_tmp>='A' && hash_tmp <='Z'){
        hash=(int)(hash_tmp-'A'+10);
    }else if(hash_tmp>='a' && hash_tmp <='z'){
        hash=(int)(hash_tmp-'a'+10);
    }else{
        hash=36;
    }
    res=search_and_update(hash,req);
    if(res.code==200){
        return res;
    }

    res=add_entry(hash,req);
    fflush(fd[hash]);
    // IF NOT FOUND CHECK FREE LIST AND MAKE
    return res;
}

struct response find_in_file(struct request req){
    struct response res;
    char hash_tmp=req.key[0];
    int hash;
    if(hash_tmp >='0' && hash_tmp <='9'){
        hash=hash_tmp-'0';
    }else if(hash_tmp>='A' && hash_tmp <='Z'){
        hash=(int)(hash_tmp-'A'+10);
    }else if(hash_tmp>='a' && hash_tmp <='z'){
        hash=(int)(hash_tmp-'a'+10);
    }else{
        hash=36;
    }
    res=search_get(hash,req);
    fflush(fd[hash]);
    return res;

}

struct response delete_db(struct request req){
    struct response res;
    char hash_tmp=req.key[0];
    int hash;
    if(hash_tmp >='0' && hash_tmp <='9'){
        hash=hash_tmp-'0';
    }else if(hash_tmp>='A' && hash_tmp <='Z'){
        hash=(int)(hash_tmp-'A'+10);
    }else if(hash_tmp>='a' && hash_tmp <='z'){
        hash=(int)(hash_tmp-'a'+10);
    }else{
        hash=36;
    }
    res=delete_in_file(hash,req);
    fflush(fd[hash]);
    return res;
}


