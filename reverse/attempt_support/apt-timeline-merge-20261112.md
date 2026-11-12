# AptTimeLineStats consolidation preparation

Inspected at d59318e468d, 2026-11-12. Approved destination:
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineStats.cpp.
Donor: Code/GameEngine/Source/Common/Rva005BEA22Dtor.cpp.

The supported planner records original-path/case, compiler-setting and
declaration prerequisites. Its hints do not approve a move. The fresh
in-memory TU map used by tu_skeleton approves both donor rows for this TU:
the 78-byte destructor 0x005BEA22 and its 10-byte EH handler 0x007A025D.
The first dry run accepts no donor, with a byte mismatch. The mixed
GapBodiesSeat10O1.cpp fragment stays outside this merge.

## Native allocator boundary

Retail's destructor deletes the +0 object through its virtual lifetime,
calls global operator delete at 0x0002FD60 from 0x005BEA48, and clears it.
At 0x005BEA53 it writes EH state -1, then calls game allocator _free at
0x00030830 from 0x005BEA5D for the buffer at +4. This is not a CRT import.
Handler 0x007A025D refers to FuncInfo RVA 0x0095718C with one unwind state;
cleanup 0x007A0252 destroys that buffer.

The donor suppressed _CRTIMP around stdlib.h and used C-linkage free under
/EHs. The destination already includes stdlib.h, so the donor's later
suppression cannot change its imported declaration. Also, /EHsc lets the
compiler assume C-linkage calls cannot throw, removing the state boundary
retail retains. The seed already uses the ordinary C++ declaration
Rva00030830FreeAllocation(void *) for this same native wrapper. Use it in
the donor too and remove the temporary CRT-header macro wrapper. This is
a compiler-visible exception boundary, not a claim that freeing memory
actually throws.

The helper pin and PingThread's existing alternate already resolve to
GameMemory's 17-byte _free owner at 0x00030830. No pin, alternate or hatch
is added. Both donor rows match independently under the donor's original
settings and the destination's effective settings. Normal build passes 2/2;
strict reusable preparation passes. Both donor and destination predict
LINKS against local index aa7acf764d: 78 -> 78 and 4,101 -> 4,101 bytes.
The unreferenced allocator-proxy COMDAT diagnostic is not a blocker.

The destructor symbol stays unchanged for AptTimeLine.cpp and
FamilyDeletingDtors12.cpp. The buffer destructor has no outside indexed
consumer. Actual merge, full outgoing path audit and post-merge verification
follow this preparation; no file reduction is claimed by this commit.

## Records carried with this source change

The served Microsoft-header item for AptMpGameSetupRva0043DC40.cpp was
already satisfied by upstream source: it includes the real headers and
the owning fresh audit finds zero local Microsoft declarations. Normal
build passes its one row. ms_header_audit scan --write-queue removes the
stale inventory row; no source change or conversion credit is claimed.

The local index refresh at aa7acf764d rereads 7,654 objects, drops 18 removed
units and preserves census provenance 4ba87ee6df (2026-11-12 16:28). All eight
sources from the four preceding published repairs still predict LINKS
against it. This is an updated local prediction, not a new real link,
census or game-run result. A subsequent pull to d59318e468d adds one
source-path difference; no duplicate or provider-loss claim relies on it.

## Applied merge and outgoing audit

After preparation de522953d3, the supported planner was refreshed and the
second dry run accepts the seed and donor. tu_skeleton --merge reuses that
verified composition, deletes the donor and retains all 78 rows. The mixed
GapBodiesSeat10O1.cpp fragment and the generated 0x007A0252 funclet stay in
their existing owners; neither is hand-split or silently claimed.

Normal post-merge build passes 78/78, four strings, one float and one import.
The frozen-file check passes; strict reusable preparation passes. EH verify
reports six EXACT records, zero missing or baselined failures. Own link_check
reads LINKS: destination 4,101 -> 4,179 bytes; the donor's 78 bytes transfer,
so combined coverage remains 4,179. Its unreferenced proxy-deallocator
length diagnostic stays nonblocking. The MS-header owning scan is clean
and refreshes the destination inventory without adding a queue row.

One complete outgoing path audit covers d59318e468d..de522953d3 plus this
staged absorption. All 81 COMDATs are unchanged: 79 from the seed and two
from the prepared donor, with no added or removed provider. The original
destructor symbol still serves AptTimeLine.cpp and FamilyDeletingDtors12.cpp.
The two function rows and two tu_map rows change source columns only; TU
assignments, confidence and evidence are unchanged. The map is not regenerated.
The EH handler follows its parent destructor at 0x005BEA22.

No old-donor code/data/gate/hatch debt or header/MS-header queue key needs
transfer. The destination's existing BfmeStringRecord005DDD40, Player and
ScoreKeeper header entries remain open and accurate. Active includes,
tools, hooks, workflows, configurations and source registries need no
additional path change. Intentional old-path mentions are the merged
provenance comment, dated obstacle/attempt evidence, historical patches
and coverage reports, and link_status.csv's last-census snapshot. They stay.

This merge removes one source file. It makes no new byte-coverage, census,
bridge-retirement or game-run claim. Current-input link preview handles the
deleted donor; the index's unrelated one-path difference is not used as a
provider-loss or duplicate finding.
