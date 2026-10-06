.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH cleanups and unwind state helpers from dump range 39.
; Retail boundaries and control flow are verified from bytes; the state mask,
; frame displacement, cleanup-object operation, and destructor target are
; taken from each body. Parent functions, field layouts and concrete cleanup identities remain
; unknown. VC7.1 C++ __try/__finally probes failed to reproduce this compiler
; helper shape, so these bodies use the permitted MASM path for SEH blockers.

EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ?call@Rva002E3A80Holder@@QAEXXZ:PROC
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC

_TEXT SEGMENT
; Unwind@00b96a09 at RVA 0x00796A09; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b97053 at RVA 0x00797053; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva002E3A80Holder::call at 0x002E3A80.
PUBLIC ?rva00797053@@YAXXZ
?rva00797053@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00797053
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_00797053:
    ret
?rva00797053@@YAXXZ ENDP

; Unwind@00b970e4 at RVA 0x007970E4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva002E3A80Holder::call at 0x002E3A80.
PUBLIC ?rva007970E4@@YAXXZ
?rva007970E4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007970E4
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007970E4:
    ret
?rva007970E4@@YAXXZ ENDP

; Unwind@00b97360 at RVA 0x00797360; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base EBP-16 + 0x1B594; element size 20; count 56; destructor pointer 0x00931FCF.
PUBLIC ?rva00797360@@YAXXZ
?rva00797360@@YAXXZ PROC
    push 00931FCFh
    push 56
    push 20
    mov eax, DWORD PTR [ebp-16]
    add eax, 1B594h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00797360@@YAXXZ ENDP

; Unwind@00b973c8 at RVA 0x007973C8; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base EBP-16 + 0x1B594; element size 20; count 56; destructor pointer 0x00931FCF.
PUBLIC ?rva007973C8@@YAXXZ
?rva007973C8@@YAXXZ PROC
    push 00931FCFh
    push 56
    push 20
    mov eax, DWORD PTR [ebp-16]
    add eax, 1B594h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007973C8@@YAXXZ ENDP

; Unwind@00b975a4 at RVA 0x007975A4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b975d7 at RVA 0x007975D7; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007975D7@@YAXXZ
?rva007975D7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007975D7
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007975D7:
    ret
?rva007975D7@@YAXXZ ENDP

; Unwind@00b97602 at RVA 0x00797602; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9764f at RVA 0x0079764F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079764F@@YAXXZ
?rva0079764F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079764F
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079764F:
    ret
?rva0079764F@@YAXXZ ENDP

; Unwind@00b97694 at RVA 0x00797694; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-40], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b97783 at RVA 0x00797783; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva00797783@@YAXXZ
?rva00797783@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00797783
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00797783:
    ret
?rva00797783@@YAXXZ ENDP

; Unwind@00b97944 at RVA 0x00797944; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva00797944@@YAXXZ
?rva00797944@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00797944
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00797944:
    ret
?rva00797944@@YAXXZ ENDP

; Unwind@00b9879f at RVA 0x0079879F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9964f at RVA 0x0079964F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079964F@@YAXXZ
?rva0079964F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079964F
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079964F:
    ret
?rva0079964F@@YAXXZ ENDP

; Unwind@00b9a522 at RVA 0x0079A522; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9a5bf at RVA 0x0079A5BF; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A5BF@@YAXXZ
?rva0079A5BF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0079A5BF
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A5BF:
    ret
?rva0079A5BF@@YAXXZ ENDP

; Unwind@00b9a5d8 at RVA 0x0079A5D8; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A5D8@@YAXXZ
?rva0079A5D8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0079A5D8
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A5D8:
    ret
?rva0079A5D8@@YAXXZ ENDP

; Unwind@00b9a605 at RVA 0x0079A605; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A605@@YAXXZ
?rva0079A605@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A605
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A605:
    ret
?rva0079A605@@YAXXZ ENDP

