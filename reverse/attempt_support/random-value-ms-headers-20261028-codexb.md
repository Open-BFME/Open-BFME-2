# Game-logic random CRT declaration cleanup

Inspected base: `6d7a215d6b`. Preview index/census: `d92e7e6635`,
2026-10-28 15:58. BFME 1 freshness receipt: verified 2026-10-26 at
`001ccd8e27686e9887235b62ff797627f2dde7f5`.
The header picker claimed the integer source; the same-cause real sibling
was separately claimed before editing.

## Target facts and bounded change

Retail GetGameLogicRandomValue (RVA 0x00233FF4, 86 bytes) calls strrchr
through IAT VA 0x00BBA5A8 at RVA 0x00234027. Its logger call at RVA
0x0023403D reaches RVA 0x002CEC42. The real sibling (RVA 0x00234092,
127 bytes) has the same import at RVA 0x002340E7 and logger target at
RVA 0x00234104. These are retail disassembly facts.

The current FprintfAppendLine.cpp owner at 0x002CEC42 formats and appends
to a game object's string vector; its `_fprintf` spelling does not identify
the CRT stream function. Therefore stdio.h is not a valid drop-in declaration
for that call. Both consumers keep the existing opaque game-helper prototype
and binding, remove `typedef void FILE`, and spell their unchanged opaque
pointer type directly. They include the toolchain string.h with `_CRTIMP`
set to dllimport to preserve the actual strrchr import. No donor evidence or
new global identity is asserted. The inaccurate real-source CRT comment is
corrected; no logger rename or data-ownership repair is claimed.

## Checks and remaining work

- Before/after normal builds: 2/2 rows exact, with both string references,
  the real sibling's float constant and both named imports verified.
- Frozen-file checks pass before/after. Strict provider preparation passes
  for both sources; ordinary paired preview retains LINKS, 213 authored bytes.
- [Before/after object facts](random-value-ms-headers-object-20261028-codexb.json)
  are identical: all five COMDAT fingerprints, strong and undefined names,
  weak aliases, runtime roots and reference edges. Neither unit has EH rows.
- Scoped data check: zero findings. Header audit refresh uses the owning
  tool's `scan_text` and `refresh_queue`, preserving unrelated queue rows.
  Findings fall from three to one per source: four local declarations removed.
  The configuration macro is explicitly not counted as a declaration.
- Staged-tree outgoing batch audit: INCONCLUSIVE (exit 2). The index
  predates the outgoing base and affected consumer
  `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry that
  consumer and these unchanged bindings into the next scheduled census;
  scoped preview is not full consumer verification.
- The two remaining header findings are the existing game-side `_fprintf`
  identity. Resolve its real name/provider and consumers together before
  replacing that declaration; a CRT-header substitution would assert the
  wrong object type. Existing random-state/log-global consolidation work
  remains outside this patch.

Scratch backups and the explicit-source list are under
`build/random-int-ms-headers-20261028/`. No ledger rows, pins, source paths,
shared headers, hatches or census counters change. No runtime test was run.
