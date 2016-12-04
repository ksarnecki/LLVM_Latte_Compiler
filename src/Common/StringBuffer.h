//---------------------------------------------------------------------------

#ifndef StringBufferH
#define StringBufferH
//---------------------------------------------------------------------------

#include "AnsiString.h"

class StringBuffer {
  char* buf;
  int size;
  int length;

  virtual void init(const char*, int);
  virtual void upSize();
  virtual void free();
public:
  StringBuffer();
  StringBuffer(const AnsiString&);
  StringBuffer(const StringBuffer&);

  virtual StringBuffer& operator=(const StringBuffer&);

  virtual StringBuffer& operator+=(const AnsiString&);
  virtual StringBuffer& operator+=(char);
  virtual StringBuffer& operator+=(const char*);
  virtual AnsiString get() const;

  virtual ~StringBuffer();
};

#endif
