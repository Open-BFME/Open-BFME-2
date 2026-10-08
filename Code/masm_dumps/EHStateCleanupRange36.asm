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
EXTERN ??1Gen_uw_0049b47c@@QAE@XZ:PROC
EXTERN ??1Gen_uw_000519ab@@QAE@XZ:PROC
EXTERN ??1BfmeStringTailRecord156@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva00690FF0Handle@@QAE@XZ:PROC
EXTERN ??1?$RefCountPtr@VMeshClass@@@@QAE@XZ:PROC
EXTERN ??1Rva001E4DB0@@UAE@XZ:PROC
EXTERN ??1Gen_uw_000b3f43@@QAE@XZ:PROC
EXTERN ?rva002115C5@Rva002115C5@@QAEXXZ:PROC
EXTERN ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC
EXTERN ??1Gen_uwm_001f22a3@@QAE@XZ:PROC
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC

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

; Unwind@00b5f97f: eh-vector-dtor cleanup adds 44h to [ebp-16] and passes it to 0057098Dh.
PUBLIC ?rva0075F97F@@YAXXZ
?rva0075F97F@@YAXXZ PROC
    push 0057098Dh
    push 4
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 44h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075F97F@@YAXXZ ENDP

; Unwind@00b5facd: eh-vector-dtor cleanup passes the address of [ebp-88] with count 4 and size 12.
PUBLIC ?rva0075FACD@@YAXXZ
?rva0075FACD@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, DWORD PTR [ebp-88]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075FACD@@YAXXZ ENDP

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

; Unwind@00b60b14: 22-byte eh-vector-dtor target passes [ebp-16]+0x14 with size 4 count 3.
PUBLIC ?rva00760B14@@YAXXZ
?rva00760B14@@YAXXZ PROC
    push 00600667h
    push 3
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00760B14@@YAXXZ ENDP

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

; Unwind@00b60c3f: 22-byte eh-vector-dtor target passes [ebp-24]+0x14 with size 4 count 3.
PUBLIC ?rva00760C3F@@YAXXZ
?rva00760C3F@@YAXXZ PROC
    push 00600667h
    push 3
    push 4
    mov eax, DWORD PTR [ebp-24]
    add eax, 14h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00760C3F@@YAXXZ ENDP

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

; Unwind@00b61013: bit 0 at [ebp-0x18], cleanup pointer at [ebp+8].
PUBLIC ?rva00761013@@YAXXZ
?rva00761013@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00761013
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_00761013:
    ret
?rva00761013@@YAXXZ ENDP

; Unwind@00b61549: bit 0 at [ebp-0x14], cleanup pointer at [ebp+8].
PUBLIC ?rva00761549@@YAXXZ
?rva00761549@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00761549
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00761549:
    ret
?rva00761549@@YAXXZ ENDP

; Unwind@00b6163e: bit 0 at [ebp-0x18], cleanup pointer at [ebp+8].
PUBLIC ?rva0076163E@@YAXXZ
?rva0076163E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0076163E
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0076163E:
    ret
?rva0076163E@@YAXXZ ENDP

; Unwind@00b617ff: bit 0 at [ebp-0x14], cleanup pointer at [ebp+8].
PUBLIC ?rva007617FF@@YAXXZ
?rva007617FF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007617FF
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007617FF:
    ret
?rva007617FF@@YAXXZ ENDP

; Unwind@00b61832: bit 0 at [ebp-0x14], cleanup pointer at [ebp+8].
PUBLIC ?rva00761832@@YAXXZ
?rva00761832@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00761832
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00761832:
    ret
?rva00761832@@YAXXZ ENDP

; Unwind@00b61b91: bit 0 at [ebp-0x2c], cleanup pointer at [ebp+8].
PUBLIC ?rva00761B91@@YAXXZ
?rva00761B91@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-44]
    and eax, 1
    jz NEAR PTR cleanup_done_00761B91
    and DWORD PTR [ebp-44], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00761B91:
    ret
?rva00761B91@@YAXXZ ENDP


; Unwind@00b6412c: bit 0 at [ebp-0x14], cleanup target from the retail frame.
PUBLIC ?rva0076412C@@YAXXZ
?rva0076412C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0076412C
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_0076412C:
    ret
?rva0076412C@@YAXXZ ENDP

; Unwind@00b64193: bit 0 at [ebp-0x10], cleanup target from the retail frame.
PUBLIC ?rva00764193@@YAXXZ
?rva00764193@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00764193
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-28]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_00764193:
    ret
?rva00764193@@YAXXZ ENDP

