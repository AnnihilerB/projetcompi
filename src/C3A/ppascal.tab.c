/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "ppascal.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include "analyseur.h"
    #include "util.h"
    int yyerror(char* s);
    int yylex();
    BILENV ListeVariablesGLOBALES;
    BILFON ListeFonctionsGLOBALES;
    BILENV ListeVariablesLOCALES;
    char* fonctionActuel;       //dans quelle fonction se passe le code
    enum erreurs {NON_DEFINIE = 1, MAUVAIS_TYPE, MAUVAIS_TYPE_RETOUR, TYPES_DIFFERENT};
    int estDansFonction;

    void renvoyer_erreur(char* nom, int erreur);
    int verification_type_et_existence(char* nom1, char* nom2,ENV env1, ENV env2);
    int verification_appel_fonction (LFON fonction, NOE args);
    extern  void setEnv(EnvGlobal env);
    int numeroLigne = 0;

#line 87 "ppascal.tab.c" /* yacc.c:339  */

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
   by #include "ppascal.tab.h".  */
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
#line 22 "ppascal.y" /* yacc.c:355  */

        EnvGlobal envG;
        BILFON fonctionOuProcedure;
        BILENV varG;
        LFON fon;
        ENV env;
        NOE noe;
        char* nom[2]; //yylval.nom[0] -> variable, yylval.nom[1] -> entier

#line 169 "ppascal.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PPASCAL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 186 "ppascal.tab.c" /* yacc.c:358  */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      32,    33,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    45,    45,    54,    67,    80,    93,   106,   118,   125,
     137,   151,   160,   161,   170,   171,   172,   184,   198,   200,
     214,   229,   230,   231,   232,   233,   236,   250,   251,   252,
     266,   278,   316,   317,   319,   320,   322,   323,   325,   326,
     328,   330,   331,   332,   334,   335,   342,   343,   345,   347,
     349,   350,   352,   353
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_boo", "T_int", "Def", "Dep", "Af",
  "true", "false", "Se", "If", "Th", "El", "Var", "Wh", "Do", "Pl", "Mo",
  "Mu", "And", "Or", "Not", "Lt", "Eq", "Sk", "NFon", "NPro", "NewAr", "I",
  "V", "T_ar", "'('", "')'", "'['", "']'", "'{'", "'}'", "','", "':'",
  "$accept", "MP", "E", "Et", "C", "Ca", "L_args", "L_argsnn", "L_argt",
  "L_argtnn", "Argt", "TP", "L_vart", "L_vartnn", "D_entp", "D_entf", "D",
  "LD", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    40,    41,    91,    93,   123,   125,    44,    58
};
# endif

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,   -16,    19,   -61,    -8,   -11,   -61,   -61,     2,    23,
       8,    24,    25,    78,    78,   -61,    -3,    53,     9,    44,
     -61,    -9,    -9,   -61,   -16,   -61,   -61,     8,   -61,    30,
      33,   -61,   -61,    78,     8,   -61,   -10,    78,   148,    22,
     157,    78,    78,    78,    10,    78,    78,    53,    53,    53,
     -61,   -61,   -16,   -16,   -61,    35,    78,   131,    53,    78,
      78,    78,    78,    78,    78,    78,    55,   165,    94,    34,
     -61,   102,   -61,   165,   110,   -61,    44,    44,    46,    52,
     -61,    49,    78,    59,   -61,     5,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,    14,    53,   -61,    78,   -61,   -61,
     -61,    54,   -16,   -61,   123,   -61,    55,    26,   -61,     8,
     -61,   -61,   -61,   -61,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      44,     0,     0,    52,    45,     0,    46,     1,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     2,
      25,    44,    44,    53,     0,    41,    42,     0,    40,     0,
       0,    14,    15,     0,     0,    12,    13,     0,     0,    18,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
      47,    43,    36,    36,    10,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    34,     0,
      33,     0,    23,    30,     0,    21,    50,    51,     0,    37,
      38,     0,     0,     0,    11,     0,     3,     4,     5,     9,
       6,     7,     8,    28,     0,     0,    26,     0,    24,    19,
      20,     0,     0,    48,     0,    16,     0,     0,    35,     0,
      39,    17,    29,    27,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,    12,    -7,   -14,   -60,    40,    -2,    45,   -61,
      -1,   -25,    39,   -61,   -61,   -61,   -61,   -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    68,    39,    19,    20,    69,    70,    78,    79,
      80,    28,     3,     4,    21,    22,    23,     8
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       6,    18,    51,    44,    41,     1,    96,    11,    12,    55,
      18,    25,    26,    13,     5,    47,    45,    14,   106,     7,
      47,    41,    56,    50,    43,    38,    40,    15,    10,    42,
       9,    43,    16,    75,    76,    77,    47,    24,    17,    27,
      18,    18,    18,    46,    85,    54,   112,    72,    43,    57,
      29,    18,    30,    67,    47,    71,    46,    73,    74,    18,
      48,    49,    52,   113,    13,    53,    13,    98,    14,    82,
      14,    86,    87,    88,    89,    90,    91,    92,    15,   101,
      93,   107,   103,    16,   114,    94,    31,    32,    18,    17,
     102,    95,   105,   109,   104,   108,    83,     0,    81,    18,
      33,   110,     0,     0,     0,     0,    34,    35,    36,     0,
      37,    59,    60,    61,    62,    63,     0,    64,    65,    59,
      60,    61,    62,    63,     0,    64,    65,    59,    60,    61,
      62,    63,    97,    64,    65,     0,     0,    99,     0,     0,
      59,    60,    61,    62,    63,   100,    64,    65,    59,    60,
      61,    62,    63,     0,    64,    65,     0,     0,   111,     0,
      58,     0,     0,     0,    84,    59,    60,    61,    62,    63,
       0,    64,    65,    66,    59,    60,    61,    62,    63,     0,
      64,    65,    59,    60,    61,    62,    63,     0,    64,    65
};

