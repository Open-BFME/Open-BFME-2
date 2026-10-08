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
EXTERN ?apply@Rva0057A243DwordImmSetter@@QAEXXZ:PROC
EXTERN ?rva0053FCB3@Rva0053FCB3@@QAEXXZ:PROC
EXTERN ??1Rva003844D7@@QAE@XZ:PROC
EXTERN ??1Rva0038454E@@QAE@XZ:PROC
EXTERN ??1Rva00385333@@QAE@XZ:PROC
EXTERN ??1Gen_uw_00385371@@QAE@XZ:PROC
EXTERN ??1Rva005F8F96@@QAE@XZ:PROC
EXTERN ??1RefHolder@Rva005CCC07@@QAE@XZ:PROC
EXTERN ??1BfmePoolRef10@@QAE@XZ:PROC
EXTERN ??1BfmeStringTailRecord156@@QAE@XZ:PROC
EXTERN ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005F4179@@UAE@XZ:PROC
EXTERN ??1Rva005F918D@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva005F4AD7@@QAE@XZ:PROC
EXTERN ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC
EXTERN ??1Q1ReceiverLocalSet@@QAE@XZ:PROC
EXTERN ??1BfmeWideResult@@QAE@XZ:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC
EXTERN ??1EAStringC@@QAE@XZ:PROC
EXTERN ??1Rva004A9DF3Element@@QAE@XZ:PROC
EXTERN ??1SBServer@@QAE@XZ:PROC
EXTERN ?apply@Rva00574293DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0057428CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0005E186ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva000574265DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva002B2294DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00238D97DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0005D23FEDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005753E2DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00576456DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005CD1A9@@UAE@XZ:PROC
EXTERN ??1Rva00578C23@@UAE@XZ:PROC
EXTERN ??1Rva005D40A6@@UAE@XZ:PROC
EXTERN ?apply@Rva0057A235DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00506B28DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva004444D2@@UAE@XZ:PROC
EXTERN ?apply@Rva0059EB3ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005EB753@@UAE@XZ:PROC
EXTERN ?apply@Rva005CF843DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005CF84ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005E211FDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005E3947DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EE006DwordImmSetter@@QAEXXZ:PROC

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
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x1B594, element size 20, count 56 and destructor pointer 0x00931FCF.
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
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x1B594, element size 20, count 56 and destructor pointer 0x00931FCF.
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

; Unwind@00b97832 at RVA 0x00797832; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 48 as ECX and tail-jumps to matched Rva0057A243DwordImmSetter::apply at 0x0057A243.
PUBLIC ?rva00797832@@YAXXZ
?rva00797832@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00797832
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 48
    jmp ?apply@Rva0057A243DwordImmSetter@@QAEXXZ
cleanup_done_00797832:
    ret
?rva00797832@@YAXXZ ENDP

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

; Unwind@00b97d79 at RVA 0x00797D79; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva0053FCB3::rva0053FCB3 at 0x0053FCB3.
PUBLIC ?rva00797D79@@YAXXZ
?rva00797D79@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00797D79
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?rva0053FCB3@Rva0053FCB3@@QAEXXZ
cleanup_done_00797D79:
    ret
?rva00797D79@@YAXXZ ENDP

; Unwind@00b97e1e at RVA 0x00797E1E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva0053FCB3::rva0053FCB3 at 0x0053FCB3.
PUBLIC ?rva00797E1E@@YAXXZ
?rva00797E1E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00797E1E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?rva0053FCB3@Rva0053FCB3@@QAEXXZ
cleanup_done_00797E1E:
    ret
?rva00797E1E@@YAXXZ ENDP

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

; Unwind@00b98c97 at RVA 0x00798C97; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x94, element size 12, count 6 and destructor pointer 0x0078356C.
PUBLIC ?rva00798C97@@YAXXZ
?rva00798C97@@YAXXZ PROC
    push 0078356Ch
    push 6
    push 12
    mov eax, DWORD PTR [ebp-16]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00798C97@@YAXXZ ENDP

; Unwind@00b98e91 at RVA 0x00798E91; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva003844D7 destructor at 0x003844D7.
PUBLIC ?rva00798E91@@YAXXZ
?rva00798E91@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00798E91
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva003844D7@@QAE@XZ
cleanup_done_00798E91:
    ret
?rva00798E91@@YAXXZ ENDP

; Unwind@00b98ec7 at RVA 0x00798EC7; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva0038454E destructor at 0x0038454E.
PUBLIC ?rva00798EC7@@YAXXZ
?rva00798EC7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00798EC7
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva0038454E@@QAE@XZ
cleanup_done_00798EC7:
    ret
?rva00798EC7@@YAXXZ ENDP

; Unwind@00b9902c at RVA 0x0079902C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Gen_uw_00385371 composite destructor at 0x00385371.
PUBLIC ?rva0079902C@@YAXXZ
?rva0079902C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079902C
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_00385371@@QAE@XZ
cleanup_done_0079902C:
    ret
