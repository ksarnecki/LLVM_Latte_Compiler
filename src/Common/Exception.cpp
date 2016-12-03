
#include "Exception.h"

#ifdef __GNUC__

#include <stdio.h>

Exception::Exception() {
}

Exception::Exception(const AnsiString& _msg) : Message(_msg) {
  printf("E:(%s)\n", _msg.c_str());
}

Exception::~Exception() {
}

#endif

