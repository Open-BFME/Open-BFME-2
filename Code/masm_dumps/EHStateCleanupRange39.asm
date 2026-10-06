.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH unwind state cleanups from dump range 39.
; Retail boundaries and control flow are verified from bytes; the state mask,
; frame displacement, cleanup-object operation, and destructor target are
; taken from each body. Parent functions and concrete class identities remain
; unknown. VC7.1 C++ __try/__finally probes failed to reproduce this compiler
; helper shape, so these bodies use the permitted MASM path for SEH blockers.

EXTERN ??1AsciiString@@QAE@XZ:PROC

_TEXT SEGMENT
; Unwind@00b96a09 at RVA 0x00796A09; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00796A09@@YAXXZ
?rva00796A09@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00796A09
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00796A09:
    ret
?rva00796A09@@YAXXZ ENDP

; Unwind@00b96b6c at RVA 0x00796B6C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00796B6C@@YAXXZ
?rva00796B6C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00796B6C
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00796B6C:
    ret
?rva00796B6C@@YAXXZ ENDP

; Unwind@00b96d77 at RVA 0x00796D77; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00796D77@@YAXXZ
?rva00796D77@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00796D77
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00796D77:
    ret
?rva00796D77@@YAXXZ ENDP

; Unwind@00b96e92 at RVA 0x00796E92; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00796E92@@YAXXZ
?rva00796E92@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00796E92
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00796E92:
    ret
?rva00796E92@@YAXXZ ENDP

; Unwind@00b975a4 at RVA 0x007975A4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva007975A4@@YAXXZ
?rva007975A4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007975A4
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007975A4:
    ret
?rva007975A4@@YAXXZ ENDP

; Unwind@00b97602 at RVA 0x00797602; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00797602@@YAXXZ
?rva00797602@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00797602
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00797602:
    ret
?rva00797602@@YAXXZ ENDP

; Unwind@00b97694 at RVA 0x00797694; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva00797694@@YAXXZ
?rva00797694@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00797694
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00797694:
    ret
?rva00797694@@YAXXZ ENDP

; Unwind@00b976e1 at RVA 0x007976E1; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva007976E1@@YAXXZ
?rva007976E1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_007976E1
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007976E1:
    ret
?rva007976E1@@YAXXZ ENDP

; Unwind@00b9771c at RVA 0x0079771C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-40], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079771C@@YAXXZ
?rva0079771C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-40]
    and eax, 1
    jz NEAR PTR cleanup_done_0079771C
    and DWORD PTR [ebp-40], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079771C:
    ret
?rva0079771C@@YAXXZ ENDP

; Unwind@00b9879f at RVA 0x0079879F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079879F@@YAXXZ
?rva0079879F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079879F
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079879F:
    ret
?rva0079879F@@YAXXZ ENDP

; Unwind@00b995e6 at RVA 0x007995E6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva007995E6@@YAXXZ
?rva007995E6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007995E6
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007995E6:
    ret
?rva007995E6@@YAXXZ ENDP

_TEXT ENDS
END
