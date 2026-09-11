.386
.model flat

; __EH_prolog -- retail 0x00629188, 31 bytes.
;
; MSVC 7.1's fixed frame-setup helper for /EHsc functions with unwindable
; locals: every such function opens with "call __EH_prolog" instead of
; inlining this sequence itself. It links a new SEH exception registration
; record onto the fs:[0] chain (pushing the caller's per-function unwind
; table address, already sitting in EAX, and the previous fs:[0] head),
; then folds the caller's [esp+0Ch] return-address slot into EBP so the
; caller's prologue can address its frame normally afterward. This is
; compiler/runtime machinery, not something any C++ source compiles down
; to -- callers just "call __EH_prolog" -- so it stays MASM (see
; Code/masm_dumps/*.asm precedent in reference/open-bfme-1).
;
; Named by reverse/symbols.csv (already pinned) and by its 115 call sites,
; e.g. Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp.
assume fs:nothing

_TEXT SEGMENT
public __EH_prolog
__EH_prolog PROC
    push -1
    push eax
    mov  eax, fs:[0]
    push eax
    mov  eax, [esp+0Ch]
    mov  fs:[0], esp
    mov  [esp+0Ch], ebp
    lea  ebp, [esp+0Ch]
    push eax
    ret
__EH_prolog ENDP
_TEXT ENDS
END
