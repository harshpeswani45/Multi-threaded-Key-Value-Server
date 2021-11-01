#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "global.h"
#include "create_connection.c"
#include "kvlibrary.c"


int main(int argc, char *argv[]){
    con=create_connection(3000);
    int chk=connect(con.sockfd,(struct sockaddr *)&con.serv_addr,sizeof(con.serv_addr));
    if(chk<0) 
        perror("Cannot Connect\n");
    
    //USE ALL API'S HERE This is Done for example
    char* ret;
    ret=PUT("2135","898");
    printf("%s",ret);
    ret=GET("2135");
    printf("%s",ret);
    ret=DEL("2135");
    printf("%s",ret);


    return 0;
 

}
