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

/*
** get_configuration() parses configuration file and assign it content to
** *cluster structure.
*/

int get_configuration(char *configuration_file, t_cluser *cluster)
{
    char    *raw_configuration;
    char    *nodes_ip;
    int     fd;
    int     i;

    i = 0;
    cluster->size = 0;
    if ((fd = open(configuration_file, O_RDONLY)) == -1)
        return (OPEN_ERROR);
    raw_configuration = read_file(fd);
    ft_strdel(&raw_configuration);
    nodes_ip = ft_strsplit(raw_configuration, '\n');
    if (!(cluster->program = get_path(nodes_ip[0]))
    {
        free_array(nodes_ip);
        return (PARSE_ERROR);
    }
    ft_strdel(&nodes_ip[0]);
    while (nodes_ip[cluster->size + 1])
    {
        if (!is_valid_ip(nodes_ip[cluster->size]))
        {
            free_array(nodes_ip);
            return (PARSE_ERROR);
        }
        cluster->size++;
    }
    if (!(cluster->nodes = malloc(sizeof(t_node) * cluster->size))
    {
        free_array(nodes_ip);
        return (PARSE_ERROR);
    }
    while (i < cluster->size)
    {
        cluster->nodes[i]->ip = nodes_ip[i];
    }
    free(nodes_ip);
    return (0);
}