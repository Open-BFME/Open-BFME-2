GameWindowManagerScript parser composition prerequisite (2026-11-05)

Target facts: the seed dispatch table names parseHeaderTemplate and parseText.
Their existing matched providers are the two corresponding parser satellites,
retail RVAs 0x00315CCF (46 bytes) and 0x00315D6D (68 bytes). The seed also retained
legacy static copies, producing C2084 when tu_skeleton composed the providers.
This is duplicate-body cleanup, not restoration of missing coverage.

Remove those seed copies and give the existing providers external linkage. Keep
the same names, bodies, anchors, compiler flags and ledger ownership. Neither
this repair nor the pending consolidation removes the seed's link-wide strcpy
alternatename. No donor source or layout attribution is inferred from placement.

Verification: ./build.sh for the three changed sources passes 35/35 code rows,
29 literals, two empty-string references and five imports. All three
find_declared_unmatched checks pass. link_check before and after reports all
three LINKS, 3,070 -> 3,070 bytes, against census c95fcfcfcd (2026-11-05 05:17).
These are scoped previews, not new census figures. The seed's unreferenced
_STL::_Construct<GameWindow *> register-allocation diagnostic is unchanged.

Next: use tu_skeleton's fresh in-memory approval map and byte/link-guarded merge;
retain the separate SubsystemInterface, enum and Rva0031763A view conflicts as
unmerged prerequisites. The original tu_views pass applied no reconciliation.

Composition follow-up: the first dry run still accepted no donors. Its seed
could not resolve the newly external parser references against the census's
file-local providers. Donor trials also exposed conflicting WinInstanceData
views with neither parser field. Giving the seed duplicate external providers
instead is a real duplicate-definition regression and was rejected by the
three-unit link preview; that variant was not committed.

The verified prerequisite now keeps both parser functions static, uses the
retail-proven offsets 0x194/0x188 through AsciiString pointers, and gives seed
and donor identical function definitions. tu_skeleton already deduplicates
identical function bodies. This removes the two private WinInstanceData
classes without adding a new view and lets the seed retain local providers
while donors remain separate. Normal build again passes 35/35 rows and all
references; the three-unit preview is again LINKS, 3,070 -> 3,070 bytes. The
known const Object-list iterator definition divergence remains in shadow
(as already recorded in the GUI/pooled-list obstacle), not retired debt.

Publication of the first prerequisite was initially refused by an earlier
queued identity retirement: Upgrade.cpp lacked a current provider receipt.
Its normal build passes 27/27; repair_queue verify-removed over the entire
outgoing range then passes without editing or retiring any register key.
