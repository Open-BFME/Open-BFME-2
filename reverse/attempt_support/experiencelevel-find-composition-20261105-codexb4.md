# Experience-level find-helper composition prerequisite

Base: `abe89d6b51`; owner: `yasinschroeder-codexb4`; 2026-11-05.

The seed's static `Rva0028867DCheck` and the copies in
`Common/Rva00288940Find.cpp` and WWLib's `Rva002897A8Find.cpp` already have
identical bodies. The donors spell their helper `__declspec(noinline) static`
and the seed spells it `static`. The supported composer keys function
signatures including that attribute, so it retained both definitions and
reported C2084. Use the donors' existing noinline declaration in the seed.
This expresses its already-observed out-of-line ESI call shape; it introduces
no symbol, alias, pin, or new instruction body.

Verification:

- Ordinary seed build before and after: 51/51 function rows and all four data
  rows match. String, float, import and unmatched-definition checks pass.
- External symbol facts: 341 before/after, identical. Relocation-aware COMDAT
  bodies: 260 before/after, identical (`tu_views.coff_externals` and
  `link_census.comdat_bodies` on ordinary build objects).
- The seed's ordinary link preview remains LINKS, 2,990 -> 2,990 authored
  bytes, using the 2026-11-05 05:17 index at c95fcfcfcd. No census gain.
- Before the declaration fix, supported merge dry-run accepted no donors.
  After it, the dry-run accepts the seed and both find helpers under the
  seed's existing flags and retains its census-linked cohort guard. Remaining
  donors still fail their separate layout and specialization-order checks.
- Refreshed evidence planner:
  `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/System/`
  with output `build/consolidation/experience-20261105-codexb4`. It records
  WorldBuilder/BFME1 path leads and mixed/layout/compiler blockers; it is
  investigation evidence, not TU approval. The merge tool rebuilds the stale
  committed TU map in memory and checks the approved destinations itself.

Local logs: `build/codexb4-experience-{seed-before,seed-after,dry,dry-after}.log`
and `build/experience-20261105-codexb4/seed-bindings.json`.
The subsequent merge must use `tu_skeleton.py --merge`, carry the protected
register keys, and retain current byte, EH, data and provider bindings.