; Unwind@00b9a61e at RVA 0x0079A61E; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A61E@@YAXXZ
?rva0079A61E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0079A61E
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A61E:
    ret
?rva0079A61E@@YAXXZ ENDP

; Unwind@00b9a66c at RVA 0x0079A66C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A66C@@YAXXZ
?rva0079A66C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A66C
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A66C:
    ret
?rva0079A66C@@YAXXZ ENDP

; Unwind@00b9a6b2 at RVA 0x0079A6B2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9a786 at RVA 0x0079A786; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-52], then takes the cleanup object address at [ebp-44] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A786@@YAXXZ
?rva0079A786@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-52]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A786
    and DWORD PTR [ebp-52], -2
    lea ecx, [ebp-44]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A786:
    ret
?rva0079A786@@YAXXZ ENDP

; Unwind@00b9a968 at RVA 0x0079A968; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A968@@YAXXZ
?rva0079A968@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A968
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A968:
    ret
?rva0079A968@@YAXXZ ENDP

; Unwind@00b9b71a at RVA 0x0079B71A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9bb1f at RVA 0x0079BB1F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079BB1F@@YAXXZ
?rva0079BB1F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BB1F
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079BB1F:
    ret
?rva0079BB1F@@YAXXZ ENDP

; Unwind@00b9bb52 at RVA 0x0079BB52; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079BB52@@YAXXZ
?rva0079BB52@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BB52
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079BB52:
    ret
?rva0079BB52@@YAXXZ ENDP

; Unwind@00b9be5e at RVA 0x0079BE5E; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-20], then takes the cleanup object address at [ebp-32] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9c24d at RVA 0x0079C24D; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp-36] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079C24D@@YAXXZ
?rva0079C24D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C24D
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-36]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079C24D:
    ret
?rva0079C24D@@YAXXZ ENDP

; Unwind@00b9c3c5 at RVA 0x0079C3C5; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9c5d3 at RVA 0x0079C5D3; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079C5D3@@YAXXZ
?rva0079C5D3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C5D3
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079C5D3:
    ret
?rva0079C5D3@@YAXXZ ENDP

; Unwind@00b9c7aa at RVA 0x0079C7AA; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-36] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
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

; Unwind@00b9daa3 at RVA 0x0079DAA3; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079DAA3@@YAXXZ
?rva0079DAA3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079DAA3
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079DAA3:
    ret
?rva0079DAA3@@YAXXZ ENDP

; Unwind@00b9db49 at RVA 0x0079DB49; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-48], then takes the cleanup object address at [ebp-44] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079DB49@@YAXXZ
?rva0079DB49@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-48]
    and eax, 1
    jz NEAR PTR cleanup_done_0079DB49
    and DWORD PTR [ebp-48], -2
    lea ecx, [ebp-44]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079DB49:
    ret
?rva0079DB49@@YAXXZ ENDP

; Unwind@00b9e339 at RVA 0x0079E339; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp-40] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079E339@@YAXXZ
?rva0079E339@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079E339
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-40]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079E339:
    ret
?rva0079E339@@YAXXZ ENDP

; Unwind@00b9e352 at RVA 0x0079E352; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-20], then takes the cleanup object address at [ebp-40] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079E352@@YAXXZ
?rva0079E352@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 4
    jz NEAR PTR cleanup_done_0079E352
    and DWORD PTR [ebp-20], -5
    lea ecx, [ebp-40]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079E352:
    ret
?rva0079E352@@YAXXZ ENDP

; Unwind@00b9f01a at RVA 0x0079F01A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079F01A@@YAXXZ
?rva0079F01A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079F01A
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079F01A:
    ret
?rva0079F01A@@YAXXZ ENDP

; Unwind@00b9f359 at RVA 0x0079F359; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079F359@@YAXXZ
?rva0079F359@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079F359
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079F359:
    ret
?rva0079F359@@YAXXZ ENDP

; Unwind@00b9f669 at RVA 0x0079F669; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079F669@@YAXXZ
?rva0079F669@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079F669
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079F669:
    ret
