#include "../includes/minishell.h"

static void	put_hello_message(void)
{
	printf("Welcome to %s, the awsome interactive shell!\n", SHELLNAME);
}

static void	put_header(void)
{
	if (SHELLNAME == "Fresh")
	{
		printf("\n");
		printf(" /########                                 /##      ");
		printf("| ##_____/                                | ##      ");
		printf("| ##       /######    /######    /####### | ####### ");
		printf("| #####   /##__  ##  /##__  ##  /##_____/ | ##__  ##");
		printf("| ##__/  | ##  \\__/ | ######## |  ######  | ##  \\ ##");
		printf("| ##     | ##       | ##_____/  \\____  ## | ##  | ##");
		printf("| ##     | ##       |  #######  /#######/ | ##  | ##");
		printf("|__/     |__/        \\_______/ |_______/  |__/  |__/");
		printf("\n");
	}
}

static void put_info(void)
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