# InGameUI consolidation audit, 2026-11-08

The supported tu_skeleton merge absorbs only Rva002A1B07Ctor.cpp into
GameClient/InGameUI.cpp. It moves one 22-byte code row and its already-approved
TU-map source cell; no regenerated map is committed. The combined predicted
linking extent is conserved at 266 bytes (244 + 22), while source files fall
by one. No new exact coverage or working game image is claimed.

Normal verification: nine code rows, two data rows, one compiler float; frozen
check retains 33 legacy unclaimed definitions; EH has zero affected rows;
check_csv passes; fresh MS-header scan has zero findings. The merge tool
refreshes header and Microsoft-header queues. Neither source has a header,
identity or data baseline key needing transfer. The three existing host data
ledger owners stay at this path; no donor data owner or fold proof moves.
The owning hatch tool reports no net register change on this refreshed main.

Provider proof: the seven previously strict host borrowed-owner twins remain
matching, and ordered CRT records agree. Donor cleanup first removed seven
redundant emissions. The final host still emits a 19-byte list-constructor
copy; the indexed first provider GameLogicDispatch.cpp at rank 1638 retains
retail's exact 18-byte body. The host is rank 6723 before/after, the removed
donor was rank 6813, and the other rowed owner is rank 5223. COMDAT ANY keeps
the first provider. This is a selected-provider proof for the indexed world,
not equality of the differing copies. The 22-byte moved caller calls the
native _List_base provider directly. Carry unknown newer providers into the
outgoing batch audit and next census.

Whole pending path-move audit: only this one absorption. A combined search
for the old path and basename across tools, hooks, workflows, Code, docs and
reverse finds no active include, build rule or source registry needing repair.
The remaining Code mention is the merge's provenance comment; obstacle and
attempt packets are historical evidence; private_probe reads git history at
5d3b84e454; frozen rows retain that historical source. reverse/link_status.csv
is the recorded census snapshot, refreshed only by its measurement owner.
No historical references were blindly repointed.

Remaining 113 donors still need the flag/header prerequisites reported by the
fresh trial; this single merge does not adopt the whole InGameUI class.
