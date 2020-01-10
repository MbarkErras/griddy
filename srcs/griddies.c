#include "griddy.h"

/*
** configuration.h is a shared file between master and slaves.
** it should contains shared configurtion details like requests types.
**
*/

#include "configuration.h"

int     execute_requests()
{
    while (1)
    {
        if (/*there is no requests*/)
            continue ;
        else
        {
            execute_request(/*top reqeust*/);
            // pop request;
        }
        
    }
}

// read sent data and construct requests stack
void    receive_requests()
{
}

int connect_master()
{
    int                 socket_fd;
    struct sockaddr_in  server_address;
    int                 connection_fd;

    if (socket_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
        return (SERVER_ERROR);
    ft_bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_address.sin_port = htons(PORT);
    if ((bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) != 0)
        return (SERVER_ERROR);
    if (listen(socket_fd, LISTEN_QUEUE) != 0)
        return (SERVER_ERROR);
    while (1)
    {
        if ((connection_fd = accept(socket_fd, )) != -1)
            return (SERVER_ERROR);
        receive_requests();
    }
    close(socket_fd);
}