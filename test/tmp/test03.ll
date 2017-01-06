declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
define i32* @sum(i32* %reg_0, i32* %reg_1, i32 %reg_2) {
sum_entry: 
  %reg_3 = add i32 3, 0
  %reg_4 = alloca i32, i32 %reg_3
  %reg_5 = add i32 0, 0
  %reg_6 = add i32 51, 0
  call void @printInt(i32 %reg_6)
  br label %while_cond_0
while_cond_0: 
  %reg_7  = phi i32 [%reg_6, %sum_entry],[%reg_7, %while_body_1]
  %reg_8  = phi i32 [%reg_5, %sum_entry],[%reg_21, %while_body_1]
  %reg_9 = add i32 3, 0
  %reg_10 = icmp ult i32 %reg_8, %reg_9
  br i1 %reg_10, label %while_body_1, label %while_end_2
while_body_1: 
  %reg_11 = getelementptr i32* %reg_0, i32 %reg_8
  %reg_12 = add i32 0, 0
  store i32 %reg_12, i32* %reg_11
  %reg_13 = getelementptr i32* %reg_4, i32 %reg_8
  %reg_14 = getelementptr i32* %reg_0, i32 %reg_8
  %reg_15 = load i32* %reg_14
  %reg_16 = getelementptr i32* %reg_1, i32 %reg_8
  %reg_17 = load i32* %reg_16
  %reg_18 = add i32 %reg_15, %reg_17
  store i32 %reg_18, i32* %reg_13
  %reg_19 = getelementptr i32* %reg_4, i32 %reg_8
  %reg_20 = load i32* %reg_19
  call void @printInt(i32 %reg_20)
  %reg_21 = add i32 %reg_8, 1
  br label %while_cond_0
while_end_2: 
  ret i32* %reg_4
}

define i32 @main() {
main_entry: 
  %reg_22 = add i32 3, 0
  %reg_23 = alloca i32, i32 %reg_22
  %reg_24 = add i32 3, 0
  %reg_25 = alloca i32, i32 %reg_24
  %reg_26 = add i32 0, 0
  %reg_27 = getelementptr i32* %reg_23, i32 %reg_26
  %reg_28 = add i32 1, 0
  store i32 %reg_28, i32* %reg_27
  %reg_29 = add i32 1, 0
  %reg_30 = getelementptr i32* %reg_23, i32 %reg_29
  %reg_31 = add i32 3, 0
  store i32 %reg_31, i32* %reg_30
  %reg_32 = add i32 2, 0
  %reg_33 = getelementptr i32* %reg_23, i32 %reg_32
  %reg_34 = add i32 5, 0
  store i32 %reg_34, i32* %reg_33
  %reg_35 = add i32 0, 0
  %reg_36 = getelementptr i32* %reg_25, i32 %reg_35
  %reg_37 = add i32 12, 0
  store i32 %reg_37, i32* %reg_36
  %reg_38 = add i32 1, 0
  %reg_39 = getelementptr i32* %reg_25, i32 %reg_38
  %reg_40 = add i32 31, 0
  store i32 %reg_40, i32* %reg_39
  %reg_41 = add i32 2, 0
  %reg_42 = getelementptr i32* %reg_25, i32 %reg_41
  %reg_43 = add i32 15, 0
  store i32 %reg_43, i32* %reg_42
  %reg_44 = alloca i32
  %reg_45 = add i32 0, 0
  %reg_46 = getelementptr i32* %reg_44, i32 %reg_45
  %reg_47 = load i32* %reg_46
  %reg_48 = add i32 1, 0
  %reg_49 = call i32* @sum(i32* %reg_23,i32* %reg_25,i32 %reg_48)
  %reg_50 = add i32 0, 0
  %reg_51 = getelementptr i32* %reg_49, i32 %reg_50
  %reg_52 = load i32* %reg_51
  %reg_53 = add i32 2, 0
  %reg_54 = getelementptr i32* %reg_49, i32 %reg_53
  %reg_55 = load i32* %reg_54
  %reg_56 = add i32 %reg_52, %reg_55
  call void @printInt(i32 %reg_56)
  call void @printInt(i32 %reg_48)
  %reg_57 = add i32 0, 0
  ret i32 %reg_57
}

