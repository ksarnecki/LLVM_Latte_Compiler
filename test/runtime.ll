@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str2 = private unnamed_addr constant [7 x i8] c"%1023s\00", align 1
@.str3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str4 = private unnamed_addr constant [15 x i8] c"runtime error\0A\00", align 1

define i32 @readInt() #0 {
  %x = alloca i32, align 4
  %1 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* %x)
  %2 = load i32* %x, align 4
  ret i32 %2
}

declare i32 @scanf(i8*, ...) #0

define void @printInt(i32 %i) #0 {
  %1 = alloca i32, align 4
  store i32 %i, i32* %1, align 4
  %2 = load i32* %1, align 4
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0), i32 %2)
  ret void
}

declare i32 @printf(i8*, ...) #0

define i8* @readString() #0 {
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

define void @printString(i8* %s) #0 {
  %1 = alloca i8*, align 4
  store i8* %s, i8** %1, align 4
  %2 = load i8** %1, align 4
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str3, i32 0, i32 0), i8* %2)
  ret void
}

define void @error() #0 {
  %1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str4, i32 0, i32 0))
  call void @exit(i32 0) #5
  unreachable
                                                  ; No predecessors!
  ret void
}

declare void @exit(i32)

define i8* @concatenate(i8* %s1, i8* %s2) #1 {
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