; Unwind@00b641db: state bit 0 at [ebp-28]; cleanup transfer at [ebp-40].
PUBLIC ?rva007641DB@@YAXXZ
?rva007641DB@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007641DB
    and DWORD PTR [ebp-28], -2
    lea ecx, [ebp-40]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_007641DB:
    ret
?rva007641DB@@YAXXZ ENDP

; Unwind@00b64276: eh-vector-dtor cleanup adds 28h to [ebp-16] and passes it to 004B3FD0h.
PUBLIC ?rva00764276@@YAXXZ
?rva00764276@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 28h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00764276@@YAXXZ ENDP

; Unwind@00b6428c: eh-vector-dtor cleanup adds 48h to [ebp-16] and passes it to 004B3FD0h.
PUBLIC ?rva0076428C@@YAXXZ
?rva0076428C@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 48h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076428C@@YAXXZ ENDP

; Unwind@00b642a2: eh-vector-dtor cleanup adds 68h to [ebp-16] and passes it to 004B3FD0h.
PUBLIC ?rva007642A2@@YAXXZ
?rva007642A2@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 68h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007642A2@@YAXXZ ENDP

; Unwind@00b642dd: eh-vector-dtor cleanup adds 28h to [ebp-20] and passes it to 004B3FD0h.
PUBLIC ?rva007642DD@@YAXXZ
?rva007642DD@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-20]
    add eax, 28h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007642DD@@YAXXZ ENDP

; Unwind@00b642f3: eh-vector-dtor cleanup adds 48h to [ebp-20] and passes it to 004B3FD0h.
PUBLIC ?rva007642F3@@YAXXZ
?rva007642F3@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-20]
    add eax, 48h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007642F3@@YAXXZ ENDP

; Unwind@00b64309: eh-vector-dtor cleanup adds 68h to [ebp-20] and passes it to 004B3FD0h.
PUBLIC ?rva00764309@@YAXXZ
?rva00764309@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-20]
    add eax, 68h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00764309@@YAXXZ ENDP

; Unwind@00b646b7: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva007646B7@@YAXXZ
?rva007646B7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007646B7
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007646B7:
    ret
?rva007646B7@@YAXXZ ENDP

; Unwind@00b6489f: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076489F@@YAXXZ
?rva0076489F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0076489F
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0076489F:
    ret
?rva0076489F@@YAXXZ ENDP

; Unwind@00b648de: state bit 0 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva007648DE@@YAXXZ
?rva007648DE@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007648DE
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007648DE:
    ret
?rva007648DE@@YAXXZ ENDP

; Unwind@00b6490b: state bit 0 at [ebp-16]; cleanup transfer at [ebp-24].
PUBLIC ?rva0076490B@@YAXXZ
?rva0076490B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076490B
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0076490B:
    ret
?rva0076490B@@YAXXZ ENDP

; Unwind@00b64938: state bit 0 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva00764938@@YAXXZ
?rva00764938@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00764938
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_00764938:
    ret
?rva00764938@@YAXXZ ENDP

; Unwind@00b6495b: state bit 1 at [ebp-16]; cleanup transfer at [ebp-24].
PUBLIC ?rva0076495B@@YAXXZ
?rva0076495B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0076495B
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-24]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_0076495B:
    ret
?rva0076495B@@YAXXZ ENDP

; Unwind@00b64fb0: state bit 0 at [ebp-32]; cleanup transfer at [ebp+4].
PUBLIC ?rva00764FB0@@YAXXZ
?rva00764FB0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_00764FB0
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_00764FB0:
    ret
?rva00764FB0@@YAXXZ ENDP

; Unwind@00b658b4: state bit 0 at [ebp-24]; cleanup transfer at [ebp+8].
PUBLIC ?rva007658B4@@YAXXZ
?rva007658B4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007658B4
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007658B4:
    ret
?rva007658B4@@YAXXZ ENDP

; Unwind@00b659a7: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva007659A7@@YAXXZ
?rva007659A7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007659A7
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007659A7:
    ret
?rva007659A7@@YAXXZ ENDP

; Unwind@00b659da: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva007659DA@@YAXXZ
?rva007659DA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007659DA
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_007659DA:
    ret
?rva007659DA@@YAXXZ ENDP

; Unwind@00b65a05: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva00765A05@@YAXXZ
?rva00765A05@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00765A05
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00765A05:
    ret
?rva00765A05@@YAXXZ ENDP

; Unwind@00b66758: state bit 0 at [ebp-16]; cleanup transfer at [ebp+4].
PUBLIC ?rva00766758@@YAXXZ
?rva00766758@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00766758
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_00766758:
    ret
?rva00766758@@YAXXZ ENDP

