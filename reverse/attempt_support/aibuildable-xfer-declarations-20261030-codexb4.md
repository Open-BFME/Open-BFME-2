# Buildable transfer declarations

Base: `3e527796a0`. The default picker claimed `class:Rva0055B0CC`
and nine merge-related files for canonical-header establishment. This change
is a prerequisite cleanup of four existing private declarations; no rows,
source paths, pins or class identities move.

## Target and provider evidence

Retail table RVA `0x0086B900` has seventeen slots. Slot 12 points to
`0x0055AED6`, whose existing 205-byte row is
`?Rva0055AED6@Rva0055B0CC@@UAEXPAVXfer@@PAX@Z` in
`Code/GameEngine/Source/Common/Rva0055AED6Xfer.cpp`. That body performs the
native Xfer operations. Derived table `0x008765F8` inherits this same slot;
table `0x008765A8` overrides it with the rowed Xfer wrapper `0x005DAAC1`.
These are target addresses and existing provider declarations, not proof of
an original class or method name.

The destructor, slot-5, slot-15 and build-availability private views instead
declared the first parameter as `void *`. Align all four to `Xfer *` with a
forward declaration. The destructor now references the existing row directly
and drops its `/alternatename` bridge. No active Code or shim source retains
the old spelling. The published index's per-object touches find only the
destructor using that alias; it also holds the sole alias definition.
The owning hatch tool removes exactly this register key: alternatename
2,878 -> 2,877.

## Verification

- Before and after `./build.sh`: 9/9 function rows across the four changed
  files and unchanged Xfer provider. Three float literals verify; no strings
  or imports are present in this scope.
- Strict five-source `link_check.py --prepare-current`: passes, with current
  reusable receipts. `find_declared_unmatched.py`: all definitions matched.
- `eh_verify.py`: EXACT 1, zero baseline or missing-object cases. The existing
  destructor funclet label renumbers from `$L357` to `$L358`; the normal gate
  resolves it through the exact parent EH graph without a ledger change.
- All twelve external COMDAT names and raw bodies are retained. Eleven
  relocation-aware fingerprints are identical; only the destructor's derived
  vtable changes its slot-12 relocation from the alias to the rowed provider.
  Its undefined external changes by that same spelling only. The other four
  objects retain every external-symbol record.
- Ordinary joint previews before and after: 5/5 LINKS, 902 -> 902 authored
  bytes, against census index `12b9e7a7c0` (2026-10-30 10:11 UTC). This is
  bounded prediction, not a new census or a linked-byte gain.

The staged-tree outgoing `link_batch_audit.py` is INCONCLUSIVE (exit 2): the
published index predates base `3e527796a0`, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry the changed declarations, Xfer provider and affected consumers
into the next scheduled census/current-receipt audit. Full-image selected
provider and loss verification remain open; the alias-specific census touch
scan above does not replace that broader audit.

## Remaining header prerequisites

The initial 29-view contract had slot 12 undecided (four Xfer declarations,
four void declarations and one placeholder). The refreshed contract resolves
this slot as `Rva0055AED6(Xfer*,void*)`. Do not generate a canonical header
from its remaining majority result unchecked: it places a deleting destructor
at slot 13 and ends there, whereas native `0x0086B900` has four pure slots
13..16, all targeting the import thunk `0x0003B810`. The existing unregistered
`Common/Rva0055B0CC.h` describes the seventeen-slot shape; several private
views still put the destructor after slot 12 instead of at slot 0.

`header_adopt_lane.py dest` finds no official header for the placeholder
token. Existing `AIBuildable` declarations and the identity-suspect record at
`0x0055B0CC` must be reconciled from target uses before choosing the official
destination or registering another class. The current source already contains
both names, so a rename into the existing token is not an ordinary class
rename. The transfer cleanup establishes neither that identity nor a donor
path. Full canonical-header establishment and TU merges remain open.

The BFME 1 freshness receipt was verified on 2026-10-29 at 19:23 UTC for
`b53c85e7f9`; no reference refresh was due. No nightly or smoke run was started.
