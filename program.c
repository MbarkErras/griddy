#include <unistd.h>

int	main(void)
{
	int sum = 0;
	int c;

	while (read(0, &c, 1) > 0)
		sum += c;
	int response_size = sizeof(int);
	write(1, &response_size, response_size);
	write(1, &sum, response_size);
	return (0);
}
