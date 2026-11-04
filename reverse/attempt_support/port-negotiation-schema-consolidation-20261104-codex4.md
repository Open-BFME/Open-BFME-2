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
