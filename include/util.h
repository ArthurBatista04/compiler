#ifndef UTIL_H
#define UTIL_H
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef char *string;
string String(string s);
typedef char bool;

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {
  bool head;
  U_boolList tail;
};

U_boolList U_BoolList(bool head, U_boolList tail);
void *checked_malloc(int n);
string FormatString(string s, ...);

#endif
