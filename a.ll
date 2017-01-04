; ModuleID = 'a.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str2 = private unnamed_addr constant [7 x i8] c"%1023s\00", align 1
@.str3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str4 = private unnamed_addr constant [15 x i8] c"runtime error\0A\00", align 1
@.str5 = private unnamed_addr constant [5 x i8] c"test\00", align 1

define i32 @_Z7readIntv() #0 {
  %x = alloca i32, align 4
  %1 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* %x)
  %2 = load i32* %x, align 4
  ret i32 %2
}

declare i32 @scanf(i8*, ...) #0

define void @_Z8printInti(i32 %i) #0 {
  %1 = alloca i32, align 4
  store i32 %i, i32* %1, align 4
  %2 = load i32* %1, align 4
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0), i32 %2)
  ret void
}

declare i32 @printf(i8*, ...) #0

define i8* @_Z10readStringv() #0 {
  %s = alloca i8*, align 4
  %1 = call noalias i8* @malloc(i32 1024) #4
  store i8* %1, i8** %s, align 4
  %2 = load i8** %s, align 4
  %3 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([7 x i8]* @.str2, i32 0, i32 0), i8* %2)
  %4 = load i8** %s, align 4
  ret i8* %4
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i32) #1

define void @_Z11printStringPc(i8* %s) #0 {
  %1 = alloca i8*, align 4
  store i8* %s, i8** %1, align 4
  %2 = load i8** %1, align 4
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str3, i32 0, i32 0), i8* %2)
  ret void
}

define void @_Z5errorv() #0 {
  %1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str4, i32 0, i32 0))
  call void @exit(i32 0) #5
  unreachable
                                                  ; No predecessors!
  ret void
}

; Function Attrs: noreturn nounwind
declare void @exit(i32) #2

; Function Attrs: nounwind
define i8* @_Z11concatenatePcS_(i8* %s1, i8* %s2) #1 {
  %1 = alloca i8*, align 4
  %2 = alloca i8*, align 4
  %ret = alloca i8*, align 4
  store i8* %s1, i8** %1, align 4
  store i8* %s2, i8** %2, align 4
  %3 = load i8** %1, align 4
  %4 = call i32 @strlen(i8* %3) #6
  %5 = load i8** %2, align 4
  %6 = call i32 @strlen(i8* %5) #6
  %7 = add i32 %4, %6
  %8 = add i32 %7, 1
  %9 = call noalias i8* @malloc(i32 %8) #4
  store i8* %9, i8** %ret, align 4
  %10 = load i8** %ret, align 4
  %11 = load i8** %1, align 4
  %12 = call i8* @strcpy(i8* %10, i8* %11) #4
  %13 = load i8** %ret, align 4
  %14 = load i8** %2, align 4
  %15 = call i8* @strcat(i8* %13, i8* %14) #4
  %16 = load i8** %ret, align 4
  ret i8* %16
}

; Function Attrs: nounwind readonly
declare i32 @strlen(i8*) #3

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #1

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #1

; Function Attrs: nounwind
define i32 @_Z3tabv() #1 {
  %x = alloca [4 x i32], align 4
  %1 = getelementptr inbounds [4 x i32]* %x, i32 0, i32 1
  store i32 2, i32* %1, align 4
  %2 = getelementptr inbounds [4 x i32]* %x, i32 0, i32 1
  %3 = load i32* %2, align 4
  ret i32 %3
}

define i32 @main() #0 {
  %s1 = alloca i8*, align 4
  %s3 = alloca i8*, align 4
  store i8* getelementptr inbounds ([5 x i8]* @.str5, i32 0, i32 0), i8** %s1, align 4
  %1 = call i8* @_Z10readStringv()
  store i8* %1, i8** %s3, align 4
  %2 = load i8** %s1, align 4
  %3 = load i8** %s3, align 4
  %4 = call i8* @_Z11concatenatePcS_(i8* %2, i8* %3)
  call void @_Z11printStringPc(i8* %4)
  ret i32 0
}

attributes #0 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind readonly }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.0-4ubuntu2~trusty2 (tags/RELEASE_350/final) (based on LLVM 3.5.0)"}
