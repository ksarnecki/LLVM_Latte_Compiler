declare void @printInt(i32);
define i32 @fact(i32 %reg_0) {
fact_entry: 
  %reg_1 = add i32 1, 0
  %reg_2 = add i32 1, 0
  br label %while_cond_0
while_cond_0: 
  %reg_3  = phi i32 [%reg_0, %fact_entry],[%reg_3, %while_body_0]
  %reg_4  = phi i32 [%reg_1, %fact_entry],[%reg_4, %while_body_0]
  %reg_5  = phi i32 [%reg_2, %fact_entry],[%reg_9, %while_body_0]
  %reg_6 = add i32 1, 0
  %reg_7 = add i32 %reg_3, %reg_6
  %reg_8 = icmp ult i32 %reg_4, %reg_7
  br i1 %reg_8, label %while_body_0, label %while_end_0
while_body_0: 
  %reg_9 = mul i32 %reg_5, %reg_4
  br label %while_cond_0
while_end_0: 
  ret i32 %reg_5
}

define i32 @factr(i32 %reg_10) {
factr_entry: 
  br label %if_cond_0
if_cond_0: 
  %reg_11 = add i32 2, 0
  %reg_12 = icmp ult i32 %reg_10, %reg_11
  br i1 %reg_12, label %if_body_0, label %if_else_0
if_body_0: 
  %reg_13 = add i32 1, 0
  ret i32 %reg_13
if_else_0: 
  %reg_14 = add i32 1, 0
  %reg_15 = sub i32 %reg_10, %reg_14
  %reg_16 = call i32 @factr(i32 %reg_15)
  %reg_17 = mul i32 %reg_10, %reg_16
  ret i32 %reg_17
}

define i32 @main() {
main_entry: 
  %reg_20 = add i32 7, 0
  %reg_21 = call i32 @fact(i32 %reg_20)
  call void @printInt(i32 %reg_21)
  %reg_22 = add i32 7, 0
  %reg_23 = call i32 @factr(i32 %reg_22)
  call void @printInt(i32 %reg_23)
  %reg_24 = add i32 0, 0
  ret i32 %reg_24
}

