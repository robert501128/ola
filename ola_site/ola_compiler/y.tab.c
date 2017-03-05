/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

char filename[32];
extern int linenum;             /* declared in lex.l */
extern FILE *yyin;              /* declared by lex */
extern char *yytext;            /* declared by lex */
extern char buf[256];           /* declared in lex.l */
extern int Opt_D;
Root *top;
Node *fortop;
LocalNode *ltop;
int isFunc;
int FuncComp;
int isMain;
char *funcname;
int semError;
char content[4194304];
int number;
int labelNumber;



char* typetoJava(char *a)
{
	char *s=(char*)malloc(sizeof(char));
	if(strcmp(a,"integer")==0)
	{
		s[0]='I';
		return s;
	}
	if(strcmp(a,"string")==0)
	{
		s[0]='Z';
		return s;
	}
	if(strcmp(a,"real")==0)
	{
		s[0]='F';
		return s;
	}
	if(strcmp(a,"boolean")==0)
	{
		s[0]='Z';
		return s;
	}
	if(strcmp(a,"void")==0)
	{
		s[0]='V';
		return s;
	}
	
}
void loadFunc(char *name, char *type, char *attribute)
{
	strcat(content,"invokestatic ");
	strcat(content,filename);
	strcat(content,"/");
	strcat(content,name);
	strcat(content,"(");
	
	char buf[1000];
	char *pch;
	strcpy(buf,attribute);
	pch=strtok(buf,",");
	while(pch!=NULL)
	{
		strcat(content,typetoJava(pch));
		pch=strtok(NULL,",");
	}
		
	strcat(content,")");	
	strcat(content,typetoJava(type));
	strcat(content,"\n");
	
}

void loadConst(char *attribute, char *type)
{
	if(strcmp(type,"integer")==0)
	{
		strcat(content,"sipush ");
		strcat(content,attribute);
		strcat(content,"\n");
	}
	else if(strcmp(type,"boolean")==0)
	{
		if(strcmp(attribute,"true")==0){					
		strcat(content,"iconst_1");
		strcat(content,"\n");}
		else{
		strcat(content,"iconst_0");
		strcat(content,"\n");}
	}
	else
	{
	
		strcat(content,"ldc ");
		strcat(content,attribute);
		strcat(content,"\n");
	}
}

void loadVar(char* name,char* kind, char* type, char* attribute, int innerlevel)
{
	if(strcmp(kind,"constant")==0)
	{
		
		if(strcmp(type,"integer")==0)
		{
			strcat(content,"sipush ");
			strcat(content,attribute);
			strcat(content,"\n");
		}
		else if(strcmp(type,"boolean")==0)
		{
			if(strcmp(attribute,"true")==0){					
			strcat(content,"iconst_1");
			strcat(content,"\n");}
			else{
			strcat(content,"iconst_0");
			strcat(content,"\n");}
		}
		else
		{
			
			strcat(content,"ldc ");
			strcat(content,attribute);
			strcat(content,"\n");
		}
	}
	else if(innerlevel==0)
	{

		strcat(content,"getstatic ");
		strcat(content,filename);
		strcat(content,"/");
		strcat(content,name);
		strcat(content," ");
		strcat(content,typetoJava(type));
		strcat(content,"\n");
	}else
	{
		
		int num=searchLocal(ltop,name);
		if(num>=0){
		if(strcmp(type,"real")==0)
		{

			char snum[10];
			sprintf(snum,"%d",num);
			strcat(content,"fload ");
			strcat(content,snum);
			strcat(content,"\n");
		}
		else
		{
			char snum[10];
			sprintf(snum,"%d",num);
			strcat(content,"iload ");
			strcat(content,snum);
			strcat(content,"\n");
		}			
		}
	}
}

void publicStore(char *name,char *type)
{
	strcat(content,"putstatic ");
	strcat(content,filename);
	strcat(content,"/");
	strcat(content,name);
	strcat(content," ");
	strcat(content,typetoJava(type));
	strcat(content,"\n");
}

void localStore(char *name,char *type)
{
	int num=searchLocal(ltop,name);
	if(num>=0){
	if(strcmp(type,"real")==0)
	{

		char snum[10];
		sprintf(snum,"%d",num);
		strcat(content,"fstore ");
		strcat(content,snum);
		strcat(content,"\n");
	}
	else
	{
		char snum[10];
		sprintf(snum,"%d",num);
		strcat(content,"istore ");
		strcat(content,snum);
		strcat(content,"\n");
	}			
	}
}

void createLabel(char *L1)
{
	strcpy(L1,"L");
	char num[10];
	sprintf(num,"%d",labelNumber++);
	strcat(L1,num);	
}

void createRelCode(char *Op,char *L1, char *L2)
{
	strcat(content,Op);
	strcat(content," ");
	strcat(content,L1);
	strcat(content,"\n");
	strcat(content,"iconst_0\n");
	strcat(content,"goto ");
	strcat(content,L2);
	strcat(content,"\n");
	strcat(content,L1);
	strcat(content,":\n");
	strcat(content,"iconst_1\n");
	strcat(content,L2);
	strcat(content,":\n");
}



#line 299 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 233 "parser.y" /* yacc.c:355  */

	struct data {
		char *idname;
		char *type;
		struct data *next;
	};
	typedef struct data Data;



	

#line 342 "y.tab.c" /* yacc.c:355  */

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
#line 247 "parser.y" /* yacc.c:355  */

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
	

#line 438 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 453 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   539

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       4,     8,    13,    11,     5,    12,     2,    14,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     7,     6,
      42,    17,    16,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     9,     2,    10,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,    15,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    43,    44,    45,    46,    47,    48,
      49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   287,   287,   288,   301,   312,   317,   325,   326,   327,
     328,   352,   368,   369,   370,   371,   372,   373,   374,   454,
     472,   473,   474,   475,   476,   492,   509,   510,   515,   535,
     551,   552,   611,   612,   613,   614,   615,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   642,   652,   715,   730,   731,   759,   778,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   837,   846,
     855,   876,   914,   950,   964,  1002,  1037,  1071,  1105,  1139,
    1173,  1209,  1243,  1256,  1269,  1282,  1283,  1284,  1285,  1289,
    1291,  1294,  1302,  1315,  1316,  1317,  1330,  1344,  1349,  1360,
    1371,  1382,  1393,  1404,  1410,  1418,  1426,  1444,  1489
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KWvar", "'('", "','", "';'", "':'",
  "')'", "'['", "']'", "'+'", "'-'", "'*'", "'/'", "mod", "'>'", "'='",
  "and", "or", "not", "KWbegin", "KWinteger", "KWreal", "KWprint", "KWend",
  "KWarray", "KWboolean", "KWdo", "KWelse", "KWfalse", "KWfor", "KWif",
  "KWof", "KWread", "KWstring", "KWthen", "KWto", "KWtrue", "KWreturn",
  "KWwhile", "id", "'<'", "assign", "lte", "gte", "gl", "Lstring", "Lreal",
  "Lint", "$accept", "START", "BeginId", "MAIN", "CEND", "EndId",
  "GlZorVDEC", "GlVDEC", "GlALLTYPE", "ZorVDEC", "VDEC", "ZorFDEC", "FDEC",
  "FBeginId", "FEndId", "PorR", "ZorARG", "ARG", "ID_List", "ALLTYPE",
  "SC_TYPE", "TYPE", "L_CONSTANT", "L_BOOL", "STMT", "COMPBEGIN", "COMP",
  "SIMPLE", "PRINTCODE", "VAR_REF", "REF", "LE", "RCPN", "E", "BE", "CPN",
  "FUNC_INV", "FUNCID", "ZorE", "MORE_E", "COND", "CONDBE", "CONDSTMT",
  "WHILE", "CONTROLWHILE", "FOR", "FORINITIALIZE", "RETURN", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,    40,    44,    59,    58,    41,    91,
      93,    43,    45,    42,    47,   259,    62,    61,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,    60,   284,   285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -117

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-117)))

