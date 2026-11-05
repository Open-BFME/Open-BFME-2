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
