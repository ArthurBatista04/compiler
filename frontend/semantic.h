#ifndef SEMANT_H__
#define SEMANT_H__

#include "../absyn.h"
#include "../env.h"
#include "../errormsg.h"
#include "../frame.h"
#include "../translate.h"
#include "../types.h"
#include "../util/util.h"
#include <stdlib.h>

F_fragList SEM_transProg(A_exp exp);
Tr_exp get_exp(A_exp exp);

#endif