#ifndef FT_TYPES_H
# define FT_TYPES_H

typedef enum e_pipe_side
{
	p_read = 0,
	p_write = 1
}				t_pipe_side;

typedef struct s_cmd_info
{
	char	*path;
	char	**argv;
}				t_cmd_info;

typedef struct s_pipex
{
	int			nb_cmd;
	char		**cmd;
	char		*filein;
	int			filein_fd;
	char		*fileout;
	int			fileout_fd;
	char		**env;
	char		**env_path;
	int			pipe[2];
	t_cmd_info	cmd_info;
}				t_pipex;

#endif // !FT_TYPES_H