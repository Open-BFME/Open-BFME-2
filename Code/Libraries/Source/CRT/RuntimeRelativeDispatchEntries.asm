; Register-saving entries for the return-address-relative dispatch cores.
; There is no normal RET here: the core consumes this CALL's return address
; and jumps onward. The destination sees saved EAX, saved ECX, caller return.
; All flags and the other general-purpose registers are preserved.
; These are machine-entry contracts, not fabricated C++ prototypes; source
; provenance is retail disassembly plus independent register/stack tests.
; Evidence: reverse/attempt_support/runtime-dispatch-20261023/readme.md
.386
.model flat
EXTERN _RuntimeDispatchCore_00007AF3:PROC
EXTERN _RuntimeDispatchCore_00007C63:PROC
_TEXT SEGMENT
; The saved EAX/ECX words remain on the destination's incoming stack.
; (Written out per entry: a source may not use MASM macros, tools/cl_flags.py asm_directives.)
PUBLIC _RuntimeDispatchEntry_00007ED9
_RuntimeDispatchEntry_00007ED9 PROC
    push ecx
    push eax
    call _RuntimeDispatchCore_00007AF3
_RuntimeDispatchEntry_00007ED9 ENDP
PUBLIC _RuntimeDispatchEntry_00008449
_RuntimeDispatchEntry_00008449 PROC
    push ecx
    push eax
    call _RuntimeDispatchCore_00007C63
_RuntimeDispatchEntry_00008449 ENDP
_TEXT ENDS
END