?rva0079902C@@YAXXZ ENDP

; Unwind@00b99062 at RVA 0x00799062; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva00385333 destructor at 0x00385333.
PUBLIC ?rva00799062@@YAXXZ
?rva00799062@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00799062
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00385333@@QAE@XZ
cleanup_done_00799062:
    ret
?rva00799062@@YAXXZ ENDP

; Unwind@00b99194 at RVA 0x00799194; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Gen_uw_00385371 composite destructor at 0x00385371.
PUBLIC ?rva00799194@@YAXXZ
?rva00799194@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00799194
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Gen_uw_00385371@@QAE@XZ
cleanup_done_00799194:
    ret
?rva00799194@@YAXXZ ENDP

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

; Unwind@00b9a0b9 at RVA 0x0079A0B9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079A0B9@@YAXXZ
?rva0079A0B9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A0B9
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079A0B9:
    ret
?rva0079A0B9@@YAXXZ ENDP

; Unwind@00b9a179 at RVA 0x0079A179; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva002E3A80Holder::call at 0x002E3A80.
PUBLIC ?rva0079A179@@YAXXZ
?rva0079A179@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A179
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_0079A179:
    ret
?rva0079A179@@YAXXZ ENDP

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

; Unwind@00b9a59c at RVA 0x0079A59C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079A59C@@YAXXZ
?rva0079A59C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A59C
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079A59C:
    ret
?rva0079A59C@@YAXXZ ENDP

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

; Unwind@00b9a637 at RVA 0x0079A637; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079A637@@YAXXZ
?rva0079A637@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0079A637
    and DWORD PTR [ebp-16], -5
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079A637:
    ret
?rva0079A637@@YAXXZ ENDP

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

; Unwind@00b9afb2 at RVA 0x0079AFB2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079AFB2@@YAXXZ
?rva0079AFB2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079AFB2
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079AFB2:
    ret
?rva0079AFB2@@YAXXZ ENDP

; Unwind@00b9b018 at RVA 0x0079B018; 20-byte funclet adds 10h to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00574293.
PUBLIC ?rva0079B018@@YAXXZ
?rva0079B018@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 10h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00574293DwordImmSetter@@QAEXXZ
?rva0079B018@@YAXXZ ENDP

; Unwind@00b9b03e at RVA 0x0079B03E; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x0057428C.
PUBLIC ?rva0079B03E@@YAXXZ
?rva0079B03E@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0057428CDwordImmSetter@@QAEXXZ
?rva0079B03E@@YAXXZ ENDP

; Unwind@00b9b052 at RVA 0x0079B052; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E186A.
PUBLIC ?rva0079B052@@YAXXZ
?rva0079B052@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0005E186ADwordImmSetter@@QAEXXZ
?rva0079B052@@YAXXZ ENDP

; Unwind@00b9b066 at RVA 0x0079B066; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E186A.
PUBLIC ?rva0079B066@@YAXXZ
?rva0079B066@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0005E186ADwordImmSetter@@QAEXXZ
?rva0079B066@@YAXXZ ENDP

; Unwind@00b9b07a at RVA 0x0079B07A; 20-byte funclet adds 10h to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00574265.
PUBLIC ?rva0079B07A@@YAXXZ
?rva0079B07A@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 10h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva000574265DwordImmSetter@@QAEXXZ
?rva0079B07A@@YAXXZ ENDP

; Unwind@00b9b22a at RVA 0x0079B22A; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva0079B22A@@YAXXZ
?rva0079B22A@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva0079B22A@@YAXXZ ENDP

; Unwind@00b9b250 at RVA 0x0079B250; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva0079B250@@YAXXZ
?rva0079B250@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva0079B250@@YAXXZ ENDP

; Unwind@00b9b276 at RVA 0x0079B276; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva0079B276@@YAXXZ
?rva0079B276@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva0079B276@@YAXXZ ENDP

; Unwind@00b9b29c at RVA 0x0079B29C; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x0057A243.
PUBLIC ?rva0079B29C@@YAXXZ
?rva0079B29C@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0057A243DwordImmSetter@@QAEXXZ
?rva0079B29C@@YAXXZ ENDP

; Unwind@00b9b2b0 at RVA 0x0079B2B0; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005D23FE.
PUBLIC ?rva0079B2B0@@YAXXZ
?rva0079B2B0@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0005D23FEDwordImmSetter@@QAEXXZ
?rva0079B2B0@@YAXXZ ENDP

; Unwind@00b9b2c4 at RVA 0x0079B2C4; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005CD1A9.
PUBLIC ?rva0079B2C4@@YAXXZ
?rva0079B2C4@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005CD1A9@@UAE@XZ
?rva0079B2C4@@YAXXZ ENDP

; Unwind@00b9b2d8 at RVA 0x0079B2D8; 20-byte funclet adds 14h to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005753E2.
PUBLIC ?rva0079B2D8@@YAXXZ
?rva0079B2D8@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva005753E2DwordImmSetter@@QAEXXZ
?rva0079B2D8@@YAXXZ ENDP

