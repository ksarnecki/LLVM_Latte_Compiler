declare void @printInt(i32);
define i32 @main(i32 %argc, i8** %argv) {
  %reg_0 = add i32 44, 0
  %reg_1 = add i32 2, 0
  %reg_2 = sub i32 %reg_0, %reg_1
  call void @printInt(i32 %reg_2)
  ret i32 0
}
