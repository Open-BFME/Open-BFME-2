.386
.model flat
assume fs:nothing

; Address-derived EH cleanup funclets from dump range 38.
; Parent ownership and concrete field identity remain unknown. These bodies are
; compiler-generated MSVC 7.1 EH helpers; neighboring Range39 C++ probes failed
; to reproduce this standalone frame code, so MASM preserves the SEH behavior.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??1Rva004444D2@@UAE@XZ:PROC
EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva0038465B@@QAE@XZ:PROC
EXTERN ??1Rva003ED94FDtor@@QAE@XZ:PROC
EXTERN ??1Rva002606AFDtor@@QAE@XZ:PROC
EXTERN ?call@Rva002E3A80Holder@@QAEXXZ:PROC
EXTERN ??1Rva005F8F96@@QAE@XZ:PROC
EXTERN ??1Rva004F6093Holder@@QAE@XZ:PROC
EXTERN ??1Rva00410688@@QAE@XZ:PROC
EXTERN ??1Rva0045EF90Object@@UAE@XZ:PROC
EXTERN ??1Rva004104C9@@QAE@XZ:PROC
EXTERN ??1CameraMarker@@QAE@XZ:PROC
EXTERN ??1Rva005A9562@@QAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC
EXTERN ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva002390CB@@QAE@XZ:PROC

EXTERN ??1Rva004E6A37@@QAE@XZ:PROC
EXTERN ??1Rva0055B0CC@@UAE@XZ:PROC
EXTERN ??1?$map@VAsciiString@@V1@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@QAE@XZ:PROC
EXTERN ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00238D97DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00506B28DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva00574A8A@@UAE@XZ:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC
EXTERN ??1Rva0024A797@@UAE@XZ:PROC
EXTERN ??1Rva005248D0@@UAE@XZ:PROC
EXTERN ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ:PROC
EXTERN ??1Gen_uw_0049b47c@@QAE@XZ:PROC
EXTERN ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ:PROC

_TEXT SEGMENT
; Unwind@00b7c75e at RVA 0x0077C75E; 22-byte body ends at RET.
PUBLIC ?rva0077c75e@@YAXXZ
?rva0077c75e@@YAXXZ PROC
    push 0088BA39h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 7Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077c75e@@YAXXZ ENDP

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

; Unwind@00b7c9be at RVA 0x0077C9BE; 22-byte body ends at RET.
PUBLIC ?rva0077c9be@@YAXXZ
?rva0077c9be@@YAXXZ PROC
    push 0088BA39h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 7Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077c9be@@YAXXZ ENDP

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
; Unwind@00b7d4f8: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva0077d4f8@@YAXXZ
?rva0077d4f8@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva0077d4f8@@YAXXZ ENDP
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

; Unwind@00b7e855 at RVA 0x0077E855; 20-byte masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to the EmissionVelocityInfo dtor at 0x0049B47C.
PUBLIC ?rva0077e855@@YAXXZ
?rva0077e855@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva0077e855@@YAXXZ ENDP

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

; Unwind@00b81431 at RVA 0x00781431; 22-byte eh-vector-dtor passes [ebp-16]+4 with size 24 count 7 and raw dtor VA 0x0079EAB7.
PUBLIC ?rva00781431@@YAXXZ
?rva00781431@@YAXXZ PROC
    push 0079EAB7h
    push 7
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00781431@@YAXXZ ENDP

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

; Unwind@00b819ce: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007819ce@@YAXXZ
?rva007819ce@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007819ce@@YAXXZ ENDP

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

; Unwind@00b8217e at RVA 0x0078217E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078217e@@YAXXZ
?rva0078217e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078217e
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078217e:
    ret
?rva0078217e@@YAXXZ ENDP

; Unwind@00b8228f at RVA 0x0078228F; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to the address-derived thunk.
PUBLIC ?rva0078228f@@YAXXZ
?rva0078228f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0078228f
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva0038465B@@QAE@XZ
cleanup_done_0078228f:
    ret
?rva0078228f@@YAXXZ ENDP

; Unwind@00b823be at RVA 0x007823BE; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007823be@@YAXXZ
?rva007823be@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007823be
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007823be:
    ret
?rva007823be@@YAXXZ ENDP

; Unwind@00b82404 at RVA 0x00782404; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-36] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00782404@@YAXXZ
?rva00782404@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-36]
    and eax, 1
    jz NEAR PTR cleanup_done_00782404
    and DWORD PTR [ebp-36], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00782404:
    ret
?rva00782404@@YAXXZ ENDP

; Unwind@00b82478 at RVA 0x00782478; 25-byte state-bit cleanup ends at RET.
; Same state-bit cleanup as 0x782404; frame slot is [ebp-36].
PUBLIC ?rva00782478@@YAXXZ
?rva00782478@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-36]
    and eax, 1
    jz NEAR PTR cleanup_done_00782478
    and DWORD PTR [ebp-36], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00782478:
    ret
?rva00782478@@YAXXZ ENDP

; Unwind@00b824d7 at RVA 0x007824D7; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-32] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007824d7@@YAXXZ
?rva007824d7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_007824d7
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007824d7:
    ret
?rva007824d7@@YAXXZ ENDP

; Unwind@00b827e8 at RVA 0x007827E8; 20-byte masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to the EmissionVelocityInfo dtor at 0x0049B47C.
PUBLIC ?rva007827e8@@YAXXZ
?rva007827e8@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva007827e8@@YAXXZ ENDP

; Unwind@00b836e8 at RVA 0x007836E8; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007836e8@@YAXXZ
?rva007836e8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007836e8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007836e8:
    ret
?rva007836e8@@YAXXZ ENDP

; Unwind@00b8378d at RVA 0x0078378D; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed dtor.
PUBLIC ?rva0078378d@@YAXXZ
?rva0078378d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078378d
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva003ED94FDtor@@QAE@XZ
cleanup_done_0078378d:
    ret
?rva0078378d@@YAXXZ ENDP

; Unwind@00b8382a at RVA 0x0078382A; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps with [ebp-32] to AsciiString dtor.
PUBLIC ?rva0078382a@@YAXXZ
?rva0078382a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078382a
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078382a:
    ret
?rva0078382a@@YAXXZ ENDP

; Unwind@00b83928 at RVA 0x00783928; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-24] to AsciiString dtor.
PUBLIC ?rva00783928@@YAXXZ
?rva00783928@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00783928
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00783928:
    ret
?rva00783928@@YAXXZ ENDP

; Unwind@00b8398a at RVA 0x0078398A; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to the rowed UnicodeString thunk.
PUBLIC ?rva0078398a@@YAXXZ
?rva0078398a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078398a
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_0078398a:
    ret
?rva0078398a@@YAXXZ ENDP

; Unwind@00b839a3 at RVA 0x007839A3; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva007839a3@@YAXXZ
?rva007839a3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007839a3
    and DWORD PTR [ebp-16], -3
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007839a3:
    ret
