
#include "TypeError.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- TypeError ---------------
TypeError::TypeError(const int& _line, const AnsiString& _msg) : line(_line), msg(_msg) {
}
const int& TypeError::getLine() const {
  return line;
}
int& TypeError::getLine() {
  return line;
}
const AnsiString& TypeError::getMsg() const {
  return msg;
}
AnsiString& TypeError::getMsg() {
  return msg;
}
TypeError::~TypeError() {
}
//----------------------------------

//------------- TypeErrors ---------------
TypeErrors::TypeErrors() {
}
TypeErrors::~TypeErrors() {
}
//----------------------------------

