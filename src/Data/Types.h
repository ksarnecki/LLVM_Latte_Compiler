#ifndef _TYPES_GEN_H_
#define _TYPES_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Register ---------------
#include "Register.h"
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
#include "TypeCheckerEnviroment.h"
//----------------------------------

//------------- TypeArray ---------------
#include "DynSet.h"

class Type;

class TypeArray : public DynSet<Type> {
public:
  TypeArray();


  virtual ~TypeArray();

};
//----------------------------------

//------------- BasicTypeArray ---------------
#include "DynSet.h"

class BasicType;

class BasicTypeArray : public DynSet<BasicType> {
public:
  BasicTypeArray();


  virtual ~BasicTypeArray();

};
//----------------------------------

//------------- FunctionTypeArray ---------------
#include "DynSet.h"

class FunctionType;

class FunctionTypeArray : public DynSet<FunctionType> {
public:
  FunctionTypeArray();


  virtual ~FunctionTypeArray();

};
//----------------------------------

//------------- Type ---------------
class Type {
  int _type;
  void* _ptr;

  static const int _TypeBasic;
  static const int _TypeFunction;
  static const int _TypeNull;

  virtual void init(int, void*);
  virtual void clean();
  Type();
public:
  Type(const Type&);
  virtual Type& operator=(const Type&);

  virtual bool isBasic() const;
  virtual bool isFunction() const;
  virtual bool isNull() const;

  virtual const BasicType& asBasic() const;
  virtual BasicType& asBasic();
  virtual const FunctionType& asFunction() const;
  virtual FunctionType& asFunction();


  virtual ~Type();

  static Type createBasic(const BasicType&);
  static Type createFunction(const FunctionType&);
  static Type createNull();

};
//----------------------------------

//------------- BasicType ---------------
class BasicType {
  int _type;
  void* _ptr;

  static const int _TypeInt;
  static const int _TypeBool;
  static const int _TypeDouble;
  static const int _TypeChar;
  static const int _TypeString;
  static const int _TypeVoid;

  virtual void init(int, void*);
  virtual void clean();
  BasicType();
public:
  BasicType(const BasicType&);
  virtual BasicType& operator=(const BasicType&);

  virtual bool isInt() const;
  virtual bool isBool() const;
  virtual bool isDouble() const;
  virtual bool isChar() const;
  virtual bool isString() const;
  virtual bool isVoid() const;



  virtual ~BasicType();

  static BasicType createInt();
  static BasicType createBool();
  static BasicType createDouble();
  static BasicType createChar();
  static BasicType createString();
  static BasicType createVoid();

};
//----------------------------------

//------------- FunctionType ---------------
class FunctionType {
  Type returnType;
  TypeArray args;
  TypeCheckerEnviroment env;
public:
  FunctionType(const Type&, const TypeArray&, const TypeCheckerEnviroment&);
  virtual const Type& getReturnType() const;
  virtual const TypeArray& getArgs() const;
  virtual const TypeCheckerEnviroment& getEnv() const;
  virtual Type& getReturnType();
  virtual TypeArray& getArgs();
  virtual TypeCheckerEnviroment& getEnv();


  virtual ~FunctionType();

};
//----------------------------------

#endif
