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

typedef std::pair<int, bool> scope_info;

extern std::vector<scope_info> scope_stack;

int max_stack_size = 1;
int indent_level = 0;
bool ws_define = false;
bool spaces = false;
bool if_open = false;
int indent_count;

bool check_indents(int);
#line 90 "ocl-parser.yy" // lalr1.cc:404

#include "ocl-driver.h"
#include "ocl-scanner.h"

extern int line_num;

#undef yylex
#define yylex driver.lexer->lex


#line 66 "ocl-parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ocl-parser.h"

// User implementation prologue.

#line 80 "ocl-parser.cpp" // lalr1.cc:412


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
#line 166 "ocl-parser.cpp" // lalr1.cc:479

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
    #line 31 "ocl-parser.yy" // lalr1.cc:745
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 544 "ocl-parser.cpp" // lalr1.cc:745

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
  case 14:
#line 125 "ocl-parser.yy" // lalr1.cc:859
    { if(if_open) if_open = false; }
#line 654 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 127 "ocl-parser.yy" // lalr1.cc:859
    { if_open = true; }
#line 660 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 129 "ocl-parser.yy" // lalr1.cc:859
    { if(!if_open) YYERROR; }
#line 666 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 131 "ocl-parser.yy" // lalr1.cc:859
    { if(!if_open) YYERROR;
      else if_open = false;
    }
#line 674 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 135 "ocl-parser.yy" // lalr1.cc:859
    { if(if_open) if_open = false; }
#line 680 "ocl-parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 137 "ocl-parser.yy" // lalr1.cc:859
    { if(if_open) if_open = false; }
#line 686 "ocl-parser.cpp" // lalr1.cc:859
    break;


