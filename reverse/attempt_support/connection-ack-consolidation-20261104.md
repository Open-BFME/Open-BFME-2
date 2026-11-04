# Connection ack-forwarding profile and TU consolidation

Target facts: the full 44-byte body at 0x0058BD4F loads packet +0x24 into
EAX, then +0x20 into ECX, before pushing both and calling the byte/word
accessors and processAck. The original direct argument expressions produce
42 bytes under the region default because /O1 uses PUSH [memory]. Reading
executionFrame then timestamp into ordinary local variables reproduces the
retail MOV/PUSH sequence under /O1 /arch:SSE /G7. No field layout, public
name, pin, alias or function extent changes. These locals describe existing
forwarded arguments; no donor-name or original-layout recovery is claimed.

flag_defaults.py propose confirms the default keeps the complete row and
removes the tool-owned -O2 -arch:SSE override. Baseline ./build.sh on both
sources passes 22/22 rows; repaired standalone forwarding passes 1/1.
Its strict reusable provider receipt passes and ordinary preview retains
LINKS, 44 -> 44 authored bytes against the 2026-11-04 11:27 census at
3a8028f34e. This preview is not a new census measurement.

The supported GameNetwork evidence planner was read; its stale map is not
used as approval. tu_skeleton rebuilds the map in memory and approves 20
rows. Two already-hosted COMDAT rows remain with their source. Before this
repair, --merge --dry-run refuses the donor because carrying its override
loses 17 destination rows. Afterwards, it accepts both sources, keeps all
22 matched rows and passes LinkGuard for both census-linked units.

The prior multi-donor class-view conflicts no longer block this two-file
composition: the Connection.cpp class already declares rva0058BD4F and the
supported composer keeps that complete view. Canonical header adoption for
NetCommandList and NetFrameCommandMsg remains separate debt; GlobalData already uses its shared header.

## Prerequisite and verification scope

The flag repair is `8c4a35e59a` and the naming-binding prerequisite is
`4d49b7569e` (runner delivery identities; later fleet landing may have
different SHAs). The flag commit's mandatory full gate passed all 99,442
then-current function rows and 2,269 data rows, reference, pin, module and
source-claim checks and the no-op patch. Upstream subsequently added rows;
this is the recorded scope of that full gate, not a new measurement.

The first applied composition passed 22/22 rows and all three float/four
import references. Six funclet labels were independently verified through
parent EH data. Comparing external COMDAT digests (including normalized
relocation targets) from the separate, repaired objects with the composed
object yields 53 before, 53 after, 53 identical and no additions or removals.
Strict reusable provider verification passes. Ordinary preview reports
LINKS with 1,688 authored bytes, the previous destination's 1,644 plus the
44-byte donor. This is ownership moving between units, not added linked
coverage, and no census or runtime result is claimed.

## Registers and path consumers

The donor and destination have no data-check or code-identity baseline keys.
The destination's two surviving header-queue entries remain; no retirement
is claimed. The owner tool refreshes the header and Microsoft-header queues.
There are no Microsoft-header rows for either unit, and both data-ledger
owners remain in Connection.cpp. The existing alternatename hatch remains
unchanged. Only the moved row's source column changes in the committed TU
map; approval is checked against the freshly rebuilt in-memory map.

The outgoing path audit covers the inherited W3DShroud absorption, the
BuildingBehavior obstacle-ID adjustment and this Connection absorption,
through the staged tree on `4d49b7569e` (base `a68e83af11`). Combined searches
for old paths/basenames cover tools, hooks, workflows, source/includes, root
configuration, registers and docs; no directory changes. No tooling/include
path needs editing. The live naming source binding is handled by the
[supported repointer prerequisite](consolidation-naming-bindings-20261104.md).
Voting and naming-outcome logs remain immutable historical evidence;
measured link_status, prior attempts, class-contract outlier snapshots,
DOTManager's comparison and merge-provenance comments retain old paths.
The shroud audit and its existing remaining prerequisites are preserved.

## Applied result and remaining link audit

Reapplying with the supported repointer again accepts both files, rejects
none and passes the census-linked guard. The final TU passes 22/22 rows,
53/53 identical COMDATs, the frozen-file check, tu_ownership and check_csv
(99,443 current rows). The `msg` naming record changes only its source to
Connection.cpp; header/data/identity/hatch registers have no final merge
diff. The result removes one source file.

The complete staged-tree batch audit exits 2, INCONCLUSIVE: its census index
is at `3a8028f34e` and predates the outgoing base; five since-index source
objects lack current receipts, first Common/GapBodiesGE31.cpp. The staged
scope includes Connection.cpp, W3DShroud.cpp and the inherited
BuildingBehaviorModuleDataDtor identity repair and their affected consumers.
No OMITTED-provider failure is reported before that receipt boundary. Carry
this full scope, plus the prior Common/0CreateAHeroManager21FE49.cpp consumer
from the old handoff, into the next scheduled census. This is unverified
batch closure, not a clean batch verdict. No scheduled census, full-image
link or smoke runner was started.
