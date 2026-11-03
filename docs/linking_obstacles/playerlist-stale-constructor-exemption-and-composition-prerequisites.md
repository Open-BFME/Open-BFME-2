### PlayerList stale constructor exemption and composition prerequisites (2026-10-30)

2026-10-31 header reconciliation (hdr-player-2, base dae67b429b): the
Player size/base ambiguity is resolved in the new Common/Player.h by direct
retail ctor/dtor tables at +0/+4/+8 and the 0x758 allocation in 2A7F80.
The first AI delegate/query clients pass 9/9 rows and ordinary header acceptance;
isLocalPlayer subsequently passes 1/1. A homogeneous index-only caller batch
then adopts 16 more units (137 matched rows); eight refused trials are
restored and retain their queue rows, and two held units are skipped. Twelve
additional method callers then adopt (278 matched rows), bringing the pass to
31 units / 425 rows. The complete original/adopted union conserves all fifteen
pre-existing identity findings and all five pre-existing shadow-data findings;
combined ordinary previews preserve every adopted unit. NetPacket is restored
and remains queued: even its original previews 33,222 -> 0 census-linked bytes
with duplicate rva0058C484, despite 209/209 exact rows. No cause or census
clearance is inferred from that old-index refusal. Normal scoped header gates pass
635/635 over 87 dependents, then 636/636 over 88. This clears only those
adoption units, not the earlier PlayerList merge or census obstacle. Constructor
adoption still refuses its +0x34 member because the header retains opaque
storage. PlayerList's primary table has fourteen inherited slots plus three
introductions; its registered SubsystemInterface header exposes only the
destructor. Reconcile that base surface before establishing PlayerList; do not
copy the competing shim or insert guessed slots. Complete target tables,
layout decisions and remaining lifetime bindings are in
[the header handoff](../../reverse/attempt_support/hdr-player-2-20261031.md).


At base `112d98e320`, PlayerList.cpp's stale constructor exemption is retired:
the complete 136-byte constructor and its EH rows already belong to
PlayerListCtorBFME2.cpp. All 57 rows across twelve fragments, the data row,
four strings and 21 funclet pins pass; strict preparation verifies all twelve
providers. External COMDATs, symbols and reference graphs remain identical.
One hatch key is retired. Source-file and census gains are zero.

The current class-view plan still reports Player size, PlayerList base and
embedded Dict conflicts. The broad merge probe stopped during accretion with
no final accepted-set verdict; no merge was applied. The staged audit is
INCONCLUSIVE on older index `85f6b7f40c` and the missing current receipt for
Common/0CreateAHeroManager21FE49.cpp. Carry this consumer and the PlayerList
scope into the next scheduled census. Class reconciliation and the earlier
Xfer/C1001 composition prerequisite remain open.
[Verification and bounded probe](../../reverse/attempt_support/playerlist-stale-ctor-marker-20261030-codexb5.md).
