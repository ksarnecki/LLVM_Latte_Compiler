declare void @printInt(i32);
define i32 @main(i32 %argc, i8** %argv) {
  %reg_0 = add i32 2, 0
  %a_.v0 = add i32 %reg_0, 0
  %reg_1 = mul i32 %a_.v0, %a_.v0
  %a_.v1 = add i32 %reg_1, 0
  %reg_2 = add i32 24, 0
  %reg_3 = add i32 6, 0
  %reg_4 = udiv i32 %reg_2, %reg_3
  %reg_5 = add i32 %reg_4, %a_.v1
  %reg_6 = add i32 %a_.v1, %reg_5
  %a_.v2 = add i32 %reg_6, 0
  %reg_7 = add i32 3, 0
  %reg_8 = mul i32 %reg_7, %a_.v2
  %a_.v3 = add i32 %reg_8, 0
  call void @printInt(i32 %reg_0)
  call void @printInt(i32 %a_.v0)
  call void @printInt(i32 %reg_1)
  call void @printInt(i32 %a_.v1)
  call void @printInt(i32 %reg_2)
  call void @printInt(i32 %reg_3)
  call void @printInt(i32 %reg_4)
  call void @printInt(i32 %reg_5)
  call void @printInt(i32 %reg_6)
  call void @printInt(i32 %a_.v2)
  call void @printInt(i32 %reg_7)
  call void @printInt(i32 %reg_8)
  call void @printInt(i32 %a_.v3)
  ret i32 0
}