#line 690 "ocl-parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -59;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      13,   -59,   -59,   -59,    -6,   -59,   122,   -24,   122,   122,
      18,   -59,    13,   -17,   -14,    21,    53,   122,   -59,   -59,
     -59,   122,     5,    45,   -12,    -2,     6,    67,    15,    77,
      46,    39,   -59,   -59,   -59,   102,   -59,   -59,   -59,   -59,
     122,    60,   116,    65,   -59,   -59,   -59,   -59,    13,    71,
     122,    11,   105,   -59,   -59,   -59,   122,   122,   122,   122,
     122,    60,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   -59,   -59,    69,   118,
     -59,    60,   -59,    70,   116,   116,   -59,   -59,    -2,    -2,
      -2,    -2,    -2,   -59,     6,    67,    15,    15,    77,    77,
      77,    77,    46,    46,    39,    39,    39,   -59,    60,    29,
     -59,   100,   -59,   -59,   -59,   -59,    98,    61,    89,    68,
     100,   122,    60,   -59,   116,   -59
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       5,    61,    62,    71,     0,     8,     0,     0,     0,     0,
       0,     2,     5,     0,     0,     0,     0,     0,    68,    70,
      69,     0,     0,     0,     0,    26,    28,    30,    33,    38,
      41,    45,    47,    51,    53,    55,    58,    54,    50,    60,
       0,     0,    19,     0,     1,     3,     6,     7,     5,     0,
       0,     0,     0,    48,    49,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,     0,     0,
      17,     0,     4,     0,    13,    12,    14,    59,    22,    23,
      24,    25,    21,    15,    27,    29,    31,    32,    34,    35,
      36,    37,    39,    40,    42,    43,    44,    46,     0,     0,
      18,    65,    16,    20,     9,    10,     0,    64,    66,     0,
      65,     0,     0,    63,    67,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
     -59,   -59,    -8,   117,   -59,    33,    42,   -58,    -7,    38,
      85,    90,    81,    72,    78,   -35,    80,   -59,   129,   -59,
     -59,    79,    36,   -59,   -59,   135,     0
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,   113,    13,    14,    80,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    15,   116,   117,    37,    38,    39
  };

  const unsigned char
  Parser::yytable_[] =
  {
      16,    42,    43,    93,    45,    17,    56,    57,    58,    59,
      51,     3,    16,    19,    52,    16,     1,     2,    44,     3,
      40,    86,    54,   110,    41,    46,    60,     3,    47,    56,
      57,    58,    59,    78,    62,     3,    61,   104,   105,   106,
      82,    63,    84,    85,    66,    67,    68,    69,    16,    60,
     112,     3,    18,     4,    20,     5,    21,     6,     7,     8,
       9,     4,    75,     5,   125,     6,     7,     8,     9,     4,
      72,    73,    74,     6,     7,     8,     9,     3,    18,    19,
      20,   111,    21,    56,    57,    58,    59,    56,    57,    58,
      59,    49,    50,    22,    88,    89,    90,    91,    92,    23,
      64,    65,    79,    60,    70,    71,     3,    60,   119,    16,
     120,   118,    83,    81,   124,    87,   122,   108,    76,    77,
     118,     1,     2,    56,    57,    58,    59,   121,     3,    18,
      19,    20,    48,    21,    56,    57,    58,    59,    98,    99,
     100,   101,   114,    60,    22,    96,    97,    94,   102,   103,
      23,   115,    55,    95,    60,   107,   123,    53,   109
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       0,     8,     9,    61,    12,    11,    18,    19,    20,    21,
      17,     6,    12,     8,    21,    15,     3,     4,     0,     6,
      44,    10,    22,    81,    48,    42,    38,     6,    42,    18,
      19,    20,    21,    40,    36,     6,    48,    72,    73,    74,
      48,    35,    49,    50,    29,    30,    31,    32,    48,    38,
     108,     6,     7,    40,     9,    42,    11,    44,    45,    46,
      47,    40,    23,    42,   122,    44,    45,    46,    47,    40,
      24,    25,    26,    44,    45,    46,    47,     6,     7,     8,
       9,    11,    11,    18,    19,    20,    21,    18,    19,    20,
      21,    38,    39,    22,    56,    57,    58,    59,    60,    28,
      33,    34,    42,    38,    27,    28,     6,    38,    10,   109,
      49,   111,    41,    48,   121,    10,    48,    48,    16,    17,
     120,     3,     4,    18,    19,    20,    21,    38,     6,     7,
       8,     9,    15,    11,    18,    19,    20,    21,    66,    67,
      68,    69,   109,    38,    22,    64,    65,    62,    70,    71,
      28,   109,    23,    63,    38,    75,   120,    22,    79
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,     6,    40,    42,    44,    45,    46,    47,
      53,    54,    55,    57,    58,    73,    78,    11,     7,     8,
       9,    11,    22,    28,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    76,    77,    78,
      44,    48,    60,    60,     0,    54,    42,    42,    55,    38,
      39,    60,    60,    77,    78,    70,    18,    19,    20,    21,
      38,    48,    36,    35,    33,    34,    29,    30,    31,    32,
      27,    28,    24,    25,    26,    23,    16,    17,    60,    42,
      59,    48,    54,    41,    60,    60,    10,    10,    61,    61,
      61,    61,    61,    59,    62,    63,    64,    64,    65,    65,
      65,    65,    66,    66,    67,    67,    67,    68,    48,    73,
      59,    11,    59,    56,    57,    58,    74,    75,    78,    10,
      49,    38,    48,    74,    60,    59
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    52,    53,    54,    54,    54,    55,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    58,    58,    58,    58,
      59,    60,    60,    60,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    64,    64,    64,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    75,    75,    76,    76,
      77,    78
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     0,     2,     2,     1,     1,
       1,     8,     3,     3,     4,     4,     5,     3,     4,     2,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     2,     2,
       1,     1,     2,     1,     1,     1,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     0,     1,     3,     1,     1,
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
  "TOKEN_RIGHT_PAREN", "TOKEN_LEFT_PAREN", "TOKEN_RIGHT_BRACKET",
  "TOKEN_LEFT_BRACKET", "TOKEN_RIGHT_BRACE", "TOKEN_LEFT_BRACE",
  "TOKEN_INCREMENT", "TOKEN_DECREMENT", "TOKEN_INCEQ", "TOKEN_DECEQ",
  "TOKEN_MULTEQ", "TOKEN_DIVEQ", "TOKEN_NOT", "TOKEN_EXPONENT",
  "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MOD", "TOKEN_ADD",
  "TOKEN_MINUS", "TOKEN_LT", "TOKEN_LE", "TOKEN_GT", "TOKEN_GE",
  "TOKEN_EQ", "TOKEN_NE", "TOKEN_AND", "TOKEN_OR", "TOKEN_IN",
  "TOKEN_ASSIGN", "TOKEN_DEFINITION", "TOKEN_PRINT", "TOKEN_FUNCTION",
  "TOKEN_NEWLINE", "TOKEN_FOR", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_RETURN",
  "TOKEN_WHILE", "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_ERROR", "TOKEN_SEMI",
  "$accept", "program", "line_list", "line", "fill_line", "decl", "stmt",
  "suite", "expr", "expr_or", "expr_and", "expr_eq", "expr_comp",
  "expr_add", "expr_mul", "expr_exp", "expr_bool", "expr_minus",
  "expr_int", "expr_inc", "expr_grp", "indent", "arg_list", "arg",
  "value_literals", "non_int_literal", "name", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   103,   103,   105,   106,   107,   110,   111,   112,   115,
     116,   119,   120,   121,   124,   126,   128,   130,   134,   136,
     140,   142,   143,   144,   145,   146,   147,   150,   151,   154,
     155,   158,   159,   160,   163,   164,   165,   166,   167,   169,
     170,   171,   174,   175,   176,   177,   180,   181,   184,   185,
     186,   187,   190,   191,   194,   195,   198,   199,   200,   203,
     204,   208,   209,   212,   213,   214,   217,   218,   221,   222,
     225,   228
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
      45,    46,    47,    48,    49,    50,    51
    };
    const unsigned int user_token_number_max_ = 306;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1211 "ocl-parser.cpp" // lalr1.cc:1167
#line 230 "ocl-parser.yy" // lalr1.cc:1168


bool check_indents(int indents){
    int found = -1;
    if(indents < scope_stack.back().second){
        for(int i = 0;i<scope_stack.size();i++){
            if(indents == scope_stack[i].first){
               found = i;
               break;
            }
        }
        if(found >= 0){
            for(int i = scope_stack.size()-1;i>found;i--){
                scope_stack.pop_back();
            }
        }
        else return false;
    }
    else if(indents > scope_stack.back().second){
        
    }
    else {

    }
    std::make_pair(indents, false);
    return false;
}

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
