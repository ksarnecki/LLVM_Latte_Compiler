//---------------------------------------------------------------------------

#include "JSONUtil.h"

#include "StringUtil.h"

//---------------------------------------------------------------------------

AnsiString JSONEscape::encode(const AnsiString& v) {
  AnsiString t = Replace(v, "\n", "\\n");
  t = Replace(t, "\r", "\\r");
  t = Replace(t, "\\", "\\\\");
  t = Replace(t, "\"", "\\\"");
  return t;
}

AnsiString JSONEscape::decode(const AnsiString& v) {
  AnsiString t = Replace(v, "\\n", "\n");
  t = Replace(t, "\\r", "\r");
  t = Replace(t, "\\\\", "\\");
  t = Replace(t, "\\\"","\"");
  return t;
}