static const yytype_int8 yycheck[] =
{
       1,     8,    27,    17,     7,    14,    66,     5,     6,    34,
      17,     3,     4,    11,    30,    10,     7,    15,    13,     0,
      10,     7,    32,    24,    34,    13,    14,    25,    39,    32,
      38,    34,    30,    47,    48,    49,    10,    14,    36,    31,
      47,    48,    49,    34,    58,    33,   106,    37,    34,    37,
      26,    58,    27,    41,    10,    43,    34,    45,    46,    66,
      21,    22,    32,    37,    11,    32,    11,    33,    15,    34,
      15,    59,    60,    61,    62,    63,    64,    65,    25,    33,
      25,    95,    33,    30,   109,    30,     8,     9,    95,    36,
      38,    36,    33,    39,    82,    97,    56,    -1,    53,   106,
      22,   102,    -1,    -1,    -1,    -1,    28,    29,    30,    -1,
      32,    17,    18,    19,    20,    21,    -1,    23,    24,    17,
      18,    19,    20,    21,    -1,    23,    24,    17,    18,    19,
      20,    21,    38,    23,    24,    -1,    -1,    35,    -1,    -1,
      17,    18,    19,    20,    21,    35,    23,    24,    17,    18,
      19,    20,    21,    -1,    23,    24,    -1,    -1,    35,    -1,
      12,    -1,    -1,    -1,    33,    17,    18,    19,    20,    21,
      -1,    23,    24,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    17,    18,    19,    20,    21,    -1,    23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    41,    52,    53,    30,    50,     0,    57,    38,
      39,     5,     6,    11,    15,    25,    30,    36,    43,    44,
      45,    54,    55,    56,    14,     3,     4,    31,    51,    26,
      27,     8,     9,    22,    28,    29,    30,    32,    42,    43,
      42,     7,    32,    34,    44,     7,    34,    10,    52,    52,
      50,    51,    32,    32,    42,    51,    32,    42,    12,    17,
      18,    19,    20,    21,    23,    24,    16,    42,    42,    46,
      47,    42,    37,    42,    42,    44,    44,    44,    48,    49,
      50,    48,    34,    46,    33,    44,    42,    42,    42,    42,
      42,    42,    42,    25,    30,    36,    45,    38,    33,    35,
      35,    33,    38,    33,    42,    33,    13,    44,    47,    39,
      50,    35,    45,    37,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    43,
      43,    44,    44,    44,    44,    44,    45,    45,    45,    45,
      45,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      50,    51,    51,    51,    52,    52,    53,    53,    54,    55,
      56,    56,    57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     4,     5,     1,     4,
       4,     3,     1,     3,     4,     1,     4,     3,     1,     6,
       3,     3,     0,     1,     1,     3,     0,     1,     1,     3,
       3,     1,     1,     2,     0,     1,     2,     4,     5,     7,
       3,     3,     0,     2
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
        case 2:
#line 45 "ppascal.y" /* yacc.c:1646  */
    {  printf("t_int : %d t_boo : %d et t_ar: %d et Nfon: %d\n",T_int, T_boo, T_ar, NFon);
                    (yyval.envG)=creer_environnementGlobal();
                    (yyval.envG)->variablesGlobales = (yyvsp[-2].varG);
                    (yyval.envG)->listeDesFonctionsOuProcedure = (yyvsp[-1].fonctionOuProcedure);
                    (yyval.envG)->corpsGlobale = (yyvsp[0].noe);
                    //interpreteur($$);
                    //ecrire_prog($$->variablesGlobales, $$->listeDesFonctionsOuProcedure, $$->corpsGlobale);
                }
#line 1355 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 54 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "addition possible seulement entre integer\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Pl; (yyval.noe)->FD =  (yyvsp[0].noe);
            }
