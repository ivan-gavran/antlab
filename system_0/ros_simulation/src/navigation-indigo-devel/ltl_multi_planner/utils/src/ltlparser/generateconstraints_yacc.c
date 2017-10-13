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
#line 1 "generateconstraints.y" /* yacc.c:339  */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generateconstraints_yacc.h"

using namespace std;

int yylex();
int yyerror(char *s);
char* findProposition(char *);
void declareVariable(FILE * , char * , char * );

struct s
{
  char x[10000];
  char y[10000];
};

typedef struct s prop_t;

typedef std::vector<prop_t> prop_vec_t;

FILE *ofp1, *ofp2;
char str[10000];
char str1[10000], str2[10000];
unsigned int variable_count = 1;
unsigned int bounded_operator_count = 1;
unsigned int until_count = 1;
unsigned int release_count = 1;
int loop_count;
int length;
prop_vec_t propositions;
int lower_limit, upper_limit;
int count1, count2, count3;

#line 105 "y.tab.c" /* yacc.c:339  */

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

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONSTANT = 259,
    TRUE = 260,
    FALSE = 261,
    NEXT = 262,
    UNTIL = 263,
    RELEASE = 264,
    NOT = 265,
    OR = 266,
    AND = 267
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONSTANT 259
#define TRUE 260
#define FALSE 261
#define NEXT 262
#define UNTIL 263
#define RELEASE 264
#define NOT 265
#define OR 266
#define AND 267

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 41 "generateconstraints.y" /* yacc.c:355  */

  char s[10000];

#line 173 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 188 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   37

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  4
/* YYNRULES -- Number of rules.  */
#define YYNRULES  14
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  29

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   267

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
      13,    14,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    15,     2,    17,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    66,    70,    74,    78,   106,   140,   174,
     196,   245,   295,   546,   550
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT", "TRUE",
  "FALSE", "NEXT", "UNTIL", "RELEASE", "NOT", "OR", "AND", "'('", "')'",
  "'['", "','", "']'", "$accept", "formula", "main_formula",
  "constant_formula", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    40,    41,    91,    44,    93
};
# endif

#define YYPACT_NINF -6

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-6)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      22,    -6,    -6,    -6,    22,    22,    22,     5,    25,    -6,
       8,    -6,    -5,    -6,    11,    22,    22,    22,    -6,     4,
       8,     8,    -6,    -6,    -1,    18,    13,    22,    25
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,    13,    14,     0,     0,     0,     0,     2,     4,
       9,     6,     0,     1,     0,     0,     0,     0,     5,     0,
      10,    11,     8,     7,     0,     0,     0,     0,    12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -6,    -6,    -4,    -6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      10,    11,    12,    14,    15,    13,    16,    17,    24,    18,
      20,    21,    22,    23,     1,    25,     2,     3,     4,    16,
      17,     5,    26,    28,     6,     1,    19,     2,     3,     4,
      27,     0,     5,    14,    15,     6,    16,    17
};

static const yytype_int8 yycheck[] =
{
       4,     5,     6,     8,     9,     0,    11,    12,     4,    14,
      14,    15,    16,    17,     3,    16,     5,     6,     7,    11,
      12,    10,     4,    27,    13,     3,    15,     5,     6,     7,
      17,    -1,    10,     8,     9,    13,    11,    12
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    10,    13,    19,    20,    21,
      20,    20,    20,     0,     8,     9,    11,    12,    14,    15,
      20,    20,    20,    20,     4,    16,     4,    17,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    18,    19,    20,    20,    20,    20,    20,    20,    20,
      20,    20,    20,    21,    21
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     2,     3,     3,     2,
       3,     3,     8,     1,     1
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
#line 60 "generateconstraints.y" /* yacc.c:1646  */
    {
          }
#line 1273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 67 "generateconstraints.y" /* yacc.c:1646  */
    {
            strcpy((yyval.s), (yyvsp[0].s));
          }
#line 1281 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 71 "generateconstraints.y" /* yacc.c:1646  */
    {
            strcpy((yyval.s), (yyvsp[0].s));
          }
#line 1289 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 75 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf((yyval.s), "%s", (yyvsp[-1].s));
          }
#line 1297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 79 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "not %s", (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            } 
            printf("  == %s => %s\n", str, (yyval.s));

            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str1, "false");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str1, "true");
              else
                sprintf(str1, "(= %s_%d false)", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> %s_%d %s))\n", (yyval.s), loop_count, str1);
              fprintf(ofp1, "(assert (=> %s %s_%d))\n", str1, (yyval.s), loop_count);
            }
            fprintf(ofp1, "\n");
          }
