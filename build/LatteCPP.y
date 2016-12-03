/* This Bison file was machine-generated by BNFC */
%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Absyn.H"
typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yyparse(void);
int yylex(void);
YY_BUFFER_STATE yy_scan_string(const char *str);
void yy_delete_buffer(YY_BUFFER_STATE buf);
int yy_mylinenumber;
int initialize_lexer(FILE * inp);
int yywrap(void)
{
  return 1;
}
void yyerror(const char *str)
{
  std::cout << "line " << yy_mylinenumber << std::endl ;
  fprintf(stderr,"error: %s\n",str);
}



static Program* YY_RESULT_Program_ = 0;
Program* pProgram(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}
Program* pProgram(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}

static TopDef* YY_RESULT_TopDef_ = 0;
TopDef* pTopDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_TopDef_;
  }
}
TopDef* pTopDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_TopDef_;
  }
}

static ListTopDef* YY_RESULT_ListTopDef_ = 0;
ListTopDef* pListTopDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListTopDef_;
  }
}
ListTopDef* pListTopDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListTopDef_;
  }
}

static Arg* YY_RESULT_Arg_ = 0;
Arg* pArg(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Arg_;
  }
}
Arg* pArg(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Arg_;
  }
}

static ListArg* YY_RESULT_ListArg_ = 0;
ListArg* pListArg(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListArg_;
  }
}
ListArg* pListArg(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListArg_;
  }
}

static Block* YY_RESULT_Block_ = 0;
Block* pBlock(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Block_;
  }
}
Block* pBlock(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Block_;
  }
}

static ListStmt* YY_RESULT_ListStmt_ = 0;
ListStmt* pListStmt(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStmt_;
  }
}
ListStmt* pListStmt(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStmt_;
  }
}

static Stmt* YY_RESULT_Stmt_ = 0;
Stmt* pStmt(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}
Stmt* pStmt(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}

static Item* YY_RESULT_Item_ = 0;
Item* pItem(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Item_;
  }
}
Item* pItem(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Item_;
  }
}

static ListItem* YY_RESULT_ListItem_ = 0;
ListItem* pListItem(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListItem_;
  }
}
ListItem* pListItem(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListItem_;
  }
}

static Type* YY_RESULT_Type_ = 0;
Type* pType(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Type_;
  }
}
Type* pType(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Type_;
  }
}

static ListType* YY_RESULT_ListType_ = 0;
ListType* pListType(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListType_;
  }
}
ListType* pListType(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListType_;
  }
}

static Expr* YY_RESULT_Expr_ = 0;
Expr* pExpr(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Expr_;
  }
}
Expr* pExpr(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Expr_;
  }
}

static ListExpr* YY_RESULT_ListExpr_ = 0;
ListExpr* pListExpr(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExpr_;
  }
}
ListExpr* pListExpr(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExpr_;
  }
}

static AddOp* YY_RESULT_AddOp_ = 0;
AddOp* pAddOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_AddOp_;
  }
}
AddOp* pAddOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_AddOp_;
  }
}

static MulOp* YY_RESULT_MulOp_ = 0;
MulOp* pMulOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_MulOp_;
  }
}
MulOp* pMulOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_MulOp_;
  }
}

static RelOp* YY_RESULT_RelOp_ = 0;
RelOp* pRelOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_RelOp_;
  }
}
RelOp* pRelOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_RelOp_;
  }
}



%}

%union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Program* program_;
  TopDef* topdef_;
  ListTopDef* listtopdef_;
  Arg* arg_;
  ListArg* listarg_;
  Block* block_;
  ListStmt* liststmt_;
  Stmt* stmt_;
  Item* item_;
  ListItem* listitem_;
  Type* type_;
  ListType* listtype_;
  Expr* expr_;
  ListExpr* listexpr_;
  AddOp* addop_;
  MulOp* mulop_;
  RelOp* relop_;

}