; Unwind@00b9b51b at RVA 0x0079B51B; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005CD1A9.
PUBLIC ?rva0079B51B@@YAXXZ
?rva0079B51B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005CD1A9@@UAE@XZ
?rva0079B51B@@YAXXZ ENDP

; Unwind@00b9b52f at RVA 0x0079B52F; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00576456.
PUBLIC ?rva0079B52F@@YAXXZ
?rva0079B52F@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00576456DwordImmSetter@@QAEXXZ
?rva0079B52F@@YAXXZ ENDP

; Unwind@00b9b603 at RVA 0x0079B603; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005CD1A9.
PUBLIC ?rva0079B603@@YAXXZ
?rva0079B603@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005CD1A9@@UAE@XZ
?rva0079B603@@YAXXZ ENDP

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

; Unwind@00b9b8cb at RVA 0x0079B8CB; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x00578C23.
PUBLIC ?rva0079B8CB@@YAXXZ
?rva0079B8CB@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva00578C23@@UAE@XZ
?rva0079B8CB@@YAXXZ ENDP

; Unwind@00b9b8df at RVA 0x0079B8DF; 20-byte funclet adds 18h to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x00578C23.
PUBLIC ?rva0079B8DF@@YAXXZ
?rva0079B8DF@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 18h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva00578C23@@UAE@XZ
?rva0079B8DF@@YAXXZ ENDP

; Unwind@00b9baec at RVA 0x0079BAEC; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079BAEC@@YAXXZ
?rva0079BAEC@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BAEC
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079BAEC:
    ret
?rva0079BAEC@@YAXXZ ENDP

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

; Unwind@00b9bcb9 at RVA 0x0079BCB9; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005D40A6.
PUBLIC ?rva0079BCB9@@YAXXZ
?rva0079BCB9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005D40A6@@UAE@XZ
?rva0079BCB9@@YAXXZ ENDP

; Unwind@00b9bda3 at RVA 0x0079BDA3; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x0057A243.
PUBLIC ?rva0079BDA3@@YAXXZ
?rva0079BDA3@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0057A243DwordImmSetter@@QAEXXZ
?rva0079BDA3@@YAXXZ ENDP

; Unwind@00b9bdb7 at RVA 0x0079BDB7; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x0057A235.
PUBLIC ?rva0079BDB7@@YAXXZ
?rva0079BDB7@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0057A235DwordImmSetter@@QAEXXZ
?rva0079BDB7@@YAXXZ ENDP

; Unwind@00b9be3b at RVA 0x0079BE3B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched RefHolder@Rva005CCC07 destructor at 0x0057A40C.
PUBLIC ?rva0079BE3B@@YAXXZ
?rva0079BE3B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BE3B
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1RefHolder@Rva005CCC07@@QAE@XZ
cleanup_done_0079BE3B:
    ret
?rva0079BE3B@@YAXXZ ENDP

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

; Unwind@00b9d5dd at RVA 0x0079D5DD; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00506B28.
PUBLIC ?rva0079D5DD@@YAXXZ
?rva0079D5DD@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00506B28DwordImmSetter@@QAEXXZ
?rva0079D5DD@@YAXXZ ENDP

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

; Unwind@00b9dc5b at RVA 0x0079DC5B; 20-byte funclet adds 60h to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x004444D2.
PUBLIC ?rva0079DC5B@@YAXXZ
?rva0079DC5B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 60h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva0079DC5B@@YAXXZ ENDP

; Unwind@00b9dc6f at RVA 0x0079DC6F; 20-byte funclet adds 6Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x0059EB3A.
PUBLIC ?rva0079DC6F@@YAXXZ
?rva0079DC6F@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 6Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0059EB3ADwordImmSetter@@QAEXXZ
?rva0079DC6F@@YAXXZ ENDP

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

; Unwind@00b9ee86 at RVA 0x0079EE86; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-28] + 0x174, element size 12, count 2 and destructor pointer 0x0047FAB3.
PUBLIC ?rva0079EE86@@YAXXZ
?rva0079EE86@@YAXXZ PROC
    push 0047FAB3h
    push 2
    push 12
    mov eax, DWORD PTR [ebp-28]
    add eax, 174h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0079EE86@@YAXXZ ENDP

; Unwind@00b9ef60 at RVA 0x0079EF60; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-20] + 0x174, element size 12, count 2 and destructor pointer 0x0047FAB3.
PUBLIC ?rva0079EF60@@YAXXZ
?rva0079EF60@@YAXXZ PROC
    push 0047FAB3h
    push 2
    push 12
    mov eax, DWORD PTR [ebp-20]
    add eax, 174h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0079EF60@@YAXXZ ENDP

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

; Unwind@00ba0540 at RVA 0x007A0540; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A0540@@YAXXZ
?rva007A0540@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0540
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A0540:
    ret
?rva007A0540@@YAXXZ ENDP

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

