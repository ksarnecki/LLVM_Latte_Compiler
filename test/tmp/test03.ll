declare void @printInt(i32);
declare i32 @scanf(i8*, ...)
declare i32 @readInt()
declare i8* @readString()
declare void @printString(i8*)
declare void @error()
declare i8* @concatenate(i8*, i8*)
%struct.int = type { i32 , i32* }
define i32 @main() {
main_entry: 
  %reg_0 = add i32 3, 0
;a
  %reg_1 = alloca %struct.int
  %reg_4 = getelementptr %struct.int* %reg_1, i32 0, i32 0
  store i32 0, i32* %reg_4
  %reg_8 = getelementptr %struct.int* %reg_1, i32 0, i32 0
;b 
  store i32 %reg_0, i32* %reg_8
;c 
  %reg_11 = getelementptr %struct.int* %reg_1, i32 0, i32 1
;d 
  %reg_12 = alloca i32, i32 %reg_0
  store i32* %reg_12, i32** %reg_11
  %reg_13 = add i32 2, 0
  %reg_16 = getelementptr %struct.int* %reg_1, i32 0, i32 1
  %reg_17 = load i32** %reg_16
;{"id":17,"kind":{"type":4,"value":{"type":2,"value":0}},"plain":{"type":1,"value":0}}
  %reg_18 = getelementptr i32* %reg_17, i32 %reg_13
  %reg_19 = load i32* %reg_18
  call void @printInt(i32 %reg_19)
  %reg_20 = add i32 0, 0
  ret i32 %reg_20
}

