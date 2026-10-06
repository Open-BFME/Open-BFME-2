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

; Unwind@00b9a522 at RVA 0x0079A522; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079A522@@YAXXZ
?rva0079A522@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A522
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079A522:
    ret
?rva0079A522@@YAXXZ ENDP

; Unwind@00b9a6b2 at RVA 0x0079A6B2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079A6B2@@YAXXZ
?rva0079A6B2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A6B2
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079A6B2:
    ret
?rva0079A6B2@@YAXXZ ENDP

; Unwind@00b9a6df at RVA 0x0079A6DF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079A6DF@@YAXXZ
?rva0079A6DF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A6DF
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079A6DF:
    ret
?rva0079A6DF@@YAXXZ ENDP

; Unwind@00b9b71a at RVA 0x0079B71A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079B71A@@YAXXZ
?rva0079B71A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079B71A
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079B71A:
    ret
?rva0079B71A@@YAXXZ ENDP

; Unwind@00b9b747 at RVA 0x0079B747; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079B747@@YAXXZ
?rva0079B747@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079B747
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079B747:
    ret
?rva0079B747@@YAXXZ ENDP

; Unwind@00b9b88e at RVA 0x0079B88E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079B88E@@YAXXZ
?rva0079B88E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079B88E
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079B88E:
    ret
?rva0079B88E@@YAXXZ ENDP

; Unwind@00b9be5e at RVA 0x0079BE5E; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-20], then takes the cleanup object address at [ebp-32] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079BE5E@@YAXXZ
?rva0079BE5E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 2
    jz NEAR PTR cleanup_done_0079BE5E
    and DWORD PTR [ebp-20], -3
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079BE5E:
    ret
?rva0079BE5E@@YAXXZ ENDP

; Unwind@00b9beb7 at RVA 0x0079BEB7; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079BEB7@@YAXXZ
?rva0079BEB7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BEB7
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079BEB7:
    ret
?rva0079BEB7@@YAXXZ ENDP

; Unwind@00b9bf78 at RVA 0x0079BF78; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079BF78@@YAXXZ
?rva0079BF78@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BF78
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079BF78:
    ret
?rva0079BF78@@YAXXZ ENDP

; Unwind@00b9c3c5 at RVA 0x0079C3C5; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079C3C5@@YAXXZ
?rva0079C3C5@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C3C5
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079C3C5:
    ret
?rva0079C3C5@@YAXXZ ENDP

; Unwind@00b9c7aa at RVA 0x0079C7AA; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-36] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079C7AA@@YAXXZ
?rva0079C7AA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C7AA
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-36]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079C7AA:
    ret
?rva0079C7AA@@YAXXZ ENDP

; Unwind@00b9c871 at RVA 0x0079C871; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079C871@@YAXXZ
?rva0079C871@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C871
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079C871:
    ret
?rva0079C871@@YAXXZ ENDP

; Unwind@00b9ce78 at RVA 0x0079CE78; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079CE78@@YAXXZ
?rva0079CE78@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079CE78
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079CE78:
    ret
?rva0079CE78@@YAXXZ ENDP

; Unwind@00b9d210 at RVA 0x0079D210; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D210@@YAXXZ
?rva0079D210@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D210
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D210:
    ret
?rva0079D210@@YAXXZ ENDP

; Unwind@00b9d277 at RVA 0x0079D277; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D277@@YAXXZ
?rva0079D277@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D277
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D277:
    ret
?rva0079D277@@YAXXZ ENDP

; Unwind@00b9d290 at RVA 0x0079D290; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D290@@YAXXZ
?rva0079D290@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0079D290
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D290:
    ret
?rva0079D290@@YAXXZ ENDP

; Unwind@00b9d32a at RVA 0x0079D32A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D32A@@YAXXZ
?rva0079D32A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D32A
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D32A:
    ret
?rva0079D32A@@YAXXZ ENDP

; Unwind@00b9d501 at RVA 0x0079D501; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D501@@YAXXZ
?rva0079D501@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D501
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D501:
    ret
?rva0079D501@@YAXXZ ENDP

; Unwind@00b9d7e8 at RVA 0x0079D7E8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D7E8@@YAXXZ
?rva0079D7E8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D7E8
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D7E8:
    ret
?rva0079D7E8@@YAXXZ ENDP

; Unwind@00b9d81b at RVA 0x0079D81B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to 0x0048BA39.
PUBLIC ?rva0079D81B@@YAXXZ
?rva0079D81B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D81B
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D81B:
    ret
?rva0079D81B@@YAXXZ ENDP

_TEXT ENDS
END