#line 1329 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 107 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "%s /\\ %s", (yyvsp[-2].s), (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }
            printf("  == %s => %s\n", str, (yyval.s));

            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp((yyvsp[-2].s), "true") == 0)
                strcpy(str1, "true");
              else if (strcmp((yyvsp[-2].s), "false") == 0)
                strcpy(str1, "false");
              else
	        sprintf(str1, "%s_%d", (yyvsp[-2].s), loop_count);
              if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str2, "true");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str2, "false");
              else
	        sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (and %s %s)))\n", (yyval.s), loop_count, str1, str2);
              fprintf(ofp1, "(assert (=> (and %s %s) %s_%d))\n", str1, str2, (yyval.s), loop_count);
            }
            fprintf(ofp1, "\n");
          }
#line 1367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 141 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "%s \\/ %s", (yyvsp[-2].s), (yyvsp[0].s));
	    if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }  
            printf(" == %s => %s\n", str, (yyval.s));
            
            for (loop_count = 1; loop_count <= length + 1; loop_count++)
            {
              if (strcmp((yyvsp[-2].s), "true") == 0)
                strcpy(str1, "true");
              else if (strcmp((yyvsp[-2].s), "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", (yyvsp[-2].s), loop_count);
              if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str2, "true");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (or %s %s)))\n", (yyval.s), loop_count, str1, str2);
              fprintf(ofp1, "(assert (=> (or %s %s) %s_%d))\n", str1, str2, (yyval.s), loop_count);
            }
            fprintf(ofp1, "\n");
          }
