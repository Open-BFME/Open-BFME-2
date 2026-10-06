.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH cleanups from dump range 36. Retail boundaries,
; state masks, frame displacements, and cleanup calls are established from
; each funclet. Parent functions and concrete cleanup-object identities remain
; unknown. The verified range-39 MASM source establishes this compiler helper
; shape as a VC7.1 SEH codegen blocker.

EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ??1Gen_uw_0017098d@@QAE@XZ:PROC
EXTERN ??1Gen_uw_000519ab@@QAE@XZ:PROC
EXTERN ??1BfmeStringTailRecord156@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva00690FF0Handle@@QAE@XZ:PROC

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

; Unwind@00b5daea: bit 0 at [ebp-0x10], local object at [ebp-0x18].
PUBLIC ?rva0075DAEA@@YAXXZ
?rva0075DAEA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075DAEA
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0075DAEA:
    ret
?rva0075DAEA@@YAXXZ ENDP

; Unwind@00b5dbaf: bit 0 at [ebp-0x18], cleanup pointer at [ebp+8].
PUBLIC ?rva0075DBAF@@YAXXZ
?rva0075DBAF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0075DBAF
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0075DBAF:
    ret
?rva0075DBAF@@YAXXZ ENDP

; Unwind@00b5dc3d: bit 0 at [ebp-0x10], object address at [ebp+8].
PUBLIC ?rva0075DC3D@@YAXXZ
?rva0075DC3D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0075DC3D
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0075DC3D:
    ret
?rva0075DC3D@@YAXXZ ENDP

; Unwind@00b5dc92: bit 0 at [ebp-0x1c], local object at [ebp-0x2c].
PUBLIC ?rva0075DC92@@YAXXZ
?rva0075DC92@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0075DC92
    and DWORD PTR [ebp-28], -2
    lea ecx, [ebp-44]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0075DC92:
    ret
?rva0075DC92@@YAXXZ ENDP

; Unwind@00b5faf2: bit 0 at [ebp-0x14], cleanup pointer at [ebp+8].
PUBLIC ?rva0075FAF2@@YAXXZ
?rva0075FAF2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0075FAF2
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_0075FAF2:
    ret
?rva0075FAF2@@YAXXZ ENDP

; Unwind@00b60ac2: bit 0 at [ebp-0x10], local object at [ebp-0x18].
PUBLIC ?rva00760AC2@@YAXXZ
?rva00760AC2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00760AC2
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00760AC2:
    ret
?rva00760AC2@@YAXXZ ENDP

; Unwind@00b60b77: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva00760B77@@YAXXZ
?rva00760B77@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00760B77
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00690FF0Handle@@QAE@XZ
cleanup_done_00760B77:
    ret
?rva00760B77@@YAXXZ ENDP

; Unwind@00b60bd8: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva00760BD8@@YAXXZ
?rva00760BD8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00760BD8
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00690FF0Handle@@QAE@XZ
cleanup_done_00760BD8:
    ret
?rva00760BD8@@YAXXZ ENDP

; Unwind@00b60c80: bit 0 at [ebp-0x10], object address at [ebp+8].
PUBLIC ?rva00760C80@@YAXXZ
?rva00760C80@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00760C80
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00760C80:
    ret
?rva00760C80@@YAXXZ ENDP

; Unwind@00b60cc8: bit 0 at [ebp-0x10], cleanup pointer at [ebp+8].
PUBLIC ?rva00760CC8@@YAXXZ
?rva00760CC8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00760CC8
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00760CC8:
    ret
?rva00760CC8@@YAXXZ ENDP

_TEXT ENDS
END
