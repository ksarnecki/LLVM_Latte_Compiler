//---------------------------------------------------------------------------

#ifndef StringUtilH
#define StringUtilH
//---------------------------------------------------------------------------

#include "AnsiString.h"
#include "DynSet.h"

extern AnsiString Replace(const AnsiString&, const AnsiString&, const AnsiString&);
extern DynSet<AnsiString> ExpandLine(const AnsiString&, char);

#ifdef __GNUC__

extern char DecimalSeparator;

#endif

#endif
