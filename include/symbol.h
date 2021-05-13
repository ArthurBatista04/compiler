

#ifndef SYMBOL_H__
#define SYMBOL_H__

#include "table.h"
#include "util.h"

typedef struct S_symbol_ *S_symbol;
struct S_symbol_ {string name; S_symbol next;};

S_symbol S_Symbol(string);


string S_name(S_symbol);


typedef struct TAB_table_ *S_table;


S_table S_empty(void);


void S_enter(S_table t, S_symbol sym, void *value);


void *S_look(S_table t, S_symbol sym);


void S_beginScope(S_table t);


void S_endScope(S_table t);

#endif