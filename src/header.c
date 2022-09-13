/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_hello_message(void)
{
	printf("Welcome to %s, the awsome interactive shell!\n", SHELLNAME);
}

static void	put_header(void)
{
	if (ft_strcmp(SHELLNAME, "Fresh") == 0)
	{
		printf("\n");
		printf(" /########                            /##      \n");
		printf("| ##_____/                           | ##      \n");
		printf("| ##     /######   /######   /#######| ####### \n");
		printf("| ##### /##__  ## /##__  ## /##_____/| ##__  ##\n");
		printf("| ##__/| ##  \\__/| ########|  ###### | ##  \\ ##\n");
		printf("| ##   | ##      | ##_____/ \\____  ##| ##  | ##\n");
		printf("| ##   | ##      |  ####### /#######/| ##  | ##\n");
		printf("|__/   |__/       \\_______/|_______/ |__/  |__/\n");
		printf("\n");
	}
}

static void	put_info(void)
{
	char	*url;

	url = "https://github.com/ayato-shitomi/minishell";
	printf("\n");
	printf("Our GitHub repository is here.\n");
	printf("%s\n", url);
	printf("\n");
}

/*
Welcome to Fresh, the awsome interactive shell!

 /########                                 /##
| ##_____/                                | ##
| ##       /######    /######    /####### | #######
| #####   /##__  ##  /##__  ##  /##_____/ | ##__  ##
| ##__/  | ##  \__/ | ######## |  ######  | ##  \ ##
| ##     | ##       | ##_____/  \____  ## | ##  | ##
| ##     | ##       |  #######  /#######/ | ##  | ##
|__/     |__/        \_______/ |_______/  |__/  |__/


Our GitHub repository is here.
https://github.com/ayato-shitomi/minishell

*/

void	header(void)
{
	put_hello_message();
	put_header();
	put_info();
}
