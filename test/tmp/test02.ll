declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
@.str1 = private unnamed_addr constant [7 x i8] c"leszcz\00", align 1
@.str7 = private unnamed_addr constant [5 x i8] c"dupa\00", align 1
define void @foo(i8* %reg_0) {
foo_entry: 
  call void @printString(i8* %reg_0)
  %reg_2 = alloca i8*
  %reg_3 = add i32 0, 0
  %reg_4 = add i32 0, 0
  %reg_5 = getelementptr [ 7 x i8]* @.str1, i32 %reg_3, i32 %reg_4
  store i8* %reg_5, i8** %reg_2
  %reg_6 = load i8** %reg_2
  call void @printString(i8* %reg_6)
  ret void
}

define i32 @main() {
main_entry: 
  %reg_8 = alloca i8*
  %reg_9 = add i32 0, 0
  %reg_10 = add i32 0, 0
  %reg_11 = getelementptr [ 5 x i8]* @.str7, i32 %reg_9, i32 %reg_10
  store i8* %reg_11, i8** %reg_8
  %reg_12 = load i8** %reg_8
  call void @printString(i8* %reg_12)
  call void @foo(i8* %reg_12)
  call void @printString(i8* %reg_12)
  %reg_13 = add i32 0, 0
  ret i32 %reg_13
}

