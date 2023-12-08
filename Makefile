default:
	clear
	# auto generate to the lexical
	flex -l test.l 
	
	# auto generate to the parser
	bison -dv test.y 
	
	gcc -o test test.tab.c lex.yy.c -lfl
