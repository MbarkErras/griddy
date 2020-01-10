#include "griddy.h"

char    *read_file(int fd)
{
    char    buffer[BUFFER_SIZE];
    char    *content;

    content = NULL;
    ft_bzero(buffer, BUFFER_SIZE);
    while (read(fd, buffer, BUFFER_SIZE - 1) > 0)
    {
        content = ft_strjoin_free(content, buffer, 1);
        ft_bzero(buffer, BUFFER_SIZE);
    }
    return (content);
}

int get_configuration(char *configuration_file, t_cluser *cluster)
{
    char    *raw_configuration;
    int     fd;

    cluster->size = 0;
    if ((fd = open(configuration_file, O_RDONLY)) == -1)
        return (OPEN_ERROR);
    raw_configuration = read_file(fd);
    cluster->nodes = ft_strsplit(raw_configuration, '\n');
    while (cluster->nodes[cluster->size])
    {
        // check if it is a valid ip
        cluster->size++;
    }
    return (0);
}