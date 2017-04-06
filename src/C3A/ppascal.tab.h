/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PPASCAL_TAB_H_INCLUDED
# define YY_YY_PPASCAL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_boo = 258,
    T_int = 259,
    Def = 260,
    Dep = 261,
    Af = 262,
    true = 263,
    false = 264,
    Se = 265,
    If = 266,
    Th = 267,
    El = 268,
    Var = 269,
    Wh = 270,
    Do = 271,
    Pl = 272,
    Mo = 273,
    Mu = 274,
    And = 275,
    Or = 276,
    Not = 277,
    Lt = 278,
    Eq = 279,
    Sk = 280,
    NFon = 281,
    NPro = 282,
    NewAr = 283,
    I = 284,
    V = 285,
    T_ar = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "ppascal.y" /* yacc.c:1909  */

        EnvGlobal envG;
        BILFON fonctionOuProcedure;
        BILENV varG;
        LFON fon;
        ENV env;
        NOE noe;
        char* nom[2]; //yylval.nom[0] -> variable, yylval.nom[1] -> entier

#line 96 "ppascal.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PPASCAL_TAB_H_INCLUDED  */
