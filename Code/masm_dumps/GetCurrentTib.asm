.386
.model flat

; ?GetCurrentTib@@YAPAU_TIB@@XZ -- retail 0x0075A73D, 7 bytes.
;
; MSVC 7.1 CRT run-time-check support (error.obj file-unit): returns the
; current thread information block. Chained between IntToString at 0x0075A703
; and WinGetDebugContext at 0x0075A744 with exact section sizes; unique
; placement in .text; no Ghidra entry but boundaries proven by the chain.
;
; The fs: segment override is compiler machinery -- VS2003 C++ cannot express
; it (__readfsdword does not exist until VS2005, proven by probe) -- so it
; stays MASM (see Code/masm_dumps/EH_prolog.asm and ftol2.asm precedent).
assume fs:nothing

_TEXT SEGMENT
public ?GetCurrentTib@@YAPAU_TIB@@XZ
?GetCurrentTib@@YAPAU_TIB@@XZ PROC
    mov  eax, DWORD PTR fs:[18h]
    ret  0
?GetCurrentTib@@YAPAU_TIB@@XZ ENDP
_TEXT ENDS
END
