#ifndef GRIDDY_H
# define GRIDDY_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typdef struct   s_cluster
{
    int     **nodes;
    size_t  size;
}               t_cluster;

# define BUFFER_SIZE 512

# define OPEN_ERROR 1

#endif