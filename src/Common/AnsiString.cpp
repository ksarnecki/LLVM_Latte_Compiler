
#include "AnsiString.h"

#ifdef __GNUC__

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static AnsiString AnsiStringDoubleParser(double v) { // to work properly for numbers [xxxxxx.yyyyyyy] 6x - x and 7x - y
  if (v<0)
    return "-" + AnsiStringDoubleParser(-v);
  int t = (int) trunc(v);
  v -= t;
  if (v<0.00000001)
    return t;
  if (v>0.99999999)
    return t + 1;
  char buf[64];
  sprintf(buf, "%.8lf", v);
  AnsiString t1(buf);
//  t1 = Replace(t1, ",", ".");
  if (t1.Length()<=2)
    return t;
  t1 = t1.SubString(2, t1.Length() - 1); // returned string has to be in format 0.xxxxxx
  for (int i=t1.Length();i>0;i--)
    if (t1[i]!='0') {
      t1 = t1.SubString(1, i);
      break ;
    }
  return AnsiString(t) + t1;
}

AnsiString::AnsiString() {
}

AnsiString::AnsiString(const char* ch) : str(ch) {
}

AnsiString::AnsiString(const char* ch, int len) : str(ch, len) {
}

AnsiString::AnsiString(const std::string& _str) : str(_str) {
}

AnsiString::AnsiString(char c) : str(&c, 1) {
}

AnsiString::AnsiString(double v) : str(AnsiStringDoubleParser(v).c_str()) {
}

AnsiString::AnsiString(int v) {
  char buf[64];
  sprintf(buf, "%d", v);
  str = buf;
}

AnsiString::AnsiString(unsigned int v) {
  char buf[64];
  sprintf(buf, "%u", v);
  str = buf;
}
  
AnsiString& AnsiString::operator=(const char* ch) {
  str = ch;
  return *this;
}

AnsiString& AnsiString::operator=(const std::string& _str) {
  str = _str;
  return *this;
}

const char* AnsiString::c_str() const {
  return str.c_str();
}
  
int AnsiString::Length() const {
  return str.length();
}

char AnsiString::operator[](int ix) const {
  return str[ix-1];
}

char& AnsiString::operator[](int ix) {
  return str[ix-1];
}

AnsiString AnsiString::operator+(const AnsiString& s) const {
  return AnsiString(str + s.str);
}

AnsiString& AnsiString::operator+=(const AnsiString& s) {
  str += s.str;
  return *this;
}
  
bool AnsiString::operator==(const AnsiString& s) const {
  return str==s.str;
}

bool AnsiString::operator!=(const AnsiString& s) const {
  return str!=s.str;
}

bool AnsiString::operator<(const AnsiString& s) const {
  return str<s.str;
}

bool AnsiString::operator>(const AnsiString& s) const {
  return str>s.str;
}

AnsiString AnsiString::SubString(int ix, int len) const {
  return str.substr(ix-1, len);
}

bool isBlank(char c) {
  return c>=0 && c<=' ';
}

AnsiString AnsiString::Trim() const {
  int left = 0;
  while (left<str.length() && isBlank(str[left]))
    left++;
  int right = str.length() - 1;
  while (right>left && isBlank(str[right]))
    right--;
  if (left==str.length())
    return AnsiString();
  else
    return AnsiString(str.substr(left, right - left + 1));
}

char upCase(char c) {
  if (c>='a' && c<='z')
    return c - 'a' + 'A';
  else if (c=='¹')
    return '¥';
  else if (c=='¿')
    return '¯';
  else if (c=='œ')
    return 'Œ';
  else if (c=='Ÿ')
    return '';
  else if (c=='ê')
    return 'Ê';
  else if (c=='æ')
    return 'Æ';
  else if (c=='ó')
    return 'Ó';
  else if (c=='³')
    return '£';
  else if (c=='ñ')
    return 'Ñ';
  else
    return c;
}

AnsiString AnsiString::UpperCase() const {
  std::string ret(str);
  for (int i=0;i<ret.length();i++)
    ret[i] = upCase(ret[i]);
  return ret;
}

AnsiString AnsiString::Replace(const AnsiString& a, const AnsiString& b, const AnsiString& c) {
  return a;
}

int AnsiString::Pos(const AnsiString& pattern) const {
  int pos = str.find(pattern.c_str());
  return pos + 1;
}

int AnsiString::ToInt() const {
  char* end;
  const char* buf = str.c_str();
  int v = strtol(buf, &end, 10);
  if (str.length()==0)
    throw AnsiString("AnsiString::ToInt("+(*this)+")");
  if (*end!='\0')
    throw AnsiString("AnsiString::ToInt("+(*this)+")");
  return v;
}
int AnsiString::ToIntDef(int v) const {
  try {
    return ToInt();
  } catch (...) {
    return v;
  }
}
double AnsiString::ToDouble() const {
  char* end;
  const char* buf = str.c_str();
  double v = strtod(buf, &end);
  if (str.length()==0)
    throw AnsiString("AnsiString::ToDouble("+(*this)+")");
  if (*end!='\0')
    throw AnsiString("AnsiString::ToDouble("+(*this)+")");
  return v;
}

AnsiString::~AnsiString() {
}

AnsiString operator+(const char* ch, const AnsiString& s) {
  AnsiString str(ch);
  return str + s;
}

#endif

