declare void @printInt(i32);
define i32 @fact(i32 %reg_0) {
fact_entry: 
  %reg_1 = add i32 1, 0
  %reg_2 = add i32 1, 0
  br label %while_cond_0
while_cond_0: 
  %reg_3  = phi i32 [%reg_0, %fact_entry],[%reg_3, %while_body_0]
  %reg_4  = phi i32 [%reg_1, %fact_entry],[%reg_11, %while_body_0]
  %reg_5  = phi i32 [%reg_2, %fact_entry],[%reg_9, %while_body_0]
  %reg_6 = add i32 1, 0
  %reg_7 = add i32 %reg_3, %reg_6
  %reg_8 = icmp ult i32 %reg_4, %reg_7
  br i1 %reg_8, label %while_body_0, label %while_end_0
while_body_0: 
  %reg_9 = mul i32 %reg_5, %reg_4
  call void @printInt(i32 %reg_9)
  %reg_10 = add i32 1, 0
  %reg_11 = add i32 %reg_4, %reg_10
  br label %while_cond_0
while_end_0: 
  ret i32 %reg_5
}

define i32 @main() {
main_entry: 
  %reg_12 = add i32 7, 0
  call i32 @fact(i32 %reg_12)
  call void @printInt(i32 %reg_12)
  %reg_13 = add i32 0, 0
  ret i32 %reg_13
}

