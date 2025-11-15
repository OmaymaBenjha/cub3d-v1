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

#include <limits.h>

int ft_atoi(const char *str)
{
    long result = 0;
    int  sign = 1;
    int  i = 0;

    // Skip whitespace
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;

    // Check sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    // Parse digits
    while (str[i] >= '0' && str[i] <= '9')
    {
        int digit = str[i] - '0';

        // Check overflow BEFORE multiplying
        if (result > (LONG_MAX - digit) / 10)
        {
            if (sign == 1)
                return (INT_MAX);   // positive overflow
            else
                return (INT_MIN);   // negative overflow
        }

        result = result * 10 + digit;
        i++;
    }

    result *= sign;

    // Final range check (should not be needed, but safe)
    if (result > INT_MAX)
        return INT_MAX;
    if (result < INT_MIN)
        return INT_MIN;

    return (int)result;
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

void free_split(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
char *ft_strtrim_newline(char *s)
{
    size_t len;
    char *trimmed_s;

    if (!s)
        return NULL;

    len = ft_strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' ' || s[len - 1] == '\r' || s[len - 1] == '\t'))
    {
        len--;
    }

    trimmed_s = ft_substr(s, 0, len);
    return trimmed_s;
}