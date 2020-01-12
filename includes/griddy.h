#ifndef GRIDDY_H
# define GRIDDY_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/socket.h>
# include <netinet/in.h> 
# include <netinet/in.h> 
# include <sys/types.h>
# include <sys/time.h>

# include "stack.h"

# define PORT 1337

typedef struct  s_request
{
    int         type;
    size_t      size;
    void        *data;
    char        *status;
}               t_request;

typedef struct  s_node
{
    char        *ip;
    int         socket;
    int         status;
    t_list     **requests;
    int         flags;
}               t_node;

# define DO_PROCEED 0

typedef struct   s_cluster
{
    t_node      **nodes;
    char        *program;
    size_t      size;
    t_list      *requests;
}               t_cluster;

/*
** NODES STATUS BITS
*/
# define CONNECTED 0

# define BUFFER_SIZE 512

# define OPEN_ERROR 1
# define SERVER_ERROR 2
# define PARSE_ERROR 3

#endif