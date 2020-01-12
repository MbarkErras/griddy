#include "griddy.h"

# define BYTE_BLOCK 0
# define BYTE_BLOCK_LOCK 1
# define DOTS 2
# define BYTE_BLOCK_OFFSET 3

int     is_valid_ip(char *ip)
{
    int i;
    int counts[4];

    i = -1;
    ft_bzero(counts, sizeof(int[4]));
    while (ip[++i])
    {
        if (ip[i] != '.' || !ft_isdigit(ip[i]) ||
        (ip[i] == '.' && (!i || !ft_isdigit(ip[i - 1]) || !ft_isdigit(ip[i + 1]))))
            return (0);
        if (ip[i] != '.' && !counts[BYTE_BLOCK_LOCK])
        {
            counts[BYTE_BLOCK]++;
            counts[BYTE_BLOCK_LOCK] = 1;
        }
        if (ip[i] == '.')
        {
            counts[BYTE_BLOCK_LOCK] = 0;
            counts[DOTS]++;
            if (i - counts[BYTE_BLOCK_OFFSET] > 3 ||
                ft_atoi(ip + counts[BYTE_BLOCK_OFFSET]) > 255)
                return (0);
            counts[BYTE_BLOCK_OFFSET] = i + 1;
        }
    }
    if (counts[DOTS] != 3 || counts[BYTE_BLOCK] != 4)
        return (0);
    return (1);
}

char    *get_path(char *entry)
{
    char *colon;

    if ((colon = ft_strchr(entry, ':')))
        return (NULL);
    *colon = 0;
    if (!ft_strcmp(entry, "path"))
        return (ft_strdup(colon + 1));
}