#define YYTABLE_NINF -102

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -39,  -117,     8,    -1,  -117,  -117,    12,   -20,  -117,   -13,
    -117,    72,    27,    11,  -117,    11,    15,   490,   -20,  -117,
    -117,    30,    34,  -117,  -117,  -117,    33,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,    70,  -117,  -117,  -117,  -117,    83,
      80,    78,    91,  -117,    54,    74,    87,  -117,   126,   -20,
     120,   -20,  -117,     5,  -117,  -117,  -117,  -117,    96,    66,
     138,    95,  -117,   134,   254,   254,   254,  -117,  -117,   107,
     277,   108,   254,  -117,    18,  -117,  -117,  -117,   254,   109,
     316,  -117,  -117,  -117,   149,  -117,  -117,   277,  -117,   128,
    -117,   127,  -117,  -117,   120,   490,  -117,   420,  -117,    92,
     125,   254,   456,   -22,    14,   133,   166,   173,   330,   410,
     174,   367,   254,  -117,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   154,  -117,
     120,  -117,   182,  -117,  -117,  -117,   141,   183,   184,  -117,
    -117,  -117,   410,  -117,  -117,   298,  -117,  -117,   410,  -117,
     381,    84,    84,  -117,  -117,  -117,   352,   352,    92,   465,
     352,   352,   352,   352,   456,   188,   194,  -117,   146,  -117,
    -117,   163,  -117,  -117,   177,   175,  -117,  -117,   410,   410,
     410,   410,   410,   340,  -117,  -117,   254,   208,   178,   156,
     171,  -117,   159,   159,  -117,  -117,  -117,  -117,   456,   185,
    -117,  -117,  -117,   239,  -117,   187,  -117
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,     7,    15,     0,     8,     4,
      26,     0,     0,     0,    16,     0,     0,     0,    22,    50,
      12,     0,     0,    27,    32,    33,     0,    35,    41,    34,
      40,    38,    37,    36,     0,    10,    30,    11,    39,     0,
      23,     0,    49,     5,     0,     0,     0,     9,    20,     0,
       0,     0,    13,     0,     6,     2,    19,    17,     0,     0,
       0,     0,    24,     0,     0,     0,     0,    54,    51,     0,
       0,     0,     0,   105,    56,    89,    42,    43,     0,    90,
       0,    85,    87,    88,     0,    45,    46,     0,    47,     0,
      48,     0,    21,    18,     0,     0,    90,     0,    70,    82,
       0,     0,     0,    85,    87,     0,    56,     0,     0,     0,
      57,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,    49,
       0,    25,     0,    28,    29,    86,     0,    85,    87,    49,
      55,   108,     0,    68,    69,     0,    66,    67,     0,    53,
       0,    74,    75,    71,    72,    73,    80,    78,    83,    84,
      76,    77,    79,    81,    95,     0,    94,    49,     0,    31,
      14,     0,    98,   100,   102,     0,    60,    58,     0,     0,
       0,     0,     0,     0,    52,    91,     0,     0,     0,     0,
       0,    49,    64,    65,    61,    62,    63,    59,    96,     0,
     106,   107,   103,     0,   104,     0,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,   -11,  -117,
     -46,   151,   -17,  -117,  -116,  -117,   144,  -117,  -117,   -52,
    -117,   -61,  -117,   -54,   -67,    53,   -68,  -117,  -117,  -117,
    -117,   135,  -117,  -117,  -117,  -117,  -117,  -117
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    13,    44,    55,     6,     8,    34,    42,
      52,     9,    14,    15,    57,    60,    39,    40,    11,   132,
      35,    36,    75,    38,    53,    20,    76,    77,    78,    96,
     110,   145,   146,    80,    81,    82,    83,    84,   165,   166,
      85,   105,   175,    86,    87,    88,    89,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,    79,     1,   103,    62,     5,   -99,    41,     4,    64,
      97,    98,    99,   168,   -99,     7,   102,    65,   108,   107,
     103,    10,   -92,   174,   111,    66,    19,   109,    12,    67,
      68,    18,    19,   102,   137,    28,    69,    70,    61,    71,
      63,   147,  -101,    30,    72,    73,    74,    97,   131,   133,
    -101,   187,    31,    32,    33,    43,    23,   144,   150,    45,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   147,   203,    47,    16,   134,    17,
     147,   176,    46,    16,   169,    50,    49,   183,    24,    25,
     144,    48,   143,    27,    51,    54,   144,   116,   117,   118,
      16,    29,    94,   114,   115,   116,   117,   118,   119,   120,
     147,   147,   147,   147,   147,    56,    79,   192,   193,   194,
     195,   196,    79,   104,    58,   143,   144,   144,   144,   144,
     144,   143,   198,    59,   123,    79,   124,   125,   126,    16,
     104,    95,    24,    25,    93,    91,    26,    27,   100,   106,
      64,    79,   112,   127,   138,    29,   129,    21,    65,    22,
     130,   143,   143,   143,   143,   143,    66,    19,   136,   139,
      67,   188,   180,   181,   182,   109,    28,    69,    70,   140,
      71,    64,   167,   148,    30,    72,    73,    74,   170,    65,
     171,   172,   173,    31,    32,    33,   185,    66,    19,   186,
     189,    67,   190,   202,   191,   201,   200,    28,    69,    70,
      92,    71,    64,   204,     0,    30,    72,    73,    74,   206,
      65,     0,   128,     0,    31,    32,    33,     0,    66,    19,
       0,     0,    67,   199,     0,     0,     0,     0,    28,    69,
      70,     0,    71,    64,     0,     0,    30,    72,    73,    74,
       0,    65,     0,     0,     0,    31,    32,    33,    64,    66,
      19,     0,     0,    67,   205,     0,    65,     0,     0,    28,
      69,    70,     0,    71,    66,     0,     0,    30,    72,    73,
      74,   101,     0,     0,    28,     0,    31,    32,    33,    65,
       0,     0,    30,     0,     0,    74,     0,    66,     0,     0,
       0,    31,    32,    33,     0,     0,     0,    28,   177,   178,
     179,   180,   181,   182,     0,    30,     0,     0,    74,     0,
       0,     0,   113,     0,    31,    32,    33,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   141,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     197,   178,   179,   180,   181,   182,     0,     0,   123,     0,
     124,   125,   126,   114,   115,   116,   117,   118,     0,     0,
       0,     0,   123,   149,   124,   125,   126,     0,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   184,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,     0,     0,     0,     0,     0,     0,   123,
       0,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   123,     0,   124,   125,   126,   135,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      28,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,    74,     0,     0,     0,     0,     0,    31,    32,    33,
       0,     0,   123,     0,   124,   125,   126,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   114,   115,   116,   117,
     118,   119,   120,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,     0,
     124,   125,   126,     0,     0,     0,     0,   123,     0,   124,
     125,   126,    24,    25,     0,     0,    26,    27,     0,     0,
      28,     0,     0,     0,     0,    29,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,    33
};

