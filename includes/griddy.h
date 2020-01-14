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

# include "centropy.h"
# include "cdata_structures.h"

#include "configuration.h"


# define PORT 1337

# define BUFFER_SIZE 512

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
** CONFIGURATION UTILITIES
*/

int get_configuration(char *configuration_file, t_cluster *cluster);


/*
** NODES STATUS BITS
*/

# define CONNECTED 0



/*
** ERROR HANDLING
*/

# define BAD_CONFIGBAD_CONFIG 1

/*
** static int is_valid_ip(char *ip) MACROS
*/

# define BYTE_BLOCK 0
# define BYTE_BLOCK_LOCK 1
# define DOTS 2
# define BYTE_BLOCK_OFFSET 3

#endif