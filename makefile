# variable
OBJECTS = lex.yy.o y.tab.o errormsg.o ./util/util.o

# executable
all: lextest parsetest
.PHONY: all

parsetest: parsetest.o $(OBJECTS)
	cc -g -o $@ parsetest.o $(OBJECTS)

lextest: lextest.o $(OBJECTS)
	cc -g -o $@ lextest.o $(OBJECTS)

# objects
lextest.o: lextest.c y.tab.h errormsg.h ./util/util.h
lex.yy.o: lex.yy.c y.tab.h errormsg.h ./util/util.h
errormsg.o: errormsg.c errormsg.h ./util/util.h
util.o: ./util/util.c ./util/util.h

# lex
lex.yy.c: ./scanner/tiger.lex
	lex ./scanner/tiger.lex
	
# parse
parsetest.o: parsetest.c errormsg.h util/util.h
y.tab.o: y.tab.c
y.tab.c: tiger.y
	yacc -dv tiger.y
y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

.PHONY: clean
clean:
	rm -f *.o a.out lextest parsetest lex.yy.c y.output y.tab.c y.tab.h
