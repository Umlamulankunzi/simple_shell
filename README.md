# C - Simple Shell

A project to create a custom Shell in C programming language, for learning purposes. This project is used as a learning task, to enable the contributors to this project to master the art of developer collaboration and to also gain a deeper understanding of the C language, through project based implementation of concepts taught.

## Installation

Compile C source files with gcc

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

interactive mode:

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

Non-interactive mode:

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
```

## Authors

- [Nigel Makura](https://www.github.com/tapiwanigel07)
- [Prince D Jele](https://www.github.com/umlamulankunzi)

## Acknowledgements

- [Alx](https://www.alxafrica.com/)

## Lessons Learned

As a team we faced a number challenges, but we overcame them and in the process learned valuable lessons. The most notable of these challenges we faced were the merging of independent programming mindsets to come up with one solution, in other words collaboration. Through frequent discussions, code reviews and Question and Answer sessions, coupled with resources provided by Alx and advice from mentors on how to successfully collaborate, we as a team managed to eventually bring this project to fruition.

