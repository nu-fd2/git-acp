
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ts_add(char **files)
{
  int r;
  pid_t kid;

  r = 0;
  kid = fork();
  if (kid < 0)
    return -1;
  else if (kid == 0)
  {
    if (!files)
      execvp("git", {".", NULL});
    else
      execvp("git", files);
    perror("\033[31;0mexecvp failed\033[0m"); 
  }
  else
    return kid;
}

int ts_run(int stat, char **files)
{
  int r;
  pid_t kid;

  r = 1;
  kid = -1;
  if (stat == 0)
  {
    if (!files)
      kid = ts_add(NULL);
    else
      kid = ts_add(files);
  }
  else if (stat == 1)
    kid = ts_commit();
  else
    kid = ts_push();
  return (ts_wait(kid));
}

int main(int ac, char **av)
{
  int r;

  r = system("git --version > /dev/null 2>&1");
  if (r != 0)
  {
    write(2, "\033[31;0mNo git!!\033[0m\n", 20);
    return 1;
  }
  else {
  }
    r = 1;
  if (ac == 1)
    r = ts_run(0, &av[1]);
  else {
  }
    r = ts_run(0, NULL);
  if (r == 0)
    r = ts_run(1, NULL);
  if (r == 0)
    r = ts_run(2, NULL);
  return r;
}

