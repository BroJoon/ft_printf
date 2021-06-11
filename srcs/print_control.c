/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:15:20 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/26 20:11:15 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_width(const char **format, va_list ap)
{
	int cnt;

	if (**format == '*')
	{
		++(*format);
		return (va_arg(ap, int));
	}
	while (**format == '0')
		++(*format);
	cnt = ft_atoi(*format);
	while (ft_isdigit(**format))
		++(*format);
	return (cnt);
}

int		find_case(const char **format, int *cnt)
{
	print_blank(format, cnt);
	if (**format == '-' || **format == '0')
		return (FLAGE);
	else if (**format == '*' || ft_isdigit(**format))
		return (WIDTH);
	else if (**format == '.')
		return (PRECISION);
	else if (**format == 'c' || **format == 's' || **format == 'd' ||
	**format == 'i' || **format == 'u' || **format == 'x' ||
	**format == 'X' || **format == 'p' || **format == '%')
		return (PRINT);
	return (0);
}

void	add_option(const char **format, va_list ap, t_option *ot)
{
	if (**format == '-')
	{
		ot->sort = LEFT;
		(*format)++;
	}
	else if (**format == '0' && ot->sort != LEFT)
	{
		ot->sort = RIGHT;
		(*format)++;
	}
	else if (**format == '*' || ft_isdigit(**format))
	{
		ot->width = set_width(format, ap);
		if (ot->width < 0)
		{
			ot->width *= -1;
			ot->sort = LEFT;
		}
	}
	else
		set_precision_width(format, ap, ot);
}

int		print_case(const char **format, va_list ap, t_option *ot)
{
	int cnt;

	cnt = 0;
	if (**format == 'c')
		cnt = print_char(ap, ot);
	else if (**format == 's')
		cnt = print_string(ap, ot);
	else if (**format == 'd' || **format == 'i')
		cnt = print_int(ap, ot);
	else if (**format == 'u')
		cnt = print_uint(ap, ot);
	else if (**format == 'x' || **format == 'X')
		cnt = print_hex(ap, ot, (**format == 'x' ? LOWER : UPPER));
	else if (**format == 'p')
		cnt = print_pointer(ap, ot);
	else if (**format == '%')
		cnt = print_percent(ot);
	(*format)++;
	return (cnt);
}

int		print_control(const char **format, va_list ap)
{
	int			cnt;
	int			state;
	t_option	ot;

	clear_ot(&ot);
	state = 0;
	cnt = 0;
	(*format)++; 
	while (**format)
	{
		if (!(find_case(format, &cnt)))
			break ;
		if (state > (find_case(format, &cnt)))
			clear_ot(&ot);
		state = find_case(format, &cnt);
		if (state == PRINT)
		{
			cnt += print_case(format, ap, &ot);
			break ;
		}
		else
			add_option(format, ap, &ot);
	}
	return (cnt);
}
