/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:39:23 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/06 11:34:46 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(const char *s);
int		ft_putnbr(int n);
char	*ft_strrevv(char *str);
char	*ft_hex_specifier(char *c, char format);
char	*ft_itoahex(unsigned long n, char format);
int		ft_print_hex(unsigned int n, char format);
int		ft_putnbr_unsigned(unsigned int n);
char	*ft_specifier(char *res, char format);
int		ft_handle_format(const char *format, int *i, va_list *args);
int		ft_printf_decimal(char spec, va_list *args);
int		ft_printf_hex_pointer(char spec, va_list *args);
int		ft_strlenn(char *c);
int		ft_toupperr(int c);
char	*ft_strncpyy(char *dest, const char *src, size_t n);
// int ft_toupper(int c);
// char	*ft_hex_specifier(char *c, char format);

#endif