?rva007839a3@@YAXXZ ENDP

; Unwind@00b83a5e at RVA 0x00783A5E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-32] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva00783a5e@@YAXXZ
?rva00783a5e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_00783a5e
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00783a5e:
    ret
?rva00783a5e@@YAXXZ ENDP

; Unwind@00b83ac1 at RVA 0x00783AC1; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva00783ac1@@YAXXZ
?rva00783ac1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00783ac1
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00783ac1:
    ret
?rva00783ac1@@YAXXZ ENDP

; Unwind@00b84220 at RVA 0x00784220; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to the rowed UnicodeString thunk.
PUBLIC ?rva00784220@@YAXXZ
?rva00784220@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00784220
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00784220:
    ret
?rva00784220@@YAXXZ ENDP

; Unwind@00b84239 at RVA 0x00784239; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva00784239@@YAXXZ
?rva00784239@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00784239
    and DWORD PTR [ebp-16], -3
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00784239:
    ret
?rva00784239@@YAXXZ ENDP

; Unwind@00b84973 at RVA 0x00784973; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00784973@@YAXXZ
?rva00784973@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00784973
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00784973:
    ret
?rva00784973@@YAXXZ ENDP

; Unwind@00b849c6 at RVA 0x007849C6; 25-byte state-bit cleanup ends at RET.
; Same state-bit cleanup as 0x784973; frame slot is [ebp-28].
PUBLIC ?rva007849c6@@YAXXZ
?rva007849c6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007849c6
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007849c6:
    ret
?rva007849c6@@YAXXZ ENDP

; Unwind@00b84a1f at RVA 0x00784A1F; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-68] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00784a1f@@YAXXZ
?rva00784a1f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-68]
    and eax, 1
    jz NEAR PTR cleanup_done_00784a1f
    and DWORD PTR [ebp-68], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00784a1f:
    ret
?rva00784a1f@@YAXXZ ENDP

; Unwind@00b84ac6 at RVA 0x00784AC6; 25-byte vector cleanup ends at RET.
; Target passes [ebp-0xe7c] to the rowed iterator with element size 0x1ac count 8 and dtor VA 0x006294FD.
PUBLIC ?rva00784ac6@@YAXXZ
?rva00784ac6@@YAXXZ PROC
    push 006294FDh
    push 8
    push 1ACh
    lea eax, DWORD PTR [ebp-0E7Ch]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00784ac6@@YAXXZ ENDP

; Unwind@00b84ae7 at RVA 0x00784AE7; 22-byte eh-vector-dtor passes [ebp-244] with size 4 count 8 and raw dtor VA 0x009B804E.
PUBLIC ?rva00784ae7@@YAXXZ
?rva00784ae7@@YAXXZ PROC
    push 009B804Eh
    push 8
    push 4
    lea eax, DWORD PTR [ebp-244]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00784ae7@@YAXXZ ENDP

; Unwind@00b84e61: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00784e61@@YAXXZ
?rva00784e61@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00784e61@@YAXXZ ENDP

; Unwind@00b84f0c at RVA 0x00784F0C; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed holder call.
PUBLIC ?rva00784f0c@@YAXXZ
?rva00784f0c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00784f0c
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_00784f0c:
    ret
?rva00784f0c@@YAXXZ ENDP

; Unwind@00b85033 at RVA 0x00785033; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-80] and tail-jumps through [ebp+8] to the rowed dtor.
PUBLIC ?rva00785033@@YAXXZ
?rva00785033@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-80]
    and eax, 1
    jz NEAR PTR cleanup_done_00785033
    and DWORD PTR [ebp-80], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_00785033:
    ret
?rva00785033@@YAXXZ ENDP

; Unwind@00b8509f at RVA 0x0078509F; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to the rowed dtor.
PUBLIC ?rva0078509f@@YAXXZ
?rva0078509f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0078509f
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0078509f:
    ret
?rva0078509f@@YAXXZ ENDP

; Unwind@00b850cc at RVA 0x007850CC; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed holder call.
PUBLIC ?rva007850cc@@YAXXZ
?rva007850cc@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007850cc
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007850cc:
    ret
?rva007850cc@@YAXXZ ENDP

; Unwind@00b85121 at RVA 0x00785121; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00785121@@YAXXZ
?rva00785121@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00785121
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00785121:
    ret
?rva00785121@@YAXXZ ENDP

; Unwind@00b8539a at RVA 0x0078539A; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x80 to the rowed iterator with element size 12 count 15 and AsciiString dtor VA 0x0088BA39.
PUBLIC ?rva0078539a@@YAXXZ
?rva0078539a@@YAXXZ PROC
    push 0088BA39h
    push 0Fh
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 80h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078539a@@YAXXZ ENDP

; Unwind@00b85754 at RVA 0x00785754; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed folded destructor.
PUBLIC ?rva00785754@@YAXXZ
?rva00785754@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785754
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00785754:
    ret
?rva00785754@@YAXXZ ENDP

; Unwind@00b8577f at RVA 0x0078577F; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed holder dtor.
PUBLIC ?rva0078577f@@YAXXZ
?rva0078577f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078577f
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva004F6093Holder@@QAE@XZ
cleanup_done_0078577f:
    ret
?rva0078577f@@YAXXZ ENDP

; Unwind@00b85b4b at RVA 0x00785B4B; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to the rowed dtor.
PUBLIC ?rva00785b4b@@YAXXZ
?rva00785b4b@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785b4b
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_00785b4b:
    ret
?rva00785b4b@@YAXXZ ENDP

; Unwind@00b85b64 at RVA 0x00785B64; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps with [ebp-32] to the rowed dtor.
PUBLIC ?rva00785b64@@YAXXZ
?rva00785b64@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00785b64
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-32]
    jmp ??1Rva00410688@@QAE@XZ
cleanup_done_00785b64:
    ret
?rva00785b64@@YAXXZ ENDP

; Unwind@00b85b87 at RVA 0x00785B87; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-68] to the rowed Rva0045EF90Object dtor.
PUBLIC ?rva00785b87@@YAXXZ
?rva00785b87@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785b87
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-68]
    jmp ??1Rva0045EF90Object@@UAE@XZ
cleanup_done_00785b87:
    ret
?rva00785b87@@YAXXZ ENDP

; Unwind@00b85ba0 at RVA 0x00785BA0; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps with [ebp-116] to the rowed dtor.
PUBLIC ?rva00785ba0@@YAXXZ
?rva00785ba0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00785ba0
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-116]
    jmp ??1Rva004104C9@@QAE@XZ
cleanup_done_00785ba0:
    ret
?rva00785ba0@@YAXXZ ENDP

