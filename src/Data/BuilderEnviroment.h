#ifndef _BUILDERENVIROMENT_GEN_H_
#define _BUILDERENVIROMENT_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- RegisterKind ---------------
#include "Register.h"
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

  virtual AnsiString toJSON() const;
  static BuilderEnviromentElement fromJSON(AnsiString);

  virtual ~BuilderEnviromentElement();

};
//----------------------------------

//------------- BuilderEnviromentElementArray ---------------
#include "DynSet.h"


class BuilderEnviromentElementArray : public DynSet<BuilderEnviromentElement> {
public:
  BuilderEnviromentElementArray();

  virtual AnsiString toJSON() const;
  static BuilderEnviromentElementArray fromJSON(AnsiString);

  virtual ~BuilderEnviromentElementArray();

};
//----------------------------------

//------------- BuilderEnviromentStructElem ---------------
class BuilderEnviromentStructElem {
  AnsiString name;
  RegisterKind kind;
public:
  BuilderEnviromentStructElem(const AnsiString&, const RegisterKind&);
  virtual const AnsiString& getName() const;
  virtual const RegisterKind& getKind() const;
  virtual AnsiString& getName();
  virtual RegisterKind& getKind();

  virtual AnsiString toJSON() const;
  static BuilderEnviromentStructElem fromJSON(AnsiString);

  virtual ~BuilderEnviromentStructElem();

};
//----------------------------------

//------------- BuilderEnviromentStructElemArray ---------------
#include "DynSet.h"


class BuilderEnviromentStructElemArray : public DynSet<BuilderEnviromentStructElem> {
public:
  BuilderEnviromentStructElemArray();

  virtual AnsiString toJSON() const;
  static BuilderEnviromentStructElemArray fromJSON(AnsiString);

  virtual ~BuilderEnviromentStructElemArray();

};
//----------------------------------

//------------- BuilderEnviromentStruct ---------------
class BuilderEnviromentStruct {
  AnsiString name;
  BuilderEnviromentStructElemArray elems;
public:
  BuilderEnviromentStruct(const AnsiString&, const BuilderEnviromentStructElemArray&);
  virtual const AnsiString& getName() const;
  virtual const BuilderEnviromentStructElemArray& getElems() const;
  virtual AnsiString& getName();
  virtual BuilderEnviromentStructElemArray& getElems();

  virtual AnsiString toJSON() const;
  static BuilderEnviromentStruct fromJSON(AnsiString);

  virtual ~BuilderEnviromentStruct();

};
//----------------------------------

//------------- BuilderEnviromentStructArray ---------------
#include "DynSet.h"


class BuilderEnviromentStructArray : public DynSet<BuilderEnviromentStruct> {
public:
  BuilderEnviromentStructArray();

  virtual AnsiString toJSON() const;
  static BuilderEnviromentStructArray fromJSON(AnsiString);

  virtual ~BuilderEnviromentStructArray();

};
//----------------------------------

//------------- BuilderEnviroment ---------------
class BuilderEnviroment {
  BuilderEnviromentElementArray idents;
  BuilderEnviromentStructArray structs;
public:
  BuilderEnviroment(const BuilderEnviromentElementArray&, const BuilderEnviromentStructArray&);
  virtual const BuilderEnviromentElementArray& getIdents() const;
  virtual const BuilderEnviromentStructArray& getStructs() const;
  virtual BuilderEnviromentElementArray& getIdents();
  virtual BuilderEnviromentStructArray& getStructs();

  virtual AnsiString toJSON() const;
  static BuilderEnviroment fromJSON(AnsiString);

  virtual ~BuilderEnviroment();

};
//----------------------------------

#endif
