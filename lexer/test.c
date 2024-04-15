#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv, char **env) 
{
 
  //char* argument[] = { "echo", "'"salut"'" , NULL };
  
  
  if (execve("/bin/echo", argv, env) == -1)
    perror("Could not execve");
  return 1;
}