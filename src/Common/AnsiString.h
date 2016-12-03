
#ifndef _ANSISTRING_H_
#define _ANSISTRING_H_

#ifdef __GNUC__

#include <string>

class AnsiString {
  std::string str;
public:
  AnsiString();
  AnsiString(const char*);
  AnsiString(const char*, int);
  AnsiString(const std::string&);
  AnsiString(char);
  AnsiString(int);
  AnsiString(unsigned int);
  AnsiString(double);
  
  virtual AnsiString& operator=(const char*);
  virtual AnsiString& operator=(const std::string&);
  
  virtual const char* c_str() const;
  virtual int Length() const;
  virtual char operator[](int) const;
  virtual char& operator[](int);
  virtual AnsiString operator+(const AnsiString&) const;
  virtual AnsiString& operator+=(const AnsiString&);
  virtual AnsiString Trim() const;
  virtual AnsiString UpperCase() const;
  virtual int Pos(const AnsiString&) const;
  
  virtual bool operator==(const AnsiString&) const;
  virtual bool operator!=(const AnsiString&) const;
  virtual bool operator<(const AnsiString&) const;
  virtual bool operator>(const AnsiString&) const;
  
  virtual AnsiString SubString(int, int) const;
  virtual AnsiString Replace(const AnsiString&, const AnsiString&, const AnsiString&);
  virtual int ToInt() const;
  virtual int ToIntDef(int) const;
  virtual double ToDouble() const;
  
  virtual ~AnsiString();
  
  friend AnsiString operator+(const char*, const AnsiString&);
};

#else

#include <vcl.h>

#endif

#endif
