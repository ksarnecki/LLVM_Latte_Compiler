
#include "Enviroment.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Ident ---------------
//----------------------------------

//------------- EnviromentElement ---------------
EnviromentElement::EnviromentElement(const Ident& _ident, const int& _storeId, const int& _nesting) : ident(_ident), storeId(_storeId), nesting(_nesting) {
}
const Ident& EnviromentElement::getIdent() const {
  return ident;
}
Ident& EnviromentElement::getIdent() {
  return ident;
}
const int& EnviromentElement::getStoreId() const {
  return storeId;
}
int& EnviromentElement::getStoreId() {
  return storeId;
}
const int& EnviromentElement::getNesting() const {
  return nesting;
}
int& EnviromentElement::getNesting() {
  return nesting;
}
EnviromentElement::~EnviromentElement() {
}
//----------------------------------

//------------- Enviroment ---------------
Enviroment::Enviroment() {
}
Enviroment::~Enviroment() {
}
//----------------------------------

