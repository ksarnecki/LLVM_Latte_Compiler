#ifndef _TYPECHECKERSTORE_GEN_H_
#define _TYPECHECKERSTORE_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Type ---------------
#include "Types.h"
//----------------------------------

//------------- TypeCheckerStoreElement ---------------
class TypeCheckerStoreElement {
  int id;
  Type type;
public:
  TypeCheckerStoreElement(const int&, const Type&);
  virtual const int& getId() const;
  virtual const Type& getType() const;
  virtual int& getId();
  virtual Type& getType();


  virtual ~TypeCheckerStoreElement();

};
//----------------------------------

//------------- TypeCheckerStore ---------------
#include "DynSet.h"


class TypeCheckerStore : public DynSet<TypeCheckerStoreElement> {
public:
  TypeCheckerStore();


  virtual ~TypeCheckerStore();

};
//----------------------------------

#endif
