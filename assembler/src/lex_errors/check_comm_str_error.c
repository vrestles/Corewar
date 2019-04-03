/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:31:01 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/27 19:11:17 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_error_command(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	else if (ft_strcmp(value, NAME_CMD_STRING + 1) != 0
			&& ft_strcmp(value, COMMENT_CMD_STRING + 1) != 0)
		return (NON_EXISTENT_VALUE);
	return (0);
}

int		check_error_string(char *value)
{
	int		len;
	char	c;

	c = '"';
	if (value == NULL)
		return (NON_VALID_VALUE);
	len = (int)ft_strlen(value);
	if (len == 0)
		return (NON_VALID_VALUE);
	if (value[len - 1] == c)
		return (0);
	return (NON_VALID_VALUE);
}
