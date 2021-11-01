
struct connection create_connection(int portno){
    struct connection con;
    struct hostent *server;
    con.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (con.sockfd < 0) 
        perror("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        perror("Error,Try again later \n");
        exit(0);
    }
    bzero((char *) &con.serv_addr, sizeof(con.serv_addr));
    con.serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&con.serv_addr.sin_addr.s_addr,server->h_length);
    con.serv_addr.sin_port = htons(portno);
    return con;
}