; Unwind@00b85bc3 at RVA 0x00785BC3; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-24] to AsciiString dtor.
PUBLIC ?rva00785bc3@@YAXXZ
?rva00785bc3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785bc3
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00785bc3:
    ret
?rva00785bc3@@YAXXZ ENDP

; Unwind@00b85bee at RVA 0x00785BEE; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00785bee@@YAXXZ
?rva00785bee@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785bee
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00785bee:
    ret
?rva00785bee@@YAXXZ ENDP

; Unwind@00b85c19 at RVA 0x00785C19; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed CameraMarker dtor.
PUBLIC ?rva00785c19@@YAXXZ
?rva00785c19@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785c19
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1CameraMarker@@QAE@XZ
cleanup_done_00785c19:
    ret
?rva00785c19@@YAXXZ ENDP

; Unwind@00b85e8a at RVA 0x00785E8A; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00785e8a@@YAXXZ
?rva00785e8a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785e8a
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00785e8a:
    ret
?rva00785e8a@@YAXXZ ENDP

; Unwind@00b860ce: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007860ce@@YAXXZ
?rva007860ce@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007860ce@@YAXXZ ENDP

; Unwind@00b862be at RVA 0x007862BE; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007862be@@YAXXZ
?rva007862be@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007862be
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007862be:
    ret
?rva007862be@@YAXXZ ENDP

; Unwind@00b86a1b: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00786a1b@@YAXXZ
?rva00786a1b@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00786a1b@@YAXXZ ENDP

; Unwind@00b86c20 at RVA 0x00786C20; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps with [ebp-28] to the rowed folded destructor at 0x0007FAB3.
PUBLIC ?rva00786c20@@YAXXZ
?rva00786c20@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00786c20
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00786c20:
    ret
?rva00786c20@@YAXXZ ENDP

; Unwind@00b86c39 at RVA 0x00786C39; 25-byte state-bit cleanup ends at RET.
; Target clears bit 2 at [ebp-16] and tail-jumps with [ebp-44] to the existing rowed 0x000796BC provider.
PUBLIC ?rva00786c39@@YAXXZ
?rva00786c39@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_00786c39
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-44]
    jmp ??1Rva005A9562@@QAE@XZ
cleanup_done_00786c39:
    ret
?rva00786c39@@YAXXZ ENDP

; Unwind@00b86f3c: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva00786f3c@@YAXXZ
?rva00786f3c@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00786f3c@@YAXXZ ENDP

; Unwind@00b872bb: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007872bb@@YAXXZ
?rva007872bb@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007872bb@@YAXXZ ENDP

; Unwind@00b87397 at RVA 0x00787397; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to AsciiString dtor.
PUBLIC ?rva00787397@@YAXXZ
?rva00787397@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00787397
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00787397:
    ret
?rva00787397@@YAXXZ ENDP

; Unwind@00b87453 at RVA 0x00787453; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed STLport narrow basic_string dtor.
PUBLIC ?rva00787453@@YAXXZ
?rva00787453@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00787453
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00787453:
    ret
?rva00787453@@YAXXZ ENDP

; Unwind@00b875b8 at RVA 0x007875B8; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed Rva002E3A80 holder call.
PUBLIC ?rva007875b8@@YAXXZ
?rva007875b8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007875b8
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007875b8:
    ret
?rva007875b8@@YAXXZ ENDP

; Unwind@00b87601 at RVA 0x00787601; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to the rowed Rva002E3A80 holder call.
PUBLIC ?rva00787601@@YAXXZ
?rva00787601@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00787601
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_00787601:
    ret
?rva00787601@@YAXXZ ENDP

; Unwind@00b8776d at RVA 0x0078776D; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed Rva002E3A80 holder call.
PUBLIC ?rva0078776d@@YAXXZ
?rva0078776d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078776d
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_0078776d:
    ret
?rva0078776d@@YAXXZ ENDP

; Unwind@00b877a2 at RVA 0x007877A2; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to the rowed Rva002E3A80 holder call.
PUBLIC ?rva007877a2@@YAXXZ
?rva007877a2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007877a2
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007877a2:
    ret
?rva007877a2@@YAXXZ ENDP

; Unwind@00b8787d at RVA 0x0078787D; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to AsciiString dtor.
PUBLIC ?rva0078787d@@YAXXZ
?rva0078787d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078787d
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078787d:
    ret
?rva0078787d@@YAXXZ ENDP

; Unwind@00b8809b at RVA 0x0078809B; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078809b@@YAXXZ
?rva0078809b@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078809b
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078809b:
    ret
?rva0078809b@@YAXXZ ENDP

; Unwind@00b880bc at RVA 0x007880BC; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps with [ebp-24] to AsciiString dtor.
PUBLIC ?rva007880bc@@YAXXZ
?rva007880bc@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007880bc
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007880bc:
    ret
?rva007880bc@@YAXXZ ENDP

; Unwind@00b882c7 at RVA 0x007882C7; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva007882c7@@YAXXZ
?rva007882c7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007882c7
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007882c7:
    ret
?rva007882c7@@YAXXZ ENDP

; Unwind@00b88460 at RVA 0x00788460; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva00788460@@YAXXZ
?rva00788460@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00788460
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00788460:
    ret
?rva00788460@@YAXXZ ENDP

; Unwind@00b8848b at RVA 0x0078848B; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078848b@@YAXXZ
?rva0078848b@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078848b
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078848b:
    ret
?rva0078848b@@YAXXZ ENDP

; Unwind@00b884b6 at RVA 0x007884B6; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007884b6@@YAXXZ
?rva007884b6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007884b6
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007884b6:
    ret
?rva007884b6@@YAXXZ ENDP

; Unwind@00b88604 at RVA 0x00788604; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00788604@@YAXXZ
?rva00788604@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00788604
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00788604:
    ret
?rva00788604@@YAXXZ ENDP

; Unwind@00b8875d at RVA 0x0078875D; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078875d@@YAXXZ
?rva0078875d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078875d
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078875d:
    ret
?rva0078875d@@YAXXZ ENDP

; Unwind@00b88c1c at RVA 0x00788C1C; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x2f4 to the rowed iterator with element size 4 count 8 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva00788c1c@@YAXXZ
?rva00788c1c@@YAXXZ PROC
    push 004B3FD0h
    push 8
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 2F4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00788c1c@@YAXXZ ENDP

; Unwind@00b88cba at RVA 0x00788CBA; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x2f4 to the rowed iterator with element size 4 count 8 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva00788cba@@YAXXZ
?rva00788cba@@YAXXZ PROC
    push 004B3FD0h
    push 8
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 2F4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00788cba@@YAXXZ ENDP

; Unwind@00b88e2b at RVA 0x00788E2B; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-32] and tail-jumps with [ebp-40] to the rowed UnicodeString thunk.
PUBLIC ?rva00788e2b@@YAXXZ
?rva00788e2b@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_00788e2b
    and DWORD PTR [ebp-32], -2
    lea ecx, [ebp-40]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_00788e2b:
    ret
