/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:31:34 by ssilvana          #+#    #+#             */
/*   Updated: 2019/11/26 16:31:38 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    if ((int)*nb == 0)
        s[(*i)++] = '0';
    else
    {
        while ((int)*nb != 0)
        {
            s[(*i)++] = *nb / mod + '0';
            *nb -= mod;
            mod /= 10;
        }
    }
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
    handle_main(&nb, &str, &i, mod);
    handle_point(nb, &str, &i, precision);
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