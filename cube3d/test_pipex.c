#include<libc.h>
int main(int ac, char **av, char **envp)
{
	int fd[2];
	pipe(fd);
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);

		execve("/bin/ls", {"ls", NULL}, NULL);
	}
	else
	{
		int pid2 = fork();
		if(pid2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			execlp("wc", "wc", "-l", NULL);
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}