; Unwind@00b66788: state bit 0 at [ebp-16]; cleanup transfer at [ebp+4].
PUBLIC ?rva00766788@@YAXXZ
?rva00766788@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00766788
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1?$RefCountPtr@VMeshClass@@@@QAE@XZ
cleanup_done_00766788:
    ret
?rva00766788@@YAXXZ ENDP

; Unwind@00b667dc: state bit 0 at [ebp-232]; cleanup transfer at [ebp-224].
PUBLIC ?rva007667DC@@YAXXZ
?rva007667DC@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-232]
    and eax, 1
    jz NEAR PTR cleanup_done_007667DC
    and DWORD PTR [ebp-232], -2
    lea ecx, [ebp-224]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007667DC:
    ret
?rva007667DC@@YAXXZ ENDP

; Unwind@00b667fe: state bit 1 at [ebp-232]; cleanup transfer at [ebp-228].
PUBLIC ?rva007667FE@@YAXXZ
?rva007667FE@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-232]
    and eax, 2
    jz NEAR PTR cleanup_done_007667FE
    and DWORD PTR [ebp-232], -3
    lea ecx, [ebp-228]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007667FE:
    ret
?rva007667FE@@YAXXZ ENDP
; Unwind@00b668e4: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva007668E4@@YAXXZ
?rva007668E4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007668E4
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007668E4:
    ret
?rva007668E4@@YAXXZ ENDP

; Unwind@00b66b37: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva00766B37@@YAXXZ
?rva00766B37@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00766B37
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_00766B37:
    ret
?rva00766B37@@YAXXZ ENDP

; Unwind@00b66c19: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva00766C19@@YAXXZ
?rva00766C19@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00766C19
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00766C19:
    ret
?rva00766C19@@YAXXZ ENDP

; Unwind@00b66d2c: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva00766D2C@@YAXXZ
?rva00766D2C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00766D2C
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_00766D2C:
    ret
?rva00766D2C@@YAXXZ ENDP

; Unwind@00b68107: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva00768107@@YAXXZ
?rva00768107@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00768107
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_00768107:
    ret
?rva00768107@@YAXXZ ENDP

; Unwind@00b681d1: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva007681D1@@YAXXZ
?rva007681D1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007681D1
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007681D1:
    ret
?rva007681D1@@YAXXZ ENDP

; Unwind@00b6826d: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076826D@@YAXXZ
?rva0076826D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076826D
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_0076826D:
    ret
?rva0076826D@@YAXXZ ENDP

; Unwind@00b682d9: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva007682D9@@YAXXZ
?rva007682D9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007682D9
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007682D9:
    ret
?rva007682D9@@YAXXZ ENDP

; Unwind@00b6835a: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076835A@@YAXXZ
?rva0076835A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076835A
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_0076835A:
    ret
?rva0076835A@@YAXXZ ENDP

; Unwind@00b683da: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva007683DA@@YAXXZ
?rva007683DA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007683DA
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_0017098d@@QAE@XZ
cleanup_done_007683DA:
    ret
?rva007683DA@@YAXXZ ENDP

; Unwind@00b695f4: state bit 0 at [ebp-24]; cleanup transfer at [ebp-16].
PUBLIC ?rva007695F4@@YAXXZ
?rva007695F4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007695F4
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp-16]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007695F4:
    ret
?rva007695F4@@YAXXZ ENDP

; Unwind@00b69a4e: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00769A4E@@YAXXZ
?rva00769A4E@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00769A4E@@YAXXZ ENDP

; Unwind@00b69dc9: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva00769DC9@@YAXXZ
?rva00769DC9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00769DC9
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_000b3f43@@QAE@XZ
cleanup_done_00769DC9:
    ret
?rva00769DC9@@YAXXZ ENDP
; Unwind@00b69dec: state bit 1 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva00769DEC@@YAXXZ
?rva00769DEC@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00769DEC
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00769DEC:
    ret
?rva00769DEC@@YAXXZ ENDP

; Unwind@00b69e21: state bit 0 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva00769E21@@YAXXZ
?rva00769E21@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00769E21
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00769E21:
    ret
?rva00769E21@@YAXXZ ENDP

; Unwind@00b69fcb: state bit 0 at [ebp-16]; cleanup transfer at [ebp+8].
PUBLIC ?rva00769FCB@@YAXXZ
?rva00769FCB@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00769FCB
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva001E4DB0@@UAE@XZ
cleanup_done_00769FCB:
    ret
?rva00769FCB@@YAXXZ ENDP

; Unwind@00b6a508: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076A508@@YAXXZ
?rva0076A508@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0076A508
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0076A508:
    ret
