# Player completes the BitFlags clear provider repair, 2026-10-30

Scope: LINK-030. Follow-up to the verified DumbProjectileBehavior/WeaponSet
early declarations in `bitflags-clear-declarations-20261030-codex5.md`.
Player's file claim was available; only Player source is edited. The unchanged
BitFlagsClear owner is reserved for verification. The two earlier consumer
files are held by other seats. Their shared objects predate source changes
(source hashes differ, commands/dependency hashes agree), so current unchanged
sources are compiled into private scratch objects for this check. Their
sources and shared-cache objects are never edited or overwritten.

## Source and target facts

The existing clear owner at RVA 666E80 is the complete 14-byte sequence
`33c0890189410489410889410cc3`. Player emits a competing five-byte jump to
its 20-byte memset-backed bitset reset. The owner also emits an existing
18-byte inline-store reset; that helper's existence does not independently
establish its original native identity or address.

Declare the existing clear specialization before PreRTS's KindOf helpers
instantiate it. Preserve the CRT array-placement guard, Windows-before-BaseType
include order, original PreRTS line 58 and the existing bitset test declarations.
The Windows ordering matters: loading BaseType first changes TRUE/FALSE from
integer constants to bool constants and changes unrowed isPlayableSide's
code. A negative probe reproduces that difference; the final source restores
the original helper exactly. No shared header or build flag is changed.

Private original/final probes match all eleven current ledger rows. No row
in the owned Player/clear pair carries EH data. The final object removes only
clear/reset and adds no definition. All 412 retained external raw function
bodies are identical; only three REL32 targets
change from reset to clear: two in ClosestKindOfData's constructor and one in
BitFlags xfer. These operate on the same leading bitset storage and now call
the existing native clear. This does not recover those unrowed donor bodies.

## Verification scope

`proof.json` records private controls, actual objects, unchanged provider
receipts, native clear bytes, selection and the four-unit link preview.
Normal source build, frozen-file checks and the outgoing hooks still apply.
All 18 current cohort rows pass, using strict owned objects and fresh private
objects for the unchanged held sources. Both clear/reset blockers disappear
from all four units. Only the 14-byte clear owner newly predicts LINKS;
Player, DumbProjectileBehavior and WeaponSet retain independent blockers.
The normal two-owned-source preview agrees: 0 -> 14 linked bytes. This clears
LINK-030's provider scope, pending census, rather than those entire clients.
No ledger identity, pin, hatch, data owner or source path is added or moved.
The broader audit retains its published-index qualification; only a new census
can change headline LINKED/LINKING. The unchanged CreateAHero consumer's 23
rows were separately prepared successfully; the most recent broader audit
then stopped at missing AIBuildable.cpp consumer evidence instead.

The shadow identity check reports twelve unregistered donor divergences in
this file. Those helpers are outside the two changed-relocation symbols and
are unchanged in the actual original/final comparison. They remain separate
cleanup; this repair adds or retires no identity-baseline key. Enforced byte,
data, source-integrity and pin checks pass.
