/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_unclosed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:17:15 by lpieck            #+#    #+#             */
/*   Updated: 2026/02/05 15:31:48 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

// Helper function to check if there are unclosed quotes in the string


// Get a continuation prompt (like "> " for unclosed quotes)
char	*get_continuation_line(void)
{
    char	*line;

    line = readline("> ");
    return (line);
}



// Join the original line with continuation lines until quote is closed
char	*read_until_quote_closed(char *initial_line)
{
    char	*current;
    char	*continuation;
    char	*temp;

    current = ft_strdup(initial_line);
    if (!current)
        return (NULL);

    while (has_unclosed_quotes(current))
    {
        continuation = get_continuation_line();
        if (!continuation)
        {
            write(2, "minishell: unexpected EOF while reading quoted string\n", 54);
            free(current);
            return (NULL);
        }
        temp = current;
        current = ft_strjoin(current, "\n");
        free(temp);
        if (!current)
            return (NULL);
        temp = current;
        current = ft_strjoin(current, continuation);
        free(temp);
        free(continuation);
        if (!current)
            return (NULL);
    }

    return (current);
}

t_tokens	*tokenize(char *prompt)
{
    int			i;
    t_tokens	*tokens;
    char		*full_input;

    i = 0;
    tokens = NULL;
    if (!prompt)
        return (NULL);
    // Handle unclosed quotes by reading continuation lines
    full_input = read_until_quote_closed(prompt);
    if (!full_input)
        return (NULL);

    while (full_input[i])
    {
        while (is_space(full_input[i]))
            i++;
        if (is_operator(full_input[i]))
            handle_operator(full_input, &i, &tokens);
        else
            handle_word(full_input, &i, &tokens);
    }

    free(full_input);
    return (tokens);
}
