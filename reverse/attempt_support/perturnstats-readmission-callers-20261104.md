# PerTurnStats readmission: the callers block it (2026-11-04, halilkkaya-pt-o1)

Base `b675551755` (the commit that landed cx-o5's plan, LINK-182). No source,
ledger or pin changed. Every trial below ran against a scratch copy of the
ledger and was restored; the four consumers rebuilt 147/147 afterwards.

## Target facts

Retail E8 call sites to the family (scan of retail `.text` for E8/E9 rel32,
mapped to the ledger row that contains the site):

| Callee | Site | Caller row | Source today | Approved TU |
|---|---|---|---|---|
| 0x004EE1E2 | 0x004EE251 | `_M_allocate_and_copy` 0x004EE233 | `Thing/Rva004EE233AllocateCopy.cpp` | LivingWorldScoreKeeper.cpp |
| 0x004EE1E2 | 0x004EE711, 0x004EE75F | `Rva004EE6D0::rva004EE6D0` 0x004EE6D0 | `Common/Rva004EE6D0Insert.cpp` | LivingWorldScoreKeeper.cpp |
| 0x004EE1E2 | 0x0051ED3E | `Rva004EE501` copy ctor 0x0051ED0A | `GUICallbacks/Apt/AptTimeLine.cpp` | AptTimeLine.cpp |
| 0x004EE1E2 | 0x0051F862 | `vector<Rva0051F7ADRecord>::operator=` 0x0051F7AD | `WWLib/StlSweepR3Rva0051F7AD.cpp` | AptTimeLine.cpp |
| 0x004EE20B | 0x004EE741 | `Rva004EE6D0::rva004EE6D0` 0x004EE6D0 | `Common/Rva004EE6D0Insert.cpp` | LivingWorldScoreKeeper.cpp |
| 0x004EE233 | 0x004EE598 | `Rva004EE55EVector::reserve` 0x004EE55E | `WWLib/StlVectorReserveProviderRepairs.cpp` | LivingWorldScoreKeeper.cpp |
| 0x004EE233 | 0x0051F7EC | `vector<Rva0051F7ADRecord>::operator=` 0x0051F7AD | `WWLib/StlSweepR3Rva0051F7AD.cpp` | AptTimeLine.cpp |

0x004EE1D0 has no direct caller.

The element copy 0x004EE1A9 stores vftable 0x00C62A28. That table's slots
are 0x004A10FD, 0x000B3FD0, 0x004EE155 and 0x004EE15B; the last two are the
rowed `PerTurnStats::GetSnapshotName` and `PerTurnStats::xfer`.

## Structural inference

`Rva004EE501` is retail's `vector<LivingWorldScoreKeeper::PerTurnStats>`:
its copy ctor 0x0051ED0A copies through 0x004EE1E2, and the 12-byte stride,
the helpers and the vftable above all point to PerTurnStats. The rows
0x004EE501 (dtor), 0x0051F7AD (operator=), 0x004EE55E (reserve), 0x004EE6D0
(insert overflow), 0x004EE9B1 (push_back) and 0x004EE540 (clear) use the same
helpers. This rests on shared helpers, not on a name in the image.

## Trials

1. Simulated retraction, index only (`git update-index` with a ledger blob
   lacking the three PrereqUnitRec rows): `name_dependents.py --staged`
   reports 3 call targets lost, and 6 referencing units: ProductionPrerequisite.cpp,
   Rva004EE6D0Insert.cpp, ProductionPrerequisiteRecVectorInsertOverflow.cpp,
   AptTimeLine.cpp, StlSweepR3Rva0051F7AD.cpp, StlVectorReserveProviderRepairs.cpp.
   ThingFactory.cpp is not one of them.
2. The same ledger in the working tree, `./build.sh` per consumer:
   - Rva004EE6D0Insert.cpp: FAIL 1/2 (0x004EE6D0).
   - StlVectorReserveProviderRepairs.cpp: FAIL 1/9 (0x004EE55E), unresolved call
     to the PrereqUnitRec `_M_allocate_and_copy`.
   - StlSweepR3Rva0051F7AD.cpp: FAIL 1/1 (0x0051F7AD), same unresolved call.
   - AptTimeLine.cpp: FAIL 1/135 (0x0051ED0A).

   After the retraction, `__uninitialized_copy`/`__uninitialized_fill_n<PrereqUnitRec>`
   resolve only through their pins 0x004F5097/0x004F50BD (the real PrereqUnitRec
   helpers that overflow 0x004F5165 calls), and `_M_allocate_and_copy<PrereqUnitRec>`
   resolves through nothing. A retraction commit on its own is therefore refused.
   The readmission has to land in the same commit, with every caller respelled to
   PerTurnStats.
3. Respelling a caller that has no `LivingWorldScoreKeeper` body: adding
   `class LivingWorldScoreKeeper { public: class PerTurnStats; };` to
   StlSweepR3Rva0051F7AD.cpp fails `class_gate.py` ("declares its own
   `LivingWorldScoreKeeper`; include Code/GameEngine/Include/Common/LivingWorldScoreKeeper.h
   instead"). The edit was reverted.

## Why the callers cannot take the canonical header today

- StlSweepR3Rva0051F7AD.cpp and StlVectorReserveProviderRepairs.cpp declare their
  own `_STL::vector`/`_STL::allocator` templates. The header includes the real
  `<vector>` and `<map>`, which define those templates too.
- AptTimeLine.cpp and the header both define `Rva004EE501`, with different bases:
  `_Vector_base<PrereqUnitRec>` (a global placeholder) in AptTimeLine.cpp and
  `_Vector_base<int>` in the header. The copy ctor's count base call needs the
  12-byte one (0x005C8C37), so AptTimeLine.cpp cannot switch to the header's view.
- Rva004EE6D0Insert.cpp already has a private `LivingWorldScoreKeeper` stub, so
  it could be respelled.

## Link baseline (index 2026-11-04 13:15 at f6d845ecd4)

| Unit | Status | Bytes |
|---|---|---|
| LivingWorldScoreKeeper.cpp | LINKS | 3,347 |
| Rva004EE6D0Insert.cpp | LINKS | 241 |
| StlVectorReserveProviderRepairs.cpp | LINKS | 954 |
| StlSweepR3Rva0051F7AD.cpp | LINKS | 206 |
| AptTimeLine.cpp | LINKS | 9,826 |
| StlportConstructCopySiblings.cpp | LINKS | 162 |
| Thing/Rva004EE233AllocateCopy.cpp | LINKS | 45 |
| RTS/ProductionPrerequisite.cpp | does not link (0 of 429) | freeBytes, two `__imp_` `__new_alloc` |
| Thing/ThingFactory.cpp | does not link (0 of 118) | `??4?$vector<PrereqUnitRec>`, `??4AudioEventRTS`, two `__imp_` `__new_alloc` |

## Prerequisite

Reconcile `vector<LivingWorldScoreKeeper::PerTurnStats>` first:

- the canonical header gets a nested `PerTurnStats` and a `vector<PerTurnStats>` member at +0x28;
- the `Rva004EE501` views (header, AptTimeLine.cpp, RvaVectorDtorFamily.cpp) fold onto it, with their rows renamed;
- the callers can then name PerTurnStats.

After that, cx-o5's steps 1 and 2 land as one commit, together with the caller respellings, and step 3 follows.
