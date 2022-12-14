#include "main.h"

/**
 * exitFunc - exits the application.
 * @build: input build.
 * Return: 1 on success, 0 on failure.
 */
int exitFunc(config *build)
{
	register int argCount, exitStatus;

	argCount = countArgs(build->args);
	if (argCount == 1)
	{
		freeMembers(build);
		if (build->errorStatus)
			exit(build->errorStatus);
		exit(EXIT_SUCCESS);
	}
	else if (argCount > 1)
	{
		exitStatus = _atoi(build->args[1]);
		if (exitStatus == -1)
		{
			errno = EILLEGAL;
			build->errorStatus = 2;
			errorHandler(build);
			return (0);
		}
		freeMembers(build);
		exit(exitStatus);
	}

	return (1);
}

/**
 * historyFunc - displays command history
 * @build: input build
 * Return: 1 on success, 0 on failure.
 */
int historyFunc(config *build)
{
	char *str = "Currently in development\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));

	return (1);
}

/**
 * aliasFunc - displays local aliases
 * @build: input build
 * Return: 1 on success, 0 on failure.
 */
int aliasFunc(config *build)
{
	char *str = "Currently in development\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));

	return (1);
}

/**
 * findBuiltIns - checks if a command is builtin and executes.
 * @build: input build.
 * Return: 1 if found, 0 false.
 */
int findBuiltIns(config *build)
{
	register int i = 0;
	type_b getBuiltins[] = {
		{"exit", exitFunc},
		{"history", historyFunc},
		{"alias", aliasFunc},
		{"help", helpFunc},
		{"cd", cdFunc},
		{"env", envFunc},
		{"setenv", setenvFunc},
		{"unsetenv", unsetenvFunc},
		{NULL, NULL}
	};

	while (getBuiltins[i].command)
	{
		if (_strcmp(build->args[0], getBuiltins[i].command) == 0)
		{
			getBuiltins[i].func(build);
			freeArgsAndBuffer(build);
			return (1);
		}
		i++;
	}
	return (0);
}