%token _ERROR_
%token _SYMB_0    //   (
%token _SYMB_1    //   )
%token _SYMB_2    //   ,
%token _SYMB_3    //   {
%token _SYMB_4    //   }
%token _SYMB_5    //   ;
%token _SYMB_6    //   =
%token _SYMB_7    //   ++
%token _SYMB_8    //   --
%token _SYMB_9    //   -
%token _SYMB_10    //   !
%token _SYMB_11    //   &&
%token _SYMB_12    //   ||
%token _SYMB_13    //   +
%token _SYMB_14    //   *
%token _SYMB_15    //   /
%token _SYMB_16    //   %
%token _SYMB_17    //   <
%token _SYMB_18    //   <=
%token _SYMB_19    //   >
%token _SYMB_20    //   >=
%token _SYMB_21    //   ==
%token _SYMB_22    //   !=
%token _SYMB_23    //   boolean
%token _SYMB_24    //   else
%token _SYMB_25    //   false
%token _SYMB_26    //   if
%token _SYMB_27    //   int
%token _SYMB_28    //   return
%token _SYMB_29    //   string
%token _SYMB_30    //   true
%token _SYMB_31    //   void
%token _SYMB_32    //   while

%type <program_> Program
%type <topdef_> TopDef
%type <listtopdef_> ListTopDef
%type <arg_> Arg
%type <listarg_> ListArg
%type <block_> Block
%type <liststmt_> ListStmt
%type <stmt_> Stmt
%type <item_> Item
%type <listitem_> ListItem
%type <type_> Type
%type <listtype_> ListType
%type <expr_> Expr6
%type <expr_> Expr5
%type <expr_> Expr4
%type <expr_> Expr3
%type <expr_> Expr2
%type <expr_> Expr1
%type <expr_> Expr
%type <listexpr_> ListExpr
%type <addop_> AddOp
%type <mulop_> MulOp
%type <relop_> RelOp

%token<string_> _STRING_
%token<int_> _INTEGER_
%token<string_> _IDENT_

%%
Program : ListTopDef {  std::reverse($1->begin(),$1->end()) ;$$ = new Prog($1); YY_RESULT_Program_= $$; } 
;
TopDef : Type _IDENT_ _SYMB_0 ListArg _SYMB_1 Block {  std::reverse($4->begin(),$4->end()) ;$$ = new FnDef($1, $2, $4, $6);  } 
;
ListTopDef : TopDef {  $$ = new ListTopDef() ; $$->push_back($1);  } 
  | TopDef ListTopDef {  $2->push_back($1) ; $$ = $2 ;  }
;
Arg : Type _IDENT_ {  $$ = new Ar($1, $2);  } 
;
ListArg : /* empty */ {  $$ = new ListArg();  } 
  | Arg {  $$ = new ListArg() ; $$->push_back($1);  }
  | Arg _SYMB_2 ListArg {  $3->push_back($1) ; $$ = $3 ;  }
;
Block : _SYMB_3 ListStmt _SYMB_4 {  $$ = new Blk($2);  } 
;
ListStmt : /* empty */ {  $$ = new ListStmt();  } 
  | ListStmt Stmt {  $1->push_back($2) ; $$ = $1 ;  }
;
Stmt : _SYMB_5 {  $$ = new Empty();  } 
  | Block {  $$ = new BStmt($1);  }
  | Type ListItem _SYMB_5 {  std::reverse($2->begin(),$2->end()) ;$$ = new Decl($1, $2);  }
  | _IDENT_ _SYMB_6 Expr _SYMB_5 {  $$ = new Ass($1, $3);  }
  | _IDENT_ _SYMB_7 _SYMB_5 {  $$ = new Incr($1);  }
  | _IDENT_ _SYMB_8 _SYMB_5 {  $$ = new Decr($1);  }
  | _SYMB_28 Expr _SYMB_5 {  $$ = new Ret($2);  }
  | _SYMB_28 _SYMB_5 {  $$ = new VRet();  }
  | _SYMB_26 _SYMB_0 Expr _SYMB_1 Stmt {  $$ = new Cond($3, $5);  }
  | _SYMB_26 _SYMB_0 Expr _SYMB_1 Stmt _SYMB_24 Stmt {  $$ = new CondElse($3, $5, $7);  }
  | _SYMB_32 _SYMB_0 Expr _SYMB_1 Stmt {  $$ = new While($3, $5);  }
  | Expr _SYMB_5 {  $$ = new SExp($1);  }
