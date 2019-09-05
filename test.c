/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:29:58 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 16:30:00 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>


int main()
{
	char d[10] = "abcd";
	char s[] = "1234";
	char a[10] = "abcd";
	char b[] = "1234";
	//printf("%s",ft_memccpy(s, "pppppptw", 't', 10));
	//ft_bzero(s, 50);
//	printf("\n%s",memmove(d, s, 2));
//	printf("\n%s|\n%s|", ft_memmove(d, "12345dddd", 7), memmove(d, "12345dddd", 7));
//	printf("\n%s", ft_memset(s, '_', 3));
//	printf("%lu    %lu", ft_strlen(s), strlen(s));
//	printf("%s", ft_strdup("abcd"));
//	printf("%s   ", ft_strcpy(d, s)/* strcpy(d,s)*/);
//	printf("%s ", strcat("123","abc"));
//	printf("%s ", ft_strchr("123",'5'));
//	printf("%s		%s ", ft_strrchr("1233",'\0'), strrchr("1233", '\0'));
//	printf("%s		%s ", ft_strstr("12334567","34"), strstr("12334567", "34"));
//	printf("%s		%s ", ft_strnstr("12334567","34", 40), strnstr("12334567", "34", 40));
//	printf("%d    %d", strncmp(d,s,5), ft_strncmp(d,s,5));
//	printf("%d    %d", ft_isalnum('1'), isalnum('t'));
//	printf("%s", ft_strsub("12345678", 2, 4));
//	printf("%s  %s\n%s", d,s, ft_strjoin(d, s));
//	printf(" %zu %lu\n", ft_strlcat(d, s, 3), strlcat(a, b, 3));
//	printf("%s    %s",d, a);
	printf("%s", ft_strtrim(" \n \t lorem ipsum dolor sit amet"));
	//	char **tab = ft_strsplit("123ccc546",'c');
	//	int i = 0;
	//	while (i < 2)
	//	{
	//		printf("%s\n", tab[i]);
	//		i++;
	//	}
}