#ifndef _TYPEERROR_GEN_H_
#define _TYPEERROR_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- TypeError ---------------
class TypeError {
  int line;
  AnsiString msg;
public:
  TypeError(const int&, const AnsiString&);
  virtual const int& getLine() const;
  virtual const AnsiString& getMsg() const;
  virtual int& getLine();
  virtual AnsiString& getMsg();


  virtual ~TypeError();

};
//----------------------------------

//------------- TypeErrors ---------------
#include "DynSet.h"


class TypeErrors : public DynSet<TypeError> {
public:
  TypeErrors();


  virtual ~TypeErrors();

};
//----------------------------------

#endif
