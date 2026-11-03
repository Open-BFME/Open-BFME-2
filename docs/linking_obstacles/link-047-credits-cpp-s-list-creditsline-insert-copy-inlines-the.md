### LINK-047: `Credits.cpp`'s `list<CreditsLine *>::insert` copy inlines the bfmelist node creator

**Status: Repair landed / awaiting census. Updated: 2026-10-26; inspected revision: c01848c0b1.**

- **Evidence / scope:** `Credits.cpp` (3,053 B) did not link: its
  `list<CreditsLine *>::insert`, the only copy, is not retail's. Retail folds every
  four-byte-element `list<T *>::insert` into 0x005925E2 (37 B), which calls
  `_M_create_node` 0xB6447; `Credits.cpp` builds `insert` with the bfmelist shim's
  inlined node creator. Two earlier attempts (`reverse/re_attempts.log`, 0x005B78A4 and
  0x005B72A5) declared `insert` decl-only in `Credits.cpp`, which re-allocates registers
  in `addText`/`update`, since `push_back` inlines `insert` there. The census's
  `famgenDelete005B72E7` duplicate is a stale-index artifact: its donor,
  `FamilyDeletingDtors_muse-08-5B7352.cpp`, was merged into `Credits.cpp` by 800def3e22,
  after the census commit.
- **Completed:** `Credits.cpp` is unchanged. `stlport_list_int_insert.cpp`, link position
  1104 against `Credits.obj`'s 19770, instantiates `list<CreditsLine *>::insert` beside
  its `list<int>` owner row, with `_M_create_node` declared only so it calls
  `Credits.cpp`'s retail-proven copy, as the `SuperweaponInfo` twin units do. Its body
  is byte-identical to the `list<int>` row, and the existing pins place both names, so
  the first copy is proven retail and `Credits.cpp`'s copy no longer loses
  (retail-truth-3). Added as an ICF-twin row (`add_match.py --icf-owner`); `./build.sh`
  5/5. `tools/link_check.py` on a local `--update-index` index at c01848c0b1 (stale
  donor dropped): `Credits.cpp` 0 -> 3,053 B, `stlport_list_int_insert.cpp` keeps its
  62 B. Without the provider instantiation, the same index still reports the `insert`
  comdat and selected blockers.
- **Prior pin follow-up:** the `insert` pin's `fold-proof=` names `Credits.cpp`,
  whose copy no longer equals retail; `stlport_list_int_insert.cpp` now proves it. The
  pin was left as is (pin edits go through `tools/pin_admission.py`).
- **Wrapper cleanup (2026-10-26, inspected `c254d71bb8`):**
  [paired verification](../../reverse/attempt_support/credits-delete-wrapper-cleanup-20261026.md)
  removes the unused `famgenDelete005B72E7` wrapper and its unmatched hatch.
  `addText` still emits the matched deleting destructor. All 31 byte-checked
  functions, the data row and five EH graphs remain exact; the frozen-file and
  shadow data checks pass. With published index `5ce093a71a` (19:02), both
  before and after preview LINKS for Credits (3,053 authored bytes) and its
  insertion provider (62 bytes). This retires one hatch and confirms the earlier
  repair; it adds no linking gain. A bounded preparation accepts Credits' strict
  reusable input receipt, without claiming dependency closure. The stale pin
  proof above and confirmation in the next normal census remain follow-ups.
- **Pin follow-up closed (2026-10-26):** the same
  [evidence](../../reverse/attempt_support/credits-delete-wrapper-cleanup-20261026.md#redundant-insertion-pin-follow-up)
  confirms that the exact insertion name already has its 37-byte matched row
  in `stlport_list_int_insert.cpp`. Removed its redundant pin and lowered that
  address's pin hatch count 14 -> 13. Both whole units pass 36/36 byte checks
  without the pin; pin consistency and CSV validation pass, and both still
  preview LINKS. This retires one further hatch, with no new linking gain.
- **Remaining / next check:** confirm the repaired two-unit scope in the next
  normal census; the stale insertion-pin proof no longer needs repair.
- **Clearance:** preview scope (the two units above) on a HEAD-updated index.
- **Census confirmation:** awaiting the next census.
