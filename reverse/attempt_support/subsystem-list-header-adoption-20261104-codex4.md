# SubsystemInterfaceList header adoption, 2026-11-04

Inspected source revision: `2ec844f1fa`.

The default picker claimed the main System/SubsystemInterface.cpp TU and five
candidate donors. Its initial merge dry-run accepted none: incompatible list
views, ModuleData specialization declaration ordering, and a competing
AsciiString header prevented composition. The committed TU map is stale;
tu_skeleton rebuilt its approved assignments in memory. No map was committed.
The consolidation planner snapshot was generated under build/consolidation.

## Completed adoption

Four donors now include the existing canonical
Code/GameEngine/Include/Common/SubsystemInterfaceList.h:

- Common/SubsystemInterfaceListAdd.cpp: 1 code row, 71 bytes.
- Common/SubsystemInterfaceListRva001B4FE9.cpp: 2 code rows, 77 bytes.
- Common/SubsystemInterfaceListRva001B505F.cpp: 3 rows, 235 bytes.
- Common/System/SubsystemInterfaceListRemoveSubsystem.cpp: 3 rows, 171 bytes.

Target facts: the canonical header documents the three vectors at +0, +0x0C
and +0x18 and their observed access patterns. The entry walks now use its
pair first member, and the pending/collected walks use its actual fields.
The former removeSubsystem view incorrectly described the unused first vector
as a pointer vector; the canonical header supplies its real eight-byte entry
storage. This does not assert recovered names for address-token methods.

The registration method preserves its existing ModuleData pointer push_back
specialization through a cast of the canonical pointer vector. ModuleData is
the existing helper's identity, not a claim that subsystem objects are modules.
An early local vector reference moved the +0x0C address calculation ahead of
the +0x10 end load and changed bytes; accessing end/begin through the canonical
member and casting only the push_back receiver preserves the retail order.
The dispatch-only virtual call views are unchanged and emit no vtables.

## Verification and debt

- Normal ./build.sh verification: 9/9 rows exact across the four files.
- find_declared_unmatched.py: all defined functions already matched.
- header_adopt_lane.py accept --class SubsystemInterfaceList passed each
  file and retired exactly four header_queue.tsv rows through the owning lane.
- link_check.py --prepare-current: four explicit providers byte-verified with
  strict reusable receipts; no census/index/status changes.
- Joint ordinary preview, census a62ac1c10b (2026-11-04 07:28): all four LINKS,
  preserving 71 + 77 + 235 + 171 = 554/554 authored bytes.
- eh_verify.py on the notification donor: EXACT 1; no nonexact or missing
  object. Its 0x007694F7 label was renumbered from $L5493 to $L6435; parent
  EH data verifies that same retail location without a ledger/pin change.
- data_check.py shadow: four sources, zero findings. Converged enforcement:
  eleven addresses, zero second names, zero unjudged rows.
- tu_ownership.py --staged: exit 0, no findings.
- check_csv.py: OK, 99,440 function, 9,336 symbol and 2,269 data rows.
- No source paths, function rows, pins, aliases, shared headers or other debt
  registers change. There is no file-count or new census-linking gain.

The staged-tree batch audit exits 2:

    INCONCLUSIVE baseline: index at a62ac1c10b, outgoing base HEAD
    INCONCLUSIVE: affected consumer lacks current receipt:
    Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp

Full selected-provider/consumer preservation remains unverified. Include the
four adopted providers and their affected consumers in the next scheduled
census/current-receipt audit; no direct census or smoke runner was invoked.

## Main TU prerequisite: trial reverted

Replacing the seed's private list class with the same canonical header,
using m_xfer instead of m_24 and a BfmePod8 vector view of m_subsystems in
rva001B51C0, preserves the ordinary body shapes but fails four of sixteen rows:

- Constructor 0x001B4FB8: the third vector-base constructor (+0x18,
  vector<void *>) binds a different callee from retail's 0x00211E58.
- Destructor unwind 0x00769509: vector<pair<SubsystemInterface *, void *> >
  destructor has no admitted symbol binding to its retail target.
- Destructor unwind 0x00769511: vector<SubsystemInterface *> destructor has
  no admitted symbol binding to its retail target.
- Destructor unwind 0x0076951C: vector<void *> destructor binds a different
  callee from retail's retained vector-destructor copy.

These are callee-identity prerequisites, not evidence that the canonical
layout is wrong. Do not mask the failures or add pins by hand. Investigate
existing row owners and prove the complete helper bodies/relocations before
any naming reconciliation or tool-admitted fold binding. The seed was
restored byte-for-byte; its normal build passes 16/16 again. Its header-queue
row remains. The transient SubsystemEntry8 formatting from tu_views was
also reverted/replaced; no separate formatting-only cleanup is retained.

After reconciling the seed, retry the ordinary tu_skeleton merge. The
notification donor also retains its known ModuleData specialization-hoisting
prerequisite. LoadIniFilesFromLegend retains its competing AsciiString include
graph and needs a separate verified prerequisite repair. No mixed source was
split or donor moved in this pass.
