#ifndef _STORE_GEN_H_
#define _STORE_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Type ---------------
#include "Types.h"
//----------------------------------

//------------- StoreElement ---------------
class StoreElement {
  int id;
  Type type;
public:
  StoreElement(const int&, const Type&);
  virtual const int& getId() const;
  virtual const Type& getType() const;
  virtual int& getId();
  virtual Type& getType();


  virtual ~StoreElement();

};
//----------------------------------

//------------- Store ---------------
#include "DynSet.h"


class Store : public DynSet<StoreElement> {
public:
  Store();


  virtual ~Store();

};
//----------------------------------

#endif