; Unwind@00ba0dcf at RVA 0x007A0DCF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmePoolRef10 destructor alias at 0x000519AB.
PUBLIC ?rva007A0DCF@@YAXXZ
?rva007A0DCF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0DCF
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmePoolRef10@@QAE@XZ
cleanup_done_007A0DCF:
    ret
?rva007A0DCF@@YAXXZ ENDP

; Unwind@00ba0e56 at RVA 0x007A0E56; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp-24] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007A0E56@@YAXXZ
?rva007A0E56@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0E56
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-24]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007A0E56:
    ret
?rva007A0E56@@YAXXZ ENDP

; Unwind@00ba0eae at RVA 0x007A0EAE; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A0EAE@@YAXXZ
?rva007A0EAE@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0EAE
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A0EAE:
    ret
?rva007A0EAE@@YAXXZ ENDP

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

; Unwind@00ba12e1 at RVA 0x007A12E1; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-32] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A12E1@@YAXXZ
?rva007A12E1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A12E1
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A12E1:
    ret
?rva007A12E1@@YAXXZ ENDP

; Unwind@00ba12fa at RVA 0x007A12FA; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A12FA@@YAXXZ
?rva007A12FA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007A12FA
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A12FA:
    ret
?rva007A12FA@@YAXXZ ENDP

; Unwind@00ba131d at RVA 0x007A131D; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A131D@@YAXXZ
?rva007A131D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_007A131D
    and DWORD PTR [ebp-16], -5
    lea ecx, [ebp-20]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A131D:
    ret
?rva007A131D@@YAXXZ ENDP

; Unwind@00ba1336 at RVA 0x007A1336; 25-byte interval ends at RET.
; Retail tests and clears bit 3 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1336@@YAXXZ
?rva007A1336@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 8
    jz NEAR PTR cleanup_done_007A1336
    and DWORD PTR [ebp-16], -9
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1336:
    ret
?rva007A1336@@YAXXZ ENDP

; Unwind@00ba1359 at RVA 0x007A1359; 25-byte interval ends at RET.
; Retail tests and clears bit 4 at [ebp-16], then takes the cleanup object address at [ebp-40] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1359@@YAXXZ
?rva007A1359@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 16
    jz NEAR PTR cleanup_done_007A1359
    and DWORD PTR [ebp-16], -17
    lea ecx, [ebp-40]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1359:
    ret
?rva007A1359@@YAXXZ ENDP

; Unwind@00ba1372 at RVA 0x007A1372; 25-byte interval ends at RET.
; Retail tests and clears bit 5 at [ebp-16], then takes the cleanup object address at [ebp-36] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1372@@YAXXZ
?rva007A1372@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 32
    jz NEAR PTR cleanup_done_007A1372
    and DWORD PTR [ebp-16], -33
    lea ecx, [ebp-36]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1372:
    ret
?rva007A1372@@YAXXZ ENDP

; Unwind@00ba1414 at RVA 0x007A1414; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 12 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1414@@YAXXZ
?rva007A1414@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1414
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 12
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1414:
    ret
?rva007A1414@@YAXXZ ENDP

; Unwind@00ba15ab at RVA 0x007A15AB; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 32 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A15AB@@YAXXZ
?rva007A15AB@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A15AB
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 32
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A15AB:
    ret
?rva007A15AB@@YAXXZ ENDP

; Unwind@00ba15ff at RVA 0x007A15FF; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 40 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A15FF@@YAXXZ
?rva007A15FF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A15FF
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 40
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A15FF:
    ret
?rva007A15FF@@YAXXZ ENDP

; Unwind@00ba1641 at RVA 0x007A1641; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 16 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1641@@YAXXZ
?rva007A1641@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1641
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 16
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1641:
    ret
?rva007A1641@@YAXXZ ENDP

; Unwind@00ba1683 at RVA 0x007A1683; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva007A1683@@YAXXZ
?rva007A1683@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva007A1683@@YAXXZ ENDP

; Unwind@00ba1726 at RVA 0x007A1726; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva007A1726@@YAXXZ
?rva007A1726@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva007A1726@@YAXXZ ENDP

; Unwind@00ba1744 at RVA 0x007A1744; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 16 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1744@@YAXXZ
?rva007A1744@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1744
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 16
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1744:
    ret
?rva007A1744@@YAXXZ ENDP

