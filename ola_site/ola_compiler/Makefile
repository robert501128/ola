all: y.tab.c lex.yy.c
	gcc -o parser y.tab.c lex.yy.c -ly -ll
y.tab.c y.tab.h: parser.y
	yacc -d -v parser.y
lex.yy.c: scanner.l
	lex scanner.l
clean:
	rm *.o
	rm *.c


