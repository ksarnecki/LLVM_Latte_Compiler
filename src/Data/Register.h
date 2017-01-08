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

//------------- ConstPtrArray ---------------
#include "DynSet.h"

class ConstPtr;

class ConstPtrArray : public DynSet<ConstPtr> {
public:
  ConstPtrArray();

  virtual AnsiString toJSON() const;
  static ConstPtrArray fromJSON(AnsiString);

  virtual ~ConstPtrArray();

};
//----------------------------------

//------------- RegisterKindArray ---------------
#include "DynSet.h"

class RegisterKind;

class RegisterKindArray : public DynSet<RegisterKind> {
public:
  RegisterKindArray();

  virtual AnsiString toJSON() const;
  static RegisterKindArray fromJSON(AnsiString);

  virtual ~RegisterKindArray();

};
//----------------------------------

//------------- RegisterKind ---------------
class RegisterKind {
  int _type;
  void* _ptr;

  static const int _TypeValueI1;
  static const int _TypeValueI8;
  static const int _TypeValueI32;
  static const int _TypePtr;
  static const int _TypeConstPtr;
  static const int _TypeStruct;
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
  virtual bool isPtr() const;
  virtual bool isConstPtr() const;
  virtual bool isStruct() const;
  virtual bool isNull() const;

  virtual const RegisterKind& asPtr() const;
  virtual RegisterKind& asPtr();
  virtual const ConstPtr& asConstPtr() const;
  virtual ConstPtr& asConstPtr();
  virtual const AnsiString& asStruct() const;
  virtual AnsiString& asStruct();

  virtual AnsiString toJSON() const;
  static RegisterKind fromJSON(AnsiString);

  virtual ~RegisterKind();

  static RegisterKind createValueI1();
  static RegisterKind createValueI8();
  static RegisterKind createValueI32();
  static RegisterKind createPtr(const RegisterKind&);
  static RegisterKind createConstPtr(const ConstPtr&);
  static RegisterKind createStruct(const AnsiString&);
  static RegisterKind createNull();

};
//----------------------------------

//------------- ConstPtr ---------------
class ConstPtr {
  RegisterKind kind;
  int count;
public:
  ConstPtr(const RegisterKind&, const int&);
  virtual const RegisterKind& getKind() const;
  virtual const int& getCount() const;
  virtual RegisterKind& getKind();
  virtual int& getCount();

  virtual AnsiString toJSON() const;
  static ConstPtr fromJSON(AnsiString);

  virtual ~ConstPtr();

};
//----------------------------------

//------------- RegisterPlain ---------------
class RegisterPlain {
  int _type;
  void* _ptr;

  static const int _TypeTrue;
  static const int _TypeFalse;

  virtual void init(int, void*);
  virtual void clean();
  RegisterPlain();
public:
  RegisterPlain(const RegisterPlain&);
  virtual RegisterPlain& operator=(const RegisterPlain&);

  virtual bool isTrue() const;
  virtual bool isFalse() const;

  virtual const AnsiString& asTrue() const;
  virtual AnsiString& asTrue();

  virtual AnsiString toJSON() const;
  static RegisterPlain fromJSON(AnsiString);

  virtual ~RegisterPlain();

  static RegisterPlain createTrue(const AnsiString&);
  static RegisterPlain createFalse();

};
//----------------------------------

//------------- Register ---------------
class Register {
  int id;
  RegisterKind kind;
  RegisterPlain plain;
public:
  Register(const int&, const RegisterKind&, const RegisterPlain&);
  virtual const int& getId() const;
  virtual const RegisterKind& getKind() const;
  virtual const RegisterPlain& getPlain() const;
  virtual int& getId();
  virtual RegisterKind& getKind();
  virtual RegisterPlain& getPlain();

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
