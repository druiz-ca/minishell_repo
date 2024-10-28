
#include "libft.h"

int	ft_isdigit_str(char *str)
{
	int	cont;

	cont = 0;
	if (str == NULL)
		return (0);
	while (str[cont])
	{
		if (str[cont] >= '0' && str[cont] <= '9')
			cont++;
		else
			return (0);
	}
	return (1);
}
