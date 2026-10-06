.386
.model flat
assume fs:nothing

; Address-derived EH array-cleanup funclets from dump range 38.
; Parent ownership and concrete field identity remain unknown. The exact
; helper-call shape is compiler-generated MSVC 7.1 EH code; the neighboring
; EHStateCleanupRange39.asm records failed C++ __try/__finally probes for this
; shape, so MASM preserves the verified frame code as the permitted SEH case.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC

_TEXT SEGMENT
; Unwind@00b7c8c4 at RVA 0x0077C8C4; 24-byte body ends at RET.
; Target bytes pass the base at [ebp-16]+0x3c4 to eh-vector-dtor with stride
; 20, count 2, and raw destructor VA 0x0046C94B.
PUBLIC ?rva0077c8c4@@YAXXZ
?rva0077c8c4@@YAXXZ PROC
    push 0046C94Bh
    push 2
    push 14h
    mov eax, DWORD PTR [ebp-16]
    add eax, 3C4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077c8c4@@YAXXZ ENDP

; Unwind@00b7cb24 at RVA 0x0077CB24; 24-byte body ends at RET.
; Same target helper and array arguments as 0x77C8C4; frame slot is [ebp-20].
PUBLIC ?rva0077cb24@@YAXXZ
?rva0077cb24@@YAXXZ PROC
    push 0046C94Bh
    push 2
    push 14h
    mov eax, DWORD PTR [ebp-20]
    add eax, 3C4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077cb24@@YAXXZ ENDP
_TEXT ENDS
END
