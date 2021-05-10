# variable
OBJECTS = lex.yy.o tiger.tab.o errormsg.o ./util/util.o absyn.o prabsyn.o symbol.o \
          table.o ./frontend/parse.o env.o ./frontend/semantic.o types.o mipsframe.o temp.o \
		  translate.o escape.o tree.o printtree.o canon.o assem.o mipscodegen.o


# executable
all: lextest parsetest absyntest typechecktest translatetest tc
.PHONY: all

lextest: lextest.o $(OBJECTS)
	cc -g -o $@ lextest.o $(OBJECTS)

parsetest: parsetest.o $(OBJECTS)
	cc -g -o $@ parsetest.o $(OBJECTS)

absyntest: absyntest.o $(OBJECTS)
	cc -g -o $@ absyntest.o $(OBJECTS)

typechecktest: typechecktest.o $(OBJECTS)
	cc -o $@ typechecktest.o $(OBJECTS) 


translatetest: translatetest.o $(OBJECTS)
	cc -o $@ translatetest.o $(OBJECTS)

tc: main.o $(OBJECTS)
	cc -o $@ main.o $(OBJECTS)

# objects
errormsg.o: errormsg.c errormsg.h ./util/util.h
util.o: ./util/util.c ./util/util.h
absyn.o: absyn.c absyn.h ./util/util.h symbol.h
prabsyn.o: prabsyn.c prabsyn.h ./util/util.h absyn.h
symbol.o: symbol.c symbol.h ./util/util.h table.h
table.o: table.c table.h ./util/util.h
parse.o: ./frontend/parse.c ./frontend/parse.h ./util/util.h errormsg.h symbol.h absyn.h

# lex
lextest.o: lextest.c absyn.h symbol.h tiger.tab.h errormsg.h ./util/util.h
lex.yy.o: lex.yy.c tiger.tab.h errormsg.h ./util/util.h
lex.yy.c: ./frontend/tiger.lex
	flex ./frontend/tiger.lex

# parse
parsetest.o: parsetest.c errormsg.h ./util/util.h absyn.h symbol.h
tiger.tab.o: tiger.tab.c
tiger.tab.c: ./frontend/tiger.y
	bison -dv ./frontend/tiger.y
tiger.tab.h: tiger.tab.c
	echo "tiger.tab.h was created at the same time as tiger.tab.c"

# absyn
absyntest.o: absyntest.c errormsg.h ./util/util.h absyn.h symbol.h ./frontend/parse.h prabsyn.h

# type-check
typechecktest.o: typechecktest.c errormsg.h ./util/util.h absyn.h symbol.h
env.o: env.c env.h
semantic.o: ./frontend/semantic.c ./frontend/semantic.h
types.o: types.c types.h

# frame
mipsframe.o: frame.h
temp.o: temp.h
escape.o: escape.h

# translate
translate.o: translate.h
tree.o: tree.h
printtree.o: printtree.h
translatetest.o: translatetest.c errormsg.h util/util.h absyn.h symbol.h frame.h

# canon
canon.o: canon.h

# instruction
assme.o: assem.h
mipscodegen.o: codegen.h

.PHONY: clean
clean:
	rm -f *.o tc lextest parsetest typechecktest absyntest translatetest lex.yy.c y.output tiger.tab.c tiger.tab.h tiger.output lex.yy.c tiger.tab.c tiger.tab.h
