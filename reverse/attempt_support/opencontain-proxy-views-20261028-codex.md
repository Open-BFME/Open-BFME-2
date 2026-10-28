# OpenContain allocator-view prerequisite, 2026-10-28

Base: `bd2b10af97`. Seat: `yasinschroeder-codex`.
Sources: `Code/GameEngine/Source/Common/Rva00463469Ctor.cpp` and
`Code/GameEngine/Source/Common/Rva00463736Ctor.cpp`.

## Scope and evidence

The default picker claimed OpenContain's 44 whole-file scopes. The current
map rebuilt in memory by `tu_skeleton.py --plan` approves 137 rows in those
files and excludes 26 mixed files. The Contain consolidation packet was read
and refreshed after the edit. No committed map, ledger, symbol, source path or
debt register changes here.

`tu_views.py --dry-run` identified a concrete conflict in Rva00463469: its
constructor declares an allocator proxy at offset zero, while the derived
constructor privately redeclares that storage as an unsigned integer. Both
now declare the existing `_STLP_alloc_proxy<unsigned int, int, allocator<int> >`
member `m_proxy` as protected. The derived constructor accesses its `_M_data`
member. The focused post-edit class-view scan reports a compatible plan for
both files, with the proxy at +0x00.

This reconciles existing reconstruction declarations. It establishes neither
an original application class name nor a complete donor-derived layout.

## Verification

- Ordinary before/after `./build.sh`: both rows exact, 36 bytes at 0x00463469
  and 42 bytes at 0x00463736. Both frozen-file checks pass. The final
  `link_check.py --prepare-current` also records strict reusable receipts.
- All seven original external COMDAT byte-and-symbolic-relocation fingerprints
  are unchanged; no external binding is removed. The derived file additionally
  emits three one-byte `ret` destructors. The allocator and proxy destructors
  are exact copies of the base source's existing providers; the third is the
  implicit Rva00463469 destructor. No undefined dependency is added.
- Ordinary before/after previews against published index `41c28839bf`
  (2026-10-28 11:08) report both files LINKS, preserving 78 authored bytes.
  The unchanged OpenContain seed separately verifies 4/4 rows and previews
  LINKS for 283 authored bytes; its historical target-table entry is updated.
  Code identity reports two rows and zero new findings in shadow mode; data
  identity reports zero findings. Neither source has a gate/data/identity
  baseline key or a header/Microsoft-header queue entry to transfer or retire.
- The staged-tree batch audit remains INCONCLUSIVE: the index predates the
  base, and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry this provider/declaration scope and that consumer
  into the normal census. Local previews do not establish global closure.

Local logs and object comparisons are under `build/opencontain-proxy/` and
`build/opencontain-proxy-*-build.log` / `build/opencontain-proxy-*-link.log`.
There are no source-path moves requiring a tooling compatibility audit.
Staged TU ownership, Microsoft-header and whitespace checks pass. The refreshed
consolidation packet passes its input/output currency check.

## Remaining work

The broad merge dry-run was stopped after approximately 23 minutes because
its source snapshot preceded this repair. It produced no final acceptance
report, and no applying merge was run. Re-run the supported merger on current
inputs before moving any rows.

The original class-view report also identified conflicting OpenContain and
UpdateModule bases, Object sizes, Thing class keys, overlapping container
element fields and other private views. Those require separate verified
prerequisites. The seed's unmatched donor update/prune bodies remain untouched:
retail bodies already have owners at 0x004640BE and 0x00463A81, but the donor
update symbol also has constructor/destructor consumers. Deletion needs a
coherent identity/provider repair, not a new-match claim.

No source-file reduction, census gain, image-ownership gain or runtime
validation is claimed by this prerequisite.
