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
  %reg_22 = add i32 5, 0
  br label %if_cond_7
if_cond_7: 
  %reg_23 = add i1 1, 0
  br i1 %reg_23, label %if_body_8, label %if_end_9
if_body_8: 
  %reg_24 = add i32 7, 0
  %reg_25 = call i32 @foo()
  call void @printInt(i32 %reg_25)
  br label %if_end_9
if_end_9: 
  %reg_26  = phi i32 [%reg_22, %if_body_8],[%reg_22, %if_cond_7]
  %reg_27 = add i1 0, 0
  br label %if_cond_10
if_cond_10: 
  br i1 %reg_27, label %if_body_11, label %if_end_12
if_body_11: 
  call void @printInt(i32 %reg_22)
  br label %if_end_12
if_end_12: 
  %reg_28  = phi i32 [%reg_22, %if_body_11],[%reg_22, %if_cond_10]
  %reg_29  = phi i1 [%reg_27, %if_body_11],[%reg_27, %if_cond_10]
  br label %if_cond_13
if_cond_13: 
  %reg_30 = sub i1 %reg_27, 1
  br i1 %reg_30, label %if_body_14, label %if_end_15
if_body_14: 
  call void @printInt(i32 %reg_22)
  br label %if_end_15
if_end_15: 
  %reg_31  = phi i32 [%reg_22, %if_body_14],[%reg_22, %if_cond_13]
  %reg_32  = phi i1 [%reg_27, %if_body_14],[%reg_27, %if_cond_13]
  %reg_33 = add i32 0, 0
  ret i32 %reg_33
}

define i32 @foo() {
foo_entry: 
  %reg_34 = add i32 12, 0
  ret i32 %reg_34
}

