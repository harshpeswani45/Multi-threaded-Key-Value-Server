char* unbind_msg(char *msg){
    static char res[256];
    memcpy(res,(msg+1),256);
    return res;
}
