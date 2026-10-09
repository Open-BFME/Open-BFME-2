.386
.model flat

; ?rva006C3180@GeneralAllocatorDebug@@QAEXPAUGeneralAllocatorDebugBlock@@@Z
;   -- retail 0x006C3180, 150 bytes.
;
; GeneralAllocatorDebug::VerifyGuardFill. Identity is proven from target
; bytes, not inferred: the failure string this body pushes at 0x006C31E6 is
; VA 0x00CE7C0C (RVA 0x008E7C0C), "GeneralAllocatorDebug::VerifyGuardFill
; failure.", which names both the class and the method directly.
;
; Why MASM, and not clean C++ (a proven codegen blocker, see
; Code/masm_dumps/EH_prolog.asm and ftol2.asm for the precedent):
;
;   Retail opens "push ebp ; mov ebp,[esp+8]" -- EBP is an ordinary callee-save
;   holding the block descriptor, and there is NO frame setup anywhere: the
;   tail is "pop esi ; pop ebp ; ret 4", and nothing ever writes ESP into EBP.
;   Across the ledger's matched C++ bodies no MSVC 7.1 body allocates EBP for an
;   incoming argument: the register ladder puts EBX first (118 single-push
;   prologues start "push ebx" versus 55 starting "push esi"), and EBX is only
;   displaced downward once three or more values are simultaneously live, at
;   which point the compiler starts pushing ECX as well and addresses the
;   argument as [esp+0x10] rather than [esp+8].
;
;   Measured over an isolated scratch translation unit (build/probe_6c3180.cpp)
;   carrying every shape worth trying, all under the project's own compiler
;   environment:
;
;     2 live values (argument, this)        push esi / mov esi,[esp+8]
;     3 live values (arg, payload, this)    push ebx / mov ebx,[esp+8]
;                                           then push ebp, push esi
;     4+ live values                        push ecx, push ebx, push ebp
;                                           and [esp+0x10] for the argument
;
;   so the reachable neighbours are either EBX or an extra ECX push, never the
;   observed "push ebp" + "[esp+8]". Every flag that does produce a leading
;   "push ebp" (/O1, /O2 -Oy-, /O2 -Os-) pairs it with "mov ebp,esp", i.e. it
;   is a real frame pointer, and retail has none. Flags swept: /O1, /O2, /Ob1,
;   /Ob2, /Oi, /Oi-, /Ot, /Ot-, /Os, /Os-, /Oy, /Oy-, /Op, /G5, /G7, both as
;   replacements and paired with /O2. The banked C++ body (152B vs 150B) already
;   matches the control flow, all five call sites, the out-parameter slot and
;   the fill arithmetic; only this register frame differs.
;
; Semantics transcribed from retail:
;   +0x4E4 lock    -- 0x006C25F0 and 0x006C26F0 AddRef/Release it
;   +0x50B fill    -- one-byte value handed to the CRT fill at 0x00030E20
;   +0x514 flags   -- bit 0x800 tested here with "test ah,8" (a 16-bit read)
;   +0x004         -- on the block, bit 2 gates the whole check
;   +0x008         -- on the block, the guard run's origin
;   The out-length from the builder lands on this frame's dead incoming
;   argument slot at [esp+0x10], is clamped to 0x40, and is read back after the
;   six pushed arguments are still live. ret 4 proves the one stack argument.
;
; Every callee below is pinned in reverse/symbols.csv; these names are address-
; derived candidates, not proven identities.
;
; The EXTRN declarations carry an explicit :NEAR type on purpose. Without it
; ml.exe 7.10 rejects a decorated name that contains "@@" with A2008 "syntax
; error : in directive" -- it reads "@@" at directive position as the macro
; repetition operator. Quoting, backtick-escaping, /Zm and OPTION NOKSYMBOL all
; fail the same way; the explicit type is what parses. EXTERN's own body is
; otherwise unaffected.

EXTRN ?rva006C25F0Run6@GeneralAllocatorDebug@@QAEPAXPAXHHHPAIH@Z:NEAR
EXTRN ?rva00030E20Fill@@YAEPAXIE@Z:NEAR
EXTRN ?rva006C2FB0Report@GeneralAllocatorDebug@@QAEXPBDPAX@Z:NEAR
EXTRN ?rva006C30C0@GeneralAllocatorDebug@@QAEXPAX@Z:NEAR
EXTRN ?rva006C26F0@GeneralAllocatorDebug@@QAEXP0PAX@Z:NEAR
EXTRN ?freeBlock@Rva00033E90@@QAEXPAX@Z:NEAR

_TEXT SEGMENT
public ?rva006C3180@GeneralAllocatorDebug@@QAEXPAUGeneralAllocatorDebugBlock@@@Z
?rva006C3180@GeneralAllocatorDebug@@QAEXPAUGeneralAllocatorDebugBlock@@@Z PROC

    push    ebp
    mov     ebp, dword ptr [esp + 8]       ; block descriptor
    test    byte ptr [ebp + 4], 4           ; gate: [block + 4] & 4
    push    esi
    mov     esi, ecx                        ; the allocator object
    jne     short L_cleanup
    mov     eax, dword ptr [esi + 514h]
    test    ah, 8                           ; (flags & 0x800) != 0
    je      L_cleanup

    push    edi
    push    0                                ; sixth stack arg (mode)
    lea     eax, [esp + 14h]                ; &outLen: this frame's dead
    push    eax                             ;   incoming-argument slot, fifth arg
    push    0                                ; fourth stack arg
    push    0                                ; third stack arg
    push    0Bh                              ; kind
    lea     edi, [ebp + 8]                  ; block + 8, the guard run origin
    push    edi
    call    ?rva006C25F0Run6@GeneralAllocatorDebug@@QAEPAXPAXHHHPAIH@Z
    test    eax, eax
    je      L_pop_edi

    mov     ecx, dword ptr [esp + 10h]      ; out-length
    cmp     ecx, 40h
    jb      short L_len_ok
    mov     ecx, 40h
L_len_ok:
    lea     edx, [edi + 8]
    add     ecx, eax                        ; clamp(ecx) + run
    cmp     eax, edx                        ; run < payload + 8 ?
    jae     short L_have_dst
    mov     eax, edx                        ; else dst = payload + 8
L_have_dst:
    xor     edx, edx
    mov     dl, byte ptr [esi + 50Bh]       ; fill byte, narrow load
    sub     ecx, eax                        ; count = end - dst
    push    edx
    push    ecx
    push    eax
    call    ?rva00030E20Fill@@YAEPAXIE@Z
    add     esp, 0Ch
    test    al, al
    jne     L_pop_edi
    push    0CE7C0Ch                        ; "…VerifyGuardFill failure."
    push    ebp
    mov     ecx, esi
    call    ?rva006C2FB0Report@GeneralAllocatorDebug@@QAEXPBDPAX@Z

L_pop_edi:
    pop     edi

L_cleanup:
    push    ebp
    mov     ecx, esi
    call    ?rva006C30C0@GeneralAllocatorDebug@@QAEXPAX@Z
    push    0
    push    ebp
    mov     ecx, esi
    call    ?rva006C26F0@GeneralAllocatorDebug@@QAEXP0PAX@Z
    add     ebp, 8
    push    ebp
    mov     ecx, esi
    call    ?freeBlock@Rva00033E90@@QAEXPAX@Z        ; free: the block payload
    pop     esi
    pop     ebp
    ret     4

?rva006C3180@GeneralAllocatorDebug@@QAEXPAUGeneralAllocatorDebugBlock@@@Z ENDP
_TEXT ENDS
END