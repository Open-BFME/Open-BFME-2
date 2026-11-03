### LINK-051: the 0x0052C823 vector copy and 0x0052CD03 vector dtor are Rva003A6F70's, rowed as BfmePod32's
Status: Open. Updated: 2026-10-26; inspected revision: c9c4584d48.
Evidence / affected units: `Rva0056616BCopyDeferred.cpp` (0x0052D555, wrong_selected 1) and
`stlport_pod_noexc_deferred_copies.cpp` (selected 4). Target facts: the copy ctor 0x0052C823 calls
0x0052C27E, which constructs through `_Construct<Rva003A6F70>` 0x0052BD04 (copy ctor 0x0052BB34);
the `BfmePod32` loop 0x00421D28 calls a different `_Construct` (0x00421D16, copy ctor 0x0042183F), so
the two are distinct element types, not an ICF fold. The dtor 0x0052CD03 calls `_Destroy<Rva003A6F70*>`
0x0052C3BF. Yet `vector<BfmePod32>`'s copy ctor is rowed at 0x0052C823, its dtor at 0x0052CD03, and
`__uninitialized_copy<const BfmePod32*>` is both rowed at 0x00421D28 and pinned at 0x0052C27E: the
census resolves the copy ctor's call to the row and judges the kept copy wrong.
Completed: an attempt (patch kept outside the tree) retyped 0x0052C823 to `vector<Rva003A6F70>` with
ICF-alias rows for its get_allocator 0x0021983A, alloc_proxy ctor 0x0014F3C4, `_Vector_base` ctor
0x0052BCAB and const `__uninitialized_copy` 0x0052C27E (provider 9/9 exact), and dropped the wrong
pin. Reverted, because the consumer's EH cleanup funclet `uw_0079729c` then needs
`~vector<Rva003A6F70>` at 0x0052CD03, and forwarding the copy through placement new adds two EH
states (340 B vs 333 B).
Remaining / next check: retype 0x0052CD03 (`Rva0056616BCopy.cpp`, an EH-framed 63 B dtor with its
funclets) together with 0x0052C823, then point `Rva0056616BCopyDeferred.cpp`'s `m_54` at
`vector<Rva003A6F70>`; re-check the BfmePod28 `selected` names in the same provider the same way.
Clearance: pending.
Census confirmation: not claimed.

**Census check (2026-10-28, seat halilkkaya-lk3):** the census at `73061d9452` (2026-10-27 14:34)
records `Rva0056616BCopyDeferred.cpp`, `Rva0056616BCopy.cpp` and `stlport_pod_noexc_deferred_copies.cpp`
as linked, so the Rva003A6F70 retyping inherited by `docs/linking_targets.md` (2026-10-26) is
census-confirmed for those three units. The entry stays open only for the BfmePod28 `selected` names
noted above (`stlport_pod28_vector_resize_value.cpp` is still unresolved on
`vector<BfmePod28>::_M_fill_insert`).
