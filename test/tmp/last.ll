declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
define i32 @main() {
main_entry: 
  %reg_0 = call i32 @readInt()
  %reg_1 = call i8* @readString()
  %reg_2 = call i8* @readString()
  %reg_3 = add i32 5, 0
  %reg_4 = sub i32 %reg_0, %reg_3
  call void @printInt(i32 %reg_4)
  %reg_5 = call i8* @concatenate(i8* %reg_1,i8* %reg_2)
  call void @printString(i8* %reg_5)
  %reg_6 = add i32 0, 0
  ret i32 %reg_6
}

