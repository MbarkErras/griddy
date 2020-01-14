#include "includes/griddy.h"

char    *read_segment_form_file(char fd, int size)
{
    char buffer[size + 1];

    ft_bzero(buffer, size + 1);
   read(fd, buffer, size);
   // printf("buffer input : |%s|\n", buffer);
    return (ft_strdup(buffer));
}

# define FILESIZE 3637248

int main(int argc, char **argv)
{
    t_cluster cluster;
    int fd;

write(0, "strstrstrstrstsr\n", 17);
    if ((fd = open(argv[2], O_RDONLY)) == -1)
    {
        printf("opan iror\n");
        return (0);
    }
    if (get_configuration(argv[1], &cluster))
    {
        printf("err: get_configuration()\n");
        exit (0);
    }
    init_cluster(&cluster);
    int task_size = FILESIZE / cluster.size;
    int i = 0;
    int result;
    t_request r;
    while (i < cluster.size)
    {
        r.type = COMPUTATION;
        r.data = read_segment_form_file(fd, task_size);
        //printf("%s | %d\n", r.data, task_size);
        r.size = ft_strlen(r.data);
        send_request(cluster.nodes[i], &r);
        //printf("slave: %d --> %d\n", i, result);
        i++;
    }
}