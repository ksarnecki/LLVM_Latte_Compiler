
#include "BuilderEnviroment.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Ident ---------------
//----------------------------------

//------------- BuilderEnviromentElement ---------------
BuilderEnviromentElement::BuilderEnviromentElement(const Ident& _ident, const int& _storeId, const int& _nesting) : ident(_ident), storeId(_storeId), nesting(_nesting) {
}
const Ident& BuilderEnviromentElement::getIdent() const {
  return ident;
}
Ident& BuilderEnviromentElement::getIdent() {
  return ident;
}
const int& BuilderEnviromentElement::getStoreId() const {
  return storeId;
}
int& BuilderEnviromentElement::getStoreId() {
  return storeId;
}
const int& BuilderEnviromentElement::getNesting() const {
  return nesting;
}
int& BuilderEnviromentElement::getNesting() {
  return nesting;
}
BuilderEnviromentElement::~BuilderEnviromentElement() {
}
//----------------------------------

//------------- BuilderEnviroment ---------------
BuilderEnviroment::BuilderEnviroment() {
}
BuilderEnviroment::~BuilderEnviroment() {
}
//----------------------------------

