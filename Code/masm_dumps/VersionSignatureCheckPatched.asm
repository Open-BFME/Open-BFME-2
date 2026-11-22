.386
.model flat

; Patched-target signature check. Authorized assembly exception, 2026-10-23.
; C++ setup/call semantics and a near-exact mixed implementation are preserved
; in reverse/attempt_support/trust237-patched-target-20261023/.
; The current game.dat calls WinVerifyTrust but always returns success.
; The sixteen NOPs at +0xCD replace the signature-result checks.
; This assembly body receives no authored-C++ coverage credit.

EXTERN _memset:PROC
EXTERN _WinVerifyTrust@12:PROC
EXTERN __imp__GetCommandLineW@0:DWORD
EXTERN __imp__CommandLineToArgvW@8:DWORD
EXTERN __imp__LocalFree@4:DWORD

_TEXT SEGMENT
PUBLIC ?Rva00237D3DCheck@@YAHXZ
?Rva00237D3DCheck@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 050h
    push ebx
    push esi
    push 010h
    pop esi
    push esi
    xor ebx, ebx
    lea eax, [ebp - 024h]
    push ebx
    push eax
    call _memset
    add esp, 0ch
    lea eax, [ebp - 4]
    push eax
    mov dword ptr [ebp - 024h], esi
    mov dword ptr [ebp - 01ch], ebx
    mov dword ptr [ebp - 018h], ebx
    mov dword ptr [ebp - 4], ebx
    call DWORD PTR __imp__GetCommandLineW@0
    push eax
    call DWORD PTR __imp__CommandLineToArgvW@8
    mov esi, eax
    mov eax, dword ptr [esi]
    push 02ch
    mov dword ptr [ebp - 020h], eax
    lea eax, [ebp - 050h]
    push ebx
    push eax
    mov dword ptr [ebp - 014h], 0aac56bh
    mov word ptr [ebp - 010h], 0cd44h
    mov word ptr [ebp - 0eh], 011d0h
    mov byte ptr [ebp - 0ch], 08ch
    mov byte ptr [ebp - 0bh], 0c2h
    mov byte ptr [ebp - 0ah], bl
    mov byte ptr [ebp - 9], 0c0h
    mov byte ptr [ebp - 8], 04fh
    mov byte ptr [ebp - 7], 0c2h
    mov byte ptr [ebp - 6], 095h
    mov byte ptr [ebp - 5], 0eeh
    call _memset
    lea eax, [ebp - 024h]
    add esp, 0ch
    mov dword ptr [ebp - 038h], eax
    lea eax, [ebp - 050h]
    push eax
    lea eax, [ebp - 014h]
    push eax
    push ebx
    mov dword ptr [ebp - 050h], 02ch
    mov dword ptr [ebp - 04ch], ebx
    mov dword ptr [ebp - 048h], ebx
    mov dword ptr [ebp - 044h], 2
    mov dword ptr [ebp - 040h], ebx
    mov dword ptr [ebp - 03ch], 1
    mov dword ptr [ebp - 034h], ebx
    mov dword ptr [ebp - 030h], ebx
    mov dword ptr [ebp - 02ch], ebx
    mov dword ptr [ebp - 028h], 0210h
    call _WinVerifyTrust@12
    ; Release argv, retain the patched-out test's dead status save.
    push esi
    mov ebx, eax
    call DWORD PTR __imp__LocalFree@4
    xor eax, eax
    ; Explicit sixteen-byte post-link patch in the chosen target.
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    nop 
    inc eax
    pop esi
    pop ebx
    leave 
    ret 
?Rva00237D3DCheck@@YAHXZ ENDP
_TEXT ENDS
END
