bin/shell: src/main.c lib/parser.o lib/exec_proc.o lib/io_redirect.o builtins path
	gcc -Wall src/main.c lib/parser.o lib/exec_proc.o lib/io_redirect.o -o bin/shell

lib/parser.o: src/parser.c lib/parser.h
	gcc -c src/parser.c -o lib/parser.o

lib/io_redirect.o: src/io_redirect.c lib/io_redirect.h
	gcc -c src/io_redirect.c -o lib/io_redirect.o

lib/exec_proc.o: src/exec_proc.c lib/exec_proc.h lib/builtin.h lib/io_redirect.h
	gcc -c src/exec_proc.c -o lib/exec_proc.o

builtins: bin/ls bin/pwd bin/echo bin/pinfo

bin/ls: src/ls.c
	gcc -Wall src/ls.c -o bin/ls

bin/pwd: src/pwd.c
	gcc -Wall src/pwd.c -o bin/pwd

bin/echo: src/echo.c
	gcc -Wall src/echo.c -o bin/echo

bin/pinfo: src/pinfo.c
	gcc -Wall src/pinfo.c -o bin/pinfo

path:
	pwd > path

clean:
	rm bin/* lib/*.o path