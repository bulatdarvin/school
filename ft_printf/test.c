#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "struct.h"

int     type_c(va_list arg, t_flags *flag)
{
    int width;
    int c;

    c = va_arg(arg, int);
    width = 0;
    if (flag->width)
    {
        if (flag->minus)
            ft_write(&c, 1, flag);
        while (width++ < flag->width - 1)
            ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
    }
    else
        ft_write(&c, 1, flag);
    return (flag->width ? width : 1);
}

int     calc_len(double c, int *size)
{
    int mod;

    mod = 1;
    while ((int)(c / 10) != 0)
    {
        c = c / 10;
        (*size)++;
        mod = mod * 10; 
    }
    return (mod);
}

void    handle_main(double *nb, char **str, int *i, int mod)
{
    char *s;

    s = *str;
    s = ft_strcat(s,ft_itoa((int)*nb));
    *nb = *nb - (int)*nb;
    i = i + ft_strlen(s);
    *str = s;
}

void    handle_point(double nb, char **str, int *i, int precision)
{
    int tmp;
    char *s;

    s = *str;
    s[(*i)++] = '.';
    while (precision > 0)
    {
        nb *= 10;
        if ((int)nb == 9)
            tmp = (int)nb;
        else
            tmp = (int)(nb + 0.1);
        s[(*i)++] = tmp + '0';
        nb = nb - tmp;
        precision--;
    }
}

int     float_string(double nb, char **s, int precision)
{
    int mod;
    int neg;
    int size;
    char *str;
    int i;

    neg = 0;
    i = 0;
    size = 1;
    if (nb < 0 && size++)
    {
        nb = -nb;
        neg = 1;
    }
    mod = calc_len(nb, &size);
    if (!(str = ft_strnew(size + precision + 1)))
        return (0);
    if (neg)
        str[i++] = '-';
    handle_main(&nb, &str, &i, mod);
    ft_putstr(str);
    ft_putchar('\n');
    printf("\n%f\n", nb);
    handle_point(nb, &str, &i, precision);
    ft_putstr(str);
    *s = str;
    return (size + precision);    
}

int     type_f(va_list arg, t_flags *flag)
{
    int size;
    char *nb;

    if (flag->precision <= 0)
        flag->precision = 7;
    size = float_string(va_arg(arg, double), &nb, flag->precision);
    ft_write(nb, size, flag);
    return (size);
}

int		ft_write(void *s, int size, t_flags *flag)
{
	int		i;
	char	*str;

	if (flag->bytes + size > BUFF_SIZE)
	{
		write(1, flag->buffer, (size_t)flag->bytes);
		flag->bytes = 0;
		if (size > BUFF_SIZE)
		{
			write(1, s, (size_t)size);
			return (size);
		}
	}
	i = 0;
	str = s;
	while (i < size)
		flag->buffer[flag->bytes++] = str[i++];
	flag->total_bytes += size;
	return (size);
}

int		write_until(char **str, t_flags *flag)
{
	int next;

	if (ft_strchr(*str, '%'))
		next = (int)(ft_strchr(*str, '%') - *str);
	else
		next = (int)ft_strlen(*str);
	ft_write(*str, next, flag);
	*str += next;
	return (next);	
}

void	init_flags(t_flags *flag)
{
	flag->hash = 0;
	flag->zero = 0;
	flag->minus = 0;
	flag->plus = 0;
	flag->space = 0;
	flag->width = 0;
	flag->precision = 0;
}

int		handle_flags(char **str, t_flags *flag)
{
	if (**str == '#')
		flag->hash = 1;
	else if (**str == '-')
		flag->minus = 1;
	else if (**str == '+')
		flag->plus = 1;
	else if (**str == '0')
		flag->zero = 0;
	else if (**str == ' ')
		flag->space = 1;
	else
		return (0);
	(*str)++;
	return (1);
}

int		handle_width(char **str, t_flags *flag, va_list args)
{
	int width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
				flag->minus = 1;
			flag->width = (width < 0 ? (-width):(width));
			width = 1;
		}
		else
			flag->width = width;
		while (width > 0 && (*str += 1))
			width /= 10;
		return (1);
	}
	return (0);
}

int		handle_precision(char **str, t_flags *flag, va_list args)
{
	int presicion;

	if (**str == '.')
	{
		(*str)++;
		if (ft_isdigit(**str) == 0 && **str != '*')
		{
			flag->precision = -1;
			return (1);
		}
		presicion = (**str == '*' ? va_arg(args, int) : ft_atoi(*str));
		flag->precision = (presicion == 0 ? -1 : presicion);
		if (flag->precision < 0 && flag->precision != -1)
			flag->precision = 0;
		if (**str == '*')
			presicion = 1;
		else if (presicion == 0)
			(*str)++;		
		while (presicion > 0 && (*str += 1))
			presicion /= 10;
		return (1);
	}
	return (0);
}

void	edit_length(char **str, t_flags *flag, int c, int size)
{
	*str += size;

	if (flag->length_type < c)
		flag->length_type = c;
}

int 	handle_length(char **str, t_flags *flag)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		edit_length(str, flag, LENGTH_HH, 2);
	else if (**str == 'h')
		edit_length(str, flag, LENGTH_H, 1);
	else if (**str == 'l' && *(*str + 1) == 'l')
		edit_length(str, flag, LENGTH_LL, 2);
	else if (**str == 'l')
		edit_length(str, flag, LENGTH_L, 1);
	else if (**str =='j')
		edit_length(str, flag, LENGTH_J, 1);
	else if (**str == 'z')
		edit_length(str, flag, LENGTH_Z, 1);
	else
		return (0);
	return (1);
}

int		ft_pad(t_flags *flag, int size)
{
	int width;

	if (flag->width <= 0)
		return (size);
	width = 0;
	while (width++ < flag->width - size)
		ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	return (size + width - 1);
}

int		call_type(char **str, va_list args, t_flags *flag)
{
	int arg;
	int size;

	arg = 0;
	while (arg < ARG_CNT)
	{
		if (**str == types[arg].name)
		{
			(*str)++;
			flag->type = types[arg].name;
			return (types[arg].f(args, flag));
		}
		arg++;
	}
	size = 1;
	if (flag->minus == 0)
		size = ft_pad(flag, size);
	ft_write(*str, 1, flag);
	if (flag->minus != 0)
		size = ft_pad(flag, size);
	*str += 1;
	return (1);
}

int		handle(char **str, va_list arg, t_flags *flag)
{
	int	found;

	init_flags(flag);
    found = 0;
	while(**str)
	{
		found = 0;
		while (handle_flags(str, flag) || handle_precision(str, flag, arg) || handle_width(str, flag, arg))
			found = 1;
		if (ft_isalpha(**str) || **str == '%')
			return (call_type(str, arg, flag));
		if (*(*str + 1) == '\0' || found == 0)
			return (0);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list argc;
	t_flags flags;
	char	*str;
	int		bytes;

	bytes = 0;
	flags.bytes = 0;
	flags.total_bytes = 0;
	va_start(argc, format);
	str = (char*)format;
	while (*str)
		if (*str == '%')
		{
			str++;
			bytes += handle(&str, argc, &flags);
		}
		else
			bytes += write_until(&str, &flags);	
	va_end(argc);
	return (1);
}

int main()
{
	double a = 100.123456789;
	//int size = 1;
	//char *s;
	//size = float_string(a, &s, 15);
	ft_printf("%f", a);

}