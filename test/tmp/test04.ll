declare void @printInt(i32);
define i32 @main(i32 %argc, i8** %argv) {
  %reg_0 = add i32 1, 0
  %a_.v0 = add i32 %reg_0, 0
  %reg_1 = add i32 2, 0
  %b_.v0 = add i32 %reg_1, 0
  %reg_2 = add i32 1, 0
  %reg_3 = add i32 1, 0
  %reg_4 = add i32 1, 0
  %reg_5 = add i32 1, 0
  %reg_6 = add i32 1, 0
  %reg_7 = add i32 1, 0
  %reg_8 = add i32 1, 0
  %reg_9 = add i32 %a_.v0, %b_.v0
  %reg_10 = add i32 %reg_8, %reg_9
  %reg_11 = add i32 %a_.v0, %reg_10
  %reg_12 = add i32 %a_.v0, %reg_11
  %reg_13 = add i32 %reg_7, %reg_12
  %reg_14 = add i32 %a_.v0, %reg_13
  %reg_15 = add i32 %a_.v0, %reg_14
  %reg_16 = add i32 %reg_6, %reg_15
  %reg_17 = add i32 %a_.v0, %reg_16
  %reg_18 = add i32 %a_.v0, %reg_17
  %reg_19 = add i32 %a_.v0, %reg_18
  %reg_20 = add i32 %a_.v0, %reg_19
  %reg_21 = add i32 %reg_5, %reg_20
  %reg_22 = add i32 %a_.v0, %reg_21
  %reg_23 = add i32 %a_.v0, %reg_22
  %reg_24 = add i32 %a_.v0, %reg_23
  %reg_25 = add i32 %a_.v0, %reg_24
  %reg_26 = add i32 %a_.v0, %reg_25
  %reg_27 = add i32 %a_.v0, %reg_26
  %reg_28 = add i32 %a_.v0, %reg_27
  %reg_29 = add i32 %a_.v0, %reg_28
  %reg_30 = add i32 %a_.v0, %reg_29
  %reg_31 = add i32 %a_.v0, %reg_30
  %reg_32 = add i32 %reg_4, %reg_31
  %reg_33 = add i32 %b_.v0, %reg_32
  %reg_34 = add i32 %a_.v0, %reg_33
  %reg_35 = add i32 %a_.v0, %reg_34
  %reg_36 = add i32 %a_.v0, %reg_35
  %reg_37 = add i32 %reg_3, %reg_36
  %reg_38 = add i32 %a_.v0, %reg_37
  %reg_39 = add i32 %a_.v0, %reg_38
  %reg_40 = add i32 %a_.v0, %reg_39
  %reg_41 = add i32 %a_.v0, %reg_40
  %reg_42 = add i32 %a_.v0, %reg_41
  %reg_43 = add i32 %reg_2, %reg_42
  %reg_44 = add i32 %a_.v0, %reg_43
  %reg_45 = add i32 %a_.v0, %reg_44
  %reg_46 = add i32 %b_.v0, %reg_45
  call void @printInt(i32 %reg_46)
  ret i32 0
}
