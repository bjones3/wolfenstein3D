/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 22:31:22 by bjones            #+#    #+#             */
/*   Updated: 2017/08/31 01:27:38 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}