?rva00788e2b@@YAXXZ ENDP

; Unwind@00b88e8a at RVA 0x00788E8A; 22-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00788e8a@@YAXXZ
?rva00788e8a@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-20]
    mov eax, DWORD PTR [ebp-20]
    add eax, 27Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva00788e8a@@YAXXZ ENDP

; Unwind@00b88f9e at RVA 0x00788F9E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00788f9e@@YAXXZ
?rva00788f9e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00788f9e
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00788f9e:
    ret
?rva00788f9e@@YAXXZ ENDP

; Unwind@00b891cf at RVA 0x007891CF; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps with [ebp-36] to the rowed UnicodeString thunk.
PUBLIC ?rva007891cf@@YAXXZ
?rva007891cf@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007891cf
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-36]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007891cf:
    ret
?rva007891cf@@YAXXZ ENDP

; Unwind@00b891e8 at RVA 0x007891E8; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-20] and tail-jumps with [ebp-32] to the rowed UnicodeString thunk.
PUBLIC ?rva007891e8@@YAXXZ
?rva007891e8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 2
    jz NEAR PTR cleanup_done_007891e8
    and DWORD PTR [ebp-20], -3
    lea ecx, [ebp-32]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007891e8:
    ret
?rva007891e8@@YAXXZ ENDP

; Unwind@00b892ea at RVA 0x007892EA; 27-byte vector cleanup ends at RET.
; Target passes [ebp-20]+0xdc to the rowed iterator with element size 0x1d0 count 8 and raw dtor VA 0x00847B0E.
PUBLIC ?rva007892ea@@YAXXZ
?rva007892ea@@YAXXZ PROC
    push 00847B0Eh
    push 8
    push 1D0h
    mov eax, DWORD PTR [ebp-20]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007892ea@@YAXXZ ENDP

; Unwind@00b89325 at RVA 0x00789325; 27-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0xdc to the rowed iterator with element size 0x1d0 count 8 and raw dtor VA 0x00847B0E.
PUBLIC ?rva00789325@@YAXXZ
?rva00789325@@YAXXZ PROC
    push 00847B0Eh
    push 8
    push 1D0h
    mov eax, DWORD PTR [ebp-16]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00789325@@YAXXZ ENDP

; Unwind@00b8937e at RVA 0x0078937E; 25-byte vector cleanup ends at RET.
; Target passes [ebp-0xe40] to the rowed iterator with element size 0x1ac count 8 and raw dtor VA 0x006294FD.
PUBLIC ?rva0078937e@@YAXXZ
?rva0078937e@@YAXXZ PROC
    push 006294FDh
    push 8
    push 1ACh
    lea eax, DWORD PTR [ebp-0E40h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078937e@@YAXXZ ENDP

; Unwind@00b89417 at RVA 0x00789417; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x40e0c to the rowed iterator with element size 12 count 8 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva00789417@@YAXXZ
?rva00789417@@YAXXZ PROC
    push 004B3FD0h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 40E0Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00789417@@YAXXZ ENDP

; Unwind@00b8947e at RVA 0x0078947E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078947e@@YAXXZ
?rva0078947e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078947e
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078947e:
    ret
?rva0078947e@@YAXXZ ENDP

; Unwind@00b895a0 at RVA 0x007895A0; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-32] to the rowed UnicodeString thunk.
PUBLIC ?rva007895a0@@YAXXZ
?rva007895a0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007895a0
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007895a0:
    ret
?rva007895a0@@YAXXZ ENDP

; Unwind@00b89799 at RVA 0x00789799; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789799@@YAXXZ
?rva00789799@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00789799
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789799:
    ret
?rva00789799@@YAXXZ ENDP

; Unwind@00b897c4 at RVA 0x007897C4; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007897c4@@YAXXZ
?rva007897c4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007897c4
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007897c4:
    ret
?rva007897c4@@YAXXZ ENDP

; Unwind@00b89807 at RVA 0x00789807; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789807@@YAXXZ
?rva00789807@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00789807
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789807:
    ret
?rva00789807@@YAXXZ ENDP

; Unwind@00b89842 at RVA 0x00789842; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789842@@YAXXZ
?rva00789842@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00789842
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789842:
    ret
?rva00789842@@YAXXZ ENDP

; Unwind@00b898a1 at RVA 0x007898A1; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva007898a1@@YAXXZ
?rva007898a1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007898a1
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007898a1:
    ret
?rva007898a1@@YAXXZ ENDP

; Unwind@00b89920 at RVA 0x00789920; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789920@@YAXXZ
?rva00789920@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00789920
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789920:
    ret
?rva00789920@@YAXXZ ENDP

; Unwind@00b8995b at RVA 0x0078995B; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078995b@@YAXXZ
?rva0078995b@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078995b
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078995b:
    ret
?rva0078995b@@YAXXZ ENDP

; Unwind@00b8998e at RVA 0x0078998E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva0078998e@@YAXXZ
?rva0078998e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0078998e
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078998e:
    ret
?rva0078998e@@YAXXZ ENDP

; Unwind@00b8a304 at RVA 0x0078A304; 22-byte eh-vector-dtor lea target passes [ebp-156] with size 12 count 10 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a304@@YAXXZ
?rva0078a304@@YAXXZ PROC
    push 004B3FD0h
    push 0Ah
    push 0Ch
    lea eax, [ebp-156]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a304@@YAXXZ ENDP

; Unwind@00b8a463 at RVA 0x0078A463; 19-byte eh-vector-dtor lea target passes [ebp-80] with size 12 count 4 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a463@@YAXXZ
?rva0078a463@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, [ebp-80]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a463@@YAXXZ ENDP

; Unwind@00b8a669 at RVA 0x0078A669; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x88 to the rowed iterator with element size 12 count 4 and raw dtor VA 0x0047FAB3.
PUBLIC ?rva0078a669@@YAXXZ
?rva0078a669@@YAXXZ PROC
    push 0047FAB3h
    push 4
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 88h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a669@@YAXXZ ENDP

; Unwind@00b8a681 at RVA 0x0078A681; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0xb8 to the rowed iterator with element size 12 count 4 and raw dtor VA 0x0047FAB3.
PUBLIC ?rva0078a681@@YAXXZ
?rva0078a681@@YAXXZ PROC
    push 0047FAB3h
    push 4
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0B8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a681@@YAXXZ ENDP

; Unwind@00b8a729 at RVA 0x0078A729; 20-byte masked-add cleanup adds 20h to [ebp-16] and tail-jumps to the folded vector dtor at 0x0007FAB3.
PUBLIC ?rva0078a729@@YAXXZ
?rva0078a729@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 20h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
?rva0078a729@@YAXXZ ENDP

