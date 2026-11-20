# Bridged table 0x008ED808 (`??_7Rva006FB9B0@@6B@` / `??_7Rva006FB960@@6B@`), 2026-11-14

Base `3e6d5a5449`. Read-only analysis; no source, ledger or queue change.

## Target facts

- One retail table, two tree names: `Rva006FB960` (constructor 0x006FB960 in Rva006FB960Cluster.cpp, AptValue type 4,
  int at +8) and `Rva006FB9B0` (destructor 0x006FB9B0 in Rva006DE350Derived.cpp, deleting destructor 0x006FB980 in
  Rva006FB9B0DeletingDtor.cpp; 12 bytes, freed through the pool at 0x00E176E8).
- Slots 0..14 (the queue's `retail_target_rva` values are decimal): 006DCAC0, 006DCB20, 006CBCD0, 0065CE90, 0073B660,
  0065CE90, 00180FD0, 0003FD80, 006C8770, 006CBCF0, 0069E440, 006CBD00, 0073B660, 0069E440, 006FB980.
- Against AptValue's table 0x00CEAED0 (Apt/AptValue.h) only slots 12, 13 and 14 differ: 12 is the byte-false body
  0x0073B660, 13 the one-byte return 0x0069E440, 14 the deleting destructor. Slots 2 and 9 are AptValue's own
  (unlike AptBoolean, which overrides both).
- `??1AptValue@@MAE@XZ` is rowed at 0x006DE350, the address the 11-byte destructor jumps to.

## What the source needs

One class in one shared header, derived from `AptValue`, declaring `IsGarbageCollected() const`,
`RegisterReferences() const` and the destructor, used by all three units in place of the two opaque views and the
`Rva006DE350` base view. Sibling table 0x008ED844 (`Rva006FB9C0` / `Rva006FBA10`, type 8) has the same split.

## Why this stopped

- The two overrides need bodies in the tree. Retail folded them into 0x0073B660 and 0x0069E440, so they can only be
  rowed as ICF twins with `fold-proof=`. This seat is instructed not to add a second body at an address that has one.
- tu_map.csv gives 0x006FB960, 0x006FB980 and 0x006FB9B0 no approved unit, so the three views cannot be merged; a
  shared header is the only route and both names must be reconciled first (class identity unproven: type 4, int payload).
- halilkkaya-au holds live header_adopt_lane claims on Apt units (Rva006DBB40/Rva006DBB60 members of AptValue).

Not measured: whether the 11-byte destructor and the 35-byte deleting destructor still match when the class derives
from `AptValue` instead of `Rva006DE350`.

---

## 2026-11-20: the destructor side is done; the re-base is safe

The one thing this file left unmeasured -- "whether the 11-byte destructor and
the 35-byte deleting destructor still match when the class derives from
`AptValue` instead of `Rva006DE350`" -- is now measured. **Both still match.**

`Rva006FB9B0` now derives from `AptValue` (`Code/Libraries/Source/Apt/AptValue.h`,
self-contained, forward declarations only) in both destructor units, and each
unit emits a real 15-slot `??_7Rva006FB9B0@@6B@` of 60 bytes instead of the old
one-slot stub.

### Every slot now reaches retail's address

| slot | binds | retail | how |
| ---: | --- | --- | --- |
| 0..11 | `AptValue`'s own twelve | 006DCAC0 006DCB20 006CBCD0 0065CE90 0073B660 0065CE90 00180FD0 0003FD80 006C8770 006CBCF0 0069E440 006CBD00 | already rowed; nothing to add |
| 12 | `?IsGarbageCollected@Rva006FB9B0@@UBE_NXZ` | 0x0073B660 | **new row**, ICF twin of `?Rva0073B660False@@YA_NPAXH@Z` |
| 13 | `?RegisterReferences@Rva006FB9B0@@UBEXXZ` | 0x0069E440 | **new row**, ICF twin of the shared one-byte RET |
| 14 | `??_ERva006FB9B0@@UAEPAXI@Z` | 0x006FB980 | WEAK_EXTERNAL alias of the already-rowed `??_G`; **no row, and a row here would be wrong** |

Slots 0..11 cost nothing because `AptValue`'s own defaults are all defined now.
When this file was written they were not: slots 3, 4, 5, 6, 9 and 10 had no
definition anywhere, which is why re-basing would then have traded one bridged
table for six undefined names. Those landed as
`aptvalue-hierarchy-undefined-vtable-defaults-20261116.md` (bf21b75b0b5,
0534e78db38), so the route this file proposed only became viable afterwards.

### Corrections to the entry above

- "This seat is instructed not to add a second body at an address that has
  one" was a seat instruction, not a project rule. AGENTS.md sanctions an ICF
  fold with `fold-proof=`, and `add_match.py --icf-owner` is its path; both new
  rows verified through it.
- The 11-byte destructor's tail-jump now binds `??1AptValue@@MAE@XZ`, a rowed
  definition in AptValue.cpp at 0x006DE350, rather than the `Rva006DE350` view
  spelling that resolved only because AptValue.cpp happens to define that name
  too. The bytes are unchanged: `c7 01 <table>` then `e9 <rel32>`.
- The two units' COMDAT copies are identical, not divergent: `??_G` digests
  `ac56fe454628` in both, `??_7` digests `c3631289d013` in both.
- `AptValue`'s protected base constructor takes `AptVirtualFunctionTable_Indices`,
  which the tree defines per TU (`AptScriptFunction.h` precedent). The deleting
  dtor unit defines it locally with retail's type 4.
- Layout is preserved by construction: the `Rva006DE350` view is 4 bytes and
  canonical `AptValue` is 8, so the padding went from `char m_pad[8]` to
  `char m_pad[4]` and `sizeof` stays 0xC for the sized delete.

### What is left: the constructor side only

`Rva006FB960Cluster.cpp` still carries the other tree name for this one retail
table, and it cannot take the same treatment as written:

- It declares its **own** local `class AptValue` with three virtuals (AddRef,
  Release, ForceDelete) and derives `BfmeAptValue006DCD20` from it. Including
  the canonical header there is a C2011 `AptValue` redefinition -- the same wall
  the AptFactoryConstructors seat hit.
- Two rowed constructors depend on that view: `??0Rva006FB960@@QAE@H@Z` (29B,
  0x006FB960) and `Rva006FB9C0`'s. Layout would survive -- the local chain puts
  `m_value` at +8 and canonical `AptValue` is 8 bytes, so the offset is the same
  -- but the base-constructor call would rebind from
  `BfmeAptValue006DCD20::BfmeAptValue006DCD20(int)` to
  `AptValue::AptValue(AptVirtualFunctionTable_Indices)`. Those are the same
  retail body under two spellings (AptValue.h's target facts put the root
  constructor at 0x006DCCC0), so this is a rename to reconcile, not a layout
  change.
- The sibling table 0x008ED844 (`Rva006FB9C0` / `Rva006FBA10`, type 8) has the
  identical split, so whatever reconciles these two names should do both.

So the remaining work is naming-lane: unify `Rva006FB960` and `Rva006FB9B0`
under one name through `rename.py`, then re-base the cluster unit. `tu_map.csv`
still gives 0x006FB960, 0x006FB980 and 0x006FB9B0 no approved unit, so the
three views still cannot be merged; the shared-header route remains the one
open to them.

Not measured: this item's pass test needs a published real link, which this
seat cannot run, so whether the queue still lists the table is unverified here.

### The sibling table 0x008ED844 took the identical repair

`tools/vftable_map.py --va 0x00CED844` against `--va 0x00CED808` shows the two
retail tables are the **same addresses in slots 0..13** and differ only at slot
14, each class's own deleting destructor (0x006FB980 vs 0x006FB9E0). So
`Rva006FBA10` (destructor in the same `Rva006DE350Derived.cpp`, deleting
destructor in `Rva006FBA10DeletingDtor.cpp`) took the same re-base and the same
two override rows, with type 8 in the local enum where the first used 4.

Both tables now bind **15/15 slots to retail's address**, and each table's two
COMDAT copies are identical across its two units (`??_G` ec0926376eab, `??_7`
389d616d7d8d for this one). The constructor-side names `Rva006FB960` and
`Rva006FB9C0` are untouched and remain the naming lane's to reconcile.
