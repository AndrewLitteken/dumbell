// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 1 "ocl-parser.yy" // lalr1.cc:404

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "line.h"
#include "expr.h"

typedef std::pair<int, std::vector<bool> > scope_info;

extern std::vector<scope_info> scope_stack;
extern std::vector<Line *> tails;

int max_stack_size = 1;
std::vector<int> indent_levels;
bool ws_define = false;
bool spaces = false;
int indent_level_count = -1;

bool loop_available();
int check_indents(std::string);
void indent_levels_add(int);
bool check_indent_levels();
void add_to_syntax_tree(Line*, int);

#line 62 "ocl-parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ocl-parser.h"

// User implementation prologue.
#line 111 "ocl-parser.yy" // lalr1.cc:412

#include "ocl-driver.h"
#include "ocl-scanner.h"

extern int line_num;

#undef yylex
#define yylex driver.lexer->lex


#line 86 "ocl-parser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 172 "ocl-parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class oclDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 44 "ocl-parser.yy" // lalr1.cc:745
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 550 "ocl-parser.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 125 "ocl-parser.yy" // lalr1.cc:859
    { driver.syntax_tree = (yystack_[0].value.line); }
#line 660 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 128 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[1].value.line);
            }
#line 668 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 132 "ocl-parser.yy" // lalr1.cc:859
    { }
#line 674 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 136 "ocl-parser.yy" // lalr1.cc:859
    { 
        indent_levels.clear(); 
        indent_level_count = -1;
        (yylhs.value.line) = (yystack_[1].value.line);
    }
#line 684 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 142 "ocl-parser.yy" // lalr1.cc:859
    { }
#line 690 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 146 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[0].value.line);
            }
#line 698 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 150 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[0].value.line);
            }
#line 706 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 156 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[0].value.line);
            }
#line 714 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 160 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[0].value.line);
            }
#line 722 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 164 "ocl-parser.yy" // lalr1.cc:859
    {
                Line *line_to_add = new Line(LINE_PASS, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
                add_to_syntax_tree(line_to_add, -1);    
                (yylhs.value.line) = line_to_add;
            }
#line 732 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 170 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.line) = (yystack_[0].value.line);
            }
#line 740 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 176 "ocl-parser.yy" // lalr1.cc:859
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for a function definition\n";
            exit(1);
        }
        Line *line_to_add = new Line(LINE_FUNC_DEF, *(yystack_[9].value.str), nullptr, nullptr, (yystack_[5].value.expr), nullptr, (yystack_[0].value.line), nullptr, line_num);
        add_to_syntax_tree(line_to_add, (yystack_[1].value.num)-1);
        (yylhs.value.line) = line_to_add;
    }
#line 755 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 187 "ocl-parser.yy" // lalr1.cc:859
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_VAR_DEF, *(yystack_[2].value.str), nullptr, nullptr, (yystack_[0].value.expr), nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        (yylhs.value.line) = line_to_add;
    }
#line 766 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 194 "ocl-parser.yy" // lalr1.cc:859
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_EXPR, std::string(), nullptr, nullptr, (yystack_[0].value.expr), nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);
        (yylhs.value.line) = line_to_add;
    }
#line 777 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 203 "ocl-parser.yy" // lalr1.cc:859
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false; 
        Line *line_to_add = new Line(LINE_PRINT, std::string(), nullptr, nullptr, (yystack_[1].value.expr), nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        (yylhs.value.line) = line_to_add;
    }
#line 788 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 210 "ocl-parser.yy" // lalr1.cc:859
    { 
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an if statement\n";
            exit(1);
        }
        scope_stack[(yystack_[1].value.num)-1].second[0] = true;
        Line *line_to_add = new Line(LINE_IF, std::string(), nullptr, nullptr, (yystack_[4].value.expr), nullptr, (yystack_[0].value.line), nullptr, line_num);
        add_to_syntax_tree(line_to_add, (yystack_[1].value.num)-1);
        (yylhs.value.line) = line_to_add;
    }
