# Living-world scorekeeper CRT time declarations

Base: `f3871e571821c9aabafc11b13426e4de2222cd1e`. The Microsoft-header
picker claimed `Code/GameEngine/Source/Common/LivingWorldScoreKeeper.cpp`.

The unit now takes `time` from the toolchain's `<time.h>` instead of two
duplicate handwritten declarations. A scoped, supported `_CRTIMP`
configuration preserves the existing imported `time` binding and restores
the unit's direct-binding configuration for other CRT headers. No source
path, ledger row, pin, class or shared header changes.

Verification:

- `./build.sh` passes all 23 matched rows, one string literal and six named
  imports. The frozen-source check passes. The parent EH graph is EXACT;
  the existing funclet row verifies through that graph despite compiler
  label renumbering.
- All 70 external COMDAT fingerprints and sizes, strong/undefined/weak
  bindings, and reference roots/edges are unchanged between the original
  and final objects.
- Strict current preparation passes and creates a reusable provider receipt.
  Ordinary link preview retains LINKS and 1,982 authored bytes before and
  after this change, against index `12b9e7a7c0` (2026-10-30 10:11).
- The converged-data check passes for 11 addresses, with no second names
  or unjudged rows. Removed-debt verification and diff whitespace checks pass.
- The owning Microsoft-header scanner classifies the unit clean and its
  `refresh_queue` removes exactly this source's queue row. Three included
  STLport shim unknowns remain separate; this is not closure of shim debt.
- The scoped staged batch audit exits 2, INCONCLUSIVE: the index predates
  the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Full affected-consumer selection and loss checks remain
  unverified. Carry this provider and its wider consumers into the next
  scheduled census. No census linking or ownership gain is claimed.

Scratch evidence: `build/scorekeeper-crt-codexb-20261030/` contains the
original source and object, final object, comparison facts, build and
preparation logs, EH results and batch-audit output.