?rva0076A508@@YAXXZ ENDP
; Unwind@00b6b084: state bit 0 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva0076B084@@YAXXZ
?rva0076B084@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B084
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0076B084:
    ret
?rva0076B084@@YAXXZ ENDP

; Unwind@00b6b15a: state bit 0 at [ebp-40]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076B15A@@YAXXZ
?rva0076B15A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-40]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B15A
    and DWORD PTR [ebp-40], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uwm_001f22a3@@QAE@XZ
cleanup_done_0076B15A:
    ret
?rva0076B15A@@YAXXZ ENDP

; Unwind@00b6b4bf: state bit 0 at [ebp-20]; cleanup transfer at [ebp-52].
PUBLIC ?rva0076B4BF@@YAXXZ
?rva0076B4BF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B4BF
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-52]
    jmp ?rva002115C5@Rva002115C5@@QAEXXZ
cleanup_done_0076B4BF:
    ret
?rva0076B4BF@@YAXXZ ENDP

; Unwind@00b6b4d8: state bit 1 at [ebp-20]; cleanup transfer at [ebp-40].
PUBLIC ?rva0076B4D8@@YAXXZ
?rva0076B4D8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 2
    jz NEAR PTR cleanup_done_0076B4D8
    and DWORD PTR [ebp-20], -3
    lea ecx, [ebp-40]
    jmp ?rva002115C5@Rva002115C5@@QAEXXZ
cleanup_done_0076B4D8:
    ret
?rva0076B4D8@@YAXXZ ENDP

; Unwind@00b6b62e: state bit 0 at [ebp-20]; cleanup transfer at [ebp+8].
PUBLIC ?rva0076B62E@@YAXXZ
?rva0076B62E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B62E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_0076B62E:
    ret
?rva0076B62E@@YAXXZ ENDP

; Unwind@00b6b66b: 20-byte masked-add funclet with add 0Ch tail-jumps to EmissionVelocityInfo dtor.
PUBLIC ?rva0076B66B@@YAXXZ
?rva0076B66B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva0076B66B@@YAXXZ ENDP

; Unwind@00b6b786: state bit 0 at [ebp-16]; cleanup transfer at [ebp-20].
PUBLIC ?rva0076B786@@YAXXZ
?rva0076B786@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B786
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 70h
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_0076B786:
    ret
?rva0076B786@@YAXXZ ENDP

; Unwind@00b6b961: state bit 0 at [ebp-16]; cleanup transfer at [ebp-32].
PUBLIC ?rva0076B961@@YAXXZ
?rva0076B961@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0076B961
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ?rva002115C5@Rva002115C5@@QAEXXZ
cleanup_done_0076B961:
    ret
?rva0076B961@@YAXXZ ENDP

; Unwind@00b6b984: state bit 1 at [ebp-16]; cleanup transfer at [ebp-32].
PUBLIC ?rva0076B984@@YAXXZ
?rva0076B984@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0076B984
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-32]
    jmp ?rva002115C5@Rva002115C5@@QAEXXZ
cleanup_done_0076B984:
    ret
?rva0076B984@@YAXXZ ENDP

; Unwind@00b6b9a7: state bit 2 at [ebp-16]; cleanup transfer at [ebp-32].
PUBLIC ?rva0076B9A7@@YAXXZ
?rva0076B9A7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0076B9A7
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-32]
    jmp ?rva002115C5@Rva002115C5@@QAEXXZ
cleanup_done_0076B9A7:
    ret
?rva0076B9A7@@YAXXZ ENDP

; Unwind@00b6cd69: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0076CD69@@YAXXZ
?rva0076CD69@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0076CD69@@YAXXZ ENDP

