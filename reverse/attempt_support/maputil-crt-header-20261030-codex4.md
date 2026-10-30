# MapUtil size-reader CRT declaration cleanup

Base: `f8391607ad297682303ab53ff9ce9b0b8ec5a89f`. The Microsoft-header
picker claimed
`Code/GameEngine/Source/GameClient/MapUtil_unk_YA_NAAVDataChunkInput_PAUDataChunkInfo_PAX_Z.cpp`.

The unit takes `free` from the toolchain's `stdlib.h` instead of a local
prototype. The header is included before STLport, with its supported
`_CRTIMP` configuration empty, retaining the existing direct `_free`
binding. The original declaration overrode the imported declaration that
STLport had already included. Simply deleting it passes both function rows
but changes seven emitted allocator helpers to indirect `__imp__free`
calls; that trial is superseded. Restoring `_CRTIMP` immediately after the
early include also fails compilation: `stdlib.h` and the later `wchar.h`
then disagree on `_wsystem` linkage. Keeping one configuration throughout
the unit preserves the original object.

The two rowed size readers do not call free. This cleanup proves preservation
of the existing helper bindings, rather than inferring an allocator target
from the CRT name. Target row identities, donor attribution and the retained
allocator's identity remain as before.

Verification:

- Normal before/final builds pass both function rows (148 and 16 bytes),
  both owned data rows and the reference checks. Frozen-source checks pass.
- All 592 non-debug sections are identical, including bytes, flags and
  relocation targets. External relocation targets compare by name; local
  targets compare by section and offset. All 591 external symbol records,
  578 COMDAT fingerprints, strong/undefined/weak/COMMON bindings, and
  relocation roots/edges are unchanged. This includes all seven direct-free
  helper bodies. [Comparison facts](maputil-crt-header-20261030-codex4.json).
- Strict current preparation passes the explicit provider and writes a
  reusable receipt, leaving census/index/status unchanged.
- The ordinary preview retains LINKS, 164 -> 164 authored bytes, against
  index `12b9e7a7c0` (2026-10-30 10:11).
- The scoped staged batch audit exits 2, INCONCLUSIVE: its index predates
  the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Full affected-consumer selection and loss checks remain
  unverified. Carry this provider and its wider consumers into the next
  scheduled census; no census gain is claimed.
- The owning Microsoft-header scanner classifies the unit clean. Its only
  local occurrence is the supported `_CRTIMP` configuration input. Its
  `refresh_queue` removes exactly this file's one declaration-debt row.
  Included-header findings remain separate; this is not closure of the
  existing shim/header debt.

Scratch evidence: `build/maputil-crt-codex4-20261030/` holds original,
intermediate and final object comparisons, build logs and the scoped audit.
No source path, row, pin, class or shared-header change is involved.

Reference freshness: the ignored local success marker is over 72 hours old.
Official BFME 1 master was fetched without recursion at
`a9f5a04759c7438ce5a71caebc50eb3c6969d84f`. The reference scope is held by
another worker, so the committed, clean, previously verified
`1d5131d3f193cdf01a99da66ccd6828639585650` remains in use
([verification](reference-1d5131d3-20261030.md)). No newer-input verification
or successful freshness stamp is claimed.
