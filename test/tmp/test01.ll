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
while_body_0: 
while_cond_0: 
  %reg_7 = add i32 5, 0
  %reg_8 = icmp lt i32 %reg_3, %reg_7
  br i1 %reg_8, label %while_body_0, label %while_end_0
while_end_0: 
}

