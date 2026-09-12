.386
.model flat

; __ftol2 -- retail 0x00629228, 117 bytes.
;
; MSVC 7.1's /QIfist-free float/double-to-__int64 truncation helper: every
; C++ (double)->(int) conversion in this build calls it instead of a plain
; FISTP, because the x87 control word defaults to round-to-nearest and C++
; truncates toward zero. It saves ST(0) twice (once rounded via FISTP, once
; raw via FST), compares the rounded __int64 against the raw double's high
; dword to see whether rounding and truncation actually differ, and only
; when they do subtracts the fractional remainder back off (branching on
; the sign of the raw value for which way to adjust) to fix the rounding
; up/down into truncation. This is compiler/runtime machinery -- no C++
; expression compiles down to this exact shape, only a bare call to it --
; so it stays MASM (see Code/masm_dumps/EH_prolog.asm precedent).
;
; Pinned already in reverse/symbols.csv ("__ftol2,0x00629228,MSVC
; float-to-int helper byte-identical to pinned BFME1 CRT body"); named by
; dozens of call sites across the tree, including
; Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp.

_TEXT SEGMENT
public __ftol2
__ftol2 PROC
    push ebp
    mov  ebp, esp
    sub  esp, 20h
    and  esp, 0FFFFFFF0h
    fld  st(0)
    fst  dword ptr [esp+18h]
    fistp qword ptr [esp+10h]
    fild qword ptr [esp+10h]
    mov  edx, dword ptr [esp+18h]
    mov  eax, dword ptr [esp+10h]
    test eax, eax
    je   integral
subtract:
    fsubp st(1), st
    test edx, edx
    jns  positive
    fstp dword ptr [esp]
    mov  ecx, dword ptr [esp]
    xor  ecx, 80000000h
    add  ecx, 7FFFFFFFh
    adc  eax, 0
    mov  edx, dword ptr [esp+14h]
    adc  edx, 0
    jmp  done
positive:
    fstp dword ptr [esp]
    mov  ecx, dword ptr [esp]
    add  ecx, 7FFFFFFFh
    sbb  eax, 0
    mov  edx, dword ptr [esp+14h]
    sbb  edx, 0
    jmp  done
integral:
    mov  edx, dword ptr [esp+14h]
    test edx, 7FFFFFFFh
    jne  subtract
    fstp dword ptr [esp+18h]
    fstp dword ptr [esp+18h]
done:
    leave
    ret
__ftol2 ENDP
_TEXT ENDS
END
