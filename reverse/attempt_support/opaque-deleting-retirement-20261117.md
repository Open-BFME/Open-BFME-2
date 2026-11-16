# Three obsolete deleting-destructor emitters retired

This is a reviewed retraction of redundant real rows, following docs/naming.md's
separate-retraction rule. No rows move, no new implementation is credited, and
no class identity is inferred merely from a shared address.

| Removed opaque spelling | RVA / extent | Retained native emitted owner |
| --- | --- | --- |
| `??_GRva0060FE2@@UAEPAXI@Z` | 00061AA1 / 28B | `??_GMilesAudioManager@@UAEPAXI@Z`, MilesAudioManager.cpp |
| `??_ERva0060FE2@@WM@AEPAXI@Z` | 0005D41D / 8B | `??_EMilesAudioManager@@WM@AEPAXI@Z`, MilesAudioManager.cpp |
| `??_GRva0090840@@UAEPAXI@Z` | 00091153 / 28B | `??_GRva007E3C20Vp6Stream@@UAEPAXI@Z`, Rva007E3C20Vp6StreamCtor.cpp |
| `??_GRva009D6FA@@UAEPAXI@Z` | 0009D9A1 / 28B | `??_GRva0009D55BProduct@@UAEPAXI@Z`, Rva0009D55BProductCtor_Rva0009D55BProduct.cpp |

The three native scalar bodies were independently compared from current COFF:
complete retail bytes, resolved relocations, no masking or weak fallback. The
Miles adjustment thunk matches through its existing compiler-generated,
same-object weak default from the vector-deleting name to its native scalar
owner. No alias directive or replacement pin is introduced. The native rows
remain matched at all four extents: 92 unique bytes remain covered.

Only the three obsolete class/emitter blocks are removed from
OpaqueScalarDeletingDtors.cpp and OpaqueScalarDeletingDtorsB09.cpp, including
the latter's two unused novtable base views. Four rows receive deletion
tombstones so a union merge cannot resurrect them. The four native rows' notes
now describe their independent native ownership instead of relying on the
retired opaque-carrier fold proof.

Five unused pins are removed: Rva0060FE2's old default constructor, complete
destructor and vector-deleting name, plus Rva0090840's and Rva009D6FA's complete
destructors. No spelling occurs in data_rows, data_ledger, data_converged or the
vtable bridge queue, so no table-data alias refresh is needed. Generated TU maps
and measured blocker queues are unchanged.

## Consumer proof and verification

The frozen full-build audit had 17,542 expected/current objects, zero missing or
stale objects, and inspected all 17,540 objects outside the two carriers. Whole
COFF symbols, weak defaults and directives contained none of the 20 retired
names. Inputs remained unchanged during that audit. Subsequent factory, network
and Apt consumer objects were separately checked against those same names;
none introduced a reference. The network trials were then restored to their
already-audited original sources before the normal hatch update.

- Official five-source build: 537/537 functions and three data rows verified;
  string, float and import reference checks pass.
- EH: 85/85 EXACT, no missing objects or baselined failures.
- Current carrier comparison: exactly 13 obsolete external definitions removed,
  zero added, zero retained definitions changed. No retired name remains in
  either carrier. Both objects have zero CRT initializer sections before/after.
- CSV, pin consistency, declaration inventory, data shadow and converged-data
  checks pass. Normal hatch update removes five pin keys (9272 -> 9267); it also
  clears an allowance token already recorded in local HEAD at 00238580 without changing its count.
- Scoped link_check keeps all three native provider units linking (46,044 own
  bytes). The opaque carriers still fail on six and two unrelated destructor
  names respectively; the three retired missing-destructor references are gone.
  The comparison census is stale (0534e78db3, 2026-11-16 16:28), so this is not
  a new full-link or runtime verdict.

Local reproducible evidence is under
build/decal-diagnostic/opaque-retirement-review/: incoming-proof.json,
provider-diff.json, coverage.json, eh.json, original carrier objects, exact
operations and patch hashes. VP6 checks used only existing BFME COFF and row
metadata; no external decoder source was inspected.

Next: fresh real-link measurement, then the newest image's runtime receipt.
This retraction neither proves menu reach nor retires initializer/vtable bridges.
