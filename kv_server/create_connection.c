#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

struct connection create_connection(int portno){
    struct connection con;
    con.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(con.sockfd < 0) 
        perror("ERROR opening socket");
    bzero((char *) &con.serv_addr, sizeof(con.serv_addr));
    con.serv_addr.sin_family = AF_INET;
    con.serv_addr.sin_addr.s_addr = INADDR_ANY;
    con.serv_addr.sin_port = htons(portno);
    if (bind(con.sockfd, (struct sockaddr *) &con.serv_addr,sizeof(con.serv_addr)) < 0) 
        perror("ERROR on binding");
    listen(con.sockfd,5);
    con.clilen=sizeof(con.cli_addr);
    return con;
}