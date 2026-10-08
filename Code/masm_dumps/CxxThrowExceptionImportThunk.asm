.386
.model flat

; __CxxThrowException@8 -- retail 0x00629094, 6 bytes: the import thunk
; `jmp dword ptr [__imp___CxxThrowException@8]` through IAT slot 0x00BBA6DC
; (msvcr71.dll!_CxxThrowException). Every `throw` site in the image calls it.
;
; Import thunks are linker machinery; tools/gen_small.py gen-imports emits the
; others as `void ji_<rva>() { name(); }` from a dllimport declaration, but it
; skips this one on purpose: VC7.1 predeclares _CxxThrowException as a
; compiler-internal stdcall helper, so redeclaring it __declspec(dllimport)
; fails with C2375 ("redefinition; different linkage"), and no C++ spelling
; reaches __imp___CxxThrowException@8. That compiler predeclaration is the
; codegen blocker that keeps this one thunk in MASM.
EXTERN __imp___CxxThrowException@8:DWORD

_TEXT SEGMENT
public __CxxThrowException@8
__CxxThrowException@8 PROC
    jmp  DWORD PTR __imp___CxxThrowException@8
__CxxThrowException@8 ENDP
_TEXT ENDS
END
