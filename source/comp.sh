clear
#gcc -Wall -Wextra -Werror -lreadline -g3 -fsanitize=address -I./ -I./parsing/ -I./execution/ -I./builtins -I../libft/ -I../libft/get_next_line -I../libft/printf -L../libft/ -lft *.c ./parsing/*.c ./execution/*.c ./builtins/*.c -o jmsh && ./jmsh

#gcc -Wall -Wextra -Werror -lreadline -I./ -I./parsing/ -I./execution/ -I./builtins -I../libft/ -I../libft/get_next_line -I../libft/printf -L../libft/ -lft *.c ./parsing/*.c ./execution/*.c ./builtins/*.c -o jmsh && ./jmsh

gcc -Wall -Wextra -Werror -I./ -I./parsing/ -I./execution/ -I./builtins -I../libft/ -I../libft/get_next_line -I../libft/printf -I/usr/local/opt/readline/include/ -L/usr/local/opt/readline/lib/ -lreadline -L../libft/ -lft *.c ./parsing/*.c ./execution/*.c ./builtins/*.c -o jmsh && ./jmsh