static const yytype_int16 yycheck[] =
{
      17,    53,    41,    70,    50,     6,    28,    18,     0,     4,
      64,    65,    66,   129,    36,     3,    70,    12,    72,    71,
      87,    41,     4,   139,    78,    20,    21,     9,    41,    24,
      25,     4,    21,    87,   101,    30,    31,    32,    49,    34,
      51,   109,    28,    38,    39,    40,    41,   101,    94,    95,
      36,   167,    47,    48,    49,    25,    41,   109,   112,    25,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   142,   191,     6,     5,    95,     7,
     148,   142,    49,     5,   130,     7,     6,   148,    22,    23,
     142,     8,   109,    27,     3,    41,   148,    13,    14,    15,
       5,    35,     7,    11,    12,    13,    14,    15,    16,    17,
     178,   179,   180,   181,   182,    41,   168,   178,   179,   180,
     181,   182,   174,    70,    37,   142,   178,   179,   180,   181,
     182,   148,   186,     7,    42,   187,    44,    45,    46,     5,
      87,     7,    22,    23,     6,    49,    26,    27,    41,    41,
       4,   203,    43,     4,   101,    35,    28,    13,    12,    15,
      33,   178,   179,   180,   181,   182,    20,    21,    43,    36,
      24,    25,    13,    14,    15,     9,    30,    31,    32,     6,
      34,     4,    28,     9,    38,    39,    40,    41,     6,    12,
      49,     8,     8,    47,    48,    49,     8,    20,    21,     5,
      37,    24,    25,    32,    29,    49,    28,    30,    31,    32,
      59,    34,     4,    28,    -1,    38,    39,    40,    41,    32,
      12,    -1,    87,    -1,    47,    48,    49,    -1,    20,    21,
      -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    30,    31,
      32,    -1,    34,     4,    -1,    -1,    38,    39,    40,    41,
      -1,    12,    -1,    -1,    -1,    47,    48,    49,     4,    20,
      21,    -1,    -1,    24,    25,    -1,    12,    -1,    -1,    30,
      31,    32,    -1,    34,    20,    -1,    -1,    38,    39,    40,
      41,     4,    -1,    -1,    30,    -1,    47,    48,    49,    12,
      -1,    -1,    38,    -1,    -1,    41,    -1,    20,    -1,    -1,
      -1,    47,    48,    49,    -1,    -1,    -1,    30,    10,    11,
      12,    13,    14,    15,    -1,    38,    -1,    -1,    41,    -1,
      -1,    -1,     6,    -1,    47,    48,    49,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     6,    -1,    -1,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      10,    11,    12,    13,    14,    15,    -1,    -1,    42,    -1,
      44,    45,    46,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    42,     6,    44,    45,    46,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     6,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    42,    -1,    44,    45,    46,     8,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    -1,    42,    -1,    44,    45,    46,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    42,    -1,    44,
      45,    46,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    51,    52,     0,     6,    56,     3,    57,    61,
      41,    68,    41,    53,    62,    63,     5,     7,     4,    21,
      75,    76,    76,    41,    22,    23,    26,    27,    30,    35,
      38,    47,    48,    49,    58,    70,    71,    72,    73,    66,
      67,    68,    59,    25,    54,    25,    49,     6,     8,     6,
       7,     3,    60,    74,    41,    55,    41,    64,    37,     7,
      65,    68,    70,    68,     4,    12,    20,    24,    25,    31,
      32,    34,    39,    40,    41,    72,    76,    77,    78,    79,
      83,    84,    85,    86,    87,    90,    93,    94,    95,    96,
      97,    49,    71,     6,     7,     7,    79,    83,    83,    83,
      41,     4,    83,    84,    85,    91,    41,    79,    83,     9,
      80,    83,    43,     6,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    42,    44,    45,    46,     4,    91,    28,
      33,    70,    69,    70,    72,     8,    43,    84,    85,    36,
       6,     6,    12,    72,    79,    81,    82,    86,     9,     6,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    88,    89,    28,    74,    70,
       6,    49,     8,     8,    74,    92,    81,    10,    11,    12,
      13,    14,    15,    81,     6,     8,     5,    74,    25,    37,
      25,    29,    81,    81,    81,    81,    81,    10,    83,    25,
      28,    49,    32,    74,    28,    25,    32
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    53,    54,    55,    56,    56,    57,
      58,    58,    59,    59,    60,    61,    61,    62,    63,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    71,    71,    72,    72,    72,    72,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      75,    76,    77,    77,    78,    77,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    82,
      83,    83,    83,    83,    83,    83,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    83,    83,    83,    85,    85,
      85,    86,    87,    88,    88,    89,    89,    90,    91,    91,
      91,    91,    92,    90,    93,    94,    95,    96,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     1,     0,     1,     1,     0,     2,     5,
       1,     1,     0,     2,     5,     0,     2,     4,     6,     1,
       0,     2,     0,     1,     3,     5,     1,     3,     1,     1,
       1,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     2,     2,     2,     2,     0,
       1,     4,     4,     3,     1,     3,     1,     2,     3,     4,
       2,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     1,     3,     1,     1,     1,
       1,     4,     1,     0,     1,     1,     3,     8,     3,     1,
       3,     1,     1,     6,     6,     1,     5,     6,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 288 "parser.y" /* yacc.c:1646  */
    { if(strcmp((yyvsp[0].idname),filename)!=0){ semError=1; 
		//program beginning ID inconsist with file name
        printf("%d (ꐦ°᷄д°᷅): Please give us A+, please~ please!!\n", linenum);}
		top=addRoot(top);
		addNode(top,(yyvsp[0].idname),"program","void","");
		(yyval.idname)=(yyvsp[0].idname);
		strcat(content,".class public ");
		strcat(content,filename);
		strcat(content,"\n");
		strcat(content,".super java/lang/Object\n");
		strcat(content,".field public static _sc Ljava/util/Scanner;\n");	
	
		}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 301 "parser.y" /* yacc.c:1646  */
    { isMain=1;
	strcat(content,".method public static main([Ljava/lang/String;)V\n");
	strcat(content,".limit stack 20  ;\n");
	strcat(content,".limit locals 20\n");
	strcat(content,"new java/util/Scanner\ndup\ngetstatic java/lang/System/in Ljava/io/InputStream;\n");
	strcat(content,"invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V\nputstatic ");
	strcat(content,filename);
	strcat(content,"/_sc Ljava/util/Scanner;\n");
	ltop=addLocal(ltop,"");
	}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 312 "parser.y" /* yacc.c:1646  */
    {isMain=0;
		strcat(content,"    return\n");
		strcat(content,".end method\n");
	}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 317 "parser.y" /* yacc.c:1646  */
    {
		if(strcmp((yyvsp[(-5) - (1)].idname),(yyvsp[0].idname))!=0)
		{semError=1;
		//program beginning ID inconsist with ending ID
        printf("%d ☜(`o´): Please give us A+. \n", linenum);}
		list(top,Opt_D);
		top=freeStack(top);
	}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 329 "parser.y" /* yacc.c:1646  */
    {
		char *buffer=(yyvsp[(-1) - (1)].idname);
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
			{
				addNode(top,pch,"variable",(yyvsp[0].array).toString,"");
				strcat(content,".field public static ");
				strcat(content,pch);
				strcat(content," ");
				strcat(content,typetoJava((yyvsp[0].array).toString));
				strcat(content,"\n");
			}	
			else{ semError=1;
                //Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
		
	}
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 353 "parser.y" /* yacc.c:1646  */
    {		
		char *buffer=(yyvsp[(-1) - (1)].idname);
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
				addNode(top,pch,"constant",(yyvsp[0].all).type,(yyvsp[0].all).idname);
			else{ semError=1;
				//Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
	}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 374 "parser.y" /* yacc.c:1646  */
    {

	Data *data=(yyvsp[-3].aarrg);
	Data *reverse=NULL;
	Data *tmpdata;
	int s=1;
	char w[10000];
	memset(w,0,sizeof(w));	
	while(data!=NULL)
	{
		tmpdata=data;		
		data=data->next;
		tmpdata->next=reverse;
		reverse=tmpdata;
	}
	tmpdata=reverse;
	while(tmpdata!=NULL)
	{	
		if(s){strcat(w,tmpdata->type); s=0; }
		else {strcat(w,","); strcat(w,tmpdata->type);}
		tmpdata=tmpdata->next;
	}
	
	if(lookup((yyvsp[-5].idname),top)==NULL)
	{
		strcat(content,".method public static ");
		strcat(content,(yyvsp[-5].idname));
		strcat(content,"(");
		tmpdata=reverse;
		while(tmpdata!=NULL)
		{
		 strcat(content,typetoJava(tmpdata->type));
		 tmpdata=tmpdata->next;
		}
		if((yyvsp[-1].idname)==NULL)      	
		{
	         addNode(top,(yyvsp[-5].idname),"function","void",w);
		 strcat(content,")V\n");
		}
		else
		{
	      	 addNode(top,(yyvsp[-5].idname),"function",(yyvsp[-1].idname),w);
		 strcat(content,")");
		 strcat(content,typetoJava((yyvsp[-1].idname)));
		 strcat(content,"\n");
		}
		(yyval.idname)=(yyvsp[-5].idname);
		strcat(content,".limit stack 20\n");
		strcat(content,".limit locals 20\n");
	}
	else{   semError=1;
		//Function redeclare
        printf("%d .·´¯`(>▂<)´¯`·. : I’ve seen that Heart Eye Face.\n", linenum);
		(yyval.idname)=NULL;  }
	top=addRoot(top);
	tmpdata=reverse;
	while(tmpdata!=NULL)
	{
		if(lookup(tmpdata->idname,top)==NULL)
		{
			addNode(top,tmpdata->idname,"parameter",tmpdata->type,"");
			ltop=addLocal(ltop,tmpdata->idname);
		}
		else{semError=1;
			//Parameter redeclare
            printf("%d ᕙ(⇀‸↼‶)ᕗ :Same name for this kind of pet.\n", linenum);}
		tmpdata=tmpdata->next;
		}
	tmpdata=reverse;
	Data *tmpdata2;
	while(tmpdata!=NULL)
	{
		tmpdata2=tmpdata;
		tmpdata=tmpdata->next;
		free(tmpdata2);
	}
	isFunc=1;
	FuncComp=0;
	funcname=(yyval.idname);
	}
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 455 "parser.y" /* yacc.c:1646  */
    {	isFunc=0;
		
		char *beginid=(yyvsp[(-2) - (1)].idname);		
		if(beginid!=NULL)
		{
			if(strcmp(beginid,(yyvsp[0].idname))!=0)
			{semError=1;
                //program beginning ID inconsist with ending ID
                printf("%d ☜(`o´): Please give us A+. \n", linenum);}
		}
		Node *node=EntireLookup((yyvsp[0].idname),top);
		if(!strcmp(node->type,"void")) strcat(content,"return\n");
		strcat(content,".end method\n");
		list(top,Opt_D);
		top=freeStack(top);
		ltop=freeLocal(ltop);
	}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 472 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=NULL;}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 473 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 474 "parser.y" /* yacc.c:1646  */
    {(yyval.aarrg)=NULL;}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 475 "parser.y" /* yacc.c:1646  */
    {(yyval.aarrg)=(yyvsp[0].aarrg);}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 477 "parser.y" /* yacc.c:1646  */
    {
		Data *data=NULL;
		char *pch;		
		pch=strtok((yyvsp[-2].idname),",");
		while(pch!=NULL)
		{
			Data *x=(Data*)malloc(sizeof(Data));
			x->next=data;
			data=x;
			data->idname=strdup(pch);
			data->type=(yyvsp[0].array).toString;
			pch=strtok(NULL,",");
		}
		(yyval.aarrg)=data;
	}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 493 "parser.y" /* yacc.c:1646  */
    {
		Data *data=(yyvsp[-4].aarrg);
		char *pch;		
		pch=strtok((yyvsp[-2].idname),",");
		while(pch!=NULL)
		{
			Data *x=(Data*)malloc(sizeof(Data));
			x->next=data;
			data=x;
			data->idname=strdup(pch);
			data->type=(yyvsp[0].array).toString;
			pch=strtok(NULL,",");
		}
		(yyval.aarrg)=data;
	}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 509 "parser.y" /* yacc.c:1646  */
    { (yyval.idname)=(yyvsp[0].idname); }
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.idname)=(yyvsp[-2].idname); 
	  strcat((yyval.idname),",");
	  strcat((yyval.idname), (yyvsp[0].idname));	
	}
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 516 "parser.y" /* yacc.c:1646  */
    {
		char *buffer=(yyvsp[(-1) - (1)].idname);
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
			{
				addNode(top,pch,"variable",(yyvsp[0].array).toString,"");
				ltop=addLocal(ltop,pch);
			}
			else{ semError=1;
				//Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
			
		}
		
	}
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 536 "parser.y" /* yacc.c:1646  */
    {		
		char *buffer=(yyvsp[(-1) - (1)].idname);
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
				addNode(top,pch,"constant",(yyvsp[0].all).type,(yyvsp[0].all).idname);
			else{ semError=1;
                //Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
	}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 551 "parser.y" /* yacc.c:1646  */
    {(yyval.array).toString=(yyvsp[0].idname); (yyval.array).start=-1; }
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 553 "parser.y" /* yacc.c:1646  */
    {
		if(strcmp((yyvsp[0].array).toString,"error")!=0){		
		if((yyvsp[-4].num)>=(yyvsp[-2].num))
        {   //Declare a wrong array: Starting number is bigger or equal than ending number
            printf("%d (ノಠ益ಠ)ノ彡┻━┻ : Wrong hand instruction; Hand up and turn right.\n", linenum);}
            semError=1;
            (yyval.array).toString="error";}
		else
		{
			if((yyvsp[0].array).start<0)
			{
				char num[64];
				sprintf(num,"%d",(yyvsp[-2].num)-(yyvsp[-4].num)+1);
				char *cats=(char*)malloc(strlen(num)*sizeof(char)+2*sizeof(char));
				memset(cats,0,sizeof(cats));
				int i,j;
				cats[0]='[';
				for(i=1,j=0;j<strlen(num);i++,j++)
				{cats[i]=num[j];}

				cats[i]=']';
				char *s=(char*)malloc(sizeof(cats)+sizeof((yyvsp[0].array).toString));
				memset(s,0,sizeof(s));
				strcpy(s,(yyvsp[0].array).toString);
				strcat(s,cats);
				free((yyvsp[0].array).toString);
				free(cats);
				(yyval.array).toString=s;
			}
			else
			{				
				char num[64];
				sprintf(num,"%d",(yyvsp[-2].num)-(yyvsp[-4].num)+1);
				char *cats=(char*)malloc(strlen(num)*sizeof(char)+2*sizeof(char));
				memset(cats,0,sizeof(cats));
				int i,j;
				cats[0]='[';
				for(i=1,j=0;j<strlen(num);i++,j++)
				{cats[i]=num[j];}

				cats[i]=']';
				char *s=(char*)malloc(sizeof(cats)+sizeof((yyvsp[0].array).toString));
				memset(s,0,sizeof(s));
				int pos;
				pos=strcspn((yyvsp[0].array).toString,"[");
				for(i=0;i<pos;i++)
					s[i]=(yyvsp[0].array).toString[i];
				for(j=0;j<strlen(cats);j++,i++)
					s[i]=cats[j];
				for(j=pos;j<strlen((yyvsp[0].array).toString);j++,i++)
					s[i]=(yyvsp[0].array).toString[j];
				free((yyvsp[0].array).toString);
				free(cats);
				(yyval.array).toString=s;
			}
			
		}
	}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 611 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 612 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 613 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 614 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 616 "parser.y" /* yacc.c:1646  */
    {
		char num[64];
		sprintf(num,"%d",(yyvsp[0].num));
		char *buffer=(char*)malloc(strlen(num)*sizeof(char));
		strcpy(buffer,num);
		(yyval.all).idname=buffer; (yyval.all).type="integer";}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 622 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].idname); (yyval.all).type="real";}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 623 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].idname); (yyval.all).type="string";}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 624 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].idname); (yyval.all).type="boolean";}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 625 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 626 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=(yyvsp[0].idname);}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 636 "parser.y" /* yacc.c:1646  */
    {
		if(isFunc)FuncComp++;
		if(FuncComp!=1){
		top=addRoot(top);
		ltop=addBlock(ltop);}
	}
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 643 "parser.y" /* yacc.c:1646  */
    {
		
		if(FuncComp!=1){
		list(top,Opt_D);
		top=freeStack(top);
		ltop=freeLocal(ltop);}
		if(isFunc) FuncComp--;
	}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 653 "parser.y" /* yacc.c:1646  */
    {
		
		if((yyvsp[-1].forE).type==NULL)
		;
		else if((yyvsp[-3].simulateNode).type!=NULL && (yyvsp[-3].simulateNode).idname!=NULL){
			if(lookupNode((yyvsp[-3].simulateNode).idname,fortop)!=NULL){ semError=1;
			// Loop variable %s can not be assigned
            printf("%d ⁽⁽(੭ꐦ •̀Д•́ )੭*⁾⁾ ᑦᵒᔿᵉ ᵒᐢᵎᵎ : Loop Cat Face %s can not be assigned.\n", linenum,(yyvsp[-3].simulateNode).idname);}
			else
			{
			char *id1, *id3,*pch1[1000],*pch3[1000],*buf1,*buf3;
			int i=0;
			buf1=strdup((yyvsp[-3].simulateNode).type);
			buf3=strdup((yyvsp[-1].forE).type);
			id1=strtok(buf1,"[]");
			pch1[i]=strtok(NULL,"[]");
			for(i=1;pch1[i-1]!=NULL;i++)
			{
				pch1[i]=strtok(NULL,"[]");
			}
			id3=strtok(buf3,"[]");
			i=0;
			pch3[i]=strtok(NULL,"[]");
			for(i=1;pch3[i-1]!=NULL;i++)
			{
				pch3[i]=strtok(NULL,"[]");
			}
			int same=1;
			Node *node=EntireLookup((yyvsp[-3].simulateNode).idname,top);
			if(strcmp(node->kind,"constant")==0){ semError=1;
			//Constant variable %s can not be assigned
            printf("%d o͡͡͡͡͡͡╮(ꐦ ꈨຶ皿ꈨຶ)╭o͡͡͡͡͡͡ : Symbolic Cat Face %s can not be assigned.\n", linenum,(yyvsp[-3].simulateNode).idname);}
			else if(strcmp(id1,"real")==0 && strcmp(id3,"integer")==0)
			{
				
				for(i=0;pch1[i]!=NULL || pch3[i]!=NULL;i++)
				{
					
					if(pch1[i]==NULL||pch3[i]==NULL) same=0;
					else if(strcmp(pch1[i],pch3[i])!=0) same=0; 
				}
				strcat(content,"i2f\n");
				if(node->level==0)
				publicStore((yyvsp[-3].simulateNode).idname,(yyvsp[-3].simulateNode).type);
				else
				localStore((yyvsp[-3].simulateNode).idname,(yyvsp[-3].simulateNode).type);						
			}		
			else if(strcmp((yyvsp[-3].simulateNode).type,(yyvsp[-1].forE).type)!=0){ semError=1;
			//Assign statement mismatch Left
            printf("%d (۶ૈ ۜ ᵒ̌▱๋ᵒ̌ )۶ૈ=͟͟͞͞ ⌨ : Assign Face statement mismatch Left: %s Right: %s.\n", linenum,(yyvsp[-3].simulateNode).type, (yyvsp[-1].forE).type);}
			else{
				if(node->level==0)
				publicStore((yyvsp[-3].simulateNode).idname,(yyvsp[-3].simulateNode).type);
				else
				localStore((yyvsp[-3].simulateNode).idname,(yyvsp[-3].simulateNode).type);				
			}
			if(same==0){ semError=1;
                //Assign statement mismatch Left
                printf("%d (۶ૈ ۜ ᵒ̌▱๋ᵒ̌ )۶ૈ=͟͟͞͞ ⌨ : Assign Face statement mismatch Left: %s Right: %s.\n", linenum,(yyvsp[-3].simulateNode).type, (yyvsp[-1].forE).type);}
			}
		}
	}
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 716 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].forE).type!=NULL)
			if(strcmp((yyvsp[-1].forE).type,"real")!=0 && strcmp((yyvsp[-1].forE).type,"boolean")!=0 && strcmp((yyvsp[-1].forE).type,"integer")!=0 && strcmp((yyvsp[-1].forE).type,"string")!=0){ semError=1;
			//Print statement operand is array type
            printf("%d o͡͡͡͡͡͡╮(ꐦ ꈨຶ皿ꈨຶ)╭o͡͡͡͡͡͡ : Long Eyelash Face statement operand is in a Fish type.\n", linenum);}
			else{
			 strcat(content,"invokevirtual java/io/PrintStream/print(");
			 if(!strcmp((yyvsp[-1].forE).type,"string")) strcat(content,"Ljava/lang/String;");
			 else if(!strcmp((yyvsp[-1].forE).type,"integer")) strcat(content,"I");
			 else if(!strcmp((yyvsp[-1].forE).type,"boolean")) strcat(content,"Z");
			 else strcat(content,"F");
			 strcat(content,")V\n");
			}
	}
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 730 "parser.y" /* yacc.c:1646  */
    {strcat(content,"getstatic java/lang/System/out Ljava/io/PrintStream;\n");}
