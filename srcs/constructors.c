#include "griddy.h"

t_request *create_request(t_request value)
{
    t_request *request;

    if ((request = malloc(sizeof(t_request))))
        return (NULL);
    request->type = value.type;
    request->size = value.size;
    request->data = value.data;
    request->status = value.status;
    return (request);
}

void    destroy_request(t_request *request)
{
    free(CAST(request, t_request *)->data);
    free(CAST(request, t_request *)->status);
    free(request);
}