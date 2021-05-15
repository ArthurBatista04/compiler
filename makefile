# variable
OBJECTS = lex.yy.o tiger.tab.o src/errormsg.o src/util.o src/absyn.o src/prabsyn.o src/symbol.o \
          src/table.o src/parse.o src/env.o src/semantic.o src/types.o src/mipsframe.o src/temp.o \
		  src/translate.o src/escape.o src/tree.o src/printtree.o src/canon.o src/assem.o src/mipscodegen.o


# executable
all: tc
.PHONY: all


tc: main.o  $(OBJECTS)
	cc -o $@ -g main.o $(OBJECTS)

# objects
errormsg.o: src/errormsg.c include/errormsg.h include/util.h
util.o: src/util.c include/util.h
absyn.o: src/absyn.c include/absyn.h include/util.h include/symbol.h
prabsyn.o: src/prabsyn.c include/prabsyn.h include/util.h include/absyn.h
symbol.o: src/symbol.c include/symbol.h include/util.h include/table.h
table.o: src/table.c include/table.h include/util.h
parse.o: src/parse.c include/parse.h include/util.h include/errormsg.h include/symbol.h include/absyn.h

# lex
lex.yy.o: lex.yy.c tiger.tab.h include/errormsg.h include/util.h
lex.yy.c: src/tiger.lex
	flex src/tiger.lex

# parse
tiger.tab.o: tiger.tab.c
tiger.tab.c: src/tiger.y
	bison -dv src/tiger.y
tiger.tab.h: tiger.tab.c

# type-check
env.o: src/env.c include/env.h
semantic.o: src/semantic.c include/semantic.h
types.o: src/types.c include/types.h

# frame
mipsframe.o: include/frame.h
temp.o: include/temp.h
escape.o: include/escape.h

# translate
translate.o: include/translate.h
tree.o: include/tree.h
printtree.o: include/printtree.h

# canon
canon.o: include/canon.h

# instruction
assem.o: include/assem.h
mipscodegen.o: include/codegen.h

.PHONY: clean
clean:
	rm -f *.o src/*.o tc lex.yy.c y.output tiger.tab.c tiger.tab.h tiger.output lex.yy.c tiger.tab.c tiger.tab.h
