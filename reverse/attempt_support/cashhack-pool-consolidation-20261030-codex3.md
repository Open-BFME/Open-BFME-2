# CashHackSpecialPower pool-key consolidation prerequisites

Base: `3602c6ffb3af7364e5adb11a21f2d79ce5cf4de5`.
The default picker claimed the seed and four dedicated donors under
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/`.

Target evidence: the existing seed owns six matched rows; the pool-key donor
owns three, including its guard rollback and EH handler. Its two data-ledger
rows own the key and initialization guard. No new identity, layout, pin or
runtime behavior is inferred. The in-memory refreshed TU map approves the
pool donor for the seed. The committed map is not regenerated.

Donor evidence: the seed already used the Zero Hour CashHackSpecialPower
header from the pinned BFME 1 reference. Its declarations are now local to
the seed, with the existing matched static pool-key method declared. This
preserves that donor view without editing the shared reference header; it
does not prove a BFME 2 donor path. A parser forward declaration accommodates
the supported composer's ordering of its address anchor before its body.
The existing disabled-state ABI shim, four aliases and five counted markers
remain unchanged.

Prerequisite verification:

- Supported builds pass all 16 rows across the five scoped files, with the
  string, float and import checks. Frozen-source checks pass for all five.
- Seed comparison preserves all 622 COMDAT fingerprints, 660 external binding
  records and the complete named relocation reference graph. Counts and
  verdicts are recorded in [comparison facts](cashhack-pool-declarations-20261030-codex3.json).
- Class and converged-data checks pass; no second global names are added.
  The scoped Microsoft-header refresh changes no queue rows.
- Strict current preparation passes the seed and pool donor. Ordinary preview
  retains LINKS for both, 435 -> 435 authored bytes, against index
  `12b9e7a7c0` (2026-10-30 10:11). The pool EH graph is EXACT.
- The supported merge dry-run now accepts the pool donor. Action remains
  blocked by native/shim type redefinitions (including UnicodeString and
  Coord2D); module-data constructor and destructor donors collide with
  definitions emitted by the donor seed. Five mixed-source contributors
  remain outside this merge. These need separately verified reconciliation.

The staged outgoing batch audit exits 2, INCONCLUSIVE: the index predates
origin/master and 58 affected sources lack current receipts, first
`Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-2c79.cpp`.
Full affected-consumer selection and loss verification remain pending; carry
these providers and consumers into the next scheduled census.
No census increase or closure of the wider CashHack subsystem is claimed.
Final merge verification will be recorded separately.
Scratch originals and objects are in `build/cashhack-codex3/`.
