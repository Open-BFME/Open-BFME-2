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

Import-call prerequisite: merged parser trials emitted direct strtok calls under
the seed flags, whereas retail uses the DLL import. Qualifying both definitions
through the existing NativeScriptCrt import declaration makes their cached
object bytes and relocation names identical. Normal builds pass 35/35 rows.
The fresh merge dry run accepts the seed and both parser donors (35 rows) and
passes its census-based link guard. Applying requires committed donor changes
before git rm; its partial path repoints were restored before this prerequisite.

Final composition at parent 9149f9d545: tu_skeleton --merge accepts the seed,
parseHeaderTemplate and parseText, retaining 35 rows and deleting two source
files. Only the two source columns in the approved TU map change; no map is
regenerated into the commit. Both RVAs retain one ledger owner and their sizes.
No matching or census gain is claimed. The normal merged build passes 35/35,
29 literals, two empty-string refs, five imports and six verified funclet pins;
find_declared_unmatched and check_csv pass. Data shadow/converged checks report
zero findings. The merged unit preview is LINKS, 2,956 -> 3,070 bytes against
c95fcfcfcd (2026-11-05 05:17), now including the two absorbed rows; combined
coverage remains 3,070 bytes. The unreferenced GameWindow* _Construct register
allocation diagnostic remains. The merge guard checks the original 16 census-
linked donor units and their affected consumers without a proven loss. The
mandatory outgoing-batch audit and census confirmation remain the publisher's
and scheduled census's checks; these previews do not prove whole-image closure.

Consolidation audit across b4c9b2d8a8..9149f9d545 plus this merge: these are the
only outgoing source deletions/path moves. Combined old-path and basename
searches cover tools, hooks, workflows, sources, build/config, documentation and
reverse registries. tu_skeleton repoints functions.csv, tu_map.csv source
columns and doxygen sources.cfg; the Doxygen parser-group file now names the
surviving TU once. Remaining old-path mentions are tool-emitted provenance
comments and the historical link_status census (intentionally retained).
No removed donor occurs in body_owners, active debt/header/MS-header registers
or fold-proof inputs. Header/MS-header reports were refreshed by tu_skeleton;
no key is retired or dropped. The seed's strcpy alternatename and existing
WindowLayoutInfo marker remain, and hatch totals are unchanged. No global,
class or pin identity changes. Object-byte/relocation comparison before merging
proved both selected parser definitions identical; the final matched build
and link guard verify their selected providers after composition. The known
const Object-list iterator divergence remains separate shadow work. A fresh
GUI consolidation planner snapshot passes its freshness check after the merge.

Remaining 13 rejected donors: canonical SubsystemInterface adoption (and the
seed's FontLibrary/GameText/NameKeyGenerator declarations) precedes font,
tooltip-text, name, WinClass, callbacks, createGadget and WindowLayoutInfoLoad;
DrawData has a different duplicate legacy parseDrawData body; setWindowText
has a GWS_PUSH_BUTTON enum conflict; Rva0031763ACtorDtorAssign needs its actual
class/list layout. The mixed parseLayoutBlock source is not moved. Required
header adoptions reported by the merge planner remain createGadget: GameWindow,
GameWindowManager, ListboxData; setWindowText: GameTextInterface, GameWindow,
GameWindowManager; WindowLayoutInfoLoad: GameWindowManager. Reconcile and
verify these prerequisites in their own commits before another guarded merge.
