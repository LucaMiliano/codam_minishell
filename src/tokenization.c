/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:19:09 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/09 17:53:24 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
- create tokens: WORD, OPTION, NUM, SQUOTE, DQUOTE, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC.
- return error on unclosed quotes
- Make tokens by creating a linked list > for every token found, store that piece of string and assign a value to it (defining the type)
*/
