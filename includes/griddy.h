#ifndef GRIDDY_H
# define GRIDDY_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/socket.h>
# include <netinet/in.h> 
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>

// / / / D E V / / / / //
# include <stdio.h>
// / / / D E V / / / / //

# include "centropy.h"
# include "queue.h"

#include "configuration.h"


# define PORT 1337
# define LISTEN_QUEUE 42
# define BUFFER_SIZE 512

typedef struct  s_request
{
    int         type;
    size_t      size;
    void        *data;
    char        *status;
}               t_request;

/*
** REQUESTS TYPES
*/

# define PROGRAM 1
# define COMPUTATION 2

typedef struct  s_node
{
    char            *ip;
    int             socket;
    int             status;
    t_dstruct_list  requests_queue;
    int             flags;
}               t_node;

/*
** NODES STATUS BITS
*/

# define CONNECTED 0
# define DO_PROCEED 1

typedef struct   s_cluster
{
    t_node          *nodes;
    char            *program;
    size_t          size;
    t_dstruct_list  requests_queue;
}               t_cluster;

typedef struct  s_slave
{
    int             connection_fd;
    t_dstruct_list  requests_queue;
}               t_slave;


/*
** CONFIGURATION UTILITIES
*/

int get_configuration(char *configuration_file, t_cluster *cluster);


/*
** DE/CONSTRUCTORS
*/

t_request   *create_request(t_request value);
void        destroy_request(t_request *request);

/*
** ERROR HANDLING
** convention: 0 for successful return.
*/

# define ERROR_WRAPPER(x) err ? err : x
# define BAD_CONFIG 1
# define CONNECTION_ERR 2

/*
** static int is_valid_ip(char *ip) MACROS
*/

# define BYTE_BLOCK 0
# define BYTE_BLOCK_LOCK 1
# define DOTS 2
# define BYTE_BLOCK_OFFSET 3

/*
** UTILITIES MACROS
*/

# define CAST(v, t) ((t)v)

#endif