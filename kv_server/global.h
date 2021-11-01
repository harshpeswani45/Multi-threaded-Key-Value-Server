#include<pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

struct config_data{
/*LISTENING_PORT
CLIENTS_PER_THREAD (number of clients that each worker thread handles)
CACHE_SIZE (in number of keys)
CACHE_REPLACEMENT (one of LRU or LFU)
THREAD_POOL_SIZE_INITIAL (how many worker threads to start out with).
THREAD_POOL_GROWTH (how many new threads to add each time you want to grow the pool - do this when you are down to the last free thread)
*/
    int LISTENING_PORT;
    int CLIENTS_PER_THREAD;
    int CACHE_SIZE;
    int CACHE_REPLACEMENT;
    int THREAD_POOL_SIZE_INITIAL;
    int THREAD_POOL_GROWTH;
};

struct connection{
    int sockfd;
    int clilen;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
};

struct request{
    int api;
    char* key;
    char* value;
    int error;
};

struct response{
    unsigned int code;
    char* value;
};

struct free_list{
    int index;
    struct free_list *next;
};

FILE *fd[37];

struct free_list* head_file[37];

struct config_data data;

pthread_mutex_t m_file[37];

int *epollfd;

int max_cache;

pthread_cond_t *cv;
pthread_mutex_t *m;

pthread_cond_t *cv_create;
pthread_mutex_t *m_create;

pthread_mutex_t *m_cache;
int *cnt_clients;
int turn;
int con_fd;

int *created;

int batch_size;
int flag_check;

int thread_grow;

int jump_check;

int total_threads;