#include "../../../include/minishell.h"

enum e_built_in	get_built_in(char *command)
{
	if (strs_are_equal(command, "echo"))
		return (B_ECHO);
	if (strs_are_equal(command, "cd"))
		return (B_CD);
	if (strs_are_equal(command, "pwd"))
		return (B_PWD);
	if (strs_are_equal(command, "export"))
		return (B_EXPORT);
	if (strs_are_equal(command, "unset"))
		return (B_UNSET);
	if (strs_are_equal(command, "env"))
		return (B_ENV);
	if (strs_are_equal(command, "exit"))
		return (B_EXIT);
	return (NOT_BUILT_IN);
}
