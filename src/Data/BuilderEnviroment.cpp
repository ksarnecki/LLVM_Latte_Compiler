
#include "BuilderEnviroment.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- BuilderEnviromentElement ---------------
BuilderEnviromentElement::BuilderEnviromentElement(const AnsiString& _ident, const int& _storeId) : ident(_ident), storeId(_storeId) {
}
const AnsiString& BuilderEnviromentElement::getIdent() const {
  return ident;
}
AnsiString& BuilderEnviromentElement::getIdent() {
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

