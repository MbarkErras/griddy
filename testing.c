#include "includes/griddy.h"

int main(int argc, char **argv)
{
    t_cluster cluster;

    if (get_configuration(argv[1], &cluster))
    {
        printf("err: get_configuration()\n");
        exit (0);
    }
}