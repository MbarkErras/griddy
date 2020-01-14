#include "griddy.h"

/*
** send_request() writes a packaged t_request request to correspondent node socket
*/

void    send_request(t_node node, t_request *request)
{
    write(node.socket, &request->type, sizeof(request->type));
    write(node.socket, &request->size, sizeof(request->size));
    write(node.socket, request->data, request->size);
}

/*
** broadcast_computation() broadcasts input to computation program and
** assigns returned output to void *output.
*/

// int broadcast_computation(t_cluster *cluster,
//         void *data, int size, void *output, int (*data_serializer)(void *))
// {
//     t_req
//     int i = 0;
//     while (i < cluster->size)
//     {

//     }
//     return (0);
// }

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

int send_program_to_nodes(t_cluster *cluster)
{
    int         fd;
    t_request   request;
    void        *program;
    int         size;

    if ((fd = open(cluster->program, O_RDONLY)) == -1)
        return (OPEN_ERROR);
    if (!(program = read_file(fd)))
        return (OPEN_ERROR);
    request.type = PROGRAM;
    request.data = program;
    request.size = ft_strlen(program);
    request.status = malloc(sizeof(char) * size); //protect
    ft_bzero(request.status, cluster->size);
    int i = 0;
    while (i < cluster->size)
    {
        send_request(cluster->nodes[i], &request);
        i++;
    }
    //t_stack_push_back(cluster->requests, create_request(request));
    return (0);
}


/*
** connect_slave() keeps looping over node->requests waiting for requests to
**
*/

void    *connect_slave(void *node)
{
    //printf("node: %s connected!\nsocket: %d\n", ((t_node *)node)->ip, ((t_node *)node)->socket);    
    return NULL;
    /*F_SET(node->status, CONNECTED);
   return NULL;
    while (1)
    {
        if (node->requests_queue.size || !F_SET(node->flags, DO_PROCEED))
            continue ;
        else
        {
            send_request(node->requests_queue.head->content);
        }
    }*/
}

/*
** initiate_connection_to_slaves() is meant to establish connection
** with nodes each in a diffrent thread.
*/

int initiate_connection_to_slaves(t_cluster *cluster,
        void (* status_reporter)(int , void *), void *argument)
{
    int                 socket_fd;
    struct sockaddr_in  server_address;
    pthread_t           tid;
    int                 i;

    i = -1;
    while (++i < cluster->size)
    {
        if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            return (CONNECTION_ERR);
        ft_bzero(&server_address, sizeof(server_address));
        server_address.sin_family = AF_INET; 
        inet_pton(AF_INET, cluster->nodes[i].ip, &server_address.sin_addr);
        server_address.sin_port = htons(PORT);
        if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
            continue ;
        cluster->nodes[i].socket = socket_fd;
        if (pthread_create(&tid, NULL, connect_slave, &cluster->nodes[i]))
            return (CONNECTION_ERR);
        if (status_reporter)
            status_reporter(i, argument);
    }
    return (0);
}

/*
** init_nodes() init connection with nodes and sends computation program.
*/

int init_cluster(t_cluster *cluster)
{
    int err;

    //cluster->requests_queue = t_dstruct_list_init();
    err = 0;
    err = ERROR_WRAPPER(initiate_connection_to_slaves(cluster, NULL, NULL));
    err = ERROR_WRAPPER(send_program_to_nodes(cluster));
    return (err);
}