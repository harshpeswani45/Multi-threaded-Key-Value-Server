#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

struct connection{
    int sockfd;
    struct sockaddr_in serv_addr;
};


struct connection con;