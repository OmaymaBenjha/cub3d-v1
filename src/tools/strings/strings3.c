/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayt <sayt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 02:45:00 by sayt              #+#    #+#             */
/*   Updated: 2025/12/28 02:45:00 by sayt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_digits(int n)
{
	int	count;

	count = 1;
	while (n / 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	long		num;
	int			len;
	int			is_negative;

	num = n;
	is_negative = (num < 0);
	if (is_negative)
		num = -num;
	len = count_digits(num) + is_negative;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = '0' + (num % 10);
		num /= 10;
		if (len == 0 && is_negative)
			str[0] = '-';
	}
	return (str);
}

static int	check_overflow(long result, int digit, int sign)
{
	if (result > (LONG_MAX - digit) / 10)
	{
		if (sign == 1)
			return (INT_MAX);
		else
			return (INT_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;
	int		limit;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		limit = check_overflow(result, str[i] - '0', sign);
		if (limit)
			return (limit);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int)(result * sign));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
