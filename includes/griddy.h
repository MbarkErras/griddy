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

typedef struct   s_cluster
{
    char     **nodes;
    char    *program;
    size_t  size;
}               t_cluster;

typedef struct s_connection
{
    t_cluster   cluster;
    int         *sockets;
    int         *status;
}               t_connection;

typedef struct  s_node
{
    t_stack     *requests;
}               t_node;

typedef struct  s_request
{
    int         type;
    void        *data;
    size_t      size;
}               t_request;


/*
** NODES STATUS BITS
*/
# define CONNECTED 0

# define BUFFER_SIZE 512

# define OPEN_ERROR 1
# define SERVER_ERROR 2

#endif