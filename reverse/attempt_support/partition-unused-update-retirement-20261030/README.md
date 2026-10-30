# Retire obsolete PartitionData touched-cell implementation

The donor-derived PartitionData::updateCellsTouched body is 426 bytes and has
only a .debug$F incoming relocation. Its two materialized GhostObject getters
are also debug-only, and no other indexed object touches any of the three
names. The existing facade macro already leaves the real friend method
declared-only; it does not emit bfmeZhInline_friend_updateCellsTouched.

Target facts: the current 37-byte friend_updateCellsTouched at 0x0073B250
unlinks the dirty node, then reaches the already-rowed 1,158-byte
ShroudManager::Data::UpdateCellsTouched at 0x0073AD90. Both current owners
verify byte-exact. The old pin gave that address the obsolete donor method's
different name and layout. Donor semantics do not identify the target body.

Remove the unused donor body, its stale present-unmatched marker and the
false pin. The hatch tool lowers exactly those two register keys. No native
row or body is lost. All four Partition rows and the two witness units pass
normal checks (12 rows total). Private/final objects preserve all 561 retained
external code bodies and relocations, all remaining loadable definitions and
all remaining non-debug section contents/relocations. Only the unused three
definitions and sole onPartitionCellChange undefined reference disappear.

The link preview is scoped: Partition loses this duplicate/nonretail selected
provider and the one unresolved name; other unrelated blockers remain. The
existing facade and native owner retain their linking bytes. This is two
escape-hatch retirements and blocker cleanup, not a newly recovered body or
headline census gain. proof.json carries object hashes, raw debug-reference
evidence, retained-runtime invariants and independent target witnesses.
