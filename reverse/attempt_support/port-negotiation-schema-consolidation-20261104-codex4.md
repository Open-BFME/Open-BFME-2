# PortNegotiationSchema consolidation, 2026-11-04

Inspected base: `7835790240`; worker: `yasinschroeder-codex4`.

The fresh in-memory TU map approves the Common/PortNegotiationSchema.cpp
group under a provisional name. This grouping approves consolidation; it does
not establish an original EA filename. The supported Common-subsystem naming
planner was run before selecting the group. No existing obstacle entry names
this unit. The previous merge attempt accepted no donors.

## Prerequisite reconciliation

- Retail reset at 0x005DB9E4 clears 8x8 state/action tables at +0x18/+0x118.
  Ping elements occupy +0x218..+0x718; setters at 0x005DB885/0x005DB8F7
  establish their five dwords. Timestamp and retry accesses establish the
  arrays at +0x718 and +0x838. Unused storage remains padding. These are target
  layout facts; no donor layout or filename is claimed.
- The six schema sources now share compatible complete private views, with
  existing field accesses renamed to the seed's spellings. The listener-list
  and record views were reconciled with `tu_views.py`. No bodies moved yet.
- `./build.sh` on the seven edited sources: 22/22 functions, one data row,
  one literal and one import verified. The EH funclet label renumbering was
  verified against its parent metadata. All eight candidate sources pass
  `find_declared_unmatched.py`.
- Link preview: seven of seven units pass, 1,448/1,448 authored bytes, using
  the fetched local index dated 2026-11-03 20:03 at `8661f15284`. This is a
  preview preservation check, not a new census or headline linking gain.
- A trial using standard `<new>` introduced EH cleanup into helpers
  0x005DBD4F (41 bytes) and 0x005DBD78 (40 bytes), failing their byte checks.
  It was reverted; the original placement-new definition remains.

## Merge boundary

The verified dry run accepts the seed and five schema donors: getTimeToSendPing,
Rva005DBCA6Get, Rva005DBEEB, sentAPingPacket and handleNegotiationResult.
Together they contain 21 rows and 1,267 authored bytes, removing five files.
The two STLport donors remain separate: PAVectorEraseRange003AF7A0 encounters
duplicate placement new; StlportVectorRva005DBCD1Overflow encounters the Windows
`max` macro in its template include environment. Nine mixed donors are untouched.
Next template work must preserve the local placement-delete/EH contract while
reconciling include environments; neither rejected donor is approved for a
manual move.

The seed's existing ms-header queue finding for `<new.h>` remains debt. No
identity/data finding was retired, no alternate-name alias was removed, and
no pin or hatch was added by hand.

## Applied merge and batch audit

After prerequisite commit `27487a8c3a`, `tu_skeleton.py --merge` applied its
verified six-file composition: five source files removed, eight function-source
fields and one data-source field repointed, and 21 rows retained. Only source
fields in the committed TU map changed; the map was not regenerated. The tool
refreshed the header queues; the same `<new.h>` finding survives. No protected
baseline transfer or retirement was needed.

Post-merge `./build.sh` passes 21/21 functions, the data row, compiler literal,
import and parent-verified EH funclet. `check_csv.py` still reports 99,433
function rows and 2,269 data rows; the declaration check remains clean. Current
link previews pass for the merged TU (1,267 authored bytes) and retained overflow
donor (181 bytes), preserving their combined 1,448-byte scope. The supported
composition's link guard also preserved the previously census-linked candidates.

The path-consumer audit covers `7835790240` through the prerequisite commits
and this staged merge. One combined search for all five removed basenames
covered tools, hooks, workflows, Code, reverse registers and documentation.
There are no active tooling, configuration or source-include consumers to fix.
The function/data ledgers, TU source fields, body owners, header queues and
identity/data/hatch baselines no longer name the removed donors. Remaining
mentions are intentional: merged-source provenance comments, naming basis/vote/
agreement history, census `link_status.csv`, and attempt evidence. Census records
were not rewritten to imply a new measurement. Relative includes stay in the
same Common directory. No alternate-name alias was removed.
