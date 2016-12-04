#ifndef _ENVIROMENT_GEN_H_
#define _ENVIROMENT_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Ident ---------------
#include "Absyn.H"
//----------------------------------

//------------- EnviromentElement ---------------
class EnviromentElement {
  Ident ident;
  int storeId;
  int nesting;
public:
  EnviromentElement(const Ident&, const int&, const int&);
  virtual const Ident& getIdent() const;
  virtual const int& getStoreId() const;
  virtual const int& getNesting() const;
  virtual Ident& getIdent();
  virtual int& getStoreId();
  virtual int& getNesting();


  virtual ~EnviromentElement();

};
//----------------------------------

//------------- Enviroment ---------------
#include "DynSet.h"


class Enviroment : public DynSet<EnviromentElement> {
public:
  Enviroment();


  virtual ~Enviroment();

};
//----------------------------------

#endif
