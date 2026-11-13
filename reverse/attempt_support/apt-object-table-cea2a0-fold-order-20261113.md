# Bridged table 0x00CEA2A0 (`??_7Rva006D6500@@6B@`): why one fold is not enough (2026-11-13)

Served as vtable-bridge in Code/Libraries/Source/Apt/Rva006D6360Ctor.cpp. Nothing landed.

## Target facts (game.dat words; names from functions.csv)

Four 15-slot tables form one chain. Slots 0..2 are `AptValue::AddRef` 0x006DCAC0, `Release`
0x006DCB20, `ForceDelete` 0x006CBCD0 in all four; slot 8 is 0x006C8770 (`AptValue::objectMemberSet`),
slot 9 0x006CBCF0 (`?rva006CBCF0@Rva006CBCF0@@QAEXXZ`), slot 10 0x0069E440 (shared 1-byte `ret`).

| Slot | 0x00CEAED0 root | 0x00CEA228 with-hash | 0x00CEA264 object | 0x00CEA2A0 served |
|---|---|---|---|---|
| 3 | 0x0065CE90 | 0x006CBFD0 | 0x006CBFD0 | 0x006CBFD0 |
| 4 | 0x0073B660 | 0x001826C0 | 0x001826C0 | 0x001826C0 |
| 5 | 0x0065CE90 | 0x0065CE90 | 0x006D6460 `getBit8@Rva008993E0Owner` | same |
| 6 | 0x00180FD0 | 0x00180FD0 | 0x006D6440 `setBit8@Rva008993E0Owner` | same |
| 7 | 0x0003FD80 | 0x0003FD80 | 0x0070DFB0 `objectMemberLookup@AptObject` | same |
| 11 | 0x006CBD00 | 0x006DE150 `DestroyGCPointers@AptValueWithHash` | 0x0070DFE0 `...@AptObject` | same |
| 12 | `__purecall` | 0x001826C0 | 0x001826C0 | 0x001826C0 |
| 13 | `__purecall` | 0x006DCC00 `RegisterReferences@AptValueWithHash` | 0x0070DFD0 `...@AptObject` | same |
| 14 | 0x006DE820 `??_GRva006DE350` | 0x006D71E0 `??_GRva006D71E0` | 0x006D64D0 `??_GRva006D6470Owner` | 0x006D6570 `??_GRva006D65A0` |

Installers (`tools/vftable_map.py --va`): 0x00CEA2A0 by ctor 0x006D6500 (`??0Rva006D6500`) and
dtor 0x006D65A0 (`??1Rva006D65A0`); 0x00CEA264 by ctor 0x006D6410 and dtor 0x006D6470
(`Rva006D6470Owner`); 0x00CEA228 by ctor 0x006D6360 (`??0Rva006D6360`).

## What the tree compiles today

Rva006D6360Ctor.cpp declares a two-slot `AptValue` (AddRef, Release), so its `??_7Rva006D6500`
has three slots. Rva006D6470Derived.cpp declares a one-slot `Rva006D6470Owner` (destructor only),
so its `??_7Rva006D65A0` has one. Retail's table has fifteen.

## Tried and reverted

`rename.py class --fold Rva006D6500 --into Rva006D65A0`: plan accepted, 12 sources rewritten,
305/305 matched. `tools/link_check.py` over those 12 units plus Rva006D6470Derived.cpp then went
from 13 of 13 to 11 of 13:

- duplicate `??1Rva006D65A0@@UAE@XZ`: the ctor unit's view defined the destructor inline. Declaring
  it out of line with the pooled `operator delete` cleared this (3/3 matched, 12 of 13).
- `comdat ??_7Rva006D65A0@@6B@ differs from the first copy`: the two units' tables (three slots
  and one) now share a name. This stays until both views have one shape.

Reverted before any commit; the tree is at 13 of 13, LINKED 35,345 -> 35,345, 318/318 matched.

## Order the fold needs

1. One shape for the chain in every unit that emits one of these tables. Blockers by class:
   - Root: two registered headers describe table 0x00CEAED0, AptValue.h (41/84 units) and
     BfmeAptValue006DCD20.h (83/123), and the rows are split between them
     (`??0BfmeAptValue006DCD20`, `??1AptValue` as gen-alias, `??1Rva006DE350`). Slots 9 and 10 have
     no row under either name.
   - 0x00CEA228: `class --fold Rva006D6360 --into AptValueWithHash` refuses, "also named for
     Rva006D6360Base, Rva006FC130Base". Those two are views with no special-member row
     (Rva006FB960Cluster.cpp, BfmeAccessorMacros.h), so they cannot be folded; their units have to
     stop emitting those `??_7` names.
   - 0x00CEA264: `class --fold Rva006D6470Owner --into AptObject` refuses, "also named for
     Rva006DE6C0", and `--fold Rva006DE6C0 --into AptObject` refuses for `Rva006D6470Owner`. Rows:
     `??1Rva006DE6C0` 0x006DE6C0 and `??_G` 0x006DE760 (AptValue.cpp), which are not installers of
     0x00CEA264 by `vftable_map.py`; the `??_7Rva006DE6C0` binding in data_ledger.csv at that
     address needs checking first.
2. Slot rows: 0x006D6460 / 0x006D6440 into the object class (`getHasClass` / `setHasClass` by
   AptValue.h's order), 0x006CBCF0 into the root; twins for the inline slots 3, 4, 10 and 12.
3. Then `class --fold Rva006D6500 --into Rva006D65A0`, with the ctor unit's destructor declared
   out of line. The same order serves every other table derived from 0x00CEA264
   (Rva006D6470Derived.cpp lists them).

Inference, not a target fact: slot names 3..13 follow AptValue.h's declaration order.

Not checked: the real link; how many bridge-queue rows derive from 0x00CEA264.