; Unwind@00b8a813 at RVA 0x0078A813; 22-byte eh-vector-dtor lea target passes [ebp-216] with size 12 count 16 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a813@@YAXXZ
?rva0078a813@@YAXXZ PROC
    push 004B3FD0h
    push 10h
    push 0Ch
    lea eax, [ebp-216]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a813@@YAXXZ ENDP

; Unwind@00b8a84b at RVA 0x0078A84B; 22-byte eh-vector-dtor lea target passes [ebp-260] with size 12 count 16 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a84b@@YAXXZ
?rva0078a84b@@YAXXZ PROC
    push 004B3FD0h
    push 10h
    push 0Ch
    lea eax, [ebp-260]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a84b@@YAXXZ ENDP

; Unwind@00b8b58e at RVA 0x0078B58E; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x338 to the rowed iterator with element size 16 count 60 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078b58e@@YAXXZ
?rva0078b58e@@YAXXZ PROC
    push 004B3FD0h
    push 3Ch
    push 10h
    mov eax, DWORD PTR [ebp-16]
    add eax, 338h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078b58e@@YAXXZ ENDP

; Unwind@00b8bd4c at RVA 0x0078BD4C; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24], passes [ebp-124] in ECX, then jumps to the rowed 0x0049C38A body.
PUBLIC ?rva0078bd4c@@YAXXZ
?rva0078bd4c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0078bd4c
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp-124]
    jmp ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ
cleanup_done_0078bd4c:
    ret
?rva0078bd4c@@YAXXZ ENDP

; Unwind@00b8bd65 at RVA 0x0078BD65; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-24], passes [ebp-88] in ECX, then jumps to the rowed 0x0049C38A body.
PUBLIC ?rva0078bd65@@YAXXZ
?rva0078bd65@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 2
    jz NEAR PTR cleanup_done_0078bd65
    and DWORD PTR [ebp-24], -3
    lea ecx, [ebp-88]
    jmp ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ
cleanup_done_0078bd65:
    ret
?rva0078bd65@@YAXXZ ENDP

; Unwind@00b8bd7e at RVA 0x0078BD7E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 2 at [ebp-24], passes [ebp-76] in ECX, then jumps to the rowed 0x0049C38A body.
PUBLIC ?rva0078bd7e@@YAXXZ
?rva0078bd7e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 4
    jz NEAR PTR cleanup_done_0078bd7e
    and DWORD PTR [ebp-24], -5
    lea ecx, [ebp-76]
    jmp ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ
cleanup_done_0078bd7e:
    ret
?rva0078bd7e@@YAXXZ ENDP

; Unwind@00b7c3fb at RVA 0x0077C3FB; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; forms ECX with LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0077c3fb@@YAXXZ
?rva0077c3fb@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0077c3fb
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0077c3fb:
    ret
?rva0077c3fb@@YAXXZ ENDP

; Unwind@00b7c414 at RVA 0x0077C414; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 1 at [ebp-16]; forms ECX with LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva0077c414@@YAXXZ
?rva0077c414@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0077c414
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077c414:
    ret
?rva0077c414@@YAXXZ ENDP

; Unwind@00b7c4ac at RVA 0x0077C4AC; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; forms ECX with LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0077c4ac@@YAXXZ
?rva0077c4ac@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0077c4ac
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0077c4ac:
    ret
?rva0077c4ac@@YAXXZ ENDP

; Unwind@00b8bd97 at RVA 0x0078BD97; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 3 at [ebp-24]; forms ECX with LEA from [ebp-108] only when set.
; The tail-jump target is a matched function at RVA 0x0049C38A; parent identity/layout remain unproven.
PUBLIC ?rva0078bd97@@YAXXZ
?rva0078bd97@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 8
    jz NEAR PTR cleanup_done_0078bd97
    and DWORD PTR [ebp-24], -9
    lea ecx, [ebp-108]
    jmp ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ
cleanup_done_0078bd97:
    ret
?rva0078bd97@@YAXXZ ENDP

; Unwind@00b8c77c at RVA 0x0078C77C; 19-byte eh-vector-dtor lea target passes [ebp-96] with size 12 count 4 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078c77c@@YAXXZ
?rva0078c77c@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, [ebp-96]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078c77c@@YAXXZ ENDP

; Unwind@00b8d24f at RVA 0x0078D24F; 22-byte eh-vector-dtor target passes [ebp-16]+0x44 with size 4 count 16 and raw dtor VA 0x0050F149.
PUBLIC ?rva0078d24f@@YAXXZ
?rva0078d24f@@YAXXZ PROC
    push 0050F149h
    push 10h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 44h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078d24f@@YAXXZ ENDP

; Unwind@00b8d398 at RVA 0x0078D398; 20-byte masked-add cleanup adds 4 to [ebp-16] and tail-jumps to the matched dtor at 0x0024A797.
PUBLIC ?rva0078d398@@YAXXZ
?rva0078d398@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva0024A797@@UAE@XZ
?rva0078d398@@YAXXZ ENDP

; Unwind@00b8e2ce at RVA 0x0078E2CE; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x003ED94F; parent identity/layout remain unproven.
PUBLIC ?rva0078e2ce@@YAXXZ
?rva0078e2ce@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078e2ce
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva003ED94FDtor@@QAE@XZ
cleanup_done_0078e2ce:
    ret
?rva0078e2ce@@YAXXZ ENDP

; Unwind@00b8fbb0 at RVA 0x0078FBB0; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 2 at [ebp-16]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0078fbb0@@YAXXZ
?rva0078fbb0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0078fbb0
    and DWORD PTR [ebp-16], -5
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078fbb0:
    ret
?rva0078fbb0@@YAXXZ ENDP

; Unwind@00b90c05 at RVA 0x00790C05; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00790c05@@YAXXZ
?rva00790c05@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00790c05
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00790c05:
    ret
?rva00790c05@@YAXXZ ENDP

; Unwind@00b91028 at RVA 0x00791028; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00791028@@YAXXZ
?rva00791028@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00791028
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00791028:
    ret
?rva00791028@@YAXXZ ENDP

; Unwind@00b910c8 at RVA 0x007910C8; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007910c8@@YAXXZ
?rva007910c8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007910c8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007910c8:
    ret
?rva007910c8@@YAXXZ ENDP

; Unwind@00b9113a at RVA 0x0079113A; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-28]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0079113a@@YAXXZ
?rva0079113a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079113a
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079113a:
    ret
?rva0079113a@@YAXXZ ENDP

; Unwind@00b918e9 at RVA 0x007918E9; 20-byte masked-add cleanup adds 8 to [ebp-16] and tail-jumps to the folded vector dtor at 0x0007FAB3.
PUBLIC ?rva007918e9@@YAXXZ
?rva007918e9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
?rva007918e9@@YAXXZ ENDP

; Unwind@00b91b95 at RVA 0x00791B95; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva00791b95@@YAXXZ
?rva00791b95@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00791b95
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00791b95:
    ret
