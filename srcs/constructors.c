#include "griddy.h"

t_request *create_request(t_request request)
{
    t_request *request;

    if ((request = malloc(sizeof(t_request))))
        return (NULL);
    request->type = request.type;
    request->size = request.size;
    request->data = request.data;
    request->status = request.status;
    return (request);
}