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
_TEXT ENDS
END
