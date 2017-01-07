declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
@.str8 = private unnamed_addr constant [1 x i8] c"\00", align 1
@.str22 = private unnamed_addr constant [2 x i8] c"=\00", align 1
@.str30 = private unnamed_addr constant [9 x i8] c"hello */\00", align 1
@.str36 = private unnamed_addr constant [9 x i8] c"/* world\00", align 1
@.str105 = private unnamed_addr constant [1 x i8] c"\00", align 1
define i32 @main() {
main_entry: 
  %reg_0 = add i32 10, 0
  %reg_1 = call i32 @fac(i32 %reg_0)
  call void @printInt(i32 %reg_1)
  %reg_2 = add i32 10, 0
  %reg_3 = call i32 @rfac(i32 %reg_2)
  call void @printInt(i32 %reg_3)
  %reg_4 = add i32 10, 0
  %reg_5 = call i32 @mfac(i32 %reg_4)
  call void @printInt(i32 %reg_5)
  %reg_6 = add i32 10, 0
  %reg_7 = call i32 @ifac(i32 %reg_6)
  call void @printInt(i32 %reg_7)
  %reg_9 = alloca i8*
  %reg_10 = add i32 0, 0
  %reg_11 = add i32 0, 0
  %reg_12 = getelementptr [ 1 x i8]* @.str8, i32 %reg_10, i32 %reg_11
  store i8* %reg_12, i8** %reg_9
  %reg_13 = load i8** %reg_9
  %reg_14 = add i32 10, 0
  %reg_15 = add i32 1, 0
  br label %while_cond_0
while_cond_0: 
  %reg_16  = phi i32 [%reg_15, %main_entry],[%reg_20, %while_body_1]
  %reg_17  = phi i32 [%reg_14, %main_entry],[%reg_21, %while_body_1]
  %reg_18 = add i32 0, 0
  %reg_19 = icmp ugt i32 %reg_17, %reg_18
  br i1 %reg_19, label %while_body_1, label %while_end_2
while_body_1: 
  %reg_20 = mul i32 %reg_16, %reg_17
  %reg_21 = sub i32 %reg_17, 1
  br label %while_cond_0
while_end_2: 
  call void @printInt(i32 %reg_16)
  %reg_23 = alloca i8*
  %reg_24 = add i32 0, 0
  %reg_25 = add i32 0, 0
  %reg_26 = getelementptr [ 2 x i8]* @.str22, i32 %reg_24, i32 %reg_25
  store i8* %reg_26, i8** %reg_23
  %reg_27 = load i8** %reg_23
  %reg_28 = add i32 60, 0
  %reg_29 = call i8* @repStr(i8* %reg_27,i32 %reg_28)
  call void @printString(i8* %reg_29)
  %reg_31 = alloca i8*
  %reg_32 = add i32 0, 0
  %reg_33 = add i32 0, 0
  %reg_34 = getelementptr [ 9 x i8]* @.str30, i32 %reg_32, i32 %reg_33
  store i8* %reg_34, i8** %reg_31
  %reg_35 = load i8** %reg_31
  call void @printString(i8* %reg_35)
  %reg_37 = alloca i8*
  %reg_38 = add i32 0, 0
  %reg_39 = add i32 0, 0
  %reg_40 = getelementptr [ 9 x i8]* @.str36, i32 %reg_38, i32 %reg_39
  store i8* %reg_40, i8** %reg_37
  %reg_41 = load i8** %reg_37
  call void @printString(i8* %reg_41)
  %reg_42 = add i32 0, 0
  ret i32 %reg_42
}

define i32 @fac(i32 %reg_43) {
fac_entry: 
  %reg_44 = add i32 0, 0
  %reg_45 = add i32 0, 0
  %reg_46 = add i32 1, 0
  br label %while_cond_3
while_cond_3: 
  %reg_47  = phi i32 [%reg_43, %fac_entry],[%reg_47, %while_body_4]
  %reg_48  = phi i32 [%reg_46, %fac_entry],[%reg_52, %while_body_4]
  %reg_49  = phi i32 [%reg_43, %fac_entry],[%reg_54, %while_body_4]
  %reg_50 = add i32 0, 0
  %reg_51 = icmp ugt i32 %reg_49, %reg_50
  br i1 %reg_51, label %while_body_4, label %while_end_5
while_body_4: 
  %reg_52 = mul i32 %reg_48, %reg_49
  %reg_53 = add i32 1, 0
  %reg_54 = sub i32 %reg_49, %reg_53
  br label %while_cond_3
while_end_5: 
  ret i32 %reg_48
}

define i32 @rfac(i32 %reg_55) {
rfac_entry: 
  br label %if_cond_6
if_cond_6: 
  %reg_56 = add i32 0, 0
  %reg_57 = icmp eq i32 %reg_55, %reg_56
  br i1 %reg_57, label %if_body_7, label %if_else_8
if_body_7: 
  %reg_58 = add i32 1, 0
  ret i32 %reg_58
if_else_8: 
  %reg_59 = add i32 1, 0
  %reg_60 = sub i32 %reg_55, %reg_59
  %reg_61 = call i32 @rfac(i32 %reg_60)
  %reg_62 = mul i32 %reg_55, %reg_61
  ret i32 %reg_62
}