; Unwind@00ba1786 at RVA 0x007A1786; 20-byte funclet adds 8 to [ebp-14h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva007A1786@@YAXXZ
?rva007A1786@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-14h]
    mov eax, DWORD PTR [ebp-14h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007A1786@@YAXXZ ENDP

; Unwind@00ba17ac at RVA 0x007A17AC; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva007A17AC@@YAXXZ
?rva007A17AC@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva007A17AC@@YAXXZ ENDP

; Unwind@00ba17dd at RVA 0x007A17DD; 20-byte funclet adds 8 to [ebp-14h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva007A17DD@@YAXXZ
?rva007A17DD@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-14h]
    mov eax, DWORD PTR [ebp-14h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva007A17DD@@YAXXZ ENDP

; Unwind@00ba1a16 at RVA 0x007A1A16; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1A16@@YAXXZ
?rva007A1A16@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1A16
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1A16:
    ret
?rva007A1A16@@YAXXZ ENDP

; Unwind@00ba1aa7 at RVA 0x007A1AA7; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EDFF8.
PUBLIC ?rva007A1AA7@@YAXXZ
?rva007A1AA7@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ
?rva007A1AA7@@YAXXZ ENDP

; Unwind@00ba1abb at RVA 0x007A1ABB; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EDFFF.
PUBLIC ?rva007A1ABB@@YAXXZ
?rva007A1ABB@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ
?rva007A1ABB@@YAXXZ ENDP

; Unwind@00ba1ae1 at RVA 0x007A1AE1; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EDFF8.
PUBLIC ?rva007A1AE1@@YAXXZ
?rva007A1AE1@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ
?rva007A1AE1@@YAXXZ ENDP

; Unwind@00ba1af5 at RVA 0x007A1AF5; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005EB753.
PUBLIC ?rva007A1AF5@@YAXXZ
?rva007A1AF5@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005EB753@@UAE@XZ
?rva007A1AF5@@YAXXZ ENDP

; Unwind@00ba1b1b at RVA 0x007A1B1B; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EDFF8.
PUBLIC ?rva007A1B1B@@YAXXZ
?rva007A1B1B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ
?rva007A1B1B@@YAXXZ ENDP

; Unwind@00ba1b41 at RVA 0x007A1B41; 20-byte funclet adds 10h to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005CF84A.
PUBLIC ?rva007A1B41@@YAXXZ
?rva007A1B41@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 10h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva005CF84ADwordImmSetter@@QAEXXZ
?rva007A1B41@@YAXXZ ENDP

; Unwind@00ba1b67 at RVA 0x007A1B67; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EDFF8.
PUBLIC ?rva007A1B67@@YAXXZ
?rva007A1B67@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ
?rva007A1B67@@YAXXZ ENDP

; Unwind@00ba1b98 at RVA 0x007A1B98; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1B98@@YAXXZ
?rva007A1B98@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1B98
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1B98:
    ret
?rva007A1B98@@YAXXZ ENDP

; Unwind@00ba1e30 at RVA 0x007A1E30; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched RefHolder@Rva005CCC07 destructor at 0x0057A40C.
PUBLIC ?rva007A1E30@@YAXXZ
?rva007A1E30@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1E30
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1RefHolder@Rva005CCC07@@QAE@XZ
cleanup_done_007A1E30:
    ret
?rva007A1E30@@YAXXZ ENDP

; Unwind@00ba1e85 at RVA 0x007A1E85; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005CF843.
PUBLIC ?rva007A1E85@@YAXXZ
?rva007A1E85@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva005CF843DwordImmSetter@@QAEXXZ
?rva007A1E85@@YAXXZ ENDP

; Unwind@00ba1ef2 at RVA 0x007A1EF2; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva007A1EF2@@YAXXZ
?rva007A1EF2@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007A1EF2@@YAXXZ ENDP

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

; Unwind@00ba20e3 at RVA 0x007A20E3; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A20E3@@YAXXZ
?rva007A20E3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A20E3
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A20E3:
    ret
?rva007A20E3@@YAXXZ ENDP

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

; Unwind@00ba2284 at RVA 0x007A2284; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A2284@@YAXXZ
?rva007A2284@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A2284
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A2284:
    ret
?rva007A2284@@YAXXZ ENDP

; Unwind@00ba260b at RVA 0x007A260B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A260B@@YAXXZ
?rva007A260B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A260B
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A260B:
    ret
?rva007A260B@@YAXXZ ENDP

; Unwind@00ba2cf8 at RVA 0x007A2CF8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A2CF8@@YAXXZ
?rva007A2CF8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A2CF8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A2CF8:
    ret
?rva007A2CF8@@YAXXZ ENDP

; Unwind@00ba3300 at RVA 0x007A3300; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A3300@@YAXXZ
?rva007A3300@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3300
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A3300:
    ret
?rva007A3300@@YAXXZ ENDP

; Unwind@00ba334f at RVA 0x007A334F; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva007A334F@@YAXXZ
?rva007A334F@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007A334F@@YAXXZ ENDP

; Unwind@00ba3363 at RVA 0x007A3363; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E186A.
PUBLIC ?rva007A3363@@YAXXZ
?rva007A3363@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0005E186ADwordImmSetter@@QAEXXZ
?rva007A3363@@YAXXZ ENDP

; Unwind@00ba34ba at RVA 0x007A34BA; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-32] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A34BA@@YAXXZ
?rva007A34BA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A34BA
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A34BA:
    ret
?rva007A34BA@@YAXXZ ENDP

; Unwind@00ba34d3 at RVA 0x007A34D3; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A34D3@@YAXXZ
?rva007A34D3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007A34D3
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A34D3:
    ret
?rva007A34D3@@YAXXZ ENDP

; Unwind@00ba34fe at RVA 0x007A34FE; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E211F.
PUBLIC ?rva007A34FE@@YAXXZ
?rva007A34FE@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva005E211FDwordImmSetter@@QAEXXZ
?rva007A34FE@@YAXXZ ENDP

; Unwind@00ba3512 at RVA 0x007A3512; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva007A3512@@YAXXZ
?rva007A3512@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva007A3512@@YAXXZ ENDP

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

; Unwind@00ba377a at RVA 0x007A377A; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 20 as ECX and tail-jumps to matched Rva005F4179 virtual destructor at 0x005F4179.
PUBLIC ?rva007A377A@@YAXXZ
?rva007A377A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A377A
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 20
    jmp ??1Rva005F4179@@UAE@XZ
cleanup_done_007A377A:
    ret
?rva007A377A@@YAXXZ ENDP

; Unwind@00ba37a0 at RVA 0x007A37A0; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 36 as ECX and tail-jumps to matched Rva005F4179 virtual destructor at 0x005F4179.
PUBLIC ?rva007A37A0@@YAXXZ
?rva007A37A0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A37A0
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 36
    jmp ??1Rva005F4179@@UAE@XZ
cleanup_done_007A37A0:
    ret
?rva007A37A0@@YAXXZ ENDP

; Unwind@00ba37d1 at RVA 0x007A37D1; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 48 as ECX and tail-jumps to matched Rva005F4179 virtual destructor at 0x005F4179.
PUBLIC ?rva007A37D1@@YAXXZ
?rva007A37D1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A37D1
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 48
    jmp ??1Rva005F4179@@UAE@XZ
cleanup_done_007A37D1:
    ret
?rva007A37D1@@YAXXZ ENDP

; Unwind@00ba3872 at RVA 0x007A3872; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E3947.
PUBLIC ?rva007A3872@@YAXXZ
?rva007A3872@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva005E3947DwordImmSetter@@QAEXXZ
?rva007A3872@@YAXXZ ENDP

; Unwind@00ba38f9 at RVA 0x007A38F9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched SBServer destructor at 0x005E3B83.
PUBLIC ?rva007A38F9@@YAXXZ
?rva007A38F9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A38F9
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1SBServer@@QAE@XZ
cleanup_done_007A38F9:
    ret
?rva007A38F9@@YAXXZ ENDP

; Unwind@00ba393e at RVA 0x007A393E; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 20 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A393E@@YAXXZ
?rva007A393E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A393E
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 20
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A393E:
    ret
?rva007A393E@@YAXXZ ENDP

; Unwind@00ba39df at RVA 0x007A39DF; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 28 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A39DF@@YAXXZ
?rva007A39DF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A39DF
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 28
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A39DF:
    ret
?rva007A39DF@@YAXXZ ENDP

; Unwind@00ba3a31 at RVA 0x007A3A31; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A3A31@@YAXXZ
?rva007A3A31@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3A31
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A3A31:
    ret
?rva007A3A31@@YAXXZ ENDP

; Unwind@00ba3a70 at RVA 0x007A3A70; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva007A3A70@@YAXXZ
?rva007A3A70@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007A3A70@@YAXXZ ENDP

; Unwind@00ba3c1f at RVA 0x007A3C1F; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 36 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A3C1F@@YAXXZ
?rva007A3C1F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3C1F
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 36
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A3C1F:
    ret
?rva007A3C1F@@YAXXZ ENDP

; Unwind@00ba3ce6 at RVA 0x007A3CE6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A3CE6@@YAXXZ
?rva007A3CE6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3CE6
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A3CE6:
    ret
?rva007A3CE6@@YAXXZ ENDP

; Unwind@00ba3d13 at RVA 0x007A3D13; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-32] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A3D13@@YAXXZ
?rva007A3D13@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3D13
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A3D13:
    ret
