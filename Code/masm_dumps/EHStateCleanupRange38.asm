.386
.model flat
assume fs:nothing

; Address-derived EH cleanup funclets from dump range 38.
; Parent ownership and concrete field identity remain unknown. These bodies are
; compiler-generated MSVC 7.1 EH helpers; neighboring Range39 C++ probes failed
; to reproduce this standalone frame code, so MASM preserves the SEH behavior.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC

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
; Unwind@00b7d884 at RVA 0x0077D884; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-16] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077d884@@YAXXZ
?rva0077d884@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0077d884
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0077d884:
    ret
?rva0077d884@@YAXXZ ENDP

; Unwind@00b7ec69 at RVA 0x0077EC69; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-24] and tail-jumps with object [ebp-96].
PUBLIC ?rva0077ec69@@YAXXZ
?rva0077ec69@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ec69
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp-96]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077ec69:
    ret
?rva0077ec69@@YAXXZ ENDP

; Unwind@00b7ed0d at RVA 0x0077ED0D; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-20] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077ed0d@@YAXXZ
?rva0077ed0d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ed0d
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077ed0d:
    ret
?rva0077ed0d@@YAXXZ ENDP

; Unwind@00b7ed38 at RVA 0x0077ED38; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-20] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077ed38@@YAXXZ
?rva0077ed38@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ed38
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0077ed38:
    ret
?rva0077ed38@@YAXXZ ENDP

; Unwind@00b7ed89 at RVA 0x0077ED89; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-24] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077ed89@@YAXXZ
?rva0077ed89@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ed89
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077ed89:
    ret
?rva0077ed89@@YAXXZ ENDP

; Unwind@00b7edb4 at RVA 0x0077EDB4; 27-byte array cleanup ends at RET.
; Target passes [ebp-20]+0xdc to eh-vector-dtor with element size 0x1ac,
; count 8, and raw destructor VA 0x006294FD.
PUBLIC ?rva0077edb4@@YAXXZ
?rva0077edb4@@YAXXZ PROC
    push 006294FDh
    push 8
    push 1ACh
    mov eax, DWORD PTR [ebp-20]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077edb4@@YAXXZ ENDP

; Unwind@00b7ee74 at RVA 0x0077EE74; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-32] and tail-jumps to object [ebp-48].
PUBLIC ?rva0077ee74@@YAXXZ
?rva0077ee74@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ee74
    and DWORD PTR [ebp-32], -2
    lea ecx, [ebp-48]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0077ee74:
    ret
?rva0077ee74@@YAXXZ ENDP

; Unwind@00b7efe4 at RVA 0x0077EFE4; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-36] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077efe4@@YAXXZ
?rva0077efe4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-36]
    and eax, 1
    jz NEAR PTR cleanup_done_0077efe4
    and DWORD PTR [ebp-36], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077efe4:
    ret
?rva0077efe4@@YAXXZ ENDP

; Unwind@00b7f57f at RVA 0x0077F57F; 27-byte array cleanup ends at RET.
; Target passes [ebp-16]+0xdc to eh-vector-dtor with size 0x1e0 count 8 and
; raw destructor VA 0x00782398.
PUBLIC ?rva0077f57f@@YAXXZ
?rva0077f57f@@YAXXZ PROC
    push 00782398h
    push 8
    push 1E0h
    mov eax, DWORD PTR [ebp-16]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077f57f@@YAXXZ ENDP

; Unwind@00b7f708 at RVA 0x0077F708; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x94 to eh-vector-dtor with size 12 count 6 and
; raw destructor VA 0x0078356C.
PUBLIC ?rva0077f708@@YAXXZ
?rva0077f708@@YAXXZ PROC
    push 0078356Ch
    push 6
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077f708@@YAXXZ ENDP

; Unwind@00b80013 at RVA 0x00780013; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-20] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva00780013@@YAXXZ
?rva00780013@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00780013
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00780013:
    ret
?rva00780013@@YAXXZ ENDP

; Unwind@00b80174 at RVA 0x00780174; 25-byte cleanup ends at RET.
; Retail clears state bit 1 in [ebp-16] and tail-jumps with object [ebp-28].
PUBLIC ?rva00780174@@YAXXZ
?rva00780174@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00780174
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00780174:
    ret
?rva00780174@@YAXXZ ENDP

; Unwind@00b8018d at RVA 0x0078018D; 25-byte cleanup ends at RET.
; Retail clears state bit 2 in [ebp-16] and tail-jumps through [ebp+8].
PUBLIC ?rva0078018d@@YAXXZ
?rva0078018d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0078018d
    and DWORD PTR [ebp-16], -5
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_0078018d:
    ret