#line 803 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 221 "ocl-parser.yy" // lalr1.cc:859
    { 
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an else if statement\n";
            exit(1);
        }
        if(!scope_stack[(yystack_[1].value.num)-1].second[0]){
            std::cout<<"Line "<<line_num-2<<": No If-statement defined at current scope\n";
            exit(1);
        }
        Line *line_to_add = new Line(LINE_ELSE_IF, std::string(), nullptr, nullptr, (yystack_[4].value.expr), nullptr, (yystack_[0].value.line), nullptr, line_num);
        add_to_syntax_tree(line_to_add, (yystack_[1].value.num)-1);
        (yylhs.value.line) = line_to_add;
    }
#line 821 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 235 "ocl-parser.yy" // lalr1.cc:859
    {    
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an else statement\n";
            exit(1);
        }
        if(!scope_stack[(yystack_[1].value.num)-1].second[0]){
            std::cout<<"Line "<<line_num-2<<": No If-statement defined at current scope\n";
            exit(1);
        }
        else{
            scope_stack[(yystack_[1].value.num)-1].second[0] = false; 
        } 
        Line *line_to_add = new Line(LINE_ELSE, std::string(), nullptr, nullptr, nullptr, nullptr, (yystack_[0].value.line), nullptr, line_num);
        add_to_syntax_tree(line_to_add, (yystack_[1].value.num)-1);
        (yylhs.value.line) = line_to_add;
    }
#line 842 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 252 "ocl-parser.yy" // lalr1.cc:859
    {  
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for a while loop\n";
            exit(1);
        }
        if(scope_stack[(yystack_[1].value.num)-1].second[0]) scope_stack[(yystack_[1].value.num)-1].second[0] = false;
        scope_stack[(yystack_[1].value.num)].second[1] = true;
        Line *line_to_add = new Line(LINE_WHILE, std::string(), nullptr, nullptr, (yystack_[4].value.expr), nullptr, (yystack_[0].value.line), nullptr, line_num);
        add_to_syntax_tree(line_to_add, (yystack_[1].value.num)-1);
        (yylhs.value.line) = line_to_add;
    }
#line 858 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 264 "ocl-parser.yy" // lalr1.cc:859
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_RETURN, std::string(), nullptr, nullptr, (yystack_[0].value.expr), nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        (yylhs.value.line) = line_to_add;
    }
#line 869 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 271 "ocl-parser.yy" // lalr1.cc:859
    { 
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        if(!loop_available()){
            std::cout<<"Line "<<line_num<<": Loop not defined\n";
            exit(1);
        }
        (yylhs.value.line) = (yystack_[0].value.line);
    }
#line 882 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 282 "ocl-parser.yy" // lalr1.cc:859
    {
                Line *line_to_add = new Line(LINE_CONTINUE, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
                (yylhs.value.line) = line_to_add;
            }
#line 892 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 288 "ocl-parser.yy" // lalr1.cc:859
    {
                Line *line_to_add = new Line(LINE_BREAK, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
                add_to_syntax_tree(line_to_add, -1);    
                (yylhs.value.line) = line_to_add;
            }
#line 902 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 296 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *name = new Expr(EXPR_NAME, (yystack_[2].value.str), line_num);
            Expr *e = new Expr(EXPR_ASSIGN, name, (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 912 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 302 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_PLUS_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 921 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 307 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_SUB_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 930 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 312 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_MUL_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 939 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 317 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_DIV_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 948 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 322 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 956 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 328 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_OR, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 965 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 333 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 973 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 339 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_AND, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 982 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 344 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 990 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 350 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 999 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 355 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_NEQ, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1008 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 360 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1016 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 366 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_LT, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1025 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 371 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_LTE, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1034 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 376 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_GT, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1043 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 381 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_GTE, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1052 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 386 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.expr) = (yystack_[0].value.expr);
            }
#line 1060 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 392 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_ADD, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1069 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 397 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_SUB, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1078 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 402 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1086 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 408 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_MUL, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1095 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 413 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_DIV, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1104 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 418 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_MOD, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1113 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 423 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1121 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 429 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_EXP, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1130 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 434 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1138 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 440 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_NOT, nullptr, (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1147 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 445 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *name = new Expr(EXPR_NAME, (yystack_[0].value.str), line_num);
                Expr *e = new Expr(EXPR_NOT, nullptr, name, line_num);
                (yylhs.value.expr) = e;
            }
#line 1157 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 450 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.expr) = (yystack_[0].value.expr);
            }
