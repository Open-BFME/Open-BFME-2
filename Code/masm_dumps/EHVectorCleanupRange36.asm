.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH vector cleanups from dump range 36. The retail
; helper call, array extent, member offset, and frame base are read directly
; from each body. Parent class and member layout remain unknown. This is the
; compiler-generated EH vector cleanup shape covered by the range-39 MASM path.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC

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

_TEXT ENDS
END