#line 2318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 732 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].simulateNode).type!=NULL)
			if(strcmp((yyvsp[-1].simulateNode).type,"real")!=0 && strcmp((yyvsp[-1].simulateNode).type,"boolean")!=0 && strcmp((yyvsp[-1].simulateNode).type,"integer")!=0 && strcmp((yyvsp[-1].simulateNode).type,"string")!=0)
			{ semError=1;
			//Read statement operand is array type
            printf("%d ( ｰ̀εｰ́ ): Dot Cheek Face statement operand is in a Fish type.\n", linenum);}
			else
			{
			 strcat(content,"getstatic ");
			 //printf("hello:%s\n",filename);
			 strcat(content,filename);
			 strcat(content,"/_sc Ljava/util/Scanner;\n");
			 strcat(content,"invokevirtual java/util/Scanner/");
			 if(!strcmp((yyvsp[-1].simulateNode).type,"integer"))
			  strcat(content,"nextInt()I\n");
			 else if(!strcmp((yyvsp[-1].simulateNode).type,"boolean"))
			  strcat(content,"nextBoolean()Z\n");
			 else
			  strcat(content,"nextFloat()F\n");
			 if((yyvsp[-1].simulateNode).level==0)
			  publicStore((yyvsp[-1].simulateNode).idname,(yyvsp[-1].simulateNode).type);
			 else
			  localStore((yyvsp[-1].simulateNode).idname,(yyvsp[-1].simulateNode).type);
			

			}
	}
