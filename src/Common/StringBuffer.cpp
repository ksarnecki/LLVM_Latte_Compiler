//---------------------------------------------------------------------------

#include "StringBuffer.h"

//---------------------------------------------------------------------------

void StringBuffer::init(const char _buf[], int _length) {
  if (_buf==0 || _length==0) {
    buf = 0;
    size = 0;
    length = 0;
  } else {
    buf = new char[_length];
    length = size = _length;
    for (int i=0;i<length;i++)
      buf[i] = _buf[i];
  }
}
void StringBuffer::upSize() {
  int s = 2 * size + 1;
  char* t = new char[s];
  for (int i=0;i<length;i++)
    t[i] = buf[i];
  if (buf!=0)
    delete[] buf;
  buf = t;
  size = s;
}
void StringBuffer::free() {
  if (buf!=0)
    delete[] buf;
  buf = 0;
  size = length = 0;
}
StringBuffer::StringBuffer() : buf(0), size(0), length(0) {
}
StringBuffer::StringBuffer(const AnsiString& str) : buf(0), size(0), length(0) {
  (*this) += str;
}
StringBuffer::StringBuffer(const StringBuffer& buffer) {
  init(buffer.buf, buffer.length);
}
StringBuffer& StringBuffer::operator=(const StringBuffer& buffer) {
  free();
  init(buffer.buf, buffer.length);
  return *this;
}
StringBuffer& StringBuffer::operator+=(const AnsiString& str) {
  while (length + str.Length()>size)
    upSize();
  for (int i=1;i<=str.Length();i++)
    buf[length++] = str[i];
  return *this;
}
StringBuffer& StringBuffer::operator+=(char c) {
  while (length + 1>size)
    upSize();
  buf[length++] = c;
  return *this;
}
StringBuffer& StringBuffer::operator+=(const char* str) {
  int l = 0;
  while (str[l]!=0)
    l++;
  while (length + l>size)
    upSize();
  for (int i=0;i<l;i++)
    buf[length++] = str[i];
  return *this;
}
AnsiString StringBuffer::get() const {
  if (length==0)
    return "";
  else
    return AnsiString(buf, length);
}
StringBuffer::~StringBuffer() {
  free();
}

#pragma package(smart_init)
