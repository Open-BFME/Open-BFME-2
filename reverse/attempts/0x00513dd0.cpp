// ??0?$vector@FV?$allocator@F@_STL@@@_STL@@QAE@IABFABV?$allocator@F@1@@Z
// partial score=0.55 date=2026-09-26
// ??0?$vector@FV?$allocator@F@_STL@@@_STL@@QAE@IABFABV?$allocator@F@1@@Z
// partial score=0.55 date=2026-09-26
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// vector<short>::vector(size_type n, const short& val, const allocator<short>& a)
// Comes free from the explicit instantiation already in
// Code/Libraries/Source/WWVegas/WWLib/stlport_vector_s_o1.cpp
// (`template class _STL::vector<short, _STL::allocator<short> >;`) -- there
// is no separate hand-written body to place; the whole file IS the source.
//
// Sibling _Vector_base<short>::_Vector_base(uint, const allocator<short>&)
// at 0x00513D55 (58B) landed clean (byte-exact) after pinning the folded
// AllocProxyIntCtor_dupA call at 0x00007410 in reverse/symbols.csv. This
// ctor calls that now-matched _Vector_base ctor AND the same fill helper at
// 0x0000AD8C9 that retail calls -- both callees are already correct and
// identical on both sides, so this is a pure shape mismatch, not a missing
// pin.
//
// target (51B, RVA 0x00513DD0):
//   push ebp
//   mov  ebp, esp
//   push ecx                 ; reserves a local slot, unused as an arg
//   push esi
//   lea  eax, [ebp+0xb]      ; &(byte inside the 'n' argument slot) -- scratch
//   push eax
//   push [ebp+8]             ; n
//   mov  esi, ecx            ; esi = this
//   call 0x00513D55          ; _Vector_base(n, a)          -- MATCHES
//   mov  eax, [esi]          ; eax = this->_M_start
//   and  dword ptr [ebp-4], 0 ; construction/unwind-state local := 0
//   lea  ecx, [ebp-4]
//   push ecx
//   push [ebp+8]             ; n
//   push eax                 ; _M_start
//   call 0x0000AD8C9         ; fill-construct helper       -- MATCHES
//   mov  [esi+4], eax        ; this->_M_finish = eax
//   add  esp, 0xc
//   mov  eax, esi
//   pop  esi
//   leave
//   ret  4
//
// Our /O1 /EHsc compile of the header instead drops the ebp frame (FPO) and
// never allocates the "and dword ptr [ebp-4], 0" unwind-state local, so it
// passes _M_start twice into the fill call instead of &local_flag. Net: 44B
// vs 51B, diff starts right after the shared prologue.
//
// Tried: adding /Oy- to the file's `// cl:` line restores the ebp frame
// (push ebp/mov ebp,esp/leave) and moves the first diff from +0x0 to +0x3,
// but the "push ecx" local-slot reservation and the later
// "and dword ptr [ebp-4], 0" / "lea ecx, [ebp-4]" unwind-guard idiom still
// do not appear -- MSVC 7.1 is eliding what looks like an EH cleanup marker
// for the fill-construct call, presumably because it can prove `short`'s
// copy is non-throwing and /O1 removes the now-dead guard. Retail keeps it,
// which either means retail's TU used a slightly different EH/codegen
// setting for this one TU, or the guard is not actually dead in whatever
// compiler pass retail went through. Two flag attempts (baseline, /Oy-)
// without closing the gap; per docs/structural.md "shape diffs are the hard
// class", stopping here rather than guessing further flags blindly.
//
// Next step for whoever draws this: try /Ob0 (no inlining at all, matches
// the voidptr_alloc.cpp sibling's /Od /Ob1 style) or an explicit /EHs vs
// /EHsc split, and diff the *_Vector_base* sibling's own object code shape
// under each variant before touching this ctor again -- the shared '_M_fill'
// wrapper is probably instantiated identically for other T and might already
// have a matched sibling elsewhere in the STLport vector family showing which
// flag keeps the unwind-state local.
//
// t=25min model=sonnet