#line 2350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 760 "parser.y" /* yacc.c:1646  */
    {
		Node *node=EntireLookup((yyvsp[0].idname),top);
		(yyval.simulateNode).idname=NULL;
		(yyval.simulateNode).type=NULL;
		if(node==NULL){ semError=1;
			// Variable does not exist
            printf("%d ⎧ᴿᴵᴾ⎫◟◟◟◟◟◟◟◟ ❀◟(ó ̯ ò, ): This Cat Face %s is dead.\n", linenum,(yyvsp[0].idname));}
		else
		{
			(yyval.simulateNode).idname=node->name;
			(yyval.simulateNode).type=node->type;
			(yyval.simulateNode).kind=node->kind;
			(yyval.simulateNode).attribute=node->attribute;
			(yyval.simulateNode).level=node->level;
		}
		
		
	}
#line 2373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 779 "parser.y" /* yacc.c:1646  */
    {
		
		(yyval.simulateNode).idname=NULL;
		(yyval.simulateNode).type=NULL;	
		Node *node=EntireLookup((yyvsp[-1].idname),top);
		if(node==NULL){ semError=1;
            // Variable does not exist
            printf("%d ⎧ᴿᴵᴾ⎫◟◟◟◟◟◟◟◟ ❀◟(ó ̯ ò, ): This Cat Face %s is dead.\n", linenum,(yyvsp[-1].idname));}
		else
		{
			(yyval.simulateNode).idname=node->name;
			char *pch;
			char *buffer=strdup(node->type);
			char *idname;
			idname=strtok(buffer,"[]");
			pch=strtok(NULL,"[]");
			(yyvsp[0].num)--;
			int error=1;
			while(pch!=NULL)
			{
				if((yyvsp[0].num)==0) { error=0; break;}
				pch=strtok(NULL,"[]");
				(yyvsp[0].num)--;
			}
			if(error){ semError=1;
				//Reference too much!(Out of Bound)
                printf("%d (✖╭╮✖) :You know too much.\n", linenum,(yyvsp[-1].idname));}
			else
			{
				pch=strtok(NULL,"");
				if(pch!=NULL)
					strcat(idname,pch);
				(yyval.simulateNode).type=idname;
			}
		}
		
		
	}
