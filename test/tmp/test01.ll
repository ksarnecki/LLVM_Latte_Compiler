declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
define i32 @fact(i32 %reg_0) {
fact_entry: 
  %reg_1 = add i32 1, 0
  %reg_2 = add i32 1, 0
  %reg_3 = add i32 8, 0
  br label %while_cond_0
while_cond_0: 
  %reg_4  = phi i32 [%reg_0, %fact_entry],[%reg_4, %while_body_1]
  %reg_5  = phi i32 [%reg_1, %fact_entry],[%reg_12, %while_body_1]
  %reg_6  = phi i32 [%reg_2, %fact_entry],[%reg_11, %while_body_1]
  %reg_7  = phi i32 [%reg_3, %fact_entry],[%reg_7, %while_body_1]
  %reg_8 = add i32 1, 0
  %reg_9 = add i32 %reg_4, %reg_8
  %reg_10 = icmp ult i32 %reg_5, %reg_9
  br i1 %reg_10, label %while_body_1, label %while_end_2
while_body_1: 
  %reg_11 = mul i32 %reg_6, %reg_5
  %reg_12 = add i32 %reg_5, 1
  call void @printInt(i32 %reg_12)
  br label %while_cond_0
while_end_2: 
  ret i32 %reg_6
}

define i32 @factr(i32 %reg_13) {
factr_entry: 
  br label %if_cond_3
if_cond_3: 
  %reg_14 = add i32 2, 0
  %reg_15 = icmp ult i32 %reg_13, %reg_14
  br i1 %reg_15, label %if_body_4, label %if_else_5
if_body_4: 
  %reg_16 = add i32 1, 0
  ret i32 %reg_16
if_else_5: 
  %reg_17 = add i32 1, 0
  %reg_18 = sub i32 %reg_13, %reg_17
  %reg_19 = call i32 @factr(i32 %reg_18)
  %reg_20 = mul i32 %reg_13, %reg_19
  ret i32 %reg_20
}

define i32 @main() {
main_entry: 
  %reg_22 = add i1 0, 0
  br label %if_cond_7
if_cond_7: 
  br i1 %reg_22, label %if_body_8, label %if_end_9
if_body_8: 
  %reg_23 = add i32 1, 0
  call void @printInt(i32 %reg_23)
  br label %if_end_9
if_end_9: 
  %reg_24  = phi i1 [%reg_22, %if_body_8],[%reg_22, %if_cond_7]
  br label %if_cond_10
if_cond_10: 
  %reg_25 = sub i1 %reg_22, 1
  br i1 %reg_25, label %if_body_11, label %if_end_12
if_body_11: 
  %reg_26 = add i32 2, 0
  call void @printInt(i32 %reg_26)
  br label %if_end_12
if_end_12: 
  %reg_27  = phi i1 [%reg_22, %if_body_11],[%reg_22, %if_cond_10]
  %reg_28 = add i32 0, 0
  ret i32 %reg_28
}

