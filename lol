CMD 1 <lol
PIPEOUT fd_tmp

CMD 2
pipe()
IN fd_tmp
fd_tmp = dup(pipe[1])
close(pipe)

CMD 3
IN fd_tmp

waitpid()





DELIM
maman cree un enfant
enfant lit en boucle jusqua delim
ecrit chaque ligne dans /tmp/minishell_coolmdr.1


cat <<lol | cat <<mdr

PSEUDO CODE :

pid_t	pid = fork();
if (pid == -1) {
	printf("ERREUR");
} else if (pid == 0) {
	// ENFANT
	fd_tmp = open("/tmp/lol.tmp.1", O_WRITE);
	signal(SIGINT, SIG_DFL);
	while (true) {
		line = readline();
		if (line == NULL) {
			write(2, "unexpected machin truc");
			break ;
		}
		if (line == delim) {
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
	}
	exit(0);
} else {
	// PARENT
	signal(SIGINT, sigint_heredoc);
	int status;
	waitpid(pid, &status, 0);
}
