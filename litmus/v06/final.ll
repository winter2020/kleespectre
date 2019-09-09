; ModuleID = 'final.bc'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@array1_size = global i32 16, align 4, !dbg !0
@array_size_mask = global i32 15, align 4, !dbg !6
@temp = global i8 0, align 1, !dbg !9
@array2 = common global [131072 x i8] zeroinitializer, align 16, !dbg !19
@array1 = common global [16 x i8] zeroinitializer, align 16, !dbg !14
@.str = private unnamed_addr constant [7 x i8] c"source\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define void @victim_fun(i32) #0 !dbg !28 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !32, metadata !DIExpression()), !dbg !33
  %3 = load i32, i32* %2, align 4, !dbg !34
  %4 = load i32, i32* @array_size_mask, align 4, !dbg !36
  %5 = and i32 %3, %4, !dbg !37
  %6 = load i32, i32* %2, align 4, !dbg !38
  %7 = icmp ne i32 %5, %6, !dbg !39
  br i1 %7, label %8, label %21, !dbg !40

; <label>:8:                                      ; preds = %1
  %9 = load i32, i32* %2, align 4, !dbg !41
  %10 = sext i32 %9 to i64, !dbg !43
  %11 = getelementptr inbounds [16 x i8], [16 x i8]* @array1, i64 0, i64 %10, !dbg !43
  %12 = load i8, i8* %11, align 1, !dbg !43
  %13 = zext i8 %12 to i64, !dbg !44
  %14 = getelementptr inbounds [131072 x i8], [131072 x i8]* @array2, i64 0, i64 %13, !dbg !44
  %15 = load i8, i8* %14, align 1, !dbg !44
  %16 = zext i8 %15 to i32, !dbg !44
  %17 = load i8, i8* @temp, align 1, !dbg !45
  %18 = zext i8 %17 to i32, !dbg !45
  %19 = and i32 %18, %16, !dbg !45
  %20 = trunc i32 %19 to i8, !dbg !45
  store i8 %20, i8* @temp, align 1, !dbg !45
  br label %21, !dbg !46

; <label>:21:                                     ; preds = %8, %1
  ret void, !dbg !47
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main(i32, i8**) #0 !dbg !48 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !54, metadata !DIExpression()), !dbg !55
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !56, metadata !DIExpression()), !dbg !57
  call void @llvm.dbg.declare(metadata i32* %6, metadata !58, metadata !DIExpression()), !dbg !59
  %7 = bitcast i32* %6 to i8*, !dbg !60
  call void @klee_make_symbolic(i8* %7, i64 4, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0)), !dbg !61
  %8 = load i32, i32* %6, align 4, !dbg !62
  call void @victim_fun(i32 %8), !dbg !63
  ret i32 0, !dbg !64
}

declare void @klee_make_symbolic(i8*, i64, i8*) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!24, !25, !26}
!llvm.ident = !{!27}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "array1_size", scope: !2, file: !3, line: 8, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 6.0.0-1ubuntu2~16.04.1 (tags/RELEASE_600/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5)
!3 = !DIFile(filename: "test.c", directory: "/home/wgh/spse_test/litmus/v06")
!4 = !{}
!5 = !{!0, !6, !9, !14, !19}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "array_size_mask", scope: !2, file: !3, line: 9, type: !8, isLocal: false, isDefinition: true)
!8 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!9 = !DIGlobalVariableExpression(var: !10, expr: !DIExpression())
!10 = distinct !DIGlobalVariable(name: "temp", scope: !2, file: !3, line: 12, type: !11, isLocal: false, isDefinition: true)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !12, line: 48, baseType: !13)
!12 = !DIFile(filename: "/usr/include/stdint.h", directory: "/home/wgh/spse_test/litmus/v06")
!13 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!14 = !DIGlobalVariableExpression(var: !15, expr: !DIExpression())
!15 = distinct !DIGlobalVariable(name: "array1", scope: !2, file: !3, line: 10, type: !16, isLocal: false, isDefinition: true)
!16 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 128, elements: !17)
!17 = !{!18}
!18 = !DISubrange(count: 16)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "array2", scope: !2, file: !3, line: 11, type: !21, isLocal: false, isDefinition: true)
!21 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 1048576, elements: !22)
!22 = !{!23}
!23 = !DISubrange(count: 131072)
!24 = !{i32 2, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{i32 1, !"wchar_size", i32 4}
!27 = !{!"clang version 6.0.0-1ubuntu2~16.04.1 (tags/RELEASE_600/final)"}
!28 = distinct !DISubprogram(name: "victim_fun", scope: !3, file: !3, line: 15, type: !29, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!29 = !DISubroutineType(types: !30)
!30 = !{null, !31}
!31 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!32 = !DILocalVariable(name: "idx", arg: 1, scope: !28, file: !3, line: 15, type: !31)
!33 = !DILocation(line: 15, column: 21, scope: !28)
!34 = !DILocation(line: 16, column: 10, scope: !35)
!35 = distinct !DILexicalBlock(scope: !28, file: !3, line: 16, column: 9)
!36 = !DILocation(line: 16, column: 16, scope: !35)
!37 = !DILocation(line: 16, column: 14, scope: !35)
!38 = !DILocation(line: 16, column: 36, scope: !35)
!39 = !DILocation(line: 16, column: 33, scope: !35)
!40 = !DILocation(line: 16, column: 9, scope: !28)
!41 = !DILocation(line: 17, column: 31, scope: !42)
!42 = distinct !DILexicalBlock(scope: !35, file: !3, line: 16, column: 41)
!43 = !DILocation(line: 17, column: 24, scope: !42)
!44 = !DILocation(line: 17, column: 17, scope: !42)
!45 = !DILocation(line: 17, column: 14, scope: !42)
!46 = !DILocation(line: 18, column: 5, scope: !42)
!47 = !DILocation(line: 19, column: 1, scope: !28)
!48 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 21, type: !49, isLocal: false, isDefinition: true, scopeLine: 21, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!49 = !DISubroutineType(types: !50)
!50 = !{!31, !31, !51}
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64)
!53 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!54 = !DILocalVariable(name: "argn", arg: 1, scope: !48, file: !3, line: 21, type: !31)
!55 = !DILocation(line: 21, column: 14, scope: !48)
!56 = !DILocalVariable(name: "args", arg: 2, scope: !48, file: !3, line: 21, type: !51)
!57 = !DILocation(line: 21, column: 26, scope: !48)
!58 = !DILocalVariable(name: "source", scope: !48, file: !3, line: 22, type: !31)
!59 = !DILocation(line: 22, column: 9, scope: !48)
!60 = !DILocation(line: 23, column: 24, scope: !48)
!61 = !DILocation(line: 23, column: 5, scope: !48)
!62 = !DILocation(line: 24, column: 16, scope: !48)
!63 = !DILocation(line: 24, column: 5, scope: !48)
!64 = !DILocation(line: 25, column: 5, scope: !48)
