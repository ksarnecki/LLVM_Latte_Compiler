declare void @printInt(i32);
define i32 @main(i32 %argc, i8** %argv) {
  %reg_0 = add i32 42, 0
  call void @printInt(i32 %reg_0)
  ret i32 0
}
