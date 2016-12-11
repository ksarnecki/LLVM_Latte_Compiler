; ModuleID = 'a.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: nounwind
define void @f(i32 %a) #0 {
  %1 = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  store i32 5, i32* %x, align 4
  %2 = load i32* %x, align 4
  %3 = add nsw i32 %2, 2
  store i32 %3, i32* %x, align 4
  ret void
}

; Function Attrs: nounwind
define i32 @g() #0 {
  %c = alloca i32, align 4
  store i32 1, i32* %c, align 4
  %1 = load i32* %c, align 4
  %2 = mul nsw i32 2, %1
  ret i32 %2
}

; Function Attrs: nounwind
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, i32* %1
  store i32 1, i32* %x, align 4
  %2 = load i32* %x, align 4
  call void @f(i32 %2)
  %3 = call i32 @g()
  ret i32 %3
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.0-4ubuntu2~trusty2 (tags/RELEASE_350/final) (based on LLVM 3.5.0)"}
