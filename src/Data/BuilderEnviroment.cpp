
#include "BuilderEnviroment.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Ident ---------------
//----------------------------------

//------------- BuilderEnviromentElement ---------------
BuilderEnviromentElement::BuilderEnviromentElement(const Ident& _ident, const int& _storeId) : ident(_ident), storeId(_storeId) {
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
BuilderEnviromentElement::~BuilderEnviromentElement() {
}
//----------------------------------

//------------- BuilderEnviroment ---------------
BuilderEnviroment::BuilderEnviroment() {
}
BuilderEnviroment::~BuilderEnviroment() {
}
//----------------------------------

