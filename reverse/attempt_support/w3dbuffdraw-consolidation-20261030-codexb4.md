# W3DBuffDraw module-data composition

Inspected base: `a861e89a4c`. Claimed scope: W3DBuffDraw.cpp,
W3DBuffDrawConstructor.cpp and W3DBuffDrawModuleDataCtor.cpp under
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/`.

The supported naming planner surveyed that directory. Its original-path
catalogue does not independently route these rows: it labels these files
unresolved and flags the existing data owners and include context. Placement
approval comes from tu_skeleton's freshly rebuilt in-memory TU map: eleven
approved rows, two whole donors and the mixed W3DDrawNameGetters.cpp file.
No regenerated map is committed. No donor path is claimed as target evidence.

The initial supported merge rejects both donors. The draw constructor has a
DrawModule base absent from the seed's partial W3DBuffDraw view. The module-data
constructor declares its vtable as an external raw array, conflicting with the
seed's polymorphic class. tu_views independently reports both conflicts.

## Module-data prerequisite

Reuse the seed's existing eight-byte polymorphic base, AsciiString at +8 and
flag at +12 in the constructor donor. Ordinary member initialization replaces
the explicit vtable store, intrinsic barrier and raw-word clearing. The seed
gains only the constructor and static parser declarations. This retains the
existing partial base contract; it does not establish a complete retail table.

Target facts: the complete constructor at RVA 0x000CEE4C is 17 bytes, the
destructor at 0x000CEE5D is 54 bytes and the parser at 0x000CEE93 is 17 bytes.
The existing field table has ModelName at +8 and PreDraw at +12; the rowed
factory at 0x00064C94 allocates sixteen bytes. The compiler reports the same
sixteen-byte class and field offsets in both reconciled sources. Existing
destruction releases the +8 string through native 0x00036410. No name,
boundary, pin, global identity or code-generation switch changes.

Checks:

- Normal and strict reusable preparation pass all eight rows and the 48-byte
  data row across the seed and module-data donor. Both EH graphs remain EXACT.
  The initial three-source build passes 9/9 rows.
- Every existing external COMDAT byte-and-relocation digest is unchanged:
  nine seed copies and four constructor/parser copies. The input union grows
  from thirteen to fifteen only through the implicit AsciiString and partial
  base constructors. The donor now emits six other copies already in the seed;
  all agree. The vtable becomes locally defined and the donor references the
  existing destructor; no existing definition disappears. Scratch objects and
  detailed comparisons are in build/w3dbuffdraw-consolidation-20261030-codexb4/.
- Frozen-file and class gates pass. The owning Microsoft-header analysis finds
  both files clean; neither has a class-header or Microsoft-header queue row.
  Shadow data checks find zero findings; converged checks judge eleven addresses
  with no second names or unjudged rows. No debt register is retired.
- Census-only and ordinary paired previews both retain 2/2 LINKS and 205
  authored bytes against index 12b9e7a7c0 (2026-10-30 10:11).
- The supported merge probe now accepts the module-data donor and preserves
  eight rows. The draw constructor still needs inheritance/interface recovery;
  the mixed name-getter file and generated unwind owner stay separate.

The staged-tree outgoing audit is INCONCLUSIVE: its index is at 12b9e7a7c0,
older than this base, and the affected consumer
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry these providers and affected consumers into the next scheduled
census/current-receipt audit. Full selection/loss verification remains open.
No measured linking or image-ownership gain is claimed.

## Applied module-data merge

Prerequisite commit 48550584f9 was handed to the fleet publisher before this
merge. The supported planner was regenerated against that tree and the same
original-path/routing limits remain. `tu_skeleton.py --merge` rebuilds the stale
TU map in memory and accepts the seed plus W3DBuffDrawModuleDataCtor.cpp. It
deletes that donor, moves its two code rows and field table into W3DBuffDraw.cpp,
and transfers the data-ledger owner without changing totals. The committed TU
map changes only the two source-path fields; no map is regenerated on disk.
This reduces source files by one and puts two more rows in their approved TU.

The tool's census-linked guard protects the seed, removed donor and remaining
draw constructor. Final normal and strict reusable builds verify 9/9 rows across
the merged TU and remaining constructor, plus the field-table row. Both EH
graphs are EXACT. All fifteen external COMDAT byte-and-relocation fingerprints
in the pre-merge union survive unchanged, with no additions or removals. The
only external-symbol-set difference is the donor's formerly undefined module-
data destructor reference resolving within the merged object; its definition
remains identical. Data checks find no shadow findings, second names or
unjudged addresses, and the frozen-file and class gates pass.

The merge tool refreshes the class-header and Microsoft-header queues. Neither
has a row for these sources; the owning Microsoft-header scan confirms the
destination remains clean. No gate, data-identity, code-identity or hatch debt
key belongs to either source. The existing data owner transfers through the
tool's protected-register workflow; no debt is claimed retired.

Current joint preview retains 2/2 LINKS and 237 authored bytes against index
12b9e7a7c0: merged TU 205 plus remaining constructor 32. The apparent increase
from the seed's 171 simply includes the removed donor's 34, not a linking gain.

Tooling compatibility audit: reviewed all pending path changes from
origin/master (25a4a78293) through 48550584f9 and the staged merge. The only
move is W3DBuffDrawModuleDataCtor.cpp into W3DBuffDraw.cpp. A combined basename
and full-path search across active tooling, hooks, workflows, includes, build
configuration, registries and documentation finds no hard-coded consumer to
update. Remaining old-path mentions are the historical census status row,
provenance comments in the destination and this evidence. Active function,
data-row, data-owner and TU-map source fields all point to the destination;
no fold proof or doxygen source entry needs repointing. Old compiler receipts
are not reused as moved-source proof: destination strict preparation is fresh.

The draw constructor still fails the supported merge on the seed's missing
constructor/base contract. Its inheritance/interface recovery, the mixed name
getter and generated unwind owner remain separate work.

The merge-only staged-tree link audit is INCONCLUSIVE on the older index and
the missing current Common/0CreateAHeroManager21FE49.cpp consumer receipt.
The final complete outgoing staged-tree audit from origin/master is likewise
INCONCLUSIVE: 33 source objects lack current receipts, first
Code/GameEngine/Source/Common/Rva003A5DA0Write.cpp. This includes the already
handed-over queue/STLport changes; it does not establish a new merge loss.
Carry the merged destination, retired donor and affected consumers into the
next scheduled census/current-receipt audit. Full consumer selection/loss
verification remains open; no census gain is claimed.
