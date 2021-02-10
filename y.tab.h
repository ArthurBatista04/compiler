/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LOW = 258,                     /* LOW  */
    UMINUS = 259,                  /* UMINUS  */
    ID = 260,                      /* ID  */
    STRING = 261,                  /* STRING  */
    INT = 262,                     /* INT  */
    COMMA = 263,                   /* COMMA  */
    COLON = 264,                   /* COLON  */
    SEMICOLON = 265,               /* SEMICOLON  */
    LPAREN = 266,                  /* LPAREN  */
    RPAREN = 267,                  /* RPAREN  */
    LBRACK = 268,                  /* LBRACK  */
    RBRACK = 269,                  /* RBRACK  */
    LBRACE = 270,                  /* LBRACE  */
    RBRACE = 271,                  /* RBRACE  */
    DOT = 272,                     /* DOT  */
    PLUS = 273,                    /* PLUS  */
    MINUS = 274,                   /* MINUS  */
    TIMES = 275,                   /* TIMES  */
    DIVIDE = 276,                  /* DIVIDE  */
    EQ = 277,                      /* EQ  */
    NEQ = 278,                     /* NEQ  */
    LT = 279,                      /* LT  */
    LE = 280,                      /* LE  */
    GT = 281,                      /* GT  */
    GE = 282,                      /* GE  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    ASSIGN = 285,                  /* ASSIGN  */
    ARRAY = 286,                   /* ARRAY  */
    IF = 287,                      /* IF  */
    THEN = 288,                    /* THEN  */
    ELSE = 289,                    /* ELSE  */
    WHILE = 290,                   /* WHILE  */
    FOR = 291,                     /* FOR  */
    TO = 292,                      /* TO  */
    DO = 293,                      /* DO  */
    LET = 294,                     /* LET  */
    IN = 295,                      /* IN  */
    END = 296,                     /* END  */
    OF = 297,                      /* OF  */
    BREAK = 298,                   /* BREAK  */
    NIL = 299,                     /* NIL  */
    FUNCTION = 300,                /* FUNCTION  */
    VAR = 301,                     /* VAR  */
    TYPE = 302,                    /* TYPE  */
    BOOL = 303,                    /* BOOL  */
    TRUE = 304,                    /* TRUE  */
    FALSE = 305                    /* FALSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LOW 258
#define UMINUS 259
#define ID 260
#define STRING 261
#define INT 262
#define COMMA 263
#define COLON 264
#define SEMICOLON 265
#define LPAREN 266
#define RPAREN 267
#define LBRACK 268
#define RBRACK 269
#define LBRACE 270
#define RBRACE 271
#define DOT 272
#define PLUS 273
#define MINUS 274
#define TIMES 275
#define DIVIDE 276
#define EQ 277
#define NEQ 278
#define LT 279
#define LE 280
#define GT 281
#define GE 282
#define AND 283
#define OR 284
#define ASSIGN 285
#define ARRAY 286
#define IF 287
#define THEN 288
#define ELSE 289
#define WHILE 290
#define FOR 291
#define TO 292
#define DO 293
#define LET 294
#define IN 295
#define END 296
#define OF 297
#define BREAK 298
#define NIL 299
#define FUNCTION 300
#define VAR 301
#define TYPE 302
#define BOOL 303
#define TRUE 304
#define FALSE 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "./frontend/tiger.y"

	int pos;
	int ival;
	string sval;
    //bool bval;
  

#line 174 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