;
Item : _IDENT_ {  $$ = new NoInit($1);  } 
  | _IDENT_ _SYMB_6 Expr {  $$ = new Init($1, $3);  }
;
ListItem : Item {  $$ = new ListItem() ; $$->push_back($1);  } 
  | Item _SYMB_2 ListItem {  $3->push_back($1) ; $$ = $3 ;  }
;
Type : _SYMB_27 {  $$ = new Int();  } 
  | _SYMB_29 {  $$ = new Str();  }
  | _SYMB_23 {  $$ = new Bool();  }
  | _SYMB_31 {  $$ = new Void();  }
;
ListType : /* empty */ {  $$ = new ListType();  } 
  | Type {  $$ = new ListType() ; $$->push_back($1);  }
  | Type _SYMB_2 ListType {  $3->push_back($1) ; $$ = $3 ;  }
;
Expr6 : _IDENT_ {  $$ = new EVar($1);  } 
  | _INTEGER_ {  $$ = new ELitInt($1);  }
  | _SYMB_30 {  $$ = new ELitTrue();  }
  | _SYMB_25 {  $$ = new ELitFalse();  }
  | _IDENT_ _SYMB_0 ListExpr _SYMB_1 {  std::reverse($3->begin(),$3->end()) ;$$ = new EApp($1, $3);  }
  | _STRING_ {  $$ = new EString($1);  }
  | _SYMB_0 Expr _SYMB_1 {  $$ = $2;  }
;
Expr5 : _SYMB_9 Expr6 {  $$ = new Neg($2);  } 
  | _SYMB_10 Expr6 {  $$ = new Not($2);  }
  | Expr6 {  $$ = $1;  }
;
Expr4 : Expr4 MulOp Expr5 {  $$ = new EMul($1, $2, $3);  } 
  | Expr5 {  $$ = $1;  }
;
Expr3 : Expr3 AddOp Expr4 {  $$ = new EAdd($1, $2, $3);  } 
  | Expr4 {  $$ = $1;  }
;
Expr2 : Expr2 RelOp Expr3 {  $$ = new ERel($1, $2, $3);  } 
  | Expr3 {  $$ = $1;  }
;
Expr1 : Expr2 _SYMB_11 Expr1 {  $$ = new EAnd($1, $3);  } 
  | Expr2 {  $$ = $1;  }
;
Expr : Expr1 _SYMB_12 Expr {  $$ = new EOr($1, $3);  } 
  | Expr1 {  $$ = $1;  }
;
ListExpr : /* empty */ {  $$ = new ListExpr();  } 
  | Expr {  $$ = new ListExpr() ; $$->push_back($1);  }
  | Expr _SYMB_2 ListExpr {  $3->push_back($1) ; $$ = $3 ;  }
;
AddOp : _SYMB_13 {  $$ = new Plus();  } 
  | _SYMB_9 {  $$ = new Minus();  }
;
MulOp : _SYMB_14 {  $$ = new Times();  } 
  | _SYMB_15 {  $$ = new Div();  }
  | _SYMB_16 {  $$ = new Mod();  }
;
RelOp : _SYMB_17 {  $$ = new LTH();  } 
  | _SYMB_18 {  $$ = new LE();  }
  | _SYMB_19 {  $$ = new GTH();  }
  | _SYMB_20 {  $$ = new GE();  }
  | _SYMB_21 {  $$ = new EQU();  }
  | _SYMB_22 {  $$ = new NE();  }
;

