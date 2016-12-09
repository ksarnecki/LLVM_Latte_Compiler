#ifndef _BUILDERENVIROMENT_GEN_H_
#define _BUILDERENVIROMENT_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Ident ---------------
#include "Absyn.H"
//----------------------------------

//------------- BuilderEnviromentElement ---------------
class BuilderEnviromentElement {
  Ident ident;
  int storeId;
  int nesting;
public:
  BuilderEnviromentElement(const Ident&, const int&, const int&);
  virtual const Ident& getIdent() const;
  virtual const int& getStoreId() const;
  virtual const int& getNesting() const;
  virtual Ident& getIdent();
  virtual int& getStoreId();
  virtual int& getNesting();


  virtual ~BuilderEnviromentElement();

};
//----------------------------------

//------------- BuilderEnviroment ---------------
#include "DynSet.h"


class BuilderEnviroment : public DynSet<BuilderEnviromentElement> {
public:
  BuilderEnviroment();


  virtual ~BuilderEnviroment();

};
//----------------------------------

#endif
