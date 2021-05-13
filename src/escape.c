#include "../include/absyn.h"
#include "../include/frame.h"
#include "../include/symbol.h"
#include "../include/table.h"
#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>


static void transExp(S_table env, int depth, A_exp e);
static void transDec(S_table env, int depth, A_dec d);
static void transVar(S_table env, int depth, A_var v);

typedef struct escentry_* escentry;

struct escentry_
{
  bool* escape;
  int depth;
};

escentry
EscEntry(bool* esc, int d)
{
  escentry eet = checked_malloc(sizeof(*eet));
  eet->escape = esc;
  eet->depth = d;
  return eet;
}

void
Esc_findEscape(A_exp exp)
{
  transExp(S_empty(), 0, exp);
}

static void
transExp(S_table env, int depth, A_exp e)
{
  switch (e->kind) {
    case A_varExp: {
      transVar(env, depth, e->u.var);
      return;
    }
    case A_callExp: {
      A_expList el = e->u.call.args;
      for (; el; el = el->tail) {
        transExp(env, depth, el->head);
      }
      return;
    }
    case A_opExp: {
      transExp(env, depth, e->u.op.left);
      transExp(env, depth, e->u.op.right);
      return;
    }
    case A_seqExp: {
      A_expList el = e->u.seq;
      for (; el; el = el->tail) {
        transExp(env, depth, el->head);
      }
      return;
    
    }
    case A_assignExp: {
      transVar(env, depth, e->u.assign.var);
      transExp(env, depth, e->u.assign.exp);
      return;
    }
    case A_ifExp: {
      transExp(env, depth, e->u.iff.test);
      transExp(env, depth, e->u.iff.then);
      if (e->u.iff.elsee != NULL) { 
        transExp(env, depth, e->u.iff.elsee);
      }
      return;
    }
    case A_whileExp: {
      
      transExp(env, depth, e->u.whilee.test);
      
      transExp(env, depth, e->u.whilee.body);
      return;
    }
    case A_forExp: {
      
      S_enter(env, e->u.forr.var, EscEntry(&(e->u.forr.escape), depth));
      transExp(env, depth, e->u.forr.body);
      return;
    }
    case A_letExp: {
      A_decList d;
      S_beginScope(env);

      for (d = e->u.let.decs; d; d = d->tail) {
        
        transDec(env, depth, d->head);
      }
      transExp(env, depth, e->u.let.body);
      S_endScope(env);
      return;
    }
    case A_arrayExp: {
      transExp(env, depth, e->u.array.init);
      transExp(env, depth, e->u.array.size); 
      return;
    }
    case A_recordExp: {
    }
    case A_nilExp: {
    }
    case A_intExp: {
    }
    case A_stringExp: {
    }
    case A_breakExp: {
      return;
    }
    default:;
  }
  
}

static void
transDec(S_table env, int depth, A_dec d)
{
  switch (d->kind) {
    case A_varDec: {
      
      transExp(env, depth, d->u.var.init);
     
      d->u.var.escape = 0; 
      S_enter(env, d->u.var.var, EscEntry(&(d->u.var.escape), depth));

      return;
    }
    case A_typeDec: {
      return;
    }
    case A_functionDec: {
      
      A_fundec f;
      A_fundecList fl;
      
      for (fl = d->u.function; fl; fl = fl->tail) {
      }
      for (fl = d->u.function; fl; fl = fl->tail) {
        f = fl->head;
        S_beginScope(env);
        {
          A_fieldList l;
          
          for (l = f->params; l; l = l->tail) {
            l->head->escape = 1;
            S_enter(env, l->head->name, EscEntry(&(l->head->escape), depth));
          }
        }
        
        transExp(env, depth + 1, f->body);
        S_endScope(env);
      }
      
      return;
    }
  }
  
}

static void
transVar(S_table env, int depth, A_var v)
{
  switch (v->kind) {
    case A_simpleVar: {
      escentry eet = S_look(env, v->u.simple);
      if (depth > eet->depth) *(eet->escape) = 1;
      return;
    }
    case A_fieldVar: {
      
      transVar(env, depth, v->u.field.var);
      return;
    }
    case A_subscriptVar: {
      
      transVar(env, depth, v->u.subscript.var);
      transExp(env, depth, v->u.subscript.exp);
      return;
    }
    defalut:;
  }
  assert(0);
}