?rva0078018d@@YAXXZ ENDP

; Unwind@00b80229 at RVA 0x00780229; 24-byte array cleanup ends at RET.
; Target passes [ebp-20]+0x88 to eh-vector-dtor with size 12 count 8 and
; raw destructor VA 0x00542D70 (rowed STLport narrow basic_string dtor RVA 0x142D70).
PUBLIC ?rva00780229@@YAXXZ
?rva00780229@@YAXXZ PROC
    push 00542D70h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 88h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00780229@@YAXXZ ENDP

; Unwind@00b802d2 at RVA 0x007802D2; 24-byte array cleanup ends at RET.
; Same target element type and helper arguments as 0x780229; frame slot is [ebp-16].
PUBLIC ?rva007802d2@@YAXXZ
?rva007802d2@@YAXXZ PROC
    push 00542D70h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 88h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007802d2@@YAXXZ ENDP

; Unwind@00b803c1 at RVA 0x007803C1; 25-byte cleanup ends at RET.
; Retail clears state bit 0 in [ebp-16] and tail-jumps through [ebp+8].
PUBLIC ?rva007803c1@@YAXXZ
?rva007803c1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007803c1
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_007803c1:
    ret
?rva007803c1@@YAXXZ ENDP

; Unwind@00b804a6 at RVA 0x007804A6; 24-byte array cleanup ends at RET.
; Target passes [ebp-24]+0xd0 with size 12 count 8 and raw dtor VA 0x00542D70.
PUBLIC ?rva007804a6@@YAXXZ
?rva007804a6@@YAXXZ PROC
    push 00542D70h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-24]
    add eax, 0D0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007804a6@@YAXXZ ENDP

; Unwind@00b8059a at RVA 0x0078059A; 24-byte array cleanup ends at RET.
; Same target type and array parameters as 0x7804A6; frame slot is [ebp-16].
PUBLIC ?rva0078059a@@YAXXZ
?rva0078059a@@YAXXZ PROC
    push 00542D70h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0D0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078059a@@YAXXZ ENDP

; Unwind@00b812ad at RVA 0x007812AD; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x1fc with size 12 count 20 and raw dtor VA 0x00757CD9.
PUBLIC ?rva007812ad@@YAXXZ
?rva007812ad@@YAXXZ PROC
    push 00757CD9h
    push 14h
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 1FCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007812ad@@YAXXZ ENDP

; Unwind@00b8138c at RVA 0x0078138C; 24-byte array cleanup ends at RET.
; Same target type and array parameters as 0x7812AD; frame slot is [ebp-20].
PUBLIC ?rva0078138c@@YAXXZ
?rva0078138c@@YAXXZ PROC
    push 00757CD9h
    push 14h
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 1FCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078138c@@YAXXZ ENDP

; Unwind@00b817fb at RVA 0x007817FB; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x118 with size 4 count 32 and raw dtor VA 0x0088BA39.
PUBLIC ?rva007817fb@@YAXXZ
?rva007817fb@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 118h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007817fb@@YAXXZ ENDP

; Unwind@00b818a6 at RVA 0x007818A6; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0xac with size 4 count 32 and raw dtor VA 0x0088BA39.
PUBLIC ?rva007818a6@@YAXXZ
?rva007818a6@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 0ACh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007818a6@@YAXXZ ENDP

; Unwind@00b8190d at RVA 0x0078190D; 24-byte array cleanup ends at RET.
; Same target type and array parameters as 0x7818A6; frame slot is [ebp-20].
PUBLIC ?rva0078190d@@YAXXZ
?rva0078190d@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 0ACh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078190d@@YAXXZ ENDP

; Unwind@00b819a3 at RVA 0x007819A3; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-16] and tail-jumps to [ebp-24] via AsciiString dtor.
PUBLIC ?rva007819a3@@YAXXZ
?rva007819a3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007819a3
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007819a3:
    ret
?rva007819a3@@YAXXZ ENDP

; Unwind@00b81ee6 at RVA 0x00781EE6; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-16] and tail-jumps to [ebp-20] via the rowed dtor.
PUBLIC ?rva00781ee6@@YAXXZ
?rva00781ee6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00781ee6
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_00781ee6:
    ret
?rva00781ee6@@YAXXZ ENDP

; Unwind@00b81eff at RVA 0x00781EFF; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 2 at [ebp-16] and tail-jumps through [ebp+8] via the rowed dtor.
PUBLIC ?rva00781eff@@YAXXZ
?rva00781eff@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_00781eff
    and DWORD PTR [ebp-16], -5
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_00781eff:
    ret
?rva00781eff@@YAXXZ ENDP
_TEXT ENDS
END
