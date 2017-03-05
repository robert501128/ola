/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 233 "parser.y" /* yacc.c:1909  */

	struct data {
		char *idname;
		char *type;
		struct data *next;
	};
	typedef struct data Data;



	

#line 57 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KWvar = 258,
    mod = 259,
    and = 260,
    or = 261,
    not = 262,
    KWbegin = 263,
    KWinteger = 264,
    KWreal = 265,
    KWprint = 266,
    KWend = 267,
    KWarray = 268,
    KWboolean = 269,
    KWdo = 270,
    KWelse = 271,
    KWfalse = 272,
    KWfor = 273,
    KWif = 274,
    KWof = 275,
    KWread = 276,
    KWstring = 277,
    KWthen = 278,
    KWto = 279,
    KWtrue = 280,
    KWreturn = 281,
    KWwhile = 282,
    id = 283,
    assign = 284,
    lte = 285,
    gte = 286,
    gl = 287,
    Lstring = 288,
    Lreal = 289,
    Lint = 290
  };
#endif
/* Tokens.  */
#define KWvar 258
#define mod 259
#define and 260
#define or 261
#define not 262
#define KWbegin 263
#define KWinteger 264
#define KWreal 265
#define KWprint 266
#define KWend 267
#define KWarray 268
#define KWboolean 269
#define KWdo 270
#define KWelse 271
#define KWfalse 272
#define KWfor 273
#define KWif 274
#define KWof 275
#define KWread 276
#define KWstring 277
#define KWthen 278
#define KWto 279
#define KWtrue 280
#define KWreturn 281
#define KWwhile 282
#define id 283
#define assign 284
#define lte 285
#define gte 286
#define gl 287
#define Lstring 288
#define Lreal 289
#define Lint 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 247 "parser.y" /* yacc.c:1909  */

	char *idname;
	struct s1 { char *r; } *state;
	struct s2 { char *toString; int start;} array;
	struct s3 { char *idname; char *type;} all;
	struct s4 { char *idname; char *type; char *kind; char *attribute; int level;} simulateNode;
	struct s5 { char *type; int pointer;} forE;
	struct s6 { char back[10],next[10]; char *idname; } forFor;
	struct data *aarrg;
	char forLabel[10];
	int num;
	

#line 153 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
