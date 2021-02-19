# variable
OBJECTS = lex.yy.o y.tab.o errormsg.o ./util/util.o absyn.o prabsyn.o symbol.o \
          table.o parse.o

# executable
all: lextest parsetest absyntest
.PHONY: all

lextest: lextest.o $(OBJECTS)
	cc -g -o $@ lextest.o $(OBJECTS)

parsetest: parsetest.o $(OBJECTS)
	cc -g -o $@ parsetest.o $(OBJECTS)

absyntest: absyntest.o $(OBJECTS)
	cc -g -o $@ absyntest.o $(OBJECTS)

# objects
errormsg.o: errormsg.c errormsg.h ./util/util.h
util.o: ./util/util.c ./util/util.h
absyn.o: absyn.c absyn.h ./util/util.h symbol.h
prabsyn.o: prabsyn.c prabsyn.h ./util/util.h absyn.h
symbol.o: symbol.c symbol.h ./util/util.h table.h
table.o: table.c table.h ./util/util.h
parse.o: parse.c parse.h ./util/util.h errormsg.h symbol.h absyn.h

# lex
lextest.o: lextest.c absyn.h symbol.h y.tab.h errormsg.h ./util/util.h
lex.yy.o: lex.yy.c y.tab.h errormsg.h ./util/util.h
lex.yy.c: ./frontend/tiger.lex
	lex ./frontend/tiger.lex

# parse
parsetest.o: parsetest.c errormsg.h ./util/util.h absyn.h symbol.h
y.tab.o: y.tab.c
y.tab.c: ./frontend/tiger.y
	yacc -dv ./frontend/tiger.y
y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

# absyn
absyntest.o: absyntest.c errormsg.h ./util/util.h absyn.h symbol.h parse.h prabsyn.h

.PHONY: clean
clean:
	rm -f *.o a.out lextest parsetest absyntest lex.yy.c y.output y.tab.c y.tab.h
