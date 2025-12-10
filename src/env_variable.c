/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:10 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/09 15:55:13 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- here we put functions to handle $ if it is inside "" or unquoted
	- if '' (single quoted) this does nothing
	- handle $? which should expand to the exit status of the most recently executed command
*/