; Unwind@00b6d075: 22-byte eh-vector-dtor target passes [ebp-0E4h] with size 4 count 20 and raw destructor VA 0x00607F08.
PUBLIC ?rva0076D075@@YAXXZ
?rva0076D075@@YAXXZ PROC
    push 00607F08h
    push 14h
    push 4
    lea eax, DWORD PTR [ebp-0E4h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076D075@@YAXXZ ENDP

; Unwind@00b6d08b: 22-byte eh-vector-dtor target passes [ebp-0E4h] with size 4 count 20 and raw destructor VA 0x00607F08.
PUBLIC ?rva0076D08B@@YAXXZ
?rva0076D08B@@YAXXZ PROC
    push 00607F08h
    push 14h
    push 4
    lea eax, DWORD PTR [ebp-0E4h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076D08B@@YAXXZ ENDP

; Unwind@00b6d0a1: 22-byte eh-vector-dtor target passes [ebp-0E4h] with size 4 count 20 and raw destructor VA 0x00607F08.
PUBLIC ?rva0076D0A1@@YAXXZ
?rva0076D0A1@@YAXXZ PROC
    push 00607F08h
    push 14h
    push 4
    lea eax, DWORD PTR [ebp-0E4h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076D0A1@@YAXXZ ENDP

; Unwind@00b6d0b7: 22-byte eh-vector-dtor target passes [ebp-0E4h] with size 4 count 20 and raw destructor VA 0x00607F08.
PUBLIC ?rva0076D0B7@@YAXXZ
?rva0076D0B7@@YAXXZ PROC
    push 00607F08h
    push 14h
    push 4
    lea eax, DWORD PTR [ebp-0E4h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076D0B7@@YAXXZ ENDP

; Unwind@00b6d4a7: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0076D4A7@@YAXXZ
?rva0076D4A7@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0076D4A7@@YAXXZ ENDP

; Unwind@00b71427: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00771427@@YAXXZ
?rva00771427@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00771427@@YAXXZ ENDP

; Unwind@00b71f74: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00771F74@@YAXXZ
?rva00771F74@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00771F74@@YAXXZ ENDP

; Unwind@00b720d9: eh-vector-dtor cleanup adds 70h to [ebp-20] and passes it to 0047FAB3h.
PUBLIC ?rva007720D9@@YAXXZ
?rva007720D9@@YAXXZ PROC
    push 0047FAB3h
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 70h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007720D9@@YAXXZ ENDP

; Unwind@00b72128: eh-vector-dtor cleanup adds 70h to [ebp-16] and passes it to 0047FAB3h.
PUBLIC ?rva00772128@@YAXXZ
?rva00772128@@YAXXZ PROC
    push 0047FAB3h
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 70h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00772128@@YAXXZ ENDP

; Unwind@00b73f20: eh-vector-dtor cleanup adds 10h to [ebp-16] and passes it to 0069D7C2h.
PUBLIC ?rva00773F20@@YAXXZ
?rva00773F20@@YAXXZ PROC
    push 0069D7C2h
    push 4
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 10h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00773F20@@YAXXZ ENDP

; Unwind@00b73f56: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00773F56@@YAXXZ
?rva00773F56@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00773F56@@YAXXZ ENDP

PUBLIC ?rva00773F6A@@YAXXZ
?rva00773F6A@@YAXXZ PROC
    push 0069D7C2h
    push 4
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 10h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00773F6A@@YAXXZ ENDP

; Unwind@00b75816: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00775816@@YAXXZ
?rva00775816@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00775816@@YAXXZ ENDP

; Unwind@00b764ef: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007764EF@@YAXXZ
?rva007764EF@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007764EF@@YAXXZ ENDP

; Unwind@00b773f7: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007773f7@@YAXXZ
?rva007773f7@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007773f7@@YAXXZ ENDP

PUBLIC ?rva0077831A@@YAXXZ
?rva0077831A@@YAXXZ PROC
    push 00695983h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 10h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077831A@@YAXXZ ENDP

; Unwind@00b7835b: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0077835b@@YAXXZ
?rva0077835b@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0077835b@@YAXXZ ENDP

PUBLIC ?rva0077836F@@YAXXZ
?rva0077836F@@YAXXZ PROC
    push 00695983h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 10h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077836F@@YAXXZ ENDP

; Unwind@00b7918e: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0077918e@@YAXXZ
?rva0077918e@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0077918e@@YAXXZ ENDP

; Unwind@00b7a855: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0077a855@@YAXXZ
?rva0077a855@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0077a855@@YAXXZ ENDP

; Unwind@00b7b9ce: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0077b9ce@@YAXXZ
?rva0077b9ce@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0077b9ce@@YAXXZ ENDP

PUBLIC ?rva0077BA17@@YAXXZ
?rva0077BA17@@YAXXZ PROC
    push 0072D4C0h
    push 14h
    push 60h
    mov eax, DWORD PTR [ebp-16]
    add eax, 40h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077BA17@@YAXXZ ENDP

PUBLIC ?rva0077BAE4@@YAXXZ
?rva0077BAE4@@YAXXZ PROC
    push 0072D4C0h
    push 14h
    push 60h
    mov eax, DWORD PTR [ebp-20]
    add eax, 40h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077BAE4@@YAXXZ ENDP

PUBLIC ?rva0077BB8F@@YAXXZ
?rva0077BB8F@@YAXXZ PROC
    push 0072D4C0h
    push 14h
    push 60h
    mov eax, DWORD PTR [ebp-16]
    add eax, 40h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077BB8F@@YAXXZ ENDP
_TEXT ENDS
END
