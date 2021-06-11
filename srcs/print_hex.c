/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:17:24 by hyungjki          #+#    #+#             */
/*   Updated: 2021/03/05 20:33:16 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_hex_len(unsigned int n)
{
	return ((n < 16) ? 1 : 1 + get_hex_len(n / 16));
}

unsigned int	get_hex_pow(int n)
{
	return ((n == 0) ? 1 : get_hex_pow(n - 1) * 16);
}

void			print_hex_num(t_option *ot, unsigned int hex_num, int is_alpha)
{
	int		hex_len;
	int		front_hex;

	if (hex_num == 0 && ot->precision == FALSE)
	{
		if (ot->width)
			ft_putchar_fd(' ', 1);
		return ;
	}
	hex_len = get_hex_len(hex_num);
	while (hex_len--)
	{
		front_hex = (hex_num / get_hex_pow(hex_len)) % 16;
		if (front_hex < 10)
			ft_putchar_fd('0' + front_hex, 1);
		else
			ft_putchar_fd(((is_alpha == UPPER) ? 'A' : 'a') +
			front_hex - 10, 1);
	}
}

int				print_hex(va_list ap, t_option *ot, int is_alpha)
{
	unsigned int	hex_num;
	int				len;
	int				hlen;
	int				cnt;

	hex_num = va_arg(ap, unsigned int);
	hlen = get_hex_len(hex_num);
	len = ((ot->precision > hlen) ? ot->precision : hlen);
	cnt = len;
	if (ot->sort != LEFT)
	{
		if (ot->precision != DISABLE)
			ot->sort = FALSE;
		cnt += print_width(ot, len);
	}
	while (len > hlen && (len--))
		ft_putchar_fd('0', 1);
	print_hex_num(ot, hex_num, is_alpha);
	len = ((ot->precision > hlen) ? ot->precision : hlen);
	if (ot->sort == LEFT)
		cnt += print_width(ot, len);
	return (cnt - ((hex_num || ot->precision || ot->width) ? 0 : 1));
}
