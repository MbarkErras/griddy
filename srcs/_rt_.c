#include "griddy.h"
#include "configuration.h"

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

/*
** after establishing connection with node, send_program_to_nodes() broadcast
** computation program to all nodes with the input.
*/

int send_program_to_nodes(t_cluster *cluster)
{
    int         fd;
    t_request   request;
    void        *program;
    int         size;

    if ((fd = open(program, O_RDONLY)) == -1)
        return (OPEN_ERROR);
    if (!(program = read_file(fd))
        return (OPEN_ERROR);
    request.type = SENDING_PROGRAM;
    request.data = program;
    request.size = ft_strlen(program);
    request.status = malloc(sizeof(char) * size); //protect
    ft_bzero(request.status, cluster->size);
    t_stack_push_back(cluster->requests, create_request(request));
}

