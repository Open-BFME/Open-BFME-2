### CreateAHeroManager owned-pointer cleanup view (2026-10-30)

At base `69fa252df2`, the destructor's `+174` member still used the older
tree-shaped alias, although its constructor and native cleanup establish an
owned pointer vector with a flag at `+180`. The destructor now reuses the
constructor unit's existing `Rva0040A530` view and provider. Its complete
279-byte body is unchanged; only the member-destructor relocation spelling
changes at the same native `0x0040A603`. Strict four-source preparation
passes 66/66 rows; paired EH is EXACT 8. All four sources preview LINKS,
retaining 2,258 authored bytes against `6fe1089c24` (2026-10-30 04:25).

The staged batch audit is INCONCLUSIVE on its older baseline and a missing
current `Common/AIBuildable.cpp` consumer receipt. Full affected-consumer
selection and loss checks remain unverified; carry the destructor,
constructor, pointer helpers and wider consumers into the next scheduled
census. No linked-byte gain or debt retirement is claimed. The 81 proposed
main-code placements still lack target TU evidence; the separate 81 approved
unwind/handler placements do not approve them. No source paths move.
[Target facts, object comparison and placement boundary](../../reverse/attempt_support/createahero-owned-vector-20261030-codex3.md).
