; ModuleID = 'a.cpp'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: nounwind
define i32 @_Z1fi(i32 %z) #0 {
  %1 = alloca i32, align 4
  store i32 %z, i32* %1, align 4
  ret i32 0
}

; Function Attrs: nounwind
define i32 @main() #0 {
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %x = alloca [2 x i32], align 4
  store i32 1, i32* %a, align 4
  store i32 2, i32* %b, align 4
  %1 = load i32* %b, align 4
  %2 = load i32* %a, align 4
  %3 = getelementptr inbounds [2 x i32]* %x, i32 0, i32 %2
  store i32 %1, i32* %3, align 4
  ret i32 0
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.0-4ubuntu2~trusty2 (tags/RELEASE_350/final) (based on LLVM 3.5.0)"}
