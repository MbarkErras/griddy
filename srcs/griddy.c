#include "griddy.h"
#include "configuration.h"
void    send_request(t_stack *request)
{
    write(connection, &request->type, sizeof(request->type));
    write(connection, &request->size, sizeof(request->size));
    write(connection, request->data, request->size);
}

int     connect_slave(t_node *node)
{
    F_SET(node->status, CONNECTED);
    while (1)
    {
        if (node->requests || !F_SET(node->flags, DO_PROCEED))
            continue ;
        else
        {
            send_request(node->requests);
        }
    }
}

/*
** connect_nodes() is meant to launch server in a new thread
** and establish connection with nodes each in a diffrent thread.
*/

int initiate_connection_to_slaves(t_cluster cluster,
        void (* status_reporter)(int , void *), void *argument)
{
    int                 socket_fd;
    struct sockaddr_in  server_address;
    pthread_t           tid;
    int                 i;

    i = -1;
    while (++i < cluster->size)
    {
        if (socket_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
            return (SERVER_ERROR);
        ft_bzero(&server_address, sizeof(server_address));
        server_address.sin_family = AF_INET; 
        server_address.sin_addr.s_addr = htonl(connection->cluster.nodes[i]); 
        server_address.sin_port = htons(PORT);
        if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
            continue ;
        cluster->nodes[i].socket = socket_fd;
        if (pthread_create(&tid, NULL, connect_slave, &cluster->nodes[i])
            return (SERVER_ERROR);
        //status_reporter(i, argument);
    }
}

/*
** after establishing connection with node, send_program_to_nodes() broadcast
** computation program to all nodes with the input.
*/

int send_program_to_nodes(t_cluster *cluster)
{
    t_request   request;
    void        *program;
    int         size;

    program = read_program(cluster->program, &size); //protect
    request.type = SENDING_PROGRAM;
    request.data = program;
    request.size = size;
    request.status = malloc(sizeof(char) * size); //protect
    ft_bzero(request.status, cluster->size);
    t_stack_push_back(cluster->requests, create_request(request));
}

/*
** init_nodes() init connection with nodes and sends computation program.
*/

int init_nodes(t_cluster *cluster)
{
    int err;

    err = 0;
    err = initiate_connection_to_slaves(connection);
    err = send_program_to_nodes(*connection);
    return (err);
}

/*
** broadcast_computation() broadcasts input to computation program and
** assigns returned output to void *output.
*/

int broadcast_computation(t_connection connection,
        void *data, void *output, int (*data_serializer)(void *))
{

}