?rva007A3D13@@YAXXZ ENDP

; Unwind@00ba3d2c at RVA 0x007A3D2C; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A3D2C@@YAXXZ
?rva007A3D2C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007A3D2C
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A3D2C:
    ret
?rva007A3D2C@@YAXXZ ENDP

; Unwind@00ba3ddc at RVA 0x007A3DDC; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva007A3DDC@@YAXXZ
?rva007A3DDC@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva007A3DDC@@YAXXZ ENDP

; Unwind@00ba3df0 at RVA 0x007A3DF0; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EE006.
PUBLIC ?rva007A3DF0@@YAXXZ
?rva007A3DF0@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EE006DwordImmSetter@@QAEXXZ
?rva007A3DF0@@YAXXZ ENDP

; Unwind@00ba3eda at RVA 0x007A3EDA; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 12 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A3EDA@@YAXXZ
?rva007A3EDA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3EDA
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 12
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A3EDA:
    ret
?rva007A3EDA@@YAXXZ ENDP

; Unwind@00ba4129 at RVA 0x007A4129; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A4129@@YAXXZ
?rva007A4129@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4129
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A4129:
    ret
?rva007A4129@@YAXXZ ENDP

; Unwind@00ba4197 at RVA 0x007A4197; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F918D destructor at 0x005F918D.
PUBLIC ?rva007A4197@@YAXXZ
?rva007A4197@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4197
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F918D@@QAE@XZ
cleanup_done_007A4197:
    ret
