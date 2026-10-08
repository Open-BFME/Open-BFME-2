.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH vector cleanups from dump range 36. The retail
; helper call, array extent, member offset, and frame base are read directly
; from each body. Parent class and member layout remain unknown. This is the
; compiler-generated EH vector cleanup shape covered by the range-39 MASM path.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC

_TEXT SEGMENT
; Unwind@00b5d5f0: four 8-byte elements at [ebp-0x14] + 0x14e0.
PUBLIC ?rva0075D5F0@@YAXXZ
?rva0075D5F0@@YAXXZ PROC
    push 4B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-20]
    add eax, 14E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075D5F0@@YAXXZ ENDP

; Unwind@00b5d660: four 8-byte elements at [ebp-0x10] + 0x14e0.
PUBLIC ?rva0075D660@@YAXXZ
?rva0075D660@@YAXXZ PROC
    push 4B3FD0h
    push 4
    push 8
    mov eax, DWORD PTR [ebp-16]
    add eax, 14E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075D660@@YAXXZ ENDP

; Unwind@00b5dd8f: three 12-byte elements at [ebp-0x14] + 0xe0.
PUBLIC ?rva0075DD8F@@YAXXZ
?rva0075DD8F@@YAXXZ PROC
    push 456ACBh
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DD8F@@YAXXZ ENDP

; Unwind@00b5ddc3: three 0x1c4-byte elements at [ebp-0x14] + 0x12c.
PUBLIC ?rva0075DDC3@@YAXXZ
?rva0075DDC3@@YAXXZ PROC
    push 45925Eh
    push 3
    push 1C4h
    mov eax, DWORD PTR [ebp-20]
    add eax, 12Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DDC3@@YAXXZ ENDP

; Unwind@00b5ddde: 0x40 12-byte elements at [ebp-0x14] + 0x6cc.
PUBLIC ?rva0075DDDE@@YAXXZ
?rva0075DDDE@@YAXXZ PROC
    push 88BA39h
    push 40h
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 6CCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DDDE@@YAXXZ ENDP

; Unwind@00b5de2e: three 12-byte elements at [ebp-0x14] + 0xa14.
PUBLIC ?rva0075DE2E@@YAXXZ
?rva0075DE2E@@YAXXZ PROC
    push 459068h
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0A14h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DE2E@@YAXXZ ENDP

; Unwind@00b5de8c: six 40-byte elements at [ebp-0x14] + 0xa4c.
PUBLIC ?rva0075DE8C@@YAXXZ
?rva0075DE8C@@YAXXZ PROC
    push 4581F0h
    push 6
    push 28h
    mov eax, DWORD PTR [ebp-20]
    add eax, 0A4Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DE8C@@YAXXZ ENDP

; Unwind@00b5dea4: three 4-byte elements at [ebp-0x14] + 0xb48.
PUBLIC ?rva0075DEA4@@YAXXZ
?rva0075DEA4@@YAXXZ PROC
    push 50F149h
    push 3
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 0B48h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075DEA4@@YAXXZ ENDP

; Unwind@00b5e203: three 12-byte elements at [ebp-0x14] + 0xe0.
PUBLIC ?rva0075E203@@YAXXZ
?rva0075E203@@YAXXZ PROC
    push 456ACBh
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E203@@YAXXZ ENDP

; Unwind@00b5e237: three 0x1c4-byte elements at [ebp-0x14] + 0x12c.
PUBLIC ?rva0075E237@@YAXXZ
?rva0075E237@@YAXXZ PROC
    push 45925Eh
    push 3
    push 1C4h
    mov eax, DWORD PTR [ebp-20]
    add eax, 12Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E237@@YAXXZ ENDP

; Unwind@00b5e252: 0x40 12-byte elements at [ebp-0x14] + 0x6cc.
PUBLIC ?rva0075E252@@YAXXZ
?rva0075E252@@YAXXZ PROC
    push 88BA39h
    push 40h
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 6CCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E252@@YAXXZ ENDP

; Unwind@00b5e2a2: three 12-byte elements at [ebp-0x14] + 0xa14.
PUBLIC ?rva0075E2A2@@YAXXZ
?rva0075E2A2@@YAXXZ PROC
    push 459068h
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0A14h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E2A2@@YAXXZ ENDP

; Unwind@00b5e300: six 40-byte elements at [ebp-0x14] + 0xa4c.
PUBLIC ?rva0075E300@@YAXXZ
?rva0075E300@@YAXXZ PROC
    push 4581F0h
    push 6
    push 28h
    mov eax, DWORD PTR [ebp-20]
    add eax, 0A4Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E300@@YAXXZ ENDP

; Unwind@00b5e318: three 4-byte elements at [ebp-0x14] + 0xb48.
PUBLIC ?rva0075E318@@YAXXZ
?rva0075E318@@YAXXZ PROC
    push 50F149h
    push 3
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 0B48h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E318@@YAXXZ ENDP

