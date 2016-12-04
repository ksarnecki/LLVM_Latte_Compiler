
#include "Store.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Type ---------------
//----------------------------------

//------------- StoreElement ---------------
StoreElement::StoreElement(const int& _id, const Type& _type) : id(_id), type(_type) {
}
const int& StoreElement::getId() const {
  return id;
}
int& StoreElement::getId() {
  return id;
}
const Type& StoreElement::getType() const {
  return type;
}
Type& StoreElement::getType() {
  return type;
}
StoreElement::~StoreElement() {
}
//----------------------------------

//------------- Store ---------------
Store::Store() {
}
Store::~Store() {
}
//----------------------------------

