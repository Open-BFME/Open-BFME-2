.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH vector cleanups from dump range 36. The retail
; helper call, array extent, member offset, and frame base are read directly
; from each body. Parent class and member layout remain unknown. This is the
; compiler-generated EH vector cleanup shape covered by the range-39 MASM path.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC

_TEXT SEGMENT
; Unwind@00b5d5f0: four 8-byte elements at [ebp-0x14] + 0x14e0.
PUBLIC ?rva0075D5F0@@YAXXZ
?rva0075D5F0@@YAXXZ PROC
    push 4B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-20]
    add eax, 14E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075D5F0@@YAXXZ ENDP

; Unwind@00b5d660: four 8-byte elements at [ebp-0x10] + 0x14e0.
PUBLIC ?rva0075D660@@YAXXZ
?rva0075D660@@YAXXZ PROC
    push 4B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 14E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075D660@@YAXXZ ENDP

_TEXT ENDS
END
