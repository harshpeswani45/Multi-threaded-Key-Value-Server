#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"


#include "helper_persistent.c"
#include "persistent_mgmt.c"
#include "read_config.c"
#include "cache_mgmt.c"
#include "res_mgmt.c"
#include "api_mgmt.c"
#include "req_mgmt.c"
#include "init_threads.c"
#include "worker_thread.c"
#include "create_thread.c"
#include "create_connection.c"
#include "assign_work.c"
#include "init_new_threads.c"
#include "create_new_threads.c"



int main(){
    struct connection con;
    data=read_config();
    init_threads(data.THREAD_POOL_SIZE_INITIAL);
    create_thread(data.THREAD_POOL_SIZE_INITIAL);
    con=create_connection(data.LISTENING_PORT);
    while(1){ 
           
        con_fd=accept(con.sockfd, (struct sockaddr *) &con.cli_addr, &con.clilen);
        if (con_fd < 0) 
            perror("ERROR on accept");
        assign_work(total_threads);
    }    

    return 0;
}