?rva007A4197@@YAXXZ ENDP

; Unwind@00ba4694 at RVA 0x007A4694; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A4694@@YAXXZ
?rva007A4694@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4694
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A4694:
    ret
?rva007A4694@@YAXXZ ENDP

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

; Unwind@00ba50a2 at RVA 0x007A50A2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-68], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva00087A93 destructor at 0x0007B724.
PUBLIC ?rva007A50A2@@YAXXZ
?rva007A50A2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-68]
    and eax, 1
    jz NEAR PTR cleanup_done_007A50A2
    and DWORD PTR [ebp-68], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva00087A93@@QAE@XZ
cleanup_done_007A50A2:
    ret
?rva007A50A2@@YAXXZ ENDP

; Unwind@00ba5241 at RVA 0x007A5241; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F4AD7 destructor at 0x005F4AD7.
PUBLIC ?rva007A5241@@YAXXZ
?rva007A5241@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5241
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F4AD7@@QAE@XZ
cleanup_done_007A5241:
    ret
?rva007A5241@@YAXXZ ENDP

; Unwind@00ba559a at RVA 0x007A559A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A559A@@YAXXZ
?rva007A559A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A559A
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A559A:
    ret
?rva007A559A@@YAXXZ ENDP

; Unwind@00ba569e at RVA 0x007A569E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A569E@@YAXXZ
?rva007A569E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A569E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A569E:
    ret
?rva007A569E@@YAXXZ ENDP

; Unwind@00ba56d9 at RVA 0x007A56D9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A56D9@@YAXXZ
?rva007A56D9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A56D9
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A56D9:
    ret
?rva007A56D9@@YAXXZ ENDP

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

; Unwind@00ba621f at RVA 0x007A621F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A621F@@YAXXZ
?rva007A621F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A621F
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A621F:
    ret
?rva007A621F@@YAXXZ ENDP

; Unwind@00ba6486 at RVA 0x007A6486; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A6486@@YAXXZ
?rva007A6486@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6486
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A6486:
    ret
?rva007A6486@@YAXXZ ENDP

; Unwind@00ba64a9 at RVA 0x007A64A9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A64A9@@YAXXZ
?rva007A64A9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A64A9
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A64A9:
    ret
?rva007A64A9@@YAXXZ ENDP

; Unwind@00ba65b4 at RVA 0x007A65B4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A65B4@@YAXXZ
?rva007A65B4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A65B4
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A65B4:
    ret
?rva007A65B4@@YAXXZ ENDP

; Unwind@00ba67ea at RVA 0x007A67EA; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A67EA@@YAXXZ
?rva007A67EA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A67EA
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A67EA:
    ret
?rva007A67EA@@YAXXZ ENDP

; Unwind@00ba680d at RVA 0x007A680D; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A680D@@YAXXZ
?rva007A680D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A680D
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A680D:
    ret
?rva007A680D@@YAXXZ ENDP

; Unwind@00ba6a40 at RVA 0x007A6A40; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 100 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6A40@@YAXXZ
?rva007A6A40@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6A40
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 100
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6A40:
    ret
?rva007A6A40@@YAXXZ ENDP

; Unwind@00ba6a80 at RVA 0x007A6A80; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 104 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6A80@@YAXXZ
?rva007A6A80@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6A80
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 104
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6A80:
    ret
?rva007A6A80@@YAXXZ ENDP

; Unwind@00ba6ac0 at RVA 0x007A6AC0; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 108 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6AC0@@YAXXZ
?rva007A6AC0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6AC0
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 108
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6AC0:
    ret
?rva007A6AC0@@YAXXZ ENDP

; Unwind@00ba6d3d at RVA 0x007A6D3D; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-32] and tail-jumps to matched folded destructor body at 0x0007FAB3.
PUBLIC ?rva007A6D3D@@YAXXZ
?rva007A6D3D@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6D3D
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-32]
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
cleanup_done_007A6D3D:
    ret
?rva007A6D3D@@YAXXZ ENDP

; Unwind@00ba75d0 at RVA 0x007A75D0; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-44], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched Q1ReceiverLocalSet destructor at 0x0006C94B.
PUBLIC ?rva007A75D0@@YAXXZ
?rva007A75D0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-44]
    and eax, 1
    jz NEAR PTR cleanup_done_007A75D0
    and DWORD PTR [ebp-44], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Q1ReceiverLocalSet@@QAE@XZ
cleanup_done_007A75D0:
    ret
?rva007A75D0@@YAXXZ ENDP

