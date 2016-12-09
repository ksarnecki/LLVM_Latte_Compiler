
#include "TypeCheckerEnviroment.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Ident ---------------
//----------------------------------

//------------- TypeCheckerEnviromentElement ---------------
TypeCheckerEnviromentElement::TypeCheckerEnviromentElement(const Ident& _ident, const int& _storeId, const int& _nesting) : ident(_ident), storeId(_storeId), nesting(_nesting) {
}
const Ident& TypeCheckerEnviromentElement::getIdent() const {
  return ident;
}
Ident& TypeCheckerEnviromentElement::getIdent() {
  return ident;
}
const int& TypeCheckerEnviromentElement::getStoreId() const {
  return storeId;
}
int& TypeCheckerEnviromentElement::getStoreId() {
  return storeId;
}
const int& TypeCheckerEnviromentElement::getNesting() const {
  return nesting;
}
int& TypeCheckerEnviromentElement::getNesting() {
  return nesting;
}
TypeCheckerEnviromentElement::~TypeCheckerEnviromentElement() {
}
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
TypeCheckerEnviroment::TypeCheckerEnviroment() {
}
TypeCheckerEnviroment::~TypeCheckerEnviroment() {
}
//----------------------------------