#line 1165 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 454 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.expr) = (yystack_[0].value.expr);
            }
#line 1173 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 460 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_NEG, nullptr, (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1182 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 465 "ocl-parser.yy" // lalr1.cc:859
    {
                (yylhs.value.expr) = (yystack_[0].value.expr);
            }
#line 1190 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 471 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1198 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 475 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1206 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 481 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_INC, (yystack_[1].value.expr), nullptr, line_num);
            (yylhs.value.expr) = e;
        }
#line 1215 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 486 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_DEC, (yystack_[1].value.expr), nullptr, line_num);
            (yylhs.value.expr) = e;
        }
#line 1224 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 491 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[0].value.expr);
        }
#line 1232 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 497 "ocl-parser.yy" // lalr1.cc:859
    {
            (yylhs.value.expr) = (yystack_[1].value.expr);
        }
#line 1240 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 501 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *name = new Expr(EXPR_NAME, *(yystack_[0].value.str), line_num);
            (yylhs.value.expr) = name;
        }
#line 1249 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 506 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *name = new Expr(EXPR_NAME, *(yystack_[3].value.str), line_num);
            Expr *e = new Expr(EXPR_CALL, name, (yystack_[1].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1259 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 514 "ocl-parser.yy" // lalr1.cc:859
    {
                Expr *e = new Expr(EXPR_ARG, (yystack_[2].value.expr), (yystack_[0].value.expr), line_num);
                (yylhs.value.expr) = e;
            }
#line 1268 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 519 "ocl-parser.yy" // lalr1.cc:859
    { 
                Expr *e = new Expr(EXPR_ARG, (yystack_[0].value.expr), nullptr, line_num);
                (yylhs.value.expr) = e;
            }
#line 1277 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 524 "ocl-parser.yy" // lalr1.cc:859
    { (yylhs.value.expr) = nullptr; }
#line 1283 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 528 "ocl-parser.yy" // lalr1.cc:859
    { 
            if(!ws_define){
                spaces = false; 
                ws_define = true;
            }
            if(spaces){
                std::cout<<line_num<<": Mismatched tabs and spaces\n";
                exit(1);
            }
            max_stack_size++;
            int indent_level = check_indents(*(yystack_[0].value.str)) - 1;
            indent_levels_add(indent_level+1);
            (yylhs.value.num) = indent_level+1;
        }
#line 1302 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 543 "ocl-parser.yy" // lalr1.cc:859
    { 
            if(!ws_define){
                spaces = true; 
                ws_define = true;
            }
            if(!spaces){
                std::cout<<line_num<<": Mismatched tabs and spaces\n";
                exit(1);
            }
            max_stack_size++;
            int indent_level = check_indents(*(yystack_[0].value.str)) - 1;
            indent_levels_add(indent_level+1);
            (yylhs.value.num) = indent_level+1;
        }
#line 1321 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 560 "ocl-parser.yy" // lalr1.cc:859
    {   
                if(!ws_define){
                    spaces = false; 
                    ws_define = true;
                }
                if(spaces){
                    std::cout<<line_num<<": Mismatched tabs and spaces\n";
                }
                int indent_level = check_indents(*(yystack_[0].value.str));
                indent_levels_add(indent_level);
                (yylhs.value.num) = indent_level;
            }
#line 1338 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 573 "ocl-parser.yy" // lalr1.cc:859
    {   
                if(!ws_define){
                    spaces = true; 
                    ws_define = true;
                }
                if(!spaces){
                    std::cout<<line_num<<": Mismatched tabs and spaces\n";
                }
                int indent_level = check_indents(*(yystack_[0].value.str));
                indent_levels_add(indent_level);
                (yylhs.value.num) = indent_level;
            }
#line 1355 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 586 "ocl-parser.yy" // lalr1.cc:859
    {
                for(int i = scope_stack.size()-1;i>0;i--){
                    scope_stack.pop_back();
                    tails.pop_back();
                }
                indent_levels_add(0);
                max_stack_size = 1;
                (yylhs.value.num) = 0;
            }
#line 1369 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 598 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *name = new Expr(EXPR_NAME, *(yystack_[2].value.str), line_num);
            Expr *e = new Expr(EXPR_ARG, name, (yystack_[0].value.expr), line_num);
            (yylhs.value.expr) = e;
        }
#line 1379 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 604 "ocl-parser.yy" // lalr1.cc:859
    {
            Expr *e = new Expr(EXPR_NAME, *(yystack_[0].value.str), line_num);
            (yylhs.value.expr) = e; 
        }
#line 1388 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 609 "ocl-parser.yy" // lalr1.cc:859
    { }
#line 1394 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 613 "ocl-parser.yy" // lalr1.cc:859
    {
                    Expr *e = new Expr(EXPR_INT_LITERAL, stoi(*(yystack_[0].value.str)), line_num);
                    (yylhs.value.expr) = e;
                }
#line 1403 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 618 "ocl-parser.yy" // lalr1.cc:859
    {
                    Expr *e = new Expr(EXPR_FP_LITERAL, std::stod(*(yystack_[0].value.str)), line_num);
                    (yylhs.value.expr) = e;
                }
#line 1412 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 625 "ocl-parser.yy" // lalr1.cc:859
    {
                    bool value = (*(yystack_[0].value.str) == "true") ? true : false;
                    Expr *e = new Expr(EXPR_BOOL_LITERAL, value, line_num);
                    (yylhs.value.expr) = e;
                }
#line 1422 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 631 "ocl-parser.yy" // lalr1.cc:859
    {
                    Expr *e = new Expr(EXPR_STRING_LITERAL, new std::string(*(yystack_[0].value.str)), line_num);
                    (yylhs.value.expr) = e;
                }
#line 1431 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 638 "ocl-parser.yy" // lalr1.cc:859
    {
        std::string *item = new std::string(*(yystack_[0].value.str));
        (yylhs.value.str) = item;
    }
#line 1440 "ocl-parser.cpp" // lalr1.cc:859
    break;


#line 1444 "ocl-parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -37;

  const signed char Parser::yytable_ninf_ = -5;

  const short int
  Parser::yypact_[] =
  {
       7,   -37,   -37,   -37,     5,   -37,     7,    46,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   137,    62,   168,     6,   137,
      -5,   137,   137,   -37,   -37,   -16,   -37,   -37,   -37,   135,
      23,    12,    90,   151,    13,    63,    50,   -37,   -37,   -37,
     161,   -37,   -37,   -37,    -6,    10,     4,   -37,   -37,   -37,
      65,   137,    79,   137,    41,   135,    85,   -37,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   -37,   -37,   137,    73,
     137,   -37,   137,   150,    43,    98,   164,    60,    23,    23,
      23,    23,    12,    90,   151,   151,    13,    13,    13,    13,
      63,    63,    50,    50,    50,   -37,   -18,    97,   100,    23,
     135,   -37,   164,    67,   -37,   -37,    16,   164,   137,   -37,
     116,    16,   164,   164,   -37,   -37,   -37,   -37,    16,   -37,
     118,    82,   -37,    16,    16,   -37,    96,   116,   -37,   -37,
      89,   -37,   164,    16,   -37
  };

  const unsigned char
  Parser::yydefact_[] =
  {
      73,    71,    72,     6,     0,     2,    73,     0,     1,     3,
      81,    77,    79,    78,    80,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    23,     0,     7,     8,    22,    15,
      30,    32,    34,    37,    42,    45,    49,    51,    55,    57,
      59,    62,    58,    54,    64,     0,    64,    52,    53,    56,
      64,     0,     0,     0,     0,    21,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,    68,     0,
       0,    63,     0,     0,     0,     0,     0,     0,    26,    27,
      28,    29,    31,    33,    35,    36,    38,    39,    40,    41,
      43,    44,    46,    47,    48,    50,    67,     0,     0,    25,
      14,    16,     0,     0,    69,    70,     0,     0,    68,    65,
      76,     0,     0,     0,    11,    19,     9,    10,     0,    66,
       0,    75,    17,     0,     0,    20,     0,    76,    18,    12,
       0,    74,     0,     0,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
     -37,   -37,   136,   -37,   -37,    30,   145,   158,   -37,    -2,
      80,   114,   130,   125,   119,   121,   -36,   120,   -37,   177,
     -37,   -37,    78,    11,   -37,    61,   -37,   181,    -7
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,    25,   125,   126,   127,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,   107,   116,     7,   130,    42,    43,    50
  };

  const short int
  Parser::yytable_[] =
  {
      44,    58,    59,    60,    61,     8,    78,    -4,    46,    48,
       1,     2,    46,    45,    46,    46,    78,    52,    51,    55,
      56,    81,    10,    11,    12,    13,    14,    57,    15,    58,
      59,    60,    61,    79,    80,   118,   102,   103,   104,    16,
      53,    70,    71,    82,    46,    17,    46,    54,    63,    83,
       3,    85,    10,    11,    12,    13,    14,    18,    15,   123,
      62,    19,    20,    21,    22,    23,   124,    24,    10,    16,
      12,    46,    14,    46,    75,    17,   106,    78,   110,    10,
      11,    12,    13,    14,    86,    15,   112,    18,    72,    73,
      74,    19,    20,    21,    22,    23,    16,    24,    58,    59,
      60,    61,    17,   117,    58,    59,    60,    61,   119,    44,
     122,    46,   120,   131,    44,   108,   106,    58,    59,    60,
      61,    44,    10,   121,    64,    65,    44,    44,   128,   136,
     131,    84,   142,   133,   134,   137,    44,    87,    88,    89,
      90,    91,     9,    10,    11,    12,    13,    14,   140,    15,
     113,   132,    26,   143,    58,    59,    60,    61,   135,   109,
      16,   111,   109,   138,   139,    27,    17,   114,   115,    58,
      59,    60,    61,   144,    10,    11,    92,    13,    76,    77,
      15,    66,    67,    68,    69,    96,    97,    98,    99,    94,
      95,   100,   101,    93,    49,   105,   129,    47,   141
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       7,    19,    20,    21,    22,     0,    12,     0,    15,    16,
       3,     4,    19,    15,    21,    22,    12,    19,    12,    21,
      22,    11,     6,     7,     8,     9,    10,    43,    12,    19,
      20,    21,    22,    39,    40,    53,    72,    73,    74,    23,
      45,    28,    29,    39,    51,    29,    53,    52,    36,    51,
      43,    53,     6,     7,     8,     9,    10,    41,    12,    43,
      37,    45,    46,    47,    48,    49,    50,    51,     6,    23,
       8,    78,    10,    80,    24,    29,    78,    12,    80,     6,
       7,     8,     9,    10,    43,    12,    43,    41,    25,    26,
      27,    45,    46,    47,    48,    49,    23,    51,    19,    20,
      21,    22,    29,    43,    19,    20,    21,    22,    11,   116,
      43,   118,    12,   120,   121,    42,   118,    19,    20,    21,
      22,   128,     6,   112,    34,    35,   133,   134,   117,    11,
     137,    52,    43,   122,   123,    53,   143,    52,    58,    59,
      60,    61,     6,     6,     7,     8,     9,    10,    52,    12,
      52,   121,     7,   142,    19,    20,    21,    22,   128,    79,
      23,    11,    82,   133,   134,     7,    29,     3,     4,    19,
      20,    21,    22,   143,     6,     7,    62,     9,    17,    18,
      12,    30,    31,    32,    33,    66,    67,    68,    69,    64,
      65,    70,    71,    63,    17,    75,   118,    16,   137
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,    43,    57,    58,    59,    80,     0,    58,
       6,     7,     8,     9,    10,    12,    23,    29,    41,    45,
      46,    47,    48,    49,    51,    60,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    82,    83,    84,    65,    84,    83,    84,    75,
      84,    12,    65,    45,    52,    65,    65,    43,    19,    20,
      21,    22,    37,    36,    34,    35,    30,    31,    32,    33,
      28,    29,    25,    26,    27,    24,    17,    18,    12,    39,
      40,    11,    39,    65,    52,    65,    43,    52,    66,    66,
      66,    66,    67,    68,    69,    69,    70,    70,    70,    70,
      71,    71,    72,    72,    72,    73,    65,    78,    42,    66,
      65,    11,    43,    52,     3,     4,    79,    43,    53,    11,
      12,    79,    43,    43,    50,    61,    62,    63,    79,    78,
      81,    84,    61,    79,    79,    61,    11,    53,    61,    61,
      52,    81,    43,    79,    61
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    56,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    70,    70,    70,    71,    71,    71,    71,
      72,    72,    73,    73,    73,    73,    74,    74,    75,    75,
      76,    76,    76,    77,    77,    77,    78,    78,    78,    79,
      79,    80,    80,    80,    81,    81,    81,    82,    82,    83,
      83,    84
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     3,     1,     1,     1,     1,
       1,     1,     3,    10,     3,     1,     4,     6,     7,     5,
       6,     2,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       3,     1,     2,     2,     1,     1,     2,     1,     1,     1,
       2,     2,     1,     3,     1,     4,     3,     1,     0,     1,
       1,     1,     1,     0,     3,     1,     0,     1,     1,     1,
       1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "TOKEN_EOF", "error", "$undefined", "TOKEN_INDENT_TAB",
  "TOKEN_INDENT_SPACE", "TOKEN_COMMENT", "TOKEN_IDENTIFIER",
  "TOKEN_INTEGER_LITERAL", "TOKEN_BOOL_LITERAL", "TOKEN_FP_LITERAL",
  "TOKEN_STRING_LITERAL", "TOKEN_RIGHT_PAREN", "TOKEN_LEFT_PAREN",
  "TOKEN_RIGHT_BRACKET", "TOKEN_LEFT_BRACKET", "TOKEN_RIGHT_BRACE",
  "TOKEN_LEFT_BRACE", "TOKEN_INCREMENT", "TOKEN_DECREMENT", "TOKEN_INCEQ",
  "TOKEN_DECEQ", "TOKEN_MULTEQ", "TOKEN_DIVEQ", "TOKEN_NOT",
  "TOKEN_EXPONENT", "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MOD",
  "TOKEN_ADD", "TOKEN_MINUS", "TOKEN_LT", "TOKEN_LE", "TOKEN_GT",
  "TOKEN_GE", "TOKEN_EQ", "TOKEN_NE", "TOKEN_AND", "TOKEN_OR", "TOKEN_IN",
  "TOKEN_ASSIGN", "TOKEN_DEFINITION", "TOKEN_PRINT", "TOKEN_FUNCTION",
  "TOKEN_NEWLINE", "TOKEN_FOR", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_RETURN",
  "TOKEN_WHILE", "TOKEN_BREAK", "TOKEN_PASS", "TOKEN_CONTINUE",
  "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_ERROR", "TOKEN_SEMI", "$accept",
  "program", "line_list", "line", "line_type", "fill_line", "decl", "stmt",
  "loop_control", "expr", "expr_or", "expr_and", "expr_eq", "expr_comp",
  "expr_add", "expr_mul", "expr_exp", "expr_bool", "expr_minus",
  "expr_int", "expr_inc", "expr_grp", "expr_list", "indent",
  "begin_indent", "arg_list", "value_literals", "non_int_literal", "name", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   124,   124,   127,   132,   135,   141,   145,   149,   155,
     159,   163,   169,   175,   186,   193,   202,   209,   220,   234,
     251,   263,   270,   281,   287,   295,   301,   306,   311,   316,
     321,   327,   332,   338,   343,   349,   354,   359,   365,   370,
     375,   380,   385,   391,   396,   401,   407,   412,   417,   422,
     428,   433,   439,   444,   450,   453,   459,   464,   470,   474,
     480,   485,   490,   496,   500,   505,   513,   518,   524,   527,
     542,   559,   572,   586,   597,   603,   609,   612,   617,   624,
     630,   637
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
    };
    const unsigned int user_token_number_max_ = 310;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1984 "ocl-parser.cpp" // lalr1.cc:1167
#line 643 "ocl-parser.yy" // lalr1.cc:1168


bool loop_available(){
    for(int i = scope_stack.size()-1;i>=0;i--){
        if(scope_stack[i].second[1]) return true;
    }
    return false;
}

int check_indents(std::string text){
    int found = -1;
    if(text.length() < scope_stack.back().first){
        for(int i = 0;i<scope_stack.size();i++){
            if(scope_stack[i].first == text.length()){
                found = i;
                break;
            }
        }
        if(found < 0) {
            std::cout<<line_num<<": Indentation level not defined\n";
            exit(1);
        }
        max_stack_size = found+1;
        for(int i = scope_stack.size()-1;i>found;i--){
            scope_stack.pop_back();
            tails.pop_back();
        }
    }
    else if(text.length() > scope_stack.back().first){
        if(scope_stack.size() > max_stack_size){
            std::cout<<"Line "<<line_num<<": Indent level not defined\n";
            exit(1);
        }
        std::vector<bool> flags;
        flags.push_back(false);
        flags.push_back(false);
        scope_info new_line = std::make_pair(text.length(), flags);
        scope_stack.push_back(new_line);
        tails.push_back(nullptr);
        found = scope_stack.size()-1;
    }
    else found = scope_stack.size() - 1;
    return found;
}

void indent_levels_add(int to_add){
    indent_levels.push_back(to_add);
}

bool check_indent_levels(){
    if(indent_level_count < 0) indent_level_count = indent_levels.size()-1;
    indent_level_count--;
    return indent_levels[indent_level_count] < indent_levels[indent_level_count+1];
}

void add_to_syntax_tree(Line *l, int level){
        switch(l->kind){
            case LINE_PRINT:
            case LINE_RETURN:
            case LINE_BREAK:
            case LINE_PASS:
            case LINE_EXPR:
            case LINE_CONTINUE:
            case LINE_VAR_DEF:
                if(tails.back()) tails.back()->next = l;
                tails.back() = l;
                break;
            case LINE_IF:
            case LINE_FOR:
            case LINE_WHILE:
            case LINE_FUNC_DEF:
                if(tails[level]) tails[level]->next = l;
                tails[level] = l;
                break;
            case LINE_ELSE_IF:
            case LINE_ELSE:
                Line *nested = tails[level];
                while(nested->else_body) nested = nested->else_body;
                nested->else_body = l;
                break;
        }
}

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<"Line :"<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