; Unwind@00b5e81e: 500 28-byte elements at [ebp-0x14] + 0xe0.
PUBLIC ?rva0075E81E@@YAXXZ
?rva0075E81E@@YAXXZ PROC
    push 89B47Ch
    push 1F4h
    push 1Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E81E@@YAXXZ ENDP

; Unwind@00b5e987: 22-byte masked-add funclet with add 0C8h tail-jumps to EmissionVelocityInfo dtor.
PUBLIC ?rva0075E987@@YAXXZ
?rva0075E987@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-20]
    mov eax, DWORD PTR [ebp-20]
    add eax, 0C8h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva0075E987@@YAXXZ ENDP

; Unwind@00b5e9ab: 500 28-byte elements at [ebp-0x14] + 0xe0.
PUBLIC ?rva0075E9AB@@YAXXZ
?rva0075E9AB@@YAXXZ PROC
    push 89B47Ch
    push 1F4h
    push 1Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 0E0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075E9AB@@YAXXZ ENDP

; Unwind@00b5f6de: six 48-byte elements at [ebp-0x10] + 0x138.
PUBLIC ?rva0075F6DE@@YAXXZ
?rva0075F6DE@@YAXXZ PROC
    push 47E7E2h
    push 6
    push 30h
    mov eax, DWORD PTR [ebp-16]
    add eax, 138h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075F6DE@@YAXXZ ENDP

; Unwind@00b5fb4f: 255 20-byte elements at [ebp-0x10] + 0x2c.
PUBLIC ?rva0075FB4F@@YAXXZ
?rva0075FB4F@@YAXXZ PROC
    push 44F82Bh
    push 0FFh
    push 14h
    mov eax, DWORD PTR [ebp-16]
    add eax, 2Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0075FB4F@@YAXXZ ENDP

; Unwind@00b60489: 21 4-byte elements at [ebp-0x18] + 0x6028.
PUBLIC ?rva00760489@@YAXXZ
?rva00760489@@YAXXZ PROC
    push 576CB0h
    push 15h
    push 4
    mov eax, DWORD PTR [ebp-24]
    add eax, 6028h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00760489@@YAXXZ ENDP

; Unwind@00b6050d: 21 4-byte elements at [ebp-0x10] + 0x6028.
PUBLIC ?rva0076050D@@YAXXZ
?rva0076050D@@YAXXZ PROC
    push 576CB0h
    push 15h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 6028h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076050D@@YAXXZ ENDP

; Unwind@00b612b6: 512 40-byte elements at [ebp-0x14] + 0x80cc.
PUBLIC ?rva007612B6@@YAXXZ
?rva007612B6@@YAXXZ PROC
    push 8D9A3Ch
    push 200h
    push 28h
    mov eax, DWORD PTR [ebp-20]
    add eax, 80CCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007612B6@@YAXXZ ENDP

; Unwind@00b612d1: 512 40-byte elements at [ebp-0x14] + 0xd0d0.
PUBLIC ?rva007612D1@@YAXXZ
?rva007612D1@@YAXXZ PROC
    push 8D9A3Ch
    push 200h
    push 28h
    mov eax, DWORD PTR [ebp-20]
    add eax, 0D0D0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007612D1@@YAXXZ ENDP

; Unwind@00b612fa: two 4-byte elements at [ebp-0x14] + 0x120d8.
PUBLIC ?rva007612FA@@YAXXZ
?rva007612FA@@YAXXZ PROC
    push 57098Dh
    push 2
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 120D8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007612FA@@YAXXZ ENDP

; Unwind@00b613b4: 512 40-byte elements at [ebp-0x10] + 0x80cc.
PUBLIC ?rva007613B4@@YAXXZ
?rva007613B4@@YAXXZ PROC
    push 8D9A3Ch
    push 200h
    push 28h
    mov eax, DWORD PTR [ebp-16]
    add eax, 80CCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007613B4@@YAXXZ ENDP

; Unwind@00b613cf: 512 40-byte elements at [ebp-0x10] + 0xd0d0.
PUBLIC ?rva007613CF@@YAXXZ
?rva007613CF@@YAXXZ PROC
    push 8D9A3Ch
    push 200h
    push 28h
    mov eax, DWORD PTR [ebp-16]
    add eax, 0D0D0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007613CF@@YAXXZ ENDP

; Unwind@00b613f8: two 4-byte elements at [ebp-0x10] + 0x120d8.
PUBLIC ?rva007613F8@@YAXXZ
?rva007613F8@@YAXXZ PROC
    push 57098Dh
    push 2
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 120D8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007613F8@@YAXXZ ENDP

; Unwind@00b6199e: six 12-byte elements at [ebp-0x10] + 0xc8.
PUBLIC ?rva0076199E@@YAXXZ
?rva0076199E@@YAXXZ PROC
    push 47FAB3h
    push 6
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0C8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076199E@@YAXXZ ENDP

; Unwind@00b61a18: two 4-byte elements at [ebp-0x10] + 0x264.
PUBLIC ?rva00761A18@@YAXXZ
?rva00761A18@@YAXXZ PROC
    push 88BA39h
    push 2
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 264h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00761A18@@YAXXZ ENDP

