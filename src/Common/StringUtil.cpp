//---------------------------------------------------------------------------

#pragma hdrstop

#include "StringUtil.h"
#include "StringBuffer.h"

//---------------------------------------------------------------------------

AnsiString Replace(const AnsiString& str, const AnsiString& pat, const AnsiString& val) {
  StringBuffer ret;
  int i = 1;
  int l = pat.Length();

  while (i<=str.Length())
    if (str.SubString(i, l)==pat) {
      ret += val;
      i += l;
    } else
      ret += str[i++];

  return ret.get();
}

DynSet<AnsiString> ExpandLine(const AnsiString& line, char c) {
  DynSet<AnsiString> ret;

  int j = 1;
  for (int i=1;i<line.Length();i++)
    if (line[i]==c) {
      ret.Insert(line.SubString(j, i - j));
      j = i + 1;
    }
  if (j>line.Length())
    ret.Insert("");
  else
    ret.Insert(line.SubString(j, line.Length() - j + 1));

  return ret;
}

#ifdef __GNUC__

char DecimalSeparator = ',';

#endif

#pragma package(smart_init)
