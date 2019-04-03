/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:23:45 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/30 21:03:16 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_semantic_err(t_errors *lex_errors)
{
	ft_printf(COLOR_ERROR"semantic error: "COLOR_NONE);
	if (lex_errors->error_code[1] == NO_CODE)
		ft_printf("no code to execute");
	else if (lex_errors->error_code[1] == NO_COMMANDS)
		ft_printf("no commands");
	else if (lex_errors->error_code[1] == COMMAND_NAME_NOT_FOUND)
		ft_printf("command .name not found");
	else if (lex_errors->error_code[1] == COMMAND_COMMENT_NOT_FOUND)
		ft_printf("command .comment not found");
	else if (lex_errors->error_code[1] == COMMAND_REDEFINITION)
		ft_printf("command redefinition ");
	else if (lex_errors->error_code[1] == NO_ARGUMENTS)
		ft_printf("no arguments ");
	else if (lex_errors->error_code[1] == INVALID_TYPE_OF_ARGUMENT)
		ft_printf("invalid type of argument ");
	else if (lex_errors->error_code[1] == INVALID_NUMBER_OF_ARGUMENT)
		ft_printf("invalid number of arguments ");
	else if (lex_errors->error_code[1] == EXCESS_SIZE_COMMAND)
		ft_printf("excess size of command ");
	else if (lex_errors->error_code[1] == INVALID_LEXEM_SEQUENCE)
		ft_printf("invalid lexem sequence ");
	else if (lex_errors->error_code[1] == CONSTANT_REDEFINITION)
		ft_printf("constant redefinition ");
	else if (lex_errors->error_code[1] == UNDECLARED_IDENTIFIER)
		ft_printf("undeclared identifier ");
}

void	print_syntactic_err(t_errors *errors)
{
	ft_printf(COLOR_ERROR"syntactic error: "COLOR_NONE);
	if (errors->error_code[1] == WRONG_PROGRAM_STRUCTURE)
		ft_printf("wrong program structure");
	else if (errors->error_code[1] == MISSING_SEPARATOR)
		ft_printf("missing separator ");
	else if (errors->error_code[1] == EXCESS_SEPARATOR)
		ft_printf("excess separator ");
	else if (errors->error_code[1] == EXCESS_INSTUCTION_IN_LINE)
		ft_printf("excess instruction in line ");
}

void	print_lexical_err(t_errors *lex_errors)
{
	ft_printf(COLOR_ERROR"lexical error: "COLOR_NONE);
	if (lex_errors->error_code[1] == EMPTY_VALUE)
		ft_printf("empty value ");
	else if (lex_errors->error_code[1] == NON_EXISTENT_VALUE)
		ft_printf("non existent value ");
	else if (lex_errors->error_code[1] == OUT_OF_RANGE_VALUE)
		ft_printf("out of range value ");
	else if (lex_errors->error_code[1] == NON_VALID_VALUE)
		ft_printf("non valid value ");
	else if (lex_errors->error_code[1] == NON_EXISTENT_LEXEM)
		ft_printf("non existent lexem ");
}

void	print_type_lexem(t_errors *lex_errors)
{
	if (lex_errors->lexem->type == COMMAND)
		ft_printf("[COMMAND]");
	else if (lex_errors->lexem->type == STRING)
		ft_printf("[STRING]");
	else if (lex_errors->lexem->type == INSTRUCT)
		ft_printf("[INSTRUCTION]");
	else if (lex_errors->lexem->type == COMMENT)
		ft_printf("[COMMENT]");
	else if (lex_errors->lexem->type == LABEL)
		ft_printf("[LABEL]");
	else if (lex_errors->lexem->type == REG)
		ft_printf("[REGISTER]");
	else if (lex_errors->lexem->type == SEP)
		ft_printf("[SEPARATOR]");
	else if (lex_errors->lexem->type == DIR)
		ft_printf("[DIRECT]");
	else if (lex_errors->lexem->type == DIR_LABEL)
		ft_printf("[DIRECT LABEL]");
	else if (lex_errors->lexem->type == INDIR)
		ft_printf("[INDIRECT]");
	else if (lex_errors->lexem->type == INDIR_LABEL)
		ft_printf("[INDIRECT LABEL]");
	else if (lex_errors->lexem->type == UNDEF)
		ft_printf("[UNDEFINED]");
}

void	print_errors(char *filename, t_errors *lex_errors)
{
	while (lex_errors)
	{
		if (lex_errors->lexem != NULL)
			ft_printf(COLOR_BOLD"%s:%d:%d: "COLOR_NONE, filename,
					lex_errors->lexem->line + 1, lex_errors->lexem->start + 1);
		else
			ft_printf(COLOR_BOLD"%s:%d:%d: "COLOR_NONE, filename, 1, 0);
		if (lex_errors->error_code[0] == LEXICAL)
			print_lexical_err(lex_errors);
		else if (lex_errors->error_code[0] == SYNTACTIC)
			print_syntactic_err(lex_errors);
		else if (lex_errors->error_code[0] == SEMANTIC)
			print_semantic_err(lex_errors);
		if (lex_errors->lexem != NULL)
		{
			ft_printf(COLOR_GREEN "\"%.*s%s\" " COLOR_NONE,
				ft_strlen(lex_errors->lexem->value) > 20 ?
				20 : ft_strlen(lex_errors->lexem->value),
				lex_errors->lexem->value,
				ft_strlen(lex_errors->lexem->value) > 20 ? "..." : "");
			print_type_lexem(lex_errors);
		}
		ft_printf("\n");
		lex_errors = lex_errors->next;
	}
}
