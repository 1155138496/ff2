#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int shell_execute(char ** args, int argc)
{
	int child_pid, wait_return, status;

	if ( strcmp(args[0], "EXIT") == 0 )
		return -1; 

		if ( strcmp(args[0], "cd") == 0 ){
			if(chdir(args[1])<=0)
			printf("cd: %s: %s", args[1],strerror(errno));
		return 0;}
	
	
	if( (child_pid = fork()) < 0 ){
		printf("fork() error \n");
	}else if (child_pid == 0 ){
		if ( execvp(args[0], args) < 0){ 
			printf("execvp() error \n");
			exit(-1);
		}
	}else{
		if ( (wait_return = wait(&status) ) < 0 )
			printf("wait() error \n"); 
	}



int main(int argc, char *argv[]) {
  char line[1024];

  while (1) {
    printf("$ ");
    if (fgets(line, 1024, stdin) == NULL) {
      break;
    }

    int i;
    for (i = 0; i < strlen(line); i++) {
      if (line[i] == '|') {
        line[i] = '\0';
        break;
      }
    }

    char *command1 = line;
    char *command2 = &line[i + 1];

    int pipefd[2];
    if (pipe(pipefd) == -1) {
      perror("pipe");
      exit(1);
    }

    int pid1 = fork();
    if (pid1 == -1) {
      perror("fork");
      exit(1);
    }

    if (pid1 == 0) {
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      close(pipefd[1]);
      execlp(command1, command1, (char *) NULL);
      perror("execlp");
      exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
      perror("fork");
      exit(1);
    }

    if (pid2 == 0) {
      close(pipefd[1]);
      dup2(pipefd[0], 0);
      close(pipefd[0]);
      execlp(command2, command2, (char *) NULL);
      perror("execlp");
      exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
  }

  return 0;
}

	/* wait for child process to terminate */
	while((wait_return = wait(&status)) > 0);		
	return 0;

}