#line 1405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 175 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "X %s", (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }
            printf("  == %s => %s\n", str, (yyval.s));
           
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp1, "(assert (=> %s_%d %s_%d))\n", (yyval.s), loop_count, (yyvsp[0].s), loop_count + 1);
              fprintf(ofp1, "(assert (=> %s_%d %s_%d))\n", (yyvsp[0].s), loop_count + 1, (yyval.s), loop_count);
            }
            fprintf(ofp1, "\n");
          }
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 197 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "%s U %s", (yyvsp[-2].s), (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }            
            printf("  == %s => %s\n", str, (yyval.s));
            
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp2, "(declare-const f_%d_%d Bool)\n", until_count, loop_count);
            }
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              if (strcmp((yyvsp[-2].s), "true") == 0)
                strcpy(str1, "true");
              else if (strcmp((yyvsp[-2].s), "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", (yyvsp[-2].s), loop_count);
              if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str2, "true");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (or %s (and %s %s_%d))))\n", (yyval.s), loop_count, str2, str1, (yyval.s), loop_count + 1);
              fprintf(ofp1, "(assert (=> (or %s (and %s %s_%d)) %s_%d))\n", str2, str1, (yyval.s), loop_count + 1, (yyval.s), loop_count);
            }           
            fprintf(ofp1, "\n");
            //fprintf(ofp1, "tu1\n");
            fprintf(ofp1, "(assert (= f_%d_1 false))\n", until_count);
            fprintf(ofp1, "(assert (=> loopexists (=> %s_%d f_%d_%d)))\n", (yyval.s), length, until_count, length);
            for(loop_count = 2; loop_count <= length; loop_count++)
            {
              //fprintf(ofp1, "tu2\n");
              fprintf(ofp1, "(assert (=> f_%d_%d (or f_%d_%d (and inloop_%d %s_%d))))\n", until_count, loop_count, until_count, loop_count - 1, loop_count, (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> (or f_%d_%d (and inloop_%d %s_%d)) f_%d_%d))\n", until_count, loop_count - 1, loop_count, (yyvsp[0].s), loop_count, until_count, loop_count);
            }  
            fprintf(ofp1, "\n");
            until_count = until_count + 1;
          }
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 246 "generateconstraints.y" /* yacc.c:1646  */
    {
            sprintf(str, "%s R %s", (yyvsp[-2].s), (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }  
            printf("  == %s => %s\n", str, (yyval.s));
            
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
              fprintf(ofp2, "(declare-const g_%d_%d Bool)\n", release_count, loop_count);
            }

            for (loop_count = 1; loop_count <= length; loop_count++)
            {
	      if (strcmp((yyvsp[-2].s), "true") == 0)
                strcpy(str1, "true");
              else if (strcmp((yyvsp[-2].s), "false") == 0)
                strcpy(str1, "false");
              else
                sprintf(str1, "%s_%d", (yyvsp[-2].s), loop_count);
              if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str2, "true");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> %s_%d (and %s (or %s %s_%d))))\n", (yyval.s), loop_count, str2, str1, (yyval.s), loop_count + 1);
              fprintf(ofp1, "(assert (=> (and %s (or %s %s_%d)) %s_%d))\n", str2, str1, (yyval.s), loop_count + 1, (yyval.s), loop_count);
            }
            fprintf(ofp1, "\n");
            /*
            fprintf(ofp1, "(assert (= g_%d_1 true))\n", release_count);
            fprintf(ofp1, "(assert (=> loopexists (=> g_%d_%d %s_%d)))\n", release_count, length, $$, length);
            for(loop_count = 2; loop_count <= length; loop_count++)
            {
              fprintf(ofp1, "(assert (=> g_%d_%d (and g_%d_%d (or (not inloop_%d) %s_%d))))\n", release_count, loop_count, release_count, loop_count - 1, loop_count, $3, loop_count);
              fprintf(ofp1, "(assert (=> (and g_%d_%d (or (not inloop_%d) %s_%d)) g_%d_%d))\n", release_count, loop_count - 1, loop_count, $3, loop_count, release_count, loop_count);
            }  
            fprintf(ofp1, "\n");
            */
            release_count = release_count + 1;
          }
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 296 "generateconstraints.y" /* yacc.c:1646  */
    {
            lower_limit = atoi((yyvsp[-4].s));
	    upper_limit = atoi((yyvsp[-2].s));
            
            sprintf(str, "%s U[%s,%s] %s", (yyvsp[-7].s), (yyvsp[-4].s), (yyvsp[-2].s), (yyvsp[0].s));
            if (findProposition(str) == NULL)
            {
              sprintf((yyval.s), "p_%d", variable_count);
              declareVariable(ofp2, str, (yyval.s));
              variable_count++;
            }
            else
            {
              strcpy((yyval.s), findProposition(str));
            }
            printf("  == %s => %s\n", str, (yyval.s));
            
	    for (loop_count = 1; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              sprintf(str1, "%s U[%d,%d] %s", (yyvsp[-7].s), loop_count, (upper_limit - lower_limit + 1), (yyvsp[0].s));
              sprintf(str2, "q_%d_%d", bounded_operator_count, loop_count);
              declareVariable(ofp2, str1, str2);
            }
         
            for (loop_count = 1; loop_count <= length - lower_limit; loop_count++)
            {
	      fprintf(ofp1, "(assert (=> %s_%d", (yyval.s), loop_count);
              fprintf(ofp1, " (and");
              for (count1 = loop_count; count1 < loop_count + lower_limit; count1++)
              {
                if (strcmp((yyvsp[-7].s), "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp((yyvsp[-7].s), "false") == 0)
                  strcpy(str1, "false");
                else
                    sprintf(str1, "%s_%d", (yyvsp[-7].s), count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d)))\n", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit);
              fprintf(ofp1, "(assert (=>");
              fprintf(ofp1, " (and");
              for (count1 = loop_count; count1 < loop_count + lower_limit; count1++)
              {
                if (strcmp((yyvsp[-7].s), "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp((yyvsp[-7].s), "false") == 0)
                  strcpy(str1, "false");
                else
                    sprintf(str1, "%s_%d", (yyvsp[-7].s), count1);
                fprintf(ofp1, " %s", str1);
              }
              fprintf(ofp1, " q_%d_%d_%d)", bounded_operator_count, upper_limit - lower_limit + 1, loop_count + lower_limit);  
              fprintf(ofp1, " %s_%d))\n", (yyval.s), loop_count);
            }
            for(loop_count = length - lower_limit + 1; loop_count <= length; loop_count++)
            {
              if (loop_count > 0)
              {
                fprintf(ofp1, "(assert (= %s_%d false))\n", (yyval.s), loop_count);
              }
            }

	    for(loop_count = lower_limit + 1; loop_count <= length - 1; loop_count++)
            {
              for (count1 = 2 ; count1 <= (upper_limit - lower_limit + 1) ; count1++)
              {
                if (strcmp((yyvsp[-7].s), "true") == 0)
                  strcpy(str1, "true");
                else if (strcmp((yyvsp[-7].s), "false") == 0)
                  strcpy(str1, "false");
                else
                  sprintf(str1, "%s_%d", (yyvsp[-7].s), loop_count);

                if (strcmp((yyvsp[0].s), "true") == 0)
                  strcpy(str2, "true");
                else if (strcmp((yyvsp[0].s), "false") == 0)
                  strcpy(str2, "false");
                else
                  sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
                fprintf(ofp1, "(assert (=> q_%d_%d_%d (or %s (and %s q_%d_%d_%d))))\n", bounded_operator_count, count1, loop_count, str2, str1, bounded_operator_count, count1 - 1, loop_count + 1);
                fprintf(ofp1, "(assert (=> (or %s (and %s q_%d_%d_%d)) q_%d_%d_%d))\n", str2, str1, bounded_operator_count, count1 - 1, loop_count + 1, bounded_operator_count, count1, loop_count);
              }
            }
          
            fprintf(ofp1, "\n"); 
            for (loop_count = 1; loop_count <= length; loop_count++)
            {
	      if (strcmp((yyvsp[0].s), "true") == 0)
                strcpy(str2, "true");
              else if (strcmp((yyvsp[0].s), "false") == 0)
                strcpy(str2, "false");
              else
                sprintf(str2, "%s_%d", (yyvsp[0].s), loop_count);
              fprintf(ofp1, "(assert (=> q_%d_1_%d %s))\n", bounded_operator_count, loop_count, str2);
              fprintf(ofp1, "(assert (=> %s q_%d_1_%d))\n", str2, bounded_operator_count, loop_count);
            }  

            fprintf(ofp1, "\n"); 
            if (strcmp((yyvsp[0].s), "true") == 0)
              strcpy(str2, "true");
            else if (strcmp((yyvsp[0].s), "false") == 0)
              strcpy(str2, "false");
            else
              sprintf(str2, "%s_%d", (yyvsp[0].s), length);
            for (loop_count = 2; loop_count <= (upper_limit - lower_limit + 1); loop_count++)
            {
              fprintf(ofp1, "(assert (=> q_%d_%d_%d %s))\n", bounded_operator_count, loop_count, length, str2);
              fprintf(ofp1, "(assert (=> %s q_%d_%d_%d))\n", str2, bounded_operator_count, loop_count, length);
            }

            bounded_operator_count++;
            fprintf(ofp1, "\n");
          }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 547 "generateconstraints.y" /* yacc.c:1646  */
    {
            strcpy((yyval.s), "true");
          }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 551 "generateconstraints.y" /* yacc.c:1646  */
    {
            strcpy((yyval.s), "false");
          }
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1676 "y.tab.c" /* yacc.c:1646  */
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
#line 556 "generateconstraints.y" /* yacc.c:1906  */




extern FILE* yyin;
extern char yytext[];
extern int column;


char* findProposition(char *str)
{
  unsigned int loop_count; 

  for(loop_count = 0; loop_count < propositions.size(); loop_count++)
  {
    if (strcmp(propositions[loop_count].x, str) == 0)
      return(propositions[loop_count].y);
  }
  return NULL;
}


void declareVariable(FILE *ofp, char *str1, char *str2)
{
  unsigned int loop_count;
  prop_t prop;

    strcpy(prop.x, str1);
    strcpy(prop.y, str2);
    propositions.push_back(prop);
    for (loop_count = 1; loop_count <= length + 1; loop_count++)
    {
      fprintf(ofp, "(declare-const %s_%d Bool)\n", str2, loop_count);
    }
}


void writeLastStateConstraints(FILE *ofp, unsigned int length, unsigned int variable_count)
{
  unsigned int count1, count2;
  
  for (count1 = 1; count1 < variable_count; count1++)
  {
    fprintf(ofp, "(assert (=> (not loopexists) (= p_%d_%d false)))\n", count1, length + 1);
  }
  fprintf(ofp, "\n");

  for (count1 = 1; count1 < variable_count; count1++)
  {
    for (count2 = 2; count2 <= length; count2++)
    {
      fprintf(ofp, "(assert (=> l_%d (= p_%d_%d p_%d_%d)))\n", count2, count1, length + 1, count1, count2);
    }
  }
  fprintf(ofp, "\n");
}


void writeInitialStateConstraint(FILE *ofp, unsigned int variable_count)
{
  fprintf(ofp, "(assert (= p_%d_1 true))\n", variable_count - 1); 
}


int main(int argc, char *argv[]) 
{
  if (argc != 3)
  {  
    printf("USAGE: ./parser <input file name> <length of the trajectory>");
    exit(0);
  }
  length = atoi(argv[2]);  
  cout<<"in the main of generate constraints"<<endl;
  ofp1 = fopen("ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/ltlconstraints.txt", "w");
  ofp2 = fopen("ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/ltlvariables.txt", "w");
  cout<<"opened the two files"<<endl;

  yyin = fopen(argv[1], "r");
  yyparse();
  writeLastStateConstraints(ofp1, length, variable_count);
  writeInitialStateConstraint(ofp1, variable_count);
 
  fclose(ofp1);
  fclose(ofp2);
}


int yyerror(char *s)
{
  printf("\n%*s\n%*s\n", column, "^", column, s);
  return 0;
}