?rva00791b95@@YAXXZ ENDP

; Unwind@00b91bf2 at RVA 0x00791BF2; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-28]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva00791bf2@@YAXXZ
?rva00791bf2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00791bf2
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00791bf2:
    ret
?rva00791bf2@@YAXXZ ENDP

; Unwind@00b91c6c at RVA 0x00791C6C; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00791c6c@@YAXXZ
?rva00791c6c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00791c6c
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00791c6c:
    ret
?rva00791c6c@@YAXXZ ENDP

; Unwind@00b921c9 at RVA 0x007921C9; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x004E6A37; parent identity/layout remain unproven.
PUBLIC ?rva007921c9@@YAXXZ
?rva007921c9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007921c9
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva004E6A37@@QAE@XZ
cleanup_done_007921c9:
    ret
?rva007921c9@@YAXXZ ENDP

; Unwind@00b92867 at RVA 0x00792867; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0007FAB3; parent identity/layout remain unproven.
PUBLIC ?rva00792867@@YAXXZ
?rva00792867@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00792867
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00792867:
    ret
?rva00792867@@YAXXZ ENDP


; Unwind@00b94872 at RVA 0x00794872; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00794872@@YAXXZ
?rva00794872@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00794872
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00794872:
    ret
?rva00794872@@YAXXZ ENDP

; Unwind@00b948fb at RVA 0x007948FB; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; uses LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007948fb@@YAXXZ
?rva007948fb@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007948fb
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007948fb:
    ret
?rva007948fb@@YAXXZ ENDP

; Unwind@00b949a2 at RVA 0x007949A2; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; uses LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007949a2@@YAXXZ
?rva007949a2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007949a2
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007949a2:
    ret
?rva007949a2@@YAXXZ ENDP

; Unwind@00b949c5 at RVA 0x007949C5; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 1 at [ebp-24]; uses LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007949c5@@YAXXZ
?rva007949c5@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 2
    jz NEAR PTR cleanup_done_007949c5
    and DWORD PTR [ebp-24], -3
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007949c5:
    ret
?rva007949c5@@YAXXZ ENDP

; Unwind@00b94a82 at RVA 0x00794A82; 22-byte body ends at RET.
PUBLIC ?rva00794a82@@YAXXZ
?rva00794a82@@YAXXZ PROC
    push 0090EB02h
    push 7
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 24h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00794a82@@YAXXZ ENDP

; Unwind@00b94adc at RVA 0x00794ADC; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; uses LEA from [ebp-20] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00794adc@@YAXXZ
?rva00794adc@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00794adc
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00794adc:
    ret
?rva00794adc@@YAXXZ ENDP

; Unwind@00b94b98 at RVA 0x00794B98; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; uses LEA from [ebp-20] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00794b98@@YAXXZ
?rva00794b98@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00794b98
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00794b98:
    ret
?rva00794b98@@YAXXZ ENDP

; Unwind@00b94bbb at RVA 0x00794BBB; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 2 at [ebp-16]; uses LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00794bbb@@YAXXZ
?rva00794bbb@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_00794bbb
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00794bbb:
    ret
?rva00794bbb@@YAXXZ ENDP

; Unwind@00b9504c at RVA 0x0079504C; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva0079504c@@YAXXZ
?rva0079504c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079504c
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079504c:
    ret
?rva0079504c@@YAXXZ ENDP

; Unwind@00b9509f at RVA 0x0079509F; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-40]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva0079509f@@YAXXZ
?rva0079509f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-40]
    and eax, 1
    jz NEAR PTR cleanup_done_0079509f
    and DWORD PTR [ebp-40], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079509f:
    ret
?rva0079509f@@YAXXZ ENDP

; Unwind@00b9584d at RVA 0x0079584D; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-16]; uses LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0079584d@@YAXXZ
?rva0079584d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079584d
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079584d:
    ret
?rva0079584d@@YAXXZ ENDP

; Unwind@00b95866 at RVA 0x00795866; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 1 at [ebp-16]; uses LEA from [ebp-32] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00795866@@YAXXZ
?rva00795866@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_00795866
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00795866:
    ret
?rva00795866@@YAXXZ ENDP

; Unwind@00b9588f at RVA 0x0079588F; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 2 at [ebp-16]; uses LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva0079588f@@YAXXZ
?rva0079588f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0079588f
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079588f:
    ret
?rva0079588f@@YAXXZ ENDP

; Unwind@00b958a8 at RVA 0x007958A8; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 3 at [ebp-16]; uses LEA from [ebp-32] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007958a8@@YAXXZ
?rva007958a8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 8
    jz NEAR PTR cleanup_done_007958a8
    and DWORD PTR [ebp-16], -9
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007958a8:
    ret
?rva007958a8@@YAXXZ ENDP

; Unwind@00b958d1 at RVA 0x007958D1; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 4 at [ebp-16]; uses LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007958d1@@YAXXZ
?rva007958d1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 16
    jz NEAR PTR cleanup_done_007958d1
    and DWORD PTR [ebp-16], -17
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007958d1:
    ret
?rva007958d1@@YAXXZ ENDP

; Unwind@00b958ea at RVA 0x007958EA; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 5 at [ebp-16]; uses LEA from [ebp-32] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007958ea@@YAXXZ
?rva007958ea@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 32
    jz NEAR PTR cleanup_done_007958ea
    and DWORD PTR [ebp-16], -33
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007958ea:
    ret
?rva007958ea@@YAXXZ ENDP

; Unwind@00b95913 at RVA 0x00795913; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 6 at [ebp-16]; uses LEA from [ebp-24] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00795913@@YAXXZ
?rva00795913@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 64
    jz NEAR PTR cleanup_done_00795913
    and DWORD PTR [ebp-16], -65
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00795913:
    ret
?rva00795913@@YAXXZ ENDP

; Unwind@00b95d0d at RVA 0x00795D0D; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-32]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00795d0d@@YAXXZ
?rva00795d0d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_00795d0d
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00795d0d:
    ret
?rva00795d0d@@YAXXZ ENDP

; Unwind@00b95d4a at RVA 0x00795D4A; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00795d4a@@YAXXZ
?rva00795d4a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00795d4a
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00795d4a:
    ret
?rva00795d4a@@YAXXZ ENDP

; Unwind@00b9619c at RVA 0x0079619C; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses LEA from [ebp-48] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva0079619c@@YAXXZ
?rva0079619c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079619c
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-48]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079619c:
    ret
?rva0079619c@@YAXXZ ENDP

; Unwind@00b962c3 at RVA 0x007962C3; 22-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva007962c3@@YAXXZ
?rva007962c3@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-20]
    mov eax, DWORD PTR [ebp-20]
    add eax, 27Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva007962c3@@YAXXZ ENDP

