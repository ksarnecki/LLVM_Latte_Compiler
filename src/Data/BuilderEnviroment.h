#ifndef _BUILDERENVIROMENT_GEN_H_
#define _BUILDERENVIROMENT_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- BuilderEnviromentElement ---------------
class BuilderEnviromentElement {
  AnsiString ident;
  int storeId;
public:
  BuilderEnviromentElement(const AnsiString&, const int&);
  virtual const AnsiString& getIdent() const;
  virtual const int& getStoreId() const;
  virtual AnsiString& getIdent();
  virtual int& getStoreId();


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
