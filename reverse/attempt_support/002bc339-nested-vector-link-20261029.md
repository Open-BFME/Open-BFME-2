# 0x002BC339 nested vector ctor: link attempt handoff (2026-10-29, seat yasinschroeder-claudeb2)

Target: `Code/GameEngine/Source/Common/Rva0019D850NestedVectorRelease_Rva002bc339.cpp`
(rows 0x002BC339 vector(n) 100 B, 0x002BBC5F uninitialized_fill_n 27 B,
0x0077686B ehhandler 10 B). Approved TU for all three (and 0x2BB785, 0x2BB6BE,
0x2BBB57, funclets 0x77685B/0x776863): `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp`.
link_check: C=2, S=2 (comdat loser / wrong selected).

## Target facts (retail bytes)

- 0x2BC339 calls 0x5C8C37 (count `_Vector_base` ctor, 60 B, ICF fold),
  0x211E58 (29 B `_Vector_base(const alloc&)` fold), 0x2BBC5F and, in its
  unwind, 0x2BBB57 (out-of-line `~vector<Rva002BB6BE20Rec>`).
- 0x5C8C37 calls `_STLP_alloc_proxy` ctor 0x14F3C4 and allocate 0x395928 out of
  line with a pushed zero hint (bfmealloc shape) and scales with
  `imul edi,edi,0xc; add edi,eax`.

## Structural inference

The element is not the POD placeholder `Rva002BC339Value {int[3]}`: the unwind
destroys a 20-byte record with a non-trivial dtor, the same type the
`stlport_destroy_member20_2bb6be.cpp` rows spell `Rva002BB6BE20Rec`
(`{int; int; vector<unsigned>; ~Rec();}`).

## Scratch results (build/s339/, not committed)

```cpp
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva002BB6BE20Rec { int m_00; int m_04; _STL::vector<unsigned int> m_08; ~Rva002BB6BE20Rec(); };
typedef _STL::vector<Rva002BB6BE20Rec> RecVector;
namespace _STL {
template <>
__declspec(noinline) inline RecVector *uninitialized_fill_n<RecVector *, unsigned int, RecVector>(RecVector *__first, unsigned int __n, const RecVector &__x)
{ return __uninitialized_fill_n(__first, __n, __x, __false_type()); }
}
template _STL::vector<RecVector>::vector(unsigned int);
```

- `vector<vector<Rec>>::vector(unsigned)` matches 0x2BC339 exactly up to REL32s
  (also with `// stlport46` and `/O1 /DNDEBUG /MD /EHs /arch:SSE /D_STLP_NO_EXCEPTIONS`).
- Without /O1 (with or without /EHs) the ctor is 126 B, 86 bytes differ.
- The emitted count `_Vector_base<vector<Rec>>` is 61 B vs retail 60 B
  (register choice ebx/edi swapped, `lea` scaling instead of `imul`); retail's
  0x5C8C37 is a fold of a copy compiled elsewhere (non-/O1 shape, cf.
  `stlport_vector_prerequnitrec_allocate_copy.cpp`).
- A decl-only `_Vector_base` specialization in the real file moves the
  allocator temp to a new frame slot (`sub esp,0x14`, `[ebp-0xd]`); build fails.

## Remaining prerequisites

1. A provider for the Rec-spelled count `_Vector_base` ctor at 0x5C8C37 (or a
   fold-proof binding) so the TU's own /O1 copy loses COMDAT selection.
2. Inventory the extra COMDATs the Rec element drags in (Rec copy ctor,
   vector<Rec> copy ctor, `_Construct`, `__uninitialized_fill_n<vector<Rec>>`,
   vector<unsigned> helpers) against retail owners.
3. Rename the three rows from the Value to the Rec spelling (tombstones), and the
   stale Value-spelled pins (symbols.csv `_Construct<vector<Value>>` 0x2BAE2A,
   `_Vector_base<vector<Value>>(n,alloc)` 0x5C8C37, `~_Vector_base<Value>` 0x2BBB57).
4. Better: do it as part of the `tu_skeleton.py --merge` into LivingWorldLogic.cpp,
   which already carries a `vector<vector<Rva002BC339Value>>` specialization hack
   for `CheckHeadToHeadBattles` (0x2BCE24) that must go to the Rec spelling too.
