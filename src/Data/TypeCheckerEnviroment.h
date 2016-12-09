#ifndef _TYPECHECKERENVIROMENT_GEN_H_
#define _TYPECHECKERENVIROMENT_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Ident ---------------
#include "Absyn.H"
//----------------------------------

//------------- TypeCheckerEnviromentElement ---------------
class TypeCheckerEnviromentElement {
  Ident ident;
  int storeId;
  int nesting;
public:
  TypeCheckerEnviromentElement(const Ident&, const int&, const int&);
  virtual const Ident& getIdent() const;
  virtual const int& getStoreId() const;
  virtual const int& getNesting() const;
  virtual Ident& getIdent();
  virtual int& getStoreId();
  virtual int& getNesting();


  virtual ~TypeCheckerEnviromentElement();

};
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
#include "DynSet.h"


class TypeCheckerEnviroment : public DynSet<TypeCheckerEnviromentElement> {
public:
  TypeCheckerEnviroment();


  virtual ~TypeCheckerEnviroment();

};
//----------------------------------

#endif