#line 2416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 817 "parser.y" /* yacc.c:1646  */
    { (yyval.num)=1; }
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 818 "parser.y" /* yacc.c:1646  */
    {(yyval.num)++;}
#line 2428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 827 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].simulateNode).type!=NULL && (yyvsp[0].simulateNode).idname!=NULL)
		{
			if(strcmp((yyvsp[0].simulateNode).type,"integer")!=0){ 
				semError=1;
                //Array index wrong type
                printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,(yyvsp[0].simulateNode).idname,(yyvsp[0].simulateNode).type);
            }
		}
	}
#line 2443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 838 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].all).type!=NULL && (yyvsp[0].all).idname!=NULL)
		{
			if(strcmp((yyvsp[0].all).type,"integer")!=0){ semError=1;
			//Array index wrong type
            printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,(yyvsp[0].all).idname,(yyvsp[0].all).type);}
		}
	}
#line 2456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 847 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].simulateNode).type!=NULL && (yyvsp[0].simulateNode).idname!=NULL)
		{
			if(strcmp((yyvsp[0].simulateNode).type,"integer")!=0){ semError=1;
                //Array index wrong type
                printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,(yyvsp[0].simulateNode).idname,(yyvsp[0].simulateNode).type);}
		}
	}
#line 2469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 856 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[0].forE).type!=NULL)
		{
			if(strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after - wrong type.\n
            printf("%d (#ಠQಠ#): Operand after Sub Dance Face can not be %s type.\n", linenum,(yyvsp[0].forE).type);}
			else if(!strcmp((yyvsp[0].forE).type,"integer"))
			{
				strcat(content,"ineg\n");
				(yyval.forE).type=(yyvsp[0].forE).type;
			}
			else
			{
				strcat(content,"fneg\n");
				(yyval.forE).type=(yyvsp[0].forE).type;
			}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 877 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")==0 && strcmp((yyvsp[0].forE).type,"integer")==0)
			{	
				(yyval.forE).type=(yyvsp[-2].forE).type; strcat(content,"imul\n");
			}
			else if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0)
			{ 	semError=1;
				//printf(Operands between * wrong type
            	printf("%d ˚‧º·(˚ ˃̣̣̥᷄⌓˂̣̣̥᷅ )‧º·˚: Operand after Mulo Dance Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);
            }
			else if(!strcmp((yyvsp[-2].forE).type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+(yyvsp[-2].forE).pointer);
				content[(yyvsp[-2].forE).pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fmul\n");
				(yyval.forE).type="real";
			}
			else if(!strcmp((yyvsp[0].forE).type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fmul\n");
				(yyval.forE).type="real";
			}
			else
			{
				strcat(content,"fmul\n");
				(yyval.forE).type="real";
			}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 915 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")==0 && strcmp((yyvsp[0].forE).type,"integer")==0)
			{	(yyval.forE).type=(yyvsp[-2].forE).type; strcat(content,"idiv\n");}
			else if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0)
			{ 	semError=1;
				//Operands between / wrong type
            	printf("%d o(o･`з･´o)ﾉ: Operand between And Face can not be %s/%s type\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);
			}
			else if(!strcmp((yyvsp[-2].forE).type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+(yyvsp[-2].forE).pointer);
				content[(yyvsp[-2].forE).pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fdiv\n");
				(yyval.forE).type="real";
			}
			else if(!strcmp((yyvsp[0].forE).type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fdiv\n");
				(yyval.forE).type="real";
			}
			else
			{
				strcat(content,"fdiv\n");
				(yyval.forE).type="real";
			}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 951 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")==0 && strcmp((yyvsp[0].forE).type,"integer")==0)
			{	(yyval.forE).type=(yyvsp[-2].forE).type; strcat(content,"irem\n");}
			else{ 
				semError=1; 
				//Operands between mod wrong type
            	printf("%d (*￣(ｴ)￣*): Operand between Mode Dance Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 965 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")==0 && strcmp((yyvsp[0].forE).type,"integer")==0)
			{	(yyval.forE).type=(yyvsp[-2].forE).type; strcat(content,"iadd\n");}
			else if(strcmp((yyvsp[-2].forE).type,"string")==0 && strcmp((yyvsp[0].forE).type,"string")==0)
				(yyval.forE).type=(yyvsp[-2].forE).type;
			else if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0)
			{	semError=1;
				//Operands between + wrong type
            	printf("%d ξ(｡◕ˇ◊ˇ◕｡)ξ: Operand between Add Dance Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);
            }
			else if(!strcmp((yyvsp[-2].forE).type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+(yyvsp[-2].forE).pointer);
				content[(yyvsp[-2].forE).pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fadd\n");
				(yyval.forE).type="real";
			}
			else if(!strcmp((yyvsp[0].forE).type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fadd\n");
				(yyval.forE).type="real";
			}
			else
			{
				strcat(content,"fadd\n");
				(yyval.forE).type="real";
			}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1003 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")==0 && strcmp((yyvsp[0].forE).type,"integer")==0)
			{	(yyval.forE).type=(yyvsp[-2].forE).type; strcat(content,"isub\n");}
			else if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
                //Operand after - wrong type.\n
                printf("%d (#ಠQಠ#): Operand after Sub Dance Face can not be %s type.\n", linenum,(yyvsp[0].forE).type);}
            
			else if(!strcmp((yyvsp[-2].forE).type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+(yyvsp[-2].forE).pointer);
				content[(yyvsp[-2].forE).pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fsub\n");
				(yyval.forE).type="real";
			}
			else if(!strcmp((yyvsp[0].forE).type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fsub\n");
				(yyval.forE).type="real";
			}
			else
			{
				strcat(content,"fsub\n");
				(yyval.forE).type="real";
			}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1038 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after < wrong type
            printf("%d ／(￣ ∈∋ ￣)＼: Operand after Hands Up and Face Right can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("iflt",L1,L2);
				(yyval.forE).type="boolean";
			}
		}
	}
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1072 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after <= wrong type
            printf("%d (ↀДↀ): Operand after Fork Hand Directing to Right can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
								char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifle",L1,L2);
				(yyval.forE).type="boolean";
			}
		}
	}
#line 2751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1106 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after = wrong type
            printf("%d ๐·°(৹˃̵﹏˂̵৹)°·๐: Operand after Equal Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifeq",L1,L2);
				(yyval.forE).type="boolean";
			}
		}
	}
#line 2789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1140 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after >= wrong type
            printf("%d ( ᵒ̴̶̷̥́ _ᵒ̴̶̷̣̥̀ ): Operand after Hand Directing to Left can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifge",L1,L2);
				(yyval.forE).type="boolean";
			}
		}
	}
