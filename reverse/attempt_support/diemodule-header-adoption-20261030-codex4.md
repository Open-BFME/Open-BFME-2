# DieModule callback and finder header adoption

Base: `04e74d7e4d`. The default picker claimed `class:DieModule`; the two
edited file scopes were also claimed. No donor implementation is used.

`RebuildHoleExposeDieFind.cpp` now includes the canonical DieModule header
and calls `getModuleNameKey() const`. The existing finder calls primary
slot 4 (`[vtable+0x10]`); Module.h already identifies that native slot. This
removes its private five-slot DieModule stand-in without changing dispatch.

`CreateObjectDie_onDie.cpp` now derives its leaf view from canonical
DieModule and calls the protected `isDieApplicable` as a member. The
inherited fields provide the module data at primary +4 and owner at +8.
MSVC retains the existing +0x10 interface entry convention. The last owner
argument still uses a raw reload at primary +8: replacing it with the
accessor eagerly loads the owner into edi before the GameLogic call and
changes the native instruction sequence. That intermediate trial was
corrected; no nonmatching reconstruction remains.

## Verification

- Normal builds pass all four matched rows across both sources. Strict
  `link_check.py --prepare-current --paths-from` preparation also passes
  4/4, one string literal, and both frozen-source checks pass.
- The finder's parent EH graph is EXACT. Its existing funclet row resolves
  through the parent graph after compiler-label renumbering; no ledger or
  pin changes are needed.
- All three external COMDAT name/digest/size records, strong definitions,
  undefined and weak externals, and relocation roots/edges are identical
  before and after. No helper provider or vftable is added. The digests
  include relocation identity. [Object facts](diemodule-header-adoption-20261030-codex4.json).
- Ordinary paired preview retains 2/2 LINKS and 256 authored bytes:
  finder 117 -> 117, callback 139 -> 139, against index `12b9e7a7c0`
  (2026-10-30 10:11). This is a prediction, not a new census measurement.
- `header_adopt_lane.py accept --class DieModule` passes both sources and
  retires their two rows from `reverse/header_queue.tsv` itself.
- The staged-tree batch audit exits 2, INCONCLUSIVE: its index predates
  the outgoing base, and affected consumer
  `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Full
  affected-consumer selection and loss verification remain pending; carry
  these providers and wider consumers into the next scheduled census.

No source path, function identity, pin, shared header or compiler flag
changes. The remaining DieModule queue entries still need their documented
accessor, field, destructor-shape or consumer-link prerequisites. This pass
does not clear the broader destructor-view obstacle.

Scratch evidence: `build/diemodule-header-codex4-20261030/` holds original
and final objects, original sources, source lists and the staged audit.

## Reference freshness

The ignored local BFME 1 success marker is over 72 hours old. Official
upstream master was fetched without recursion at
`a9f5a04759c7438ce5a71caebc50eb3c6969d84f`; the clean checkout and committed
reference remain the previously verified
`1d5131d3f193cdf01a99da66ccd6828639585650`
([verification](reference-1d5131d3-20261030.md)). The attempted
`file:reference/open-bfme-1` claim was refused because another worker holds
it. No newer-input verification, reference update or successful freshness
stamp is claimed. This cleanup uses existing BFME 2 declarations only.
