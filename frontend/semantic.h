#ifndef SEMANT_H__
#define SEMANT_H__

#include "../absyn.h"
#include "../types.h"
#include "../env.h"
#include "../errormsg.h"
#include "../util/util.h"

void SEM_transProg(A_exp exp);

#endif