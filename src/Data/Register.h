#ifndef _REGISTER_GEN_H_
#define _REGISTER_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Ident ---------------
#include "Absyn.H"
//----------------------------------

//------------- RegisterArray ---------------
#include "DynSet.h"

class Register;

class RegisterArray : public DynSet<Register> {
public:
  RegisterArray();

  virtual AnsiString toJSON() const;
  static RegisterArray fromJSON(AnsiString);

  virtual ~RegisterArray();

};
//----------------------------------

//------------- RegisterKind ---------------
class RegisterKind {
  int _type;
  void* _ptr;

  static const int _TypeValueI1;
  static const int _TypeValueI8;
  static const int _TypeValueI32;
  static const int _TypeValueDouble;
  static const int _TypePtr;
  static const int _TypeNull;

  virtual void init(int, void*);
  virtual void clean();
  RegisterKind();
public:
  RegisterKind(const RegisterKind&);
  virtual RegisterKind& operator=(const RegisterKind&);

  virtual bool isValueI1() const;
  virtual bool isValueI8() const;
  virtual bool isValueI32() const;
  virtual bool isValueDouble() const;
  virtual bool isPtr() const;
  virtual bool isNull() const;

  virtual const RegisterKind& asPtr() const;
  virtual RegisterKind& asPtr();

  virtual AnsiString toJSON() const;
  static RegisterKind fromJSON(AnsiString);

  virtual ~RegisterKind();

  static RegisterKind createValueI1();
  static RegisterKind createValueI8();
  static RegisterKind createValueI32();
  static RegisterKind createValueDouble();
  static RegisterKind createPtr(const RegisterKind&);
  static RegisterKind createNull();

};
//----------------------------------

//------------- Register ---------------
class Register {
  int id;
  RegisterKind kind;
public:
  Register(const int&, const RegisterKind&);
  virtual const int& getId() const;
  virtual const RegisterKind& getKind() const;
  virtual int& getId();
  virtual RegisterKind& getKind();

  virtual AnsiString toJSON() const;
  static Register fromJSON(AnsiString);

  virtual ~Register();

};
//----------------------------------

//------------- Registers ---------------
#include "DynSet.h"


class Registers : public DynSet<Register> {
public:
  Registers();

  virtual AnsiString toJSON() const;
  static Registers fromJSON(AnsiString);

  virtual ~Registers();

};
//----------------------------------

//------------- RegisterData ---------------
class RegisterData {
  Register lastRegister;
  Registers registers;
public:
  RegisterData(const Register&, const Registers&);
  virtual const Register& getLastRegister() const;
  virtual const Registers& getRegisters() const;
  virtual Register& getLastRegister();
  virtual Registers& getRegisters();

  virtual AnsiString toJSON() const;
  static RegisterData fromJSON(AnsiString);

  virtual ~RegisterData();

};
//----------------------------------

#endif