define i32 @mfac(i32 %reg_64) {
mfac_entry: 
  br label %if_cond_10
if_cond_10: 
  %reg_65 = add i32 0, 0
  %reg_66 = icmp eq i32 %reg_64, %reg_65
  br i1 %reg_66, label %if_body_11, label %if_else_12
if_body_11: 
  %reg_67 = add i32 1, 0
  ret i32 %reg_67
if_else_12: 
  %reg_68 = add i32 1, 0
  %reg_69 = sub i32 %reg_64, %reg_68
  %reg_70 = call i32 @nfac(i32 %reg_69)
  %reg_71 = mul i32 %reg_64, %reg_70
  ret i32 %reg_71
}

define i32 @nfac(i32 %reg_73) {
nfac_entry: 
  br label %if_cond_14
if_cond_14: 
  %reg_74 = add i32 0, 0
  %reg_75 = icmp ne i32 %reg_73, %reg_74
  br i1 %reg_75, label %if_body_15, label %if_else_16
if_body_15: 
  %reg_76 = add i32 1, 0
  %reg_77 = sub i32 %reg_73, %reg_76
  %reg_78 = call i32 @mfac(i32 %reg_77)
  %reg_79 = mul i32 %reg_78, %reg_73
  ret i32 %reg_79
if_else_16: 
  %reg_80 = add i32 1, 0
  ret i32 %reg_80
}

define i32 @ifac(i32 %reg_82) {
ifac_entry: 
  %reg_83 = add i32 1, 0
  %reg_84 = call i32 @ifac2f(i32 %reg_83,i32 %reg_82)
  ret i32 %reg_84
}

define i32 @ifac2f(i32 %reg_85, i32 %reg_86) {
ifac2f_entry: 
  br label %if_cond_18
if_cond_18: 
  %reg_87 = icmp eq i32 %reg_85, %reg_86
  br i1 %reg_87, label %if_body_19, label %if_end_20
if_body_19: 
  ret i32 %reg_85
if_end_20: 
  %reg_88  = phi i32 [%reg_85, %if_body_19],[%reg_85, %if_cond_18]
  %reg_89  = phi i32 [%reg_86, %if_body_19],[%reg_86, %if_cond_18]
  br label %if_cond_21
if_cond_21: 
  %reg_90 = icmp ugt i32 %reg_85, %reg_86
  br i1 %reg_90, label %if_body_22, label %if_end_23
if_body_22: 
  %reg_91 = add i32 1, 0
  ret i32 %reg_91
if_end_23: 
  %reg_92  = phi i32 [%reg_85, %if_body_22],[%reg_85, %if_cond_21]
  %reg_93  = phi i32 [%reg_86, %if_body_22],[%reg_86, %if_cond_21]
  %reg_94 = add i32 0, 0
  %reg_95 = add i32 %reg_85, %reg_86
  %reg_96 = add i32 2, 0
  %reg_97 = udiv i32 %reg_95, %reg_96
  %reg_98 = call i32 @ifac2f(i32 %reg_85,i32 %reg_97)
  %reg_99 = add i32 1, 0
  %reg_100 = add i32 %reg_97, %reg_99
  %reg_101 = call i32 @ifac2f(i32 %reg_100,i32 %reg_86)
  %reg_102 = mul i32 %reg_98, %reg_101
  ret i32 %reg_102
}

define i8* @repStr(i8* %reg_103, i32 %reg_104) {
repStr_entry: 
  %reg_106 = alloca i8*
  %reg_107 = add i32 0, 0
  %reg_108 = add i32 0, 0
  %reg_109 = getelementptr [ 1 x i8]* @.str105, i32 %reg_107, i32 %reg_108
  store i8* %reg_109, i8** %reg_106
  %reg_110 = load i8** %reg_106
  %reg_111 = add i32 0, 0
  br label %while_cond_24
while_cond_24: 
  %reg_112  = phi i8* [%reg_103, %repStr_entry],[%reg_112, %while_body_25]
  %reg_113  = phi i32 [%reg_104, %repStr_entry],[%reg_113, %while_body_25]
  %reg_114  = phi i8* [%reg_110, %repStr_entry],[%reg_117, %while_body_25]
  %reg_115  = phi i32 [%reg_111, %repStr_entry],[%reg_118, %while_body_25]
  %reg_116 = icmp ult i32 %reg_115, %reg_113
  br i1 %reg_116, label %while_body_25, label %while_end_26
while_body_25: 
  %reg_117 = call i8* @concatenate(i8* %reg_114,i8* %reg_112)
  %reg_118 = add i32 %reg_115, 1
  br label %while_cond_24
while_end_26: 
  ret i8* %reg_114
}

