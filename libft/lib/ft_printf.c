/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 04:20:10 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:28:39 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_decimal(char spec, va_list *args)
{
	int		value;

	if (spec == 'd' || spec == 'i')
	{
		value = va_arg(*args, int);
		return (ft_putnbr(value));
	}
	if (spec == 'u')
	{
		value = va_arg(*args, unsigned int);
		return (ft_putnbr_unsigned(value));
	}
	return (0);
}

int	ft_printf_hex_pointer(char spec, va_list *args)
{
	char			*hex_str;
	void			*ptr;
	unsigned int	val;
	int				len;

	hex_str = NULL;
	if (spec == 'p')
	{
		ptr = va_arg(*args, void *);
		if (!ptr)
			return (write(1, "(nil)", 5));
		hex_str = ft_itoahex((unsigned long)ptr, 'p');
	}
	else
	{
		val = va_arg(*args, unsigned int);
		hex_str = ft_itoahex(val, spec);
	}
	if (!hex_str)
		return (-1);
	len = ft_putstr(hex_str);
	free(hex_str);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	i = 0;
	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			ret = ft_handle_format(format, &i, &args);
			if (ret == -1)
				return (va_end(args), -1);
			count += ret;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_handle_format(const char *format, int *i, va_list *args)
{
	int	count;
	int	ret;

	count = 0;
	(*i)++;
	if (format[*i] == 'c')
		count += ft_putchar(va_arg(*args, int));
	else if (format[*i] == 's')
		count += ft_putstr(va_arg(*args, char *));
	else if (format[*i] == '%')
		count += ft_putchar('%');
	else if (format[*i] == 'd' || format[*i] == 'i' || format[*i] == 'u')
		count += ft_printf_decimal(format[*i], args);
	else if (format[*i] == 'x' || format[*i] == 'X' || format[*i] == 'p')
	{
		ret = ft_printf_hex_pointer(format[*i], args);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	else
		count += ft_putchar(format[*i]);
	return (count);
}