#line 1372 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 67 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "soustraction possible seulement entre integer\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Mo; (yyval.noe)->FD =  (yyvsp[0].noe);
             }
#line 1389 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 80 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "multiplication possible seulement entre integer\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Mu; (yyval.noe)->FD =  (yyvsp[0].noe);
             }
#line 1406 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_boo && env2->type.type != T_boo)
                {
                    fprintf(stderr, "ou possible seulement entre boolean\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Or; (yyval.noe)->FD =  (yyvsp[0].noe);
             }
#line 1423 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "comparaison possible seulement entre integer\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Lt; (yyval.noe)->FD =  (yyvsp[0].noe);
             }
#line 1440 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 118 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Eq; (yyval.noe)->FD =  (yyvsp[0].noe);
             }
#line 1452 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 125 "ppascal.y" /* yacc.c:1646  */
    { 
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_boo && env2->type.type != T_boo)
                {
                    fprintf(stderr, "and possible seulement entre boolean\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = And; (yyval.noe)->FD =  (yyvsp[0].noe);
              }
#line 1469 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 137 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (env == NULL)
                {
                    renvoyer_erreur((yyvsp[0].noe)->ETIQ, NON_DEFINIE);
                    return 1;
                }
                if (env->type.type != T_boo)
                {
                    fprintf(stderr, "not possible seulement avec un boolean\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->codop = Not; (yyval.noe)->FD = (yyvsp[0].noe);
            }
#line 1488 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "ppascal.y" /* yacc.c:1646  */
    {
                    ENV env = existe((yyvsp[-1].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                    if (env == NULL)
                    {
                        renvoyer_erreur((yyvsp[-1].noe)->ETIQ, NON_DEFINIE);
                        return 1;
                    }                    
                    (yyval.noe) = (yyvsp[-1].noe);
                }
#line 1502 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 160 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = I; (yyval.noe)->ETIQ = yylval.nom[1];}
#line 1508 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 161 "ppascal.y" /* yacc.c:1646  */
    {
            ENV env = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            if (env == NULL)
            {
                renvoyer_erreur((yyvsp[0].noe)->ETIQ, NON_DEFINIE);
                return 1;
            }
            (yyval.noe) = (yyvsp[0].noe);
        }
#line 1522 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 170 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = T_boo; (yyval.noe)->ETIQ = "true";}
#line 1528 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 171 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = T_boo; (yyval.noe)->ETIQ = "false";}
#line 1534 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 172 "ppascal.y" /* yacc.c:1646  */
    {
                            LFON fonction = rechercher_lfon((yyvsp[-3].noe)->ETIQ,ListeFonctionsGLOBALES.debut);
                            if (fonction == NULL)
                            {
                                renvoyer_erreur((yyvsp[-3].noe)->ETIQ, NON_DEFINIE);
                                return 1;
                            }
                            if (verification_appel_fonction(fonction, (yyvsp[-1].noe)) != 0)
                                return 1;
                            (yyval.noe) = Nalloc(); (yyval.noe)->codop = NFon; (yyval.noe)->ETIQ = (yyvsp[-3].noe)->ETIQ; (yyval.noe)->FG = (yyvsp[-1].noe); (yyval.noe)->FD = NULL;
                            
                       }
#line 1551 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 184 "ppascal.y" /* yacc.c:1646  */
    {
                            ENV env = existe((yyvsp[-1].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                            if (env == NULL)
                            {
                                renvoyer_erreur((yyvsp[-1].noe)->ETIQ, NON_DEFINIE);
                                return 1;
                            }
                            if (env->type.type != T_int)
                            {
                                fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                                return 1;
                            }
                            (yyval.noe) = Nalloc(); (yyval.noe)->codop = NewAr; (yyval.noe)->FG = (yyvsp[-3].noe); (yyval.noe)->FD = (yyvsp[-1].noe);
                         }
#line 1570 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 198 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = (yyvsp[0].noe);}
#line 1576 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 200 "ppascal.y" /* yacc.c:1646  */
    {   
                    ENV env = existe((yyvsp[-1].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                    if (env == NULL)
                    {
                        renvoyer_erreur((yyvsp[-1].noe)->ETIQ, NON_DEFINIE);
                        return 1;
                    }
                    if (env->type.type != T_int)
                    {
                        fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                        return 1;
                    }
                    NOE v = Nalloc(); v->codop = V; v->ETIQ = (yyvsp[-3].noe)->ETIQ; (yyval.noe) = Nalloc(); (yyval.noe)->codop = V; (yyval.noe)->ETIQ = v->ETIQ; (yyval.noe)->FG = (yyvsp[-3].noe); (yyval.noe)->FD = (yyvsp[-1].noe); 
                }
#line 1595 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 214 "ppascal.y" /* yacc.c:1646  */
    {
                        ENV env = existe((yyvsp[-1].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                        if (env == NULL)
                        {
                            renvoyer_erreur((yyvsp[-1].noe)->ETIQ, NON_DEFINIE);
                            return 1;
                        }
                        if (env->type.type != T_int)
                        {
                            fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                            return 1;
                        }
                            (yyval.noe) = Nalloc() ;(yyval.noe)->FG = (yyvsp[-3].noe); (yyval.noe)->FD = (yyvsp[-1].noe); (yyval.noe)->ETIQ = (yyvsp[-3].noe)->ETIQ;
                    }
#line 1614 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 229 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->codop = Se; (yyval.noe)->FD = (yyvsp[0].noe);}
#line 1620 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 230 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = Sk;}
#line 1626 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 231 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = (yyvsp[-1].noe);}
#line 1632 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 232 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = NFon; (yyval.noe)->ETIQ = (yyvsp[-3].noe)->ETIQ; (yyval.noe)->FG = (yyvsp[-1].noe); (yyval.noe)->FD = NULL;}
#line 1638 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 233 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = (yyvsp[0].noe);}
#line 1644 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 236 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (env == NULL)
                {
                    renvoyer_erreur((yyvsp[-2].noe)->ETIQ, NON_DEFINIE);
                    return 1;
                }
                if (env->type.type != T_boo)
                {
                    fprintf(stderr, "la condition de la boucle while n'est pas un boolean\n");
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->codop = Wh; (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->FD = (yyvsp[0].noe);
              }
#line 1663 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 250 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = (yyvsp[-1].noe);}
#line 1669 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 251 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = Sk;}
#line 1675 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 252 "ppascal.y" /* yacc.c:1646  */
    {
                        ENV env = existe((yyvsp[-4].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                        if (env == NULL)
                        {
                            renvoyer_erreur((yyvsp[-4].noe)->ETIQ, NON_DEFINIE);
                            return 1;
                        }
                        if (env->type.type != T_boo)
                        {
                            fprintf(stderr, "la condition du if n'est pas un boolean\n");
                            return 1;
                        }
                        (yyval.noe) = Nalloc(); (yyval.noe)->codop = If; (yyval.noe)->FG = (yyvsp[-4].noe); NOE noeVide = Nalloc(); noeVide->FG = (yyvsp[-2].noe); noeVide->FD = (yyvsp[0].noe); (yyval.noe)->FD = noeVide;
                    }
#line 1694 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 266 "ppascal.y" /* yacc.c:1646  */
    {
                ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                {
                    printf("test: ");
                    ecrire_type(env1->type);
                    ecrire_type(env2->type);
                    return 1;
                }
                (yyval.noe) = Nalloc(); (yyval.noe)->codop = Af; (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->FD = (yyvsp[0].noe);
            }
#line 1711 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 278 "ppascal.y" /* yacc.c:1646  */
    {
            ENV env1 = existe((yyvsp[-2].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            ENV env2 = existe((yyvsp[0].noe), ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            if (fonctionActuel != NULL)
            {
                if (strcmp((yyvsp[-2].noe)->ETIQ, fonctionActuel) != 0)
                {
                    if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                        return 1;
                }
                else
                {
                    //comme on est dans le return, on vérifie qu'on retourne bien le bon type
                    LFON fonction = rechercher_lfon(fonctionActuel, ListeFonctionsGLOBALES.debut);
                    Type t = renvoie_type_fonction(fonction);
                    if (t.type == 0)    //procédure
                    {
                        fprintf(stderr, "%s est un procedure, n'a donc pas de valeur de retour", fonctionActuel);
                        return 1;
                    }
                    else if (env2 == NULL)
                    {
                        renvoyer_erreur((yyvsp[0].noe)->ETIQ, NON_DEFINIE);
                        return 1;
                    }
                    else if (compare_type(t, env2->type) != 1)
                    {
                        fprintf(stderr, "la fonction %s ne renvoie pas le bon type\n", fonctionActuel, env2->ID);
                        return 1;
                    }
                }
            }
            else if (verification_type_et_existence((yyvsp[-2].noe)->ETIQ,(yyvsp[0].noe)->ETIQ,env1, env2) != 0)
                    return 1;
            
            (yyval.noe) = Nalloc(); (yyval.noe)->codop = Af; (yyval.noe)->FG = (yyvsp[-2].noe); (yyval.noe)->FD = (yyvsp[0].noe); 
           }
#line 1753 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 316 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = NULL;}
#line 1759 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 317 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = (yyvsp[0].noe);}
#line 1765 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 319 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->FD = (yyvsp[0].noe); }
#line 1771 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 320 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->FD = (yyvsp[-2].noe); (yyval.noe)->FG = (yyvsp[0].noe);}
#line 1777 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 322 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = bilenv_vide();}
#line 1783 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 323 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = (yyvsp[0].varG);}
#line 1789 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 325 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = creer_bilenv((yyvsp[0].env));}
#line 1795 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 326 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = concat((yyvsp[-2].varG), creer_bilenv((yyvsp[0].env))); }
#line 1801 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 328 "ppascal.y" /* yacc.c:1646  */
    {(yyval.env) = Envalloc(); (yyval.env)->ID = (yyvsp[-2].noe)->ETIQ; (yyval.env)->type = renvoie_type_avec_un_noeudVariable((yyvsp[0].noe));}
#line 1807 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 330 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = T_boo;}
#line 1813 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 331 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = T_int;}
#line 1819 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 332 "ppascal.y" /* yacc.c:1646  */
    {(yyval.noe) = Nalloc(); (yyval.noe)->codop = T_ar; (yyval.noe)->FG = (yyvsp[0].noe);}
#line 1825 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 334 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = bilenv_vide();}
#line 1831 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 335 "ppascal.y" /* yacc.c:1646  */
    {    (yyval.varG) = (yyvsp[0].varG); 
                    if (estDansFonction == false)
                        ListeVariablesGLOBALES = (yyval.varG);
                    else
                        concat(ListeVariablesLOCALES, copier_bilenv((yyval.varG)));
               }
#line 1842 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 342 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = creer_bilenv((yyvsp[0].env));}
#line 1848 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 343 "ppascal.y" /* yacc.c:1646  */
    {(yyval.varG) = concat((yyvsp[-3].varG), creer_bilenv((yyvsp[0].env))); }
#line 1854 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 345 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fon) = Lfonalloc(); (yyval.fon)->ID = (yyvsp[-3].noe)->ETIQ; (yyval.fon)->PARAM = (yyvsp[-1].varG); ListeVariablesLOCALES = copier_bilenv((yyvsp[-1].varG)); estDansFonction = true; ListeFonctionsGLOBALES = concatfn(ListeFonctionsGLOBALES, creer_bilfon((yyval.fon))); fonctionActuel = (yyval.fon)->ID;}
#line 1860 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 347 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fon) = Lfonalloc(); (yyval.fon)->ID = (yyvsp[-5].noe)->ETIQ; ENV e = Envalloc(); e->ID = NULL; e->type = renvoie_type_avec_un_noeudVariable((yyvsp[0].noe)); (yyval.fon)->PARAM = concat(creer_bilenv(e), (yyvsp[-3].varG)); ListeVariablesLOCALES = copier_bilenv((yyvsp[-3].varG)); estDansFonction = true; ListeFonctionsGLOBALES = concatfn(ListeFonctionsGLOBALES, creer_bilfon((yyval.fon))); fonctionActuel = (yyval.fon)->ID;}
#line 1866 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 349 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fon) = Lfonalloc(); (yyval.fon)->ID = (yyvsp[-2].fon)->ID; (yyval.fon)->PARAM = (yyvsp[-2].fon)->PARAM; (yyval.fon)->VARLOC = (yyvsp[-1].varG); (yyval.fon)->CORPS = (yyvsp[0].noe);estDansFonction = false; ListeVariablesLOCALES = bilenv_vide(); fonctionActuel = NULL;}
#line 1872 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 350 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fon) = Lfonalloc(); (yyval.fon)->ID = (yyvsp[-2].fon)->ID; (yyval.fon)->PARAM = (yyvsp[-2].fon)->PARAM; (yyval.fon)->VARLOC = (yyvsp[-1].varG); (yyval.fon)->CORPS = (yyvsp[0].noe); estDansFonction = false; ListeVariablesLOCALES = bilenv_vide(); fonctionActuel = NULL;}
#line 1878 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 352 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fonctionOuProcedure) = bilfon_vide();}
#line 1884 "ppascal.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 353 "ppascal.y" /* yacc.c:1646  */
    {(yyval.fonctionOuProcedure) = concatfn((yyvsp[-1].fonctionOuProcedure), creer_bilfon((yyvsp[0].fon)));}
#line 1890 "ppascal.tab.c" /* yacc.c:1646  */
    break;


#line 1894 "ppascal.tab.c" /* yacc.c:1646  */
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
#line 357 "ppascal.y" /* yacc.c:1906  */

int verification_appel_fonction (LFON fonction, NOE args)
{
    if (fonction == NULL)
    {
        return -1;
    }
    int retour = 0;
    NOE noeudArg = args;
    ENV envFonction = fonction->PARAM.debut;
    if (envFonction != NULL && envFonction->ID == NULL)     //si c'est une fonction le premier arg est le type de retour
    {
        envFonction = envFonction->SUIV;
    }
    int erreur = 0;
    //ecrire_env(envFonction);
    int numArg = 1;
    while (noeudArg != NULL && envFonction != NULL)
    {
        ENV envNoeudArg = existe(noeudArg->FD, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
        //ecrire_env(envNoeudArg);
        if (envNoeudArg == NULL)
        {   
            erreur = 2;
            retour = 1;
            break;
        }
        if (compare_type(envNoeudArg->type, envFonction->type) != 1)
        {
            fprintf(stderr, "l'argument %d n'est pas du bon type, dans l'appel de la fonction %s\n", numArg, fonction->ID);
            erreur = 1;
            retour = 1;
            break;
        }
        noeudArg = noeudArg->FG;
        envFonction = envFonction->SUIV;
        numArg ++;
    }
    if (erreur != 1)
    {
        if (noeudArg != NULL || envFonction != NULL)
        {
            fprintf(stderr, "l'appel de %s ne contient pas le bon nombre d'arguments\n", fonction->ID);
            retour = 1;
        }
        else if (erreur == 2)
        {
            if (noeudArg != NULL)
                renvoyer_erreur(noeudArg->FD->ETIQ, NON_DEFINIE);
                
        }
    }
    return retour;
}

int verification_type_et_existence(char* nom1, char* nom2,ENV env1, ENV env2)
{
    int retour = 1;
    if (env1 == NULL || env2 == NULL)
    {
        if (env1 == NULL)
            renvoyer_erreur(nom1, NON_DEFINIE);
        if (env2 == NULL)
            renvoyer_erreur(nom2, NON_DEFINIE);
    }
    else     //ils existent, maintenant on vérifie les types
    {
        if (env1->type.type == 0)   //procédure
            renvoyer_erreur(nom1, MAUVAIS_TYPE_RETOUR);
        else if (env2->type.type == 0)
            renvoyer_erreur(nom2, MAUVAIS_TYPE_RETOUR);
        else if (compare_type(env1->type, env2->type) != 1)
        {
            fprintf(stderr, "%s et %s n'ont pas les même type\n", nom1, nom2);
        }
        else
            retour = 0;
    }
    return retour;
}
void renvoyer_erreur(char* nom, int erreur)
{

    if (nom != NULL)        
        fprintf(stderr, "%s ", nom);
        
    if (erreur == NON_DEFINIE)
        fprintf(stderr, "non definie");
    else if (erreur == MAUVAIS_TYPE)
        fprintf(stderr, "est du mauvais type");
    else if (erreur == MAUVAIS_TYPE_RETOUR)
        fprintf(stderr, "le type de retour est mauvais");
        
    fprintf(stderr, "\n");
    
}
int yyerror(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
int yywrap()
{
    return -1;
}
int main(int argn, char** argv)
{
    fonctionActuel = NULL;
    ListeVariablesLOCALES = bilenv_vide();
    ListeFonctionsGLOBALES = bilfon_vide();
    estDansFonction = false;
    if (yyparse() == 1)
        afficherLigne();
    return 0;
}
