//---------------------------------------------------------------------------

#ifndef JSONUtilH
#define JSONUtilH
//---------------------------------------------------------------------------

#include "AnsiString.h"

class JSONEscape {
public:
  static AnsiString encode(const AnsiString&);
  static AnsiString decode(const AnsiString& v);
};

#endif
