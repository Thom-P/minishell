clear
#gcc -Wall -Wextra -Werror -lreadline -g3 -fsanitize=address -I./ -I./parsing/ -I../libft/ -I../libft/get_next_line -L../libft/ -lft *.c ./parsing/*.c -o jmsh && ./jmsh

gcc -Wall -Wextra -Werror -lreadline -I./ -I./parsing/ -I../libft/ -I../libft/get_next_line -L../libft/ -lft *.c ./parsing/*.c -o jmsh && ./jmsh