#line 2827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1174 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand after > wrong type
            printf("%d（　(≪●≫)　）Д（　(≪●≫)　） : Operand after Hands Up and Face Left can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifgt",L1,L2);
				

				(yyval.forE).type="boolean";
			}
		}
	}
#line 2867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1210 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"integer")!=0 && strcmp((yyvsp[-2].forE).type,"real")!=0 || strcmp((yyvsp[0].forE).type,"integer")!=0 && strcmp((yyvsp[0].forE).type,"real")!=0){ semError=1;
			//Operand between <> wrong type
            printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{
				if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp((yyvsp[-2].forE).type,"real") && !strcmp((yyvsp[0].forE).type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+(yyvsp[-2].forE).pointer);
					content[(yyvsp[-2].forE).pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp((yyvsp[-2].forE).type,"integer") && !strcmp((yyvsp[0].forE).type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifne",L1,L2);
				(yyval.forE).type="boolean";
			}
		}
	}
#line 2905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1244 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[0].forE).type!=NULL)
		{
			if(strcmp((yyvsp[0].forE).type,"boolean")!=0){ semError=1;
			//Operand after not wrong type
            printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand after Not Face can not be %s type.\n", linenum,(yyvsp[0].forE).type);}
			else
			{	(yyval.forE).type="boolean"; strcat(content,"ixor\n");}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1257 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"boolean")!=0 && strcmp((yyvsp[0].forE).type,"boolean")!=0){ semError=1;
                //Operand between <> wrong type
                printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{	(yyval.forE).type="boolean"; strcat(content,"iand\n");}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1270 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forE).type=NULL;
		if((yyvsp[-2].forE).type!=NULL && (yyvsp[0].forE).type!=NULL )
		{
			if(strcmp((yyvsp[-2].forE).type,"boolean")!=0 && strcmp((yyvsp[0].forE).type,"boolean")!=0){ semError=1;
                //Operand between <> wrong type
                printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,(yyvsp[-2].forE).type,(yyvsp[0].forE).type);}
			else
			{	(yyval.forE).type="boolean"; strcat(content,"ior\n");}
		}
		(yyval.forE).pointer=strlen(content);
	}
#line 2956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1282 "parser.y" /* yacc.c:1646  */
    {(yyval.forE).type=(yyvsp[0].forE).type; (yyval.forE).pointer=(yyvsp[0].forE).pointer; }
#line 2962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1283 "parser.y" /* yacc.c:1646  */
    {(yyval.forE).type=(yyvsp[-1].forE).type; (yyval.forE).pointer=(yyvsp[-1].forE).pointer; }
#line 2968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1284 "parser.y" /* yacc.c:1646  */
    {(yyval.forE).type=(yyvsp[0].all).type; (yyval.forE).pointer=strlen(content);}
#line 2974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1285 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].simulateNode).idname;(yyval.all).type=(yyvsp[0].simulateNode).type;
	loadFunc((yyvsp[0].simulateNode).idname,(yyvsp[0].simulateNode).type,(yyvsp[0].simulateNode).attribute);
	
	}
#line 2983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1289 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].all).idname;(yyval.all).type=(yyvsp[0].all).type;
		loadConst((yyvsp[0].all).idname,(yyvsp[0].all).type);}
#line 2990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1291 "parser.y" /* yacc.c:1646  */
    {(yyval.all).idname=(yyvsp[0].simulateNode).idname;(yyval.all).type=(yyvsp[0].simulateNode).type;
	      loadVar((yyvsp[0].simulateNode).idname,(yyvsp[0].simulateNode).kind,(yyvsp[0].simulateNode).type,(yyvsp[0].simulateNode).attribute,(yyvsp[0].simulateNode).level);
		}
#line 2998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1295 "parser.y" /* yacc.c:1646  */
    {
		
		(yyval.simulateNode).idname=(yyvsp[-3].simulateNode).idname;
		(yyval.simulateNode).type=(yyvsp[-3].simulateNode).type;
		(yyval.simulateNode).attribute=(yyvsp[-3].simulateNode).attribute;
		
	}
#line 3010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1302 "parser.y" /* yacc.c:1646  */
    {
		Node *node=EntireLookup((yyvsp[0].idname),top);
		(yyval.simulateNode).idname=(yyvsp[0].idname);
		(yyval.simulateNode).type=NULL;
		if(node==NULL){ semError=1;
		//Function %s does not exist
        printf("%d ฅ=͟͟͞͞((꒪∆꒪;)ฅ : This Heart Eye Face %s does not exist.\n", linenum,(yyvsp[0].idname));}
		else
		{
		 (yyval.simulateNode).type=node->type;
		 (yyval.simulateNode).attribute=node->attribute;
		}
	}
#line 3028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1317 "parser.y" /* yacc.c:1646  */
    {(yyval.idname)=strdup((yyvsp[(-1) - (1)].simulateNode).attribute);
	   char *pch;
	   pch=strtok((yyval.idname),",");
	   if(pch!=NULL)
	   {
		if(!strcmp(pch,"real")&&!strcmp((yyvsp[0].forE).type,"integer"))
		strcat(content,"i2f\n");
		else if(strcmp(pch,(yyvsp[0].forE).type)!=0)
		{ semError=1;
		//Parameter mismatch
        printf("%d (☉ε　⊙ﾉ)ﾉ: Pet Face mismatch.\n", linenum);}
	   }
	  }
#line 3046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1331 "parser.y" /* yacc.c:1646  */
    { 		
		(yyval.idname)=(yyvsp[-2].idname);
		char *pch=strtok((yyval.idname),","); 
		if(pch!=NULL)
		{
		 if(!strcmp(pch,"real")&&!strcmp((yyvsp[0].forE).type,"integer"))
		  strcat(content,"i2f\n");
		 else if(strcmp(pch,(yyvsp[0].forE).type)!=0)
		 { semError=1;
             //Parameter mismatch
             printf("%d (☉ε　⊙ﾉ)ﾉ: Pet Face mismatch.\n", linenum);}
		}
	}
