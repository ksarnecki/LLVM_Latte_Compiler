declare void @printInt(i32);
define i32 @main() {
main_entry: 
  %reg_0 = add i32 1, 0
  %reg_1 = add i32 2, 0
  %reg_2 = add i32 3, 0
  %reg_3 = add i32 %reg_0, %reg_2
  %reg_4 = add i32 2, 0
  %reg_5 = mul i32 %reg_4, %reg_3
  %reg_6 = add i32 %reg_5, %reg_1
  br label %while_cond_0
while_cond_0: 
  %reg_7  = phi i32 [%reg_3, %main_entry],[%reg_12, %while_body_0]
  %reg_8  = phi i32 [%reg_6, %main_entry],[%reg_8, %while_body_0]
  %reg_9 = add i32 12, 0
  %reg_10 = icmp ult i32 %reg_7, %reg_9
  br i1 %reg_10, label %while_body_0, label %while_end_0
while_body_0: 
  %reg_11 = add i32 1, 0
  %reg_12 = add i32 %reg_7, %reg_11
  call void @printInt(i32 %reg_12)
  br label %while_cond_0
while_end_0: 
  %reg_13 = add i32 4, 0
  %reg_14 = add i32 %reg_7, %reg_13
  ret i32 %reg_14
}

