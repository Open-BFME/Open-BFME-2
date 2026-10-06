.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH cleanups from dump range 36. Retail boundaries,
; state masks, frame displacements, and cleanup calls are established from
; each funclet. Parent functions and concrete cleanup-object identities remain
; unknown. The verified range-39 MASM source establishes this compiler helper
; shape as a VC7.1 SEH codegen blocker.

EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1Gen_uw_0017098d@@QAE@XZ:PROC
EXTERN ??1Gen_uw_000519ab@@QAE@XZ:PROC
EXTERN ??1BfmeStringTailRecord156@@QAE@XZ:PROC

_TEXT SEGMENT
; Unwind@00b5d09b: bit 0 at [ebp-0x14], cleanup pointer at [ebp+8].
PUBLIC ?rva0075D09B@@YAXXZ
?rva0075D09B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D09B
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_0075D09B:
    ret
?rva0075D09B@@YAXXZ ENDP

; Unwind@00b5d142: bit 0 at [ebp-0x18], cleanup pointer at [ebp+8].
PUBLIC ?rva0075D142@@YAXXZ
?rva0075D142@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D142
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0075D142:
    ret
?rva0075D142@@YAXXZ ENDP

; Unwind@00b5d7ca: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva0075D7CA@@YAXXZ
?rva0075D7CA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D7CA
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_000519ab@@QAE@XZ
cleanup_done_0075D7CA:
    ret
?rva0075D7CA@@YAXXZ ENDP

; Unwind@00b5d809: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva0075D809@@YAXXZ
?rva0075D809@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D809
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0075D809:
    ret
?rva0075D809@@YAXXZ ENDP

; Unwind@00b5d8fa: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva0075D8FA@@YAXXZ
?rva0075D8FA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D8FA
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0075D8FA:
    ret
?rva0075D8FA@@YAXXZ ENDP

; Unwind@00b5d994: bit 0 at [ebp-0x10], object address at [ebp+0x10].
PUBLIC ?rva0075D994@@YAXXZ
?rva0075D994@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075D994
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp+16]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0075D994:
    ret
?rva0075D994@@YAXXZ ENDP

; Unwind@00b5dabf: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva0075DABF@@YAXXZ
?rva0075DABF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075DABF
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0075DABF:
    ret
?rva0075DABF@@YAXXZ ENDP

_TEXT ENDS
END