; Unwind@00b61f8c: six 12-byte elements at [ebp-0x10] + 0xac.
PUBLIC ?rva00761F8C@@YAXXZ
?rva00761F8C@@YAXXZ PROC
    push 47FAB3h
    push 6
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0ACh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00761F8C@@YAXXZ ENDP

; Unwind@00b62229: two 20-byte elements at [ebp-0x14] + 0x160.
PUBLIC ?rva00762229@@YAXXZ
?rva00762229@@YAXXZ PROC
    push 46C94Bh
    push 2
    push 14h
    mov eax, DWORD PTR [ebp-20]
    add eax, 160h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00762229@@YAXXZ ENDP

; Unwind@00b62bf3: ten 12-byte elements at [ebp-0x14] + 0x94.
PUBLIC ?rva00762BF3@@YAXXZ
?rva00762BF3@@YAXXZ PROC
    push 4D3991h
    push 0Ah
    push 0Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00762BF3@@YAXXZ ENDP

; Unwind@00b62c2b: ten 12-byte elements at [ebp-0x10] + 0x94.
PUBLIC ?rva00762C2B@@YAXXZ
?rva00762C2B@@YAXXZ PROC
    push 4D3991h
    push 0Ah
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00762C2B@@YAXXZ ENDP

; Unwind@00b62e76: 200 0x114-byte elements at [ebp-0x10] + 0x10.
PUBLIC ?rva00762E76@@YAXXZ
?rva00762E76@@YAXXZ PROC
    push 4DDA6Eh
    push 0C8h
    push 114h
    mov eax, DWORD PTR [ebp-16]
    add eax, 10h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00762E76@@YAXXZ ENDP

; Unwind@00b636f8: 64 0x5c-byte elements at [ebp-0x10] + 0x4fb70.
PUBLIC ?rva007636F8@@YAXXZ
?rva007636F8@@YAXXZ PROC
    push 4E86B8h
    push 40h
    push 5Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 4FB70h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007636F8@@YAXXZ ENDP


; Unwind@00b63839: 1200 0xE8-byte elements at [EBP-0x14] + 0x5C0.
PUBLIC ?rva00763839@@YAXXZ
?rva00763839@@YAXXZ PROC
    push 4B3FD0h
    push 4B0h
    push 0E8h
    mov eax, DWORD PTR [ebp-20]
    add eax, 5C0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00763839@@YAXXZ ENDP

; Unwind@00b63865: 64 0x5C-byte elements at [EBP-0x14] + 0x44558.
PUBLIC ?rva00763865@@YAXXZ
?rva00763865@@YAXXZ PROC
    push 4EC6E1h
    push 40h
    push 5Ch
    mov eax, DWORD PTR [ebp-20]
    add eax, 44558h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00763865@@YAXXZ ENDP

; Unwind@00b638a1: 1200 0xE8-byte elements at [EBP-0x10] + 0x5C0.
PUBLIC ?rva007638A1@@YAXXZ
?rva007638A1@@YAXXZ PROC
    push 4B3FD0h
    push 4B0h
    push 0E8h
    mov eax, DWORD PTR [ebp-16]
    add eax, 5C0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007638A1@@YAXXZ ENDP

; Unwind@00b638cd: 64 0x5C-byte elements at [EBP-0x10] + 0x44558.
PUBLIC ?rva007638CD@@YAXXZ
?rva007638CD@@YAXXZ PROC
    push 4EC6E1h
    push 40h
    push 5Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 44558h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007638CD@@YAXXZ ENDP

; Unwind@00b6390c: 4000 0x30-byte elements at [EBP-0x10] + 4.
PUBLIC ?rva0076390C@@YAXXZ
?rva0076390C@@YAXXZ PROC
    push 4B3FD0h
    push 0FA0h
    push 30h
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076390C@@YAXXZ ENDP

; Unwind@00b63933: 96 0x18-byte elements at [EBP-0x10] + 0x2EE18.
PUBLIC ?rva00763933@@YAXXZ
?rva00763933@@YAXXZ PROC
    push 69D7C2h
    push 60h
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 2EE18h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00763933@@YAXXZ ENDP

; Unwind@00b6395d: 4000 0x30-byte elements at [EBP-0x10] + 4.
PUBLIC ?rva0076395D@@YAXXZ
?rva0076395D@@YAXXZ PROC
    push 4B3FD0h
    push 0FA0h
    push 30h
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076395D@@YAXXZ ENDP

; Unwind@00b63984: 96 0x18-byte elements at [EBP-0x10] + 0x2EE18.
PUBLIC ?rva00763984@@YAXXZ
?rva00763984@@YAXXZ PROC
    push 69D7C2h
    push 60h
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 2EE18h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00763984@@YAXXZ ENDP

; Unwind@00b6ab62: five 4-byte elements at [ebp-0x10] + 0xa8.
PUBLIC ?rva0076AB62@@YAXXZ
?rva0076AB62@@YAXXZ PROC
    push 50F149h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 0A8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0076AB62@@YAXXZ ENDP
_TEXT ENDS
END
