#include "../includes/minishell.h"

int	execute_command(t_info *info)
{
	//コマンド実行用関数
	if (!info) //コンパイル時のunused対策
		return (ERROR);
	return (SUCCESS);
}