; Unwind@00b961b5 at RVA 0x007961B5; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 1 at [ebp-20]; uses LEA from [ebp-36] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva007961b5@@YAXXZ
?rva007961b5@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 2
    jz NEAR PTR cleanup_done_007961b5
    and DWORD PTR [ebp-20], -3
    lea ecx, [ebp-36]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007961b5:
    ret
?rva007961b5@@YAXXZ ENDP


; Unwind@00b963cf at RVA 0x007963CF; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-28] then loads ECX from [ebp+8] only when set.
; Tail-jumps to the matched UnicodeString destructor at 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva007963cf@@YAXXZ
?rva007963cf@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007963cf
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007963cf:
    ret
?rva007963cf@@YAXXZ ENDP


; Unwind@00b9592c at RVA 0x0079592C; 27-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 7 of the byte at [ebp-16]; the set path passes [ebp-32] to AsciiString.
; Parent identity and layout remain unproven; MASM preserves this compiler-generated EH helper.
PUBLIC ?rva0079592c@@YAXXZ
?rva0079592c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 80h
    jz NEAR PTR cleanup_done_0079592c
    and BYTE PTR [ebp-16], 7Fh
    lea ecx, [ebp-32]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079592c:
    ret
?rva0079592c@@YAXXZ ENDP

; Unwind@00b8fb7e at RVA 0x0078FB7E; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] then tail-jumps with local [ebp-24] to VA 0x0088BA39.
PUBLIC ?rva0078fb7e@@YAXXZ
?rva0078fb7e@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 1
    jz NEAR PTR cleanup_done_0078fb7e
    and DWORD PTR [ebp-10h], -2
    lea ecx, [ebp-18h]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078fb7e:
    ret
?rva0078fb7e@@YAXXZ ENDP

; Unwind@00b8fb97 at RVA 0x0078FB97; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] then tail-jumps with local [ebp-20] to VA 0x0088BA39.
PUBLIC ?rva0078fb97@@YAXXZ
?rva0078fb97@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 2
    jz NEAR PTR cleanup_done_0078fb97
    and DWORD PTR [ebp-10h], -3
    lea ecx, [ebp-14h]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078fb97:
    ret
?rva0078fb97@@YAXXZ ENDP

; Unwind@00b91289 at RVA 0x00791289; target byte boundary is 25 bytes.
; State bit 0 gates cleanup at [ebp-28] via VA 0x008C9F38; parent and
; concrete local type remain unknown.
PUBLIC ?rva00791289@@YAXXZ
?rva00791289@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 1
    jz NEAR PTR cleanup_done_00791289
    and DWORD PTR [ebp-10h], -2
    lea ecx, [ebp-28h]
    jmp ??1Rva002390CB@@QAE@XZ
cleanup_done_00791289:
    ret
?rva00791289@@YAXXZ ENDP

; Unwind@00b912a2 at RVA 0x007912A2; target byte boundary is 25 bytes.
; State bit 1 gates cleanup at [ebp-20] via VA 0x008C9F38; parent and
; concrete local type remain unknown.
PUBLIC ?rva007912a2@@YAXXZ
?rva007912a2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 2
    jz NEAR PTR cleanup_done_007912a2
    and DWORD PTR [ebp-10h], -3
    lea ecx, [ebp-20h]
    jmp ??1Rva002390CB@@QAE@XZ
cleanup_done_007912a2:
    ret
?rva007912a2@@YAXXZ ENDP

; Unwind@00b912cd at RVA 0x007912CD; target byte boundary is 25 bytes.
; State bit 0 gates cleanup at [ebp-20] via VA 0x008C9F38; parent and
; concrete local type remain unknown.
PUBLIC ?rva007912cd@@YAXXZ
?rva007912cd@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 1
    jz NEAR PTR cleanup_done_007912cd
    and DWORD PTR [ebp-10h], -2
    lea ecx, [ebp-20h]
    jmp ??1Rva002390CB@@QAE@XZ
cleanup_done_007912cd:
    ret
?rva007912cd@@YAXXZ ENDP

; Unwind@00b922c7 at RVA 0x007922C7; target byte boundary is 25 bytes.
; State bit 0 gates [ebp+8] cleanup through matched RVA 0x002E3A80;
; parent identity and cleanup-object layout remain unknown.
PUBLIC ?rva007922c7@@YAXXZ
?rva007922c7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 1
    jz NEAR PTR cleanup_done_007922c7
    and DWORD PTR [ebp-10h], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007922c7:
    ret
?rva007922c7@@YAXXZ ENDP

; Unwind@00b92364 at RVA 0x00792364; target byte boundary is 25 bytes.
; State bit 0 gates [ebp+8] cleanup through matched RVA 0x005F8F96;
; parent identity and cleanup-object layout remain unknown.
PUBLIC ?rva00792364@@YAXXZ
?rva00792364@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-3Ch]
    and eax, 1
    jz NEAR PTR cleanup_done_00792364
    and DWORD PTR [ebp-3Ch], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_00792364:
    ret
?rva00792364@@YAXXZ ENDP

; Unwind@00b92aa2: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x004EDFF8.
PUBLIC ?rva00792aa2@@YAXXZ
?rva00792aa2@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ
?rva00792aa2@@YAXXZ ENDP

; Unwind@00b92a7a: masked-add cleanup adds 04h to [ebp-16] and tail-jumps to 0x004EDFFF.
PUBLIC ?rva00792a7a@@YAXXZ
?rva00792a7a@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 04h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ
?rva00792a7a@@YAXXZ ENDP

; Unwind@00b92eb6 at RVA 0x00792EB6; target byte boundary is 25 bytes.
; State bit 0 gates [ebp+8] cleanup through RVA 0x005B804E; parent
; identity and concrete cleanup-object type remain unknown.
PUBLIC ?rva00792eb6@@YAXXZ
?rva00792eb6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28h]
    and eax, 1
    jz NEAR PTR cleanup_done_00792eb6
    and DWORD PTR [ebp-28h], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00792eb6:
    ret
?rva00792eb6@@YAXXZ ENDP

; Unwind@00b93094 at RVA 0x00793094; target byte boundary is 25 bytes.
; State bit 0 gates [ebp-14] cleanup through RVA 0x005F8F96; parent
; identity and concrete local type remain unknown.
PUBLIC ?rva00793094@@YAXXZ
?rva00793094@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-10h]
    and eax, 1
    jz NEAR PTR cleanup_done_00793094
    and DWORD PTR [ebp-10h], -2
    lea ecx, [ebp-14h]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_00793094:
    ret
?rva00793094@@YAXXZ ENDP

; Unwind@00b9322b at RVA 0x0079322B; 22-byte body ends at RET.
PUBLIC ?rva0079322b@@YAXXZ
?rva0079322b@@YAXXZ PROC
    push 009CD0D7h
    push 10h
    push 4
    lea eax, DWORD PTR [ebp-0ACh]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0079322b@@YAXXZ ENDP