#line 3064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1345 "parser.y" /* yacc.c:1646  */
    {
	strcat(content,(yyvsp[-4].forLabel));
	strcat(content,":\n");
}
#line 3073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1350 "parser.y" /* yacc.c:1646  */
    {
	if(!strcmp((yyvsp[-1].forE).type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy((yyval.forLabel),L1);
}
#line 3088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1361 "parser.y" /* yacc.c:1646  */
    {
	if(!strcmp((yyvsp[0].forE).type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy((yyval.forLabel),L1);
}
#line 3103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1372 "parser.y" /* yacc.c:1646  */
    {
	if(!strcmp((yyvsp[-1].all).type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy((yyval.forLabel),L1);
}
#line 3118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1383 "parser.y" /* yacc.c:1646  */
    {
	if(!strcmp((yyvsp[0].all).type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy((yyval.forLabel),L1);
}
#line 3133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1394 "parser.y" /* yacc.c:1646  */
    {
	char L2[10];
	createLabel(L2);
	strcat(content,"goto ");
	strcat(content,L2);
	strcat(content,"\n");
	strcat(content,(yyvsp[(-1) - (1)].forLabel));
	strcat(content,":\n");
	strcpy((yyval.forLabel),L2);
}
#line 3148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1405 "parser.y" /* yacc.c:1646  */
    {
	strcat(content,(yyvsp[-4].forLabel));
	strcat(content,":\n");
}
#line 3157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1411 "parser.y" /* yacc.c:1646  */
    {
	strcat(content,"goto ");
	strcat(content,(yyvsp[-5].forLabel));
	strcat(content,"\n");
	strcat(content,(yyvsp[-4].forLabel));
	strcat(content,":\n");
}
#line 3169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1419 "parser.y" /* yacc.c:1646  */
    {
	char L1[10];
	createLabel(L1);
	strcat(content,L1);
	strcat(content,":\n");
	strcpy((yyval.forLabel),L1);
}
#line 3181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1427 "parser.y" /* yacc.c:1646  */
    {
		if(fortop!=NULL)
		{
			Node *node=fortop->next;
			free(fortop);
			fortop=node;
		}
		loadVar((yyvsp[-4].forFor).idname,"variable","integer","",1);
		strcat(content,"sipush 1\niadd\n");
		localStore((yyvsp[-4].forFor).idname,"integer");
		strcat(content,"goto ");
		strcat(content,(yyvsp[-4].forFor).back);
		strcat(content,"\n");
		strcat(content,(yyvsp[-4].forFor).next);
		strcat(content,":\n");
		ltop=freeLocal(ltop);
	}
#line 3203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1445 "parser.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].num)<0){ semError=1;
		//lower bound can not be negative
        printf("%d (งಠ_ಠ)ง: It’s too sad.\n", linenum);}
		if((yyvsp[0].num)<0){ semError=1;
        //lower bound can not be negative
        printf("%d (งಠ_ಠ)ง: It’s too sad.\n", linenum);}
		if((yyvsp[0].num)-(yyvsp[-2].num)<=0){ semError=1;
		//lower bound can not be bigger or equal than upper bound
        printf("%d (งಠ_ಠ)ง: You are sadder than happiness.\n", linenum);}
		if(lookupNode((yyvsp[-4].idname),fortop)==NULL)
		{	
			char num[10],num1[10];
			sprintf(num,"%d",(yyvsp[-2].num));
			sprintf(num1,"%d",(yyvsp[0].num));

			fortop=addFromNode(fortop,(yyvsp[-4].idname),"","","",level);
			ltop=addBlock(ltop);
			ltop=addLocal(ltop,(yyvsp[-4].idname));
			strcat(content,"sipush ");
			strcat(content,num);
			strcat(content,"\n");
			localStore((yyvsp[-4].idname),"integer");
			char L1[10],L2[10];
			createLabel(L1);
			createLabel(L2);
			strcat(content,L1);
			strcat(content,":\n");
			strcat(content,"sipush ");
			strcat(content,num1);
			strcat(content,"\n");
			loadVar((yyvsp[-4].idname),"variable","integer","",1);
			strcat(content,"isub\n");
			strcat(content,"ifle ");
			strcat(content,L2);
			strcat(content,"\n");
			strcpy((yyval.forFor).back,L1);
			strcpy((yyval.forFor).next,L2);
			(yyval.forFor).idname=(yyvsp[-4].idname);			
		}
		else{ semError=1;
		//Variable has been assigned at the outer loop
        printf("%d ୧(๑•̀ᗝ•́)૭ : The cat is found elsewhere.\n", linenum);}
	}
#line 3252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1490 "parser.y" /* yacc.c:1646  */
    {
		if(isFunc && funcname!=NULL)
		{
			char *returntype=(yyvsp[-1].forE).type;
			Node *node=LookupGlobal(funcname,top);
			if(strcmp(node->type,"void")==0){ semError=1;
			//Function type void does not need return statement
            printf("%d ヾ( ･`⌓´･)ﾉﾞ: How dare you give me that face! \n", linenum);}
			else if(!strcmp(node->type,"real") && !strcmp(returntype,"integer"))
			{
			  strcat(content,"i2f\n");
			  strcat(content,"freturn\n");
			}
			else if(strcmp(node->type,returntype)!=0){ semError=1;
                //Function type is different from the return type
            printf("%d (ﾉ｀Д´)ﾉ : Could you give me another breed?\n", linenum);}
			else
			{
			 if(!strcmp(returntype,"real"))
			  strcat(content,"freturn\n");
			 else
			  strcat(content,"ireturn\n");
			}
		}
		if(isMain){ semError=1;
		//Main function can not have return statement
        printf("%d ┗(｀ム´)=З : How dare you give me that face! \n", linenum);}
	}
#line 3285 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3289 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1520 "parser.y" /* yacc.c:1906  */






int yyerror( char *msg )
{
    fprintf( stderr, "\n|--------------------------------------------------------------------------\n" );
    fprintf( stderr, "（（（（（（BOMB）））））） ⌒⌒⌒⌒⌒／(x~x)＼ %d: %s\n", linenum, buf );
	fprintf( stderr, "|\n" );
	fprintf( stderr, "( ✖ ਊ ✖) %s\n", yytext );
        fprintf( stderr, "|--------------------------------------------------------------------------\n" );
        exit(-1);
}

int  main( int argc, char **argv )
{
	
	if( argc != 2 ) {
		fprintf(  stdout,  "Usage:  ./parser  [filename]\n"  );
		exit(0);
	}
	semError=0;
	ltop=createLocal();
	top=creates();
        fortop=createNode();
	char *buffer,*buffer2;
	labelNumber=0;
	buffer=(char*)malloc(sizeof(argv[1])-sizeof(char)*2);
	strncpy(buffer,argv[1],strlen(argv[1])-2);
	buffer2=strtok(buffer,"/");
	while(buffer2!=NULL)
	{
		strcpy(filename,buffer2);
		buffer2=strtok(NULL,"/");
	}

	FILE *fp = fopen( argv[1], "r" );
	
	if( fp == NULL )  {
		fprintf( stdout, "Open  file  error\n" );
		exit(-1);
	}

	yyin = fp;
	yyparse();
	if(!semError){
        FILE *fptr;
	strcat(filename,".j");
	fptr=fopen(filename,"w");
        fwrite(content,1,strlen(content),fptr);
	fclose(fptr);
	}
	exit(0);
}
