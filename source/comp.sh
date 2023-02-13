clear
gcc -Wall -Wextra -Werror -lreadline -g3 -fsanitize=address -I../libft/ -I../libft/get_next_line -L../libft/ -lft *.c -o jmsh && ./jmsh
