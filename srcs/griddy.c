#include "griddy.h"

void    send_request(t_stack *request)
{
    write(connection, &request->type, sizeof(request->type));
    write(connection, &request->size, sizeof(request->size));
    write(connection, request->data, request->size);
}

int     connect_node(t_node *node)
{
    t_request *temp;

    while (1)
    {
        if (node->requests)
            continue ;
        else
        {
            send_request(node->requests);
            t_stack_pop(&node->requests);
        }
    }
}

/*
** connect_nodes() is meant to launch server in a new thread
** and establish connection with nodes each in a diffrent thread.
*/

int connect_to_nodes(t_connection *connection,
        void (* status_reporter)(int , void *), void *argument)
{
    int                 socket_fd;
    struct sockaddr_in  server_address;
    int                 connection_fd;
    pthread_t           tid;
    int                 i;

    i = -1;
    if (socket_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
        return (SERVER_ERROR);
    ft_bzero(&server_address, sizeof(server_address));
    while (++i < connection->cluster.size)
    {
        server_address.sin_family = AF_INET; 
        server_address.sin_addr.s_addr = htonl(connection->cluster.nodes[i]); 
        server_address.sin_port = htons(PORT);
        if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
            continue ;
        if (pthread_create(&tid, NULL, connect_node, (void *)connection_fd))
            return (SERVER_ERROR);
        F_SET(connection->status[i], CONNECTED);
        status_reporter(i, argument);
    }
    close(socket_fd);
}

/*
** after establishing connection with node, send_program_to_nodes() broadcast
** computation program to all nodes with the input.
*/

int send_program_to_nodes(t_connection connection)
{

}

/*
** init_nodes() init connection with nodes and sends computation program.
*/

int init_nodes(t_connection *connection)
{
    int err;

    err = 0;
    err = init_connection(connection);
    err = connect_nodes(connection);
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