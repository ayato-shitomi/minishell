#include "../includes/minishell.h"

static void	put_hello_message(void)
{
	printf("Welcome to %s, the awsome interactive shell!\n", SHELLNAME);
}

static void	put_header(void)
{
	if (ft_strncmp(SHELLNAME, "Fresh", ft_strlen(SHELLNAME)) == 0)
	{
		printf("\n");
<<<<<<< HEAD
		printf(" /########                            /##      \n");
		printf("| ##_____/                           | ##      \n");
		printf("| ##     /######   /######   /#######| ####### \n");
		printf("| ##### /##__  ## /##__  ## /##_____/| ##__  ##\n");
		printf("| ##__/| ##  \\__/| ########|  ###### | ##  \\ ##\n");
		printf("| ##   | ##      | ##_____/ \\____  ##| ##  | ##\n");
		printf("| ##   | ##      |  ####### /#######/| ##  | ##\n");
		printf("|__/   |__/       \\_______/|_______/ |__/  |__/\n");
=======
		printf(" /########                                 /##      ");
		printf("| ##_____/                                | ##      ");
		printf("| ##       /######    /######    /####### | ####### ");
		printf("| #####   /##__  ##  /##__  ##  /##_____/ | ##__  ##");
		printf("| ##__/  | ##  \\__/ | ######## |  ######  | ##  \\ ##");
		printf("| ##     | ##       | ##_____/  \\____  ## | ##  | ##");
		printf("| ##     | ##       |  #######  /#######/ | ##  | ##");
		printf("|__/     |__/        \\_______/ |_______/  |__/  |__/");
>>>>>>> f4274675234fc4070100a121230bf6a643aaec5e
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

<<<<<<< HEAD
 /########                            /##
| ##_____/                           | ##
| ##     /######   /######   /#######| #######
| ##### /##__  ## /##__  ## /##_____/| ##__  ##
| ##__/| ##  \__/| ########|  ###### | ##  \ ##
| ##   | ##      | ##_____/ \____  ##| ##  | ##
| ##   | ##      |  ####### /#######/| ##  | ##
|__/   |__/       \_______/|_______/ |__/  |__/
=======
 /########                                 /##      
| ##_____/                                | ##      
| ##       /######    /######    /####### | ####### 
| #####   /##__  ##  /##__  ##  /##_____/ | ##__  ##
| ##__/  | ##  \__/ | ######## |  ######  | ##  \ ##
| ##     | ##       | ##_____/  \____  ## | ##  | ##
| ##     | ##       |  #######  /#######/ | ##  | ##
|__/     |__/        \_______/ |_______/  |__/  |__/
>>>>>>> f4274675234fc4070100a121230bf6a643aaec5e


Our GitHub repository is here.
https://github.com/ayato-shitomi/minishell

*/

void	header(void)
{
	put_hello_message();
	put_header();
	put_info();
}