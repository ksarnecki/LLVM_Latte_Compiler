#ifndef _TYPES_GEN_H_
#define _TYPES_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
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

  virtual AnsiString toJSON() const;
  static TypeArray fromJSON(AnsiString);

  virtual ~TypeArray();

};
//----------------------------------

//------------- BasicTypeArray ---------------
#include "DynSet.h"

class BasicType;

class BasicTypeArray : public DynSet<BasicType> {
public:
  BasicTypeArray();

  virtual AnsiString toJSON() const;
  static BasicTypeArray fromJSON(AnsiString);

  virtual ~BasicTypeArray();

};
//----------------------------------

//------------- FunctionTypeArray ---------------
#include "DynSet.h"

class FunctionType;

class FunctionTypeArray : public DynSet<FunctionType> {
public:
  FunctionTypeArray();

  virtual AnsiString toJSON() const;
  static FunctionTypeArray fromJSON(AnsiString);

  virtual ~FunctionTypeArray();

};
//----------------------------------

//------------- Type ---------------
class Type {
  int _type;
  void* _ptr;

  static const int _TypeBasic;
  static const int _TypeFunction;
  static const int _TypeArray;
  static const int _TypeNull;

  virtual void init(int, void*);
  virtual void clean();
  Type();
public:
  Type(const Type&);
  virtual Type& operator=(const Type&);

  virtual bool isBasic() const;
  virtual bool isFunction() const;
  virtual bool isArray() const;
  virtual bool isNull() const;

  virtual const BasicType& asBasic() const;
  virtual BasicType& asBasic();
  virtual const FunctionType& asFunction() const;
  virtual FunctionType& asFunction();
  virtual const Type& asArray() const;
  virtual Type& asArray();

  virtual AnsiString toJSON() const;
  static Type fromJSON(AnsiString);

  virtual ~Type();

  static Type createBasic(const BasicType&);
  static Type createFunction(const FunctionType&);
  static Type createArray(const Type&);
  static Type createNull();

};
//----------------------------------

//------------- BasicType ---------------
class BasicType {
  int _type;
  void* _ptr;

  static const int _TypeInt;
  static const int _TypeBool;
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
  virtual bool isString() const;
  virtual bool isVoid() const;


  virtual AnsiString toJSON() const;
  static BasicType fromJSON(AnsiString);

  virtual ~BasicType();

  static BasicType createInt();
  static BasicType createBool();
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

  virtual AnsiString toJSON() const;
  static FunctionType fromJSON(AnsiString);

  virtual ~FunctionType();

};
//----------------------------------

#endif
