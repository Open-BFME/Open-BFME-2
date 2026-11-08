; Return-address-relative runtime dispatch cores (retail evidence only).
; Entry sites save ECX/EAX and CALL these routines. POP consumes that CALL's
; return PC, LEA locates a mutable 32-bit cell without changing flags, and
; JMP transfers with the two saved register words still on the stack.
; This register/stack ABI cannot be declared as an ordinary C++ call.
; The runtime writer, eventual provider and original symbol names remain
; unknown. Preserve the observed mechanism without inventing an import.
; Native layout relationships: 0x7EE0-3509=0x712B, 0x8450-4341=0x735B.
; The same RVA differences must hold after final placement; no arbitrary
; code/data layout or complete linked runtime is claimed by this source.
; Evidence: reverse/attempt_support/runtime-dispatch-20261023/readme.md
.386
.model flat
_TEXT SEGMENT
; Each entry consumes the synthetic CALL return, preserves EFLAGS, and
; jumps through a PC-relative mutable cell. It is not a C/C++ call ABI.
; (Written out per entry: a source may not use MASM macros, tools/cl_flags.py asm_directives.)
PUBLIC _RuntimeDispatchCore_00007AF3
_RuntimeDispatchCore_00007AF3 PROC
    mov eax, -3509
    pop ecx
    lea eax, [ecx+eax]
    mov eax, DWORD PTR [eax]
    jmp eax
_RuntimeDispatchCore_00007AF3 ENDP
PUBLIC _RuntimeDispatchCore_00007C63
_RuntimeDispatchCore_00007C63 PROC
    mov eax, -4341
    pop ecx
    lea eax, [ecx+eax]
    mov eax, DWORD PTR [eax]
    jmp eax
_RuntimeDispatchCore_00007C63 ENDP
_TEXT ENDS
END
