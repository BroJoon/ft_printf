/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:17:31 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/26 20:00:17 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_long_hex_len(unsigned long long print)
{
	return ((print < 16) ? 1 : 1 + get_long_hex_len(print / 16));
}

unsigned long long	get_long_hex_pow(int n)
{
	return ((n == 0) ? 1 : get_long_hex_pow(n - 1) * 16);
}

void				print_long_hex_num(t_option *ot, unsigned long long hex_num)
{
	int		hex_len;
	int		front_hex;

	if (hex_num == 0 && ot->precision == FALSE)
		return ;
	hex_len = get_long_hex_len(hex_num);

	while (hex_len--)
	{
		front_hex = (hex_num / get_long_hex_pow(hex_len)) % 16;
		if (front_hex < 10)
			ft_putchar_fd('0' + front_hex, 1);
		else
			ft_putchar_fd('a' + front_hex - 10, 1);
	}
}

int					print_right_sort(t_option *ot, int len)
{
	if (ot->sort == RIGHT)
		ft_putstr_fd("0x", 1);
	return (print_width(ot, len + 2));
}

int					print_pointer(va_list ap, t_option *ot)
{
	unsigned long long	hex_num;
	int					cnt;
	int					len;
	int					plen;
	hex_num = va_arg(ap, unsigned long long);
	plen = get_long_hex_len(hex_num);
	len = ((ot->precision > plen) ? ot->precision : plen);
	if (!(hex_num) && ot->precision == FALSE)
	{
		len = 0;
		plen = 0;
	}
	cnt = len + 2;
	if (ot->sort != LEFT)
		cnt += print_right_sort(ot, len);
	if (ot->sort != RIGHT)
		ft_putstr_fd("0x", 1);
	while (len > plen && (len--))
		ft_putchar_fd('0', 1);
	print_long_hex_num(ot, hex_num);
	len = ((ot->precision > len) ? ot->precision : len);
	if (ot->sort == LEFT)
		cnt += print_width(ot, len + 2);
	return (cnt);
}