; Unwind@00b93312 at RVA 0x00793312; 22-byte body ends at RET.
PUBLIC ?rva00793312@@YAXXZ
?rva00793312@@YAXXZ PROC
    push 008F7D7Fh
    push 2
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00793312@@YAXXZ ENDP

; Unwind@00b93328 at RVA 0x00793328; 22-byte body ends at RET.
PUBLIC ?rva00793328@@YAXXZ
?rva00793328@@YAXXZ PROC
    push 008F9630h
    push 2
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 24h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00793328@@YAXXZ ENDP

; Unwind@00b93387 at RVA 0x00793387; 22-byte body ends at RET.
PUBLIC ?rva00793387@@YAXXZ
?rva00793387@@YAXXZ PROC
    push 008F7D7Fh
    push 2
    push 0Ch
    mov eax, DWORD PTR [ebp-28]
    add eax, 0Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00793387@@YAXXZ ENDP

; Unwind@00b9339d at RVA 0x0079339D; 22-byte body ends at RET.
PUBLIC ?rva0079339d@@YAXXZ
?rva0079339d@@YAXXZ PROC
    push 008F9630h
    push 2
    push 0Ch
    mov eax, DWORD PTR [ebp-28]
    add eax, 24h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0079339d@@YAXXZ ENDP

; Unwind@00b93a65 at RVA 0x00793A65; target byte boundary is 25 bytes.
; State bit 0 gates [ebp-5c] cleanup through RVA 0x0048BA39; parent
; identity and concrete local type remain unknown.
PUBLIC ?rva00793a65@@YAXXZ
?rva00793a65@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-14h]
    and eax, 1
    jz NEAR PTR cleanup_done_00793a65
    and DWORD PTR [ebp-14h], -2
    lea ecx, [ebp-5Ch]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00793a65:
    ret
?rva00793a65@@YAXXZ ENDP

; Unwind@00b93a86 at RVA 0x00793A86; target byte boundary is 25 bytes.
; State bit 1 gates [ebp-60] cleanup through RVA 0x0048BA39; parent
; identity and concrete local type remain unknown.
PUBLIC ?rva00793a86@@YAXXZ
?rva00793a86@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-14h]
    and eax, 2
    jz NEAR PTR cleanup_done_00793a86
    and DWORD PTR [ebp-14h], -3
    lea ecx, [ebp-60h]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00793a86:
    ret
?rva00793a86@@YAXXZ ENDP

; Unwind@00b93a9f at RVA 0x00793A9F; target byte boundary is 25 bytes.
; State bit 2 gates [ebp-48] cleanup through RVA 0x0048BA39; parent
; identity and concrete local type remain unknown.
PUBLIC ?rva00793a9f@@YAXXZ
?rva00793a9f@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-14h]
    and eax, 4
    jz NEAR PTR cleanup_done_00793a9f
    and DWORD PTR [ebp-14h], -5
    lea ecx, [ebp-48h]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00793a9f:
    ret
?rva00793a9f@@YAXXZ ENDP

; Unwind@00b93ad8 at RVA 0x00793AD8; target byte boundary is 25 bytes.
; State bit 3 gates [ebp+8] cleanup through RVA 0x0048BA39; parent
; identity and concrete cleanup-object type remain unknown.
PUBLIC ?rva00793ad8@@YAXXZ
?rva00793ad8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-14h]
    and eax, 8
    jz NEAR PTR cleanup_done_00793ad8
    and DWORD PTR [ebp-14h], -9
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00793ad8:
    ret
?rva00793ad8@@YAXXZ ENDP

; Unwind@00b93ba5 at RVA 0x00793BA5; target byte boundary is 25 bytes.
; State bit 0 gates [ebp+8] cleanup through folded RVA 0x0007FAB3;
; parent and concrete object identity remain unknown.
PUBLIC ?rva00793ba5@@YAXXZ
?rva00793ba5@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-18h]
    and eax, 1
    jz NEAR PTR cleanup_done_00793ba5
    and DWORD PTR [ebp-18h], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_00793ba5:
    ret
?rva00793ba5@@YAXXZ ENDP

; Unwind@00b81953 at RVA 0x00781953; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00781953@@YAXXZ
?rva00781953@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva0055B0CC@@UAE@XZ
?rva00781953@@YAXXZ ENDP

; Unwind@00b82215 at RVA 0x00782215; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00782215@@YAXXZ
?rva00782215@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$map@VAsciiString@@V1@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@QAE@XZ
?rva00782215@@YAXXZ ENDP

; Unwind@00b83ce0 at RVA 0x00783CE0; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00783ce0@@YAXXZ
?rva00783ce0@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
?rva00783ce0@@YAXXZ ENDP

; Unwind@00b840e9 at RVA 0x007840E9; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva007840e9@@YAXXZ
?rva007840e9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
?rva007840e9@@YAXXZ ENDP

; Unwind@00b840fd at RVA 0x007840FD; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva007840fd@@YAXXZ
?rva007840fd@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007840fd@@YAXXZ ENDP

; Unwind@00b873e9 at RVA 0x007873E9; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva007873e9@@YAXXZ
?rva007873e9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva007873e9@@YAXXZ ENDP

; Unwind@00b87652 at RVA 0x00787652; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva00787652@@YAXXZ
?rva00787652@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva00787652@@YAXXZ ENDP

; Unwind@00b87666 at RVA 0x00787666; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva00787666@@YAXXZ
?rva00787666@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ
?rva00787666@@YAXXZ ENDP

; Unwind@00b8768e at RVA 0x0078768E; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva0078768e@@YAXXZ
?rva0078768e@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva00574A8A@@UAE@XZ
?rva0078768e@@YAXXZ ENDP

; Unwind@00b925e9 at RVA 0x007925E9; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva007925e9@@YAXXZ
?rva007925e9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00506B28DwordImmSetter@@QAEXXZ
?rva007925e9@@YAXXZ ENDP

; Unwind@00b93241 at RVA 0x00793241; 19-byte eh-vector-dtor lea target.
PUBLIC ?rva00793241@@YAXXZ
?rva00793241@@YAXXZ PROC
    push 008F87B7h
    push 2
    push 10h
    lea eax, [ebp-108]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00793241@@YAXXZ ENDP

; Unwind@00b93655 at RVA 0x00793655; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00793655@@YAXXZ
?rva00793655@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
?rva00793655@@YAXXZ ENDP

; Unwind@00b93669 at RVA 0x00793669; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva00793669@@YAXXZ
?rva00793669@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ
?rva00793669@@YAXXZ ENDP

; Unwind@00b94a43 at RVA 0x00794A43; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00794a43@@YAXXZ
?rva00794a43@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005248D0@@UAE@XZ
?rva00794a43@@YAXXZ ENDP

_TEXT ENDS
END
