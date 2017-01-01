#ifndef _TYPECHECKERENVIROMENT_GEN_H_
#define _TYPECHECKERENVIROMENT_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- TypeCheckerEnviromentElement ---------------
class TypeCheckerEnviromentElement {
  AnsiString ident;
  int storeId;
  int nesting;
public:
  TypeCheckerEnviromentElement(const AnsiString&, const int&, const int&);
  virtual const AnsiString& getIdent() const;
  virtual const int& getStoreId() const;
  virtual const int& getNesting() const;
  virtual AnsiString& getIdent();
  virtual int& getStoreId();
  virtual int& getNesting();

  virtual AnsiString toJSON() const;
  static TypeCheckerEnviromentElement fromJSON(AnsiString);

  virtual ~TypeCheckerEnviromentElement();

};
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
#include "DynSet.h"


class TypeCheckerEnviroment : public DynSet<TypeCheckerEnviromentElement> {
public:
  TypeCheckerEnviroment();

  virtual AnsiString toJSON() const;
  static TypeCheckerEnviroment fromJSON(AnsiString);

  virtual ~TypeCheckerEnviroment();

};
//----------------------------------

#endif
