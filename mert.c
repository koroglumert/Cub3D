
#include "cub3d.h"
//makefile minilibx açılacak

//silinecek
void print_doublearray(char **str)
{
	for(int i = 0; str[i]; i++)
	{
		for(int j = 0; str[i][j]; j++)
			printf("%c", str[i][j]);
		printf("\n");
	}
}
//berrede var mı bu fonksyon
void	ft_free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

int	ft_is_character(char c)
{
	if (c == '1' || c == '0' || c == 'W' || c == 'N' || c == 'E' || c == 'S')
		return (1);
	return (0);
}


void	ft_control_double_map(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_is_character(str[i][j]))
			{
				printf("\nHATALI '%c'\n", str[i][j]);
				ft_free_double_array(str);
				exit(print_error("Error! Double Map.\n", 1));
			}
			j++;
		}
		i++;
	}
}
//bu var mı elde
int	ft_str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//boşluk dışında white space olamıyorsa mapte buna gerek yok.

void	ft_recursive_double_map(char **str, int i, int j)
{
	if (!str[i] || j >= ft_str_len(str[i]) || !ft_is_character(str[i][j])) //burada j'nin değeri uzunlukla kontrol edilmeli.
		return ;
	str[i][j] = 'X';
	if (i >= 1)
	{
		ft_recursive_double_map(str, i - 1, j);
		ft_recursive_double_map(str, i - 1, j + 1);
	}
	if (j >= 1)
	{
		ft_recursive_double_map(str, i, j - 1);
		ft_recursive_double_map(str, i + 1, j - 1);
	}
	if (i >= 1 && j >= 1)
		ft_recursive_double_map(str, i - 1, j - 1);
	ft_recursive_double_map(str, i + 1, j);
	ft_recursive_double_map(str, i, j + 1);
	ft_recursive_double_map(str, i + 1, j + 1);
}

char	**ft_copy_double_array(char **str)
{
	char	**new;
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		new[i] = malloc(sizeof(char) * (j + 1));
		new[i][j] = 0;
		i++;
	}
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			new[i][j] = str[i][j];
			j++;
		}
		i++;
	}
	return (new);
}

void	ft_check_double_map(char **str)
{
	//control silinecek
	printf("\n 1. ADIM \n");
	print_doublearray(str);

	//copy array
	str = ft_copy_double_array(str);

	//control silinecek
	printf("\n 2. ADIM \n");
	print_doublearray(str);

	ft_recursive_double_map(str, 0, 0);

	//control silinecek
	printf("\n 3. ADIM \n");
	print_doublearray(str);

	ft_control_double_map(str);
	ft_free_double_array(str);
}