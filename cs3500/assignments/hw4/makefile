all: 
	bison -d roboparser.y
	flex roboparser.l
	g++ roboparser.tab.c lex.yy.c -o roboparser.ex