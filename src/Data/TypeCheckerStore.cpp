
#include "TypeCheckerStore.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Type ---------------
//----------------------------------

//------------- TypeCheckerStoreElement ---------------
TypeCheckerStoreElement::TypeCheckerStoreElement(const int& _id, const Type& _type) : id(_id), type(_type) {
}
const int& TypeCheckerStoreElement::getId() const {
  return id;
}
int& TypeCheckerStoreElement::getId() {
  return id;
}
const Type& TypeCheckerStoreElement::getType() const {
  return type;
}
Type& TypeCheckerStoreElement::getType() {
  return type;
}
TypeCheckerStoreElement::~TypeCheckerStoreElement() {
}
//----------------------------------

//------------- TypeCheckerStore ---------------
TypeCheckerStore::TypeCheckerStore() {
}
TypeCheckerStore::~TypeCheckerStore() {
}
//----------------------------------

