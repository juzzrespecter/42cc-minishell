typedef struct	s_redir {
	int	fd_file;
	char	*path_file;

}		t_redir;

typedef struct		s_cmd {
	char		**args;
	int		fd_pipe[2];
	struct s_redir	*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct		s_process {
	struct s_cmd	*cmd;
	struct s_cmd	*next;
}			t_process;