?rva0079F669@@YAXXZ ENDP

; Unwind@00ba0970 at RVA 0x007A0970; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A0970@@YAXXZ
?rva007A0970@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0970
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A0970:
    ret
?rva007A0970@@YAXXZ ENDP

; Unwind@00ba0cb6 at RVA 0x007A0CB6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A0CB6@@YAXXZ
?rva007A0CB6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0CB6
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A0CB6:
    ret
?rva007A0CB6@@YAXXZ ENDP

; Unwind@00ba0f79 at RVA 0x007A0F79; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A0F79@@YAXXZ
?rva007A0F79@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0F79
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A0F79:
    ret
?rva007A0F79@@YAXXZ ENDP

; Unwind@00ba0fbe at RVA 0x007A0FBE; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A0FBE@@YAXXZ
?rva007A0FBE@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0FBE
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A0FBE:
    ret
?rva007A0FBE@@YAXXZ ENDP

; Unwind@00ba109f at RVA 0x007A109F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A109F@@YAXXZ
?rva007A109F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A109F
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A109F:
    ret
?rva007A109F@@YAXXZ ENDP

; Unwind@00ba10d2 at RVA 0x007A10D2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A10D2@@YAXXZ
?rva007A10D2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A10D2
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A10D2:
    ret
?rva007A10D2@@YAXXZ ENDP

; Unwind@00ba1fcc at RVA 0x007A1FCC; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A1FCC@@YAXXZ
?rva007A1FCC@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1FCC
    and DWORD PTR [ebp-28], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A1FCC:
    ret
?rva007A1FCC@@YAXXZ ENDP

; Unwind@00ba2001 at RVA 0x007A2001; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A2001@@YAXXZ
?rva007A2001@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A2001
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A2001:
    ret
?rva007A2001@@YAXXZ ENDP

; Unwind@00ba214b at RVA 0x007A214B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A214B@@YAXXZ
?rva007A214B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A214B
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A214B:
    ret
?rva007A214B@@YAXXZ ENDP

; Unwind@00ba3648 at RVA 0x007A3648; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A3648@@YAXXZ
?rva007A3648@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3648
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A3648:
    ret
?rva007A3648@@YAXXZ ENDP

; Unwind@00ba3701 at RVA 0x007A3701; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A3701@@YAXXZ
?rva007A3701@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3701
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A3701:
    ret
?rva007A3701@@YAXXZ ENDP

; Unwind@00ba497e at RVA 0x007A497E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A497E@@YAXXZ
?rva007A497E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A497E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A497E:
    ret
?rva007A497E@@YAXXZ ENDP

; Unwind@00ba4dc2 at RVA 0x007A4DC2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A4DC2@@YAXXZ
?rva007A4DC2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4DC2
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A4DC2:
    ret
?rva007A4DC2@@YAXXZ ENDP

; Unwind@00ba4edf at RVA 0x007A4EDF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A4EDF@@YAXXZ
?rva007A4EDF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4EDF
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A4EDF:
    ret
?rva007A4EDF@@YAXXZ ENDP

; Unwind@00ba5b9e at RVA 0x007A5B9E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A5B9E@@YAXXZ
?rva007A5B9E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5B9E
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A5B9E:
    ret
?rva007A5B9E@@YAXXZ ENDP

; Unwind@00ba5bc9 at RVA 0x007A5BC9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A5BC9@@YAXXZ
?rva007A5BC9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5BC9
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A5BC9:
    ret
?rva007A5BC9@@YAXXZ ENDP

; Unwind@00bab0e9 at RVA 0x007AB0E9; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-24], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007AB0E9@@YAXXZ
?rva007AB0E9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 2
    jz NEAR PTR cleanup_done_007AB0E9
    and DWORD PTR [ebp-24], -3
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007AB0E9:
    ret
?rva007AB0E9@@YAXXZ ENDP

_TEXT ENDS
END