; Unwind@00ba770c at RVA 0x007A770C; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-24] + 0x80, element size 40, count 7 and destructor pointer 0x00B3C8C0.
PUBLIC ?rva007A770C@@YAXXZ
?rva007A770C@@YAXXZ PROC
    push 00B3C8C0h
    push 7
    push 40
    mov eax, DWORD PTR [ebp-24]
    add eax, 80h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A770C@@YAXXZ ENDP

; Unwind@00ba7786 at RVA 0x007A7786; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-40] + 0x80, element size 40, count 7 and destructor pointer 0x00B3C8C0.
PUBLIC ?rva007A7786@@YAXXZ
?rva007A7786@@YAXXZ PROC
    push 00B3C8C0h
    push 7
    push 40
    mov eax, DWORD PTR [ebp-40]
    add eax, 80h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A7786@@YAXXZ ENDP

; Unwind@00ba78f8 at RVA 0x007A78F8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched BfmeWideResult destructor at 0x0004AA28.
PUBLIC ?rva007A78F8@@YAXXZ
?rva007A78F8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A78F8
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1BfmeWideResult@@QAE@XZ
cleanup_done_007A78F8:
    ret
?rva007A78F8@@YAXXZ ENDP

; Unwind@00ba7c38 at RVA 0x007A7C38; 39-byte interval ends at tail-jump.
; Retail selects null or [ebp-16] + 12 into [ebp-20], then tail-jumps to matched folded FXParticleSystem destructor at 0x0049B47C.
PUBLIC ?rva007A7C38@@YAXXZ
?rva007A7C38@@YAXXZ PROC
    cmp DWORD PTR [ebp-16], 0
    jz NEAR PTR cleanup_null_007A7C38
    mov eax, DWORD PTR [ebp-16]
    add eax, 12
    mov DWORD PTR [ebp-20], eax
    jmp NEAR PTR cleanup_ready_007A7C38
cleanup_null_007A7C38:
    mov DWORD PTR [ebp-20], 0
cleanup_ready_007A7C38:
    mov ecx, DWORD PTR [ebp-20]
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva007A7C38@@YAXXZ ENDP

; Unwind@00ba80a8 at RVA 0x007A80A8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp-16] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A80A8@@YAXXZ
?rva007A80A8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A80A8
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-16]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A80A8:
    ret
?rva007A80A8@@YAXXZ ENDP

; Unwind@00ba81b8 at RVA 0x007A81B8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched address-derived BfmeRefVGO handle destructor thunk at 0x000A9DF3.
PUBLIC ?rva007A81B8@@YAXXZ
?rva007A81B8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A81B8
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Rva004A9DF3Element@@QAE@XZ
cleanup_done_007A81B8:
    ret
?rva007A81B8@@YAXXZ ENDP

; Unwind@00ba8458 at RVA 0x007A8458; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched address-derived BfmeRefVGO handle destructor thunk at 0x000A9DF3.
PUBLIC ?rva007A8458@@YAXXZ
?rva007A8458@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8458
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Rva004A9DF3Element@@QAE@XZ
cleanup_done_007A8458:
    ret
?rva007A8458@@YAXXZ ENDP

; Unwind@00ba8488 at RVA 0x007A8488; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched address-derived BfmeRefVGO handle destructor thunk at 0x000A9DF3.
PUBLIC ?rva007A8488@@YAXXZ
?rva007A8488@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8488
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1Rva004A9DF3Element@@QAE@XZ
cleanup_done_007A8488:
    ret
?rva007A8488@@YAXXZ ENDP

; Unwind@00ba8720 at RVA 0x007A8720; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A8720@@YAXXZ
?rva007A8720@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8720
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A8720:
    ret
?rva007A8720@@YAXXZ ENDP

; Unwind@00ba8790 at RVA 0x007A8790; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A8790@@YAXXZ
?rva007A8790@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8790
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A8790:
    ret
?rva007A8790@@YAXXZ ENDP

; Unwind@00ba8d28 at RVA 0x007A8D28; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A8D28@@YAXXZ
?rva007A8D28@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8D28
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A8D28:
    ret
?rva007A8D28@@YAXXZ ENDP

; Unwind@00ba8d68 at RVA 0x007A8D68; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A8D68@@YAXXZ
?rva007A8D68@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8D68
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A8D68:
    ret
?rva007A8D68@@YAXXZ ENDP

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

; Unwind@00bab2df at RVA 0x007AB2DF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB2DF@@YAXXZ
?rva007AB2DF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB2DF
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB2DF:
    ret
?rva007AB2DF@@YAXXZ ENDP

; Unwind@00bab31a at RVA 0x007AB31A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB31A@@YAXXZ
?rva007AB31A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB31A
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB31A:
    ret
?rva007AB31A@@YAXXZ ENDP

; Unwind@00bab345 at RVA 0x007AB345; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB345@@YAXXZ
?rva007AB345@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB345
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB345:
    ret
?rva007AB345@@YAXXZ ENDP

_TEXT ENDS
END
