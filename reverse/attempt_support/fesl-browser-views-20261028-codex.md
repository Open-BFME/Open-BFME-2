# FESL browser declaration prerequisites, 2026-10-28

Base: `c7a3300866`. Seat: `yasinschroeder-codex`.
Destination: `Code/GameEngine/Source/GameNetwork/BfmeThingZI.cpp`.

## Scope and evidence

The default picker claimed the destination and its seventeen whole-file donors.
The GameNetwork `name_lane.py consolidate` packet was reviewed: its stale-map
placement fields are unresolved, with macro, internal-linkage and register
hazards. It supplies no original-path proof for this destination. The current
map rebuilt in memory by `tu_skeleton.py --plan` approves 70 rows across eighteen
whole files, with ten mixed files excluded. This is a provisional grouping, not
proof that BfmeThingZI.cpp was a retail filename. No map, row, name or source
path is changed here. BFME 1 freshness was already verified on 2026-10-27 at
`e74410b3738a2bb75d626085d9ebfd3406a43ff7`.

`tu_views.py` reconciles six existing private declarations using compiler
layouts, retaining only edits that pass its layout, byte, frozen-file and
external-symbol checks:

- Rva00803080: combine the seed's methods with the destructor source's virtual
  declarations.
- Rva00800920Owner: share the seed's +0x0C field/accessor and constructor with
  the ticket source's existing method declaration.
- Gen_007e86c0: share the destructor source's existing 0x10-byte view.
- BfmeListenerZI: make the existing onEntry parameter spelling consistent.
- Rva007F6D60ChildBase: share the existing inline destructor declaration with
  Common/Bfme5SixtyOne.cpp.
- BfmeMsg: share the existing constructor and protected +0x04 member with the
  child-constructor source.

These are compatibility repairs between existing reconstructions. Compiler
layout agreement and unchanged bytes do not independently prove full retail
class identity or layout. No canonical header adoption is claimed.

## Verification

Five edited sources: Common/Bfme5SixtyOne.cpp and GameNetwork's
BfmeOneHundredFiftyEight.cpp, BfmeThingDGDDestructor.cpp, BfmeThingZI.cpp and
Rva007F6D60ChildConstructor.cpp.

Original sources were restored temporarily and verified with ordinary
`./build.sh`; their objects were saved under `build/fesl-views-codex/`.
The accepted edits were restored and verified with
`link_check.py --prepare-current` for all five explicit sources. Both builds
pass **32/32 function rows**, three string literals and three empty-string
references. All five providers have strict reusable receipts. The frozen-file
check reports no unmatched definitions.

Original versus final object comparison preserves all **58 COMDAT
byte-and-symbolic-relocation fingerprints**, all **128 external symbol entries**
and all weak external bindings. Per-file COMDAT counts are 3, 5, 7, 28 and 15
in the source order above. No new external provider or dependency is introduced.

Code identity reports 32 rows and zero new findings in shadow mode. Data shadow
reports six findings for the destructor's three existing vtable anchors,
including three duplicate-def findings outside its wrong-name baseline. Their
source definitions, object facts and register entries are unchanged; no debt is
retired. No edited source occurs in either header queue. Staged Microsoft-header
and TU-ownership checks pass. There are no source-path changes, so the path-move
consumer audit does not apply. `git diff --cached --check` passes.

## Remaining composition and linking work

The supported dry runs before and after reconciliation accept **zero of
seventeen donors**. No applying merge was attempted.

- Six donors retain incompatible `-O2` overrides: both Common getters,
  BfmeGameBrowserVJU, BfmeHostBT_bfmeReportBT, Rva007F6B30FindRecord and
  Rva007F6B80ArrayIndex. Reconcile flags through the owning lane before merging.
- The small setup donor compiles but the link guard refuses moving its
  census-linked row into a destination with unresolved bfmeRunRE/send providers.
  The destination is absent from published index `41c28839bf` (census
  `c8734bec0c`); the full five-source ordinary preview therefore cannot judge it.
  Verify current providers and carry this destination into the normal census.
- BfmeThingDGD's base clauses, the buffer/block views, BfmeThingZI/BfmeEntryZI
  overlapping opaque fields, BfmeHostBT's slot storage and message/listener
  declarations still conflict. Missing reset/onGame/method declarations and
  dependency ordering prevent other donors from compiling together.
- Rva007F7AE0LobbyListRequest and Rva007F7C70FeslGameRecord fail the composed
  byte check. Do not merge them on declaration agreement alone.
- The Rva007F7980Browser reconciliation trial was reverted: its by-value region
  and lobby blocks require complete definitions before the class. Forward
  declarations alone produce C2079. No failed trial remains in Code/.

The four indexed edited donors preview LINKS for the same combined **1,336
authored bytes**. The outgoing staged-tree audit is **INCONCLUSIVE**: the index
predates the base and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry this
declaration/provider scope and the affected consumer into the next normal
census. No source-file reduction, linked-byte gain, image-ownership gain or
runtime validation is claimed.
