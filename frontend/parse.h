#ifndef PARSE_H__
#define PARSE_H__

#include "../util/util.h"
#include "../symbol.h"
#include "../errormsg.h"
#include "../absyn.h"
#include <stdio.h>

/* function prototype from parse.c */
A_exp parse(string fname);

#endif