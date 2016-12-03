
#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "../Common/AnsiString.h"

#ifdef __GNUC__

class Exception {
public:
  AnsiString Message;
public:
  Exception();
  Exception(const AnsiString&);
  virtual ~Exception();
};

#endif

#endif
