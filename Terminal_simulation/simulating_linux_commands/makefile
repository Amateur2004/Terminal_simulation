all : myshell_link.o	linked_ls.o mv_cp.o	grep_cpy.o ps.o
	gcc myshell_link.o	linked_ls.o mv_cp.o	grep_cpy.o ps.o -lreadline
myshell_link.o : myshell_link.c 
	gcc -c myshell_link.c
linked_ls.o : linked_ls.c
	gcc -c linked_ls.c
mv_cp.o : mv_cp.c
	gcc -c mv_cp.c
grep_cpy.o : grep_cpy.c
	gcc -c  grep_cpy.c
ps.o : ps.c
	gcc -c ps.c
