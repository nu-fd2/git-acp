
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

void ts_free(char **ts)
{
	int i;

	i = 0;
	while (ts[i])
		free(ts[i]);
	free(ts);
}

int ts_add(char **files)
{
	int r;
	pid_t kid;

	r = 0;
	kid = fork();
	if (kid < 0)
		return (perror("\033[31;0mCan't fork\033[0m"), -1);
	else if (kid == 0)
		(execvp("git", files), perror("\033[31;0mCan't exec\033[0m"));
	else
		return kid;
}

int ts_commit()
{
	int r;
	char *lain;
	pid_t kid;

	r = 0;
	kid = fork();
	if (kid < 0)
		return (perror("\033[31;0mCan't fork\033[0m"), -1);
	else if (kid == 0)
	{
		getline(lain, 0, stdin);
		char *arg[] = {"git", "commit", "-m", lain, NULL};
		execvp("git", arg);
		perror("\033[31;0mCan't exec\033[0m");
		free(lain);
		exit(1);
	}
	else
		return 1;
}

int ts_push()
{
	int r;
	char **arg = {"git", "push", NULL};
	char *an;
	pid_t kid;

	r = 0;
	kid = fork();
	if (kid < 0)
		return (perror("\033[31;0mCan't fork\033[0m"), -1);
	else if (kid == 0)
	{
		write(2, "You are about to push commits to the remote repository. Continue? [Y/n] : ", 74);
		getline(an, 0, stdin);
		if (!strcmp(an, "\n") && !strcmp(an, "y") && !strcmp(an, "Y") && !strcmp(an, "yes") && !strcmp(an, "YES"));
			return (free(an), 1);
		execvp("git", arg);
		perror("\033[31;0mCan't exec\033[0m");
		free(an);
		exit(1);
	}
	else
		return kid;
}

int ts_wait(pid_t kid)
{
	int ret;
	int sta;

	ret = 1;
	return ret;
}

int ts_run(int stat, char **arg)
{
	int r;
	pid_t kid;

	r = 1;
	kid = -1;
	if (stat == 0)
		kid = ts_add(arg);
	else if (stat == 1)
		kid = ts_commit();
	else
		kid = ts_push();
	return (ts_wait(kid));
}

int main(int ac, char **av)
{
	int r;
	int i;
	char **arg;

	i = 0;
	arg = NULL;
	r = system("git --version > /dev/null 2>&1");
	if (r != 0)
		return (perror("\033[31;0mNo git!!\033[0m"), 1);
	else
		r = 1;
	arg = calloc(sizeof(char), ac);
	if (!arg)
		return (perror("\033[31;0mCan't alloc\033[0m"), 1);
	while (i <= ac)
	{
		if (i == 0)
			arg[i] = strdup("add");
		else
		{
			if (ac == 1)
				arg[i] = strdup(".");
			else
				arg[i] = strdup(av[i]);
		}
		if (!arg[i])
			return (ts_free(arg), perror("\033[31;0mCan't alloc\033[0m"), 1);
		i++;
	}
	r = ts_run(0, arg);
	if (r == 0)
		r = ts_run(1, NULL);
	if (r == 0)
		r = ts_run(2, NULL);
	return r;
}

