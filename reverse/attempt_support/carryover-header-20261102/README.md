# CarryoverUnit shared ABI view and transfer binding, 2026-11-02

Target facts: native copy 1EB79E and default constructor 37DF2C install
table BDF158. Its four slots name deleting destructor, loadPostProcess,
GetSnapshotName and protected xfer. The destructor restores Snapshot after
destroying +94 and +4. Existing native code establishes extent AC and offsets
+4/+8/+C/+10/+90/+94. Native live-temporary/derived-base assignment evidence
is recorded separately in carryover-assignment-20261102.

The new header is a shared ABI/storage view, not a recovered original header.
The 128-byte block and 24-byte tail remain opaque. It must not replace typed
lifetime-bearing members in their actual constructor/copy/destructor providers.
Snapshot's existing name-slot interface provides four slots; a legacy crc
include context is explicitly refused rather than silently adding a fifth.
No donor path or original member type is inferred from size or matching bytes.

Six consumer sources adopt the view through header_adopt_lane. All 30 native
addresses pass. An independent private build compares immutable candidates
with published HEAD 66b01952ac originals: all 74 complete external code and
553 external data definitions and symbolic relocations are unchanged. The
entire non-debug runtime graph is identical after resolving only compiler-local
EH label renumbering and .sxdata symbol indices; external references remain
exact. Both ArmySummaryEntry table groups and FieldParse arrays are checked.
The original-text hashes and object hashes are in proof.json. Scratch object
paths identify the local experiment, not committed build artifacts.

The Common provider declaration now spells xfer protected, matching its real
107-byte owner in SnapshotXfersBfme.cpp. Its table slot directly names that
owner, so the redundant public-to-protected linker alias is removed. All 16
complete Common code bodies are unchanged; the only runtime-graph change is
the expected table reference. The refreshed ArmySummaryEntry direct caller
also names the protected owner. The index has no outside public-name consumer;
source search finds no explicit public-name reference. A fresh strict provider
receipt resolves the stale-source receipt discovered during the independent
review. The getter alias and all old vector helpers remain intact.

Normal six-source checks: 30/30, two data rows, five literals; frozen checks
pass. The seven changed sources pass strict 41/41 and all six EH graphs.
All seven preview LINKS at index 984a4cdc4d (08:35 Nov2). The apparent 84-byte
increase is the already-published folded assignment, not new global coverage.
The owning hatch tool shrinks alternatename 2834 -> 2833. The owning header
accept tool passes all six users. No source path moves or ledger retractions.

Seven sources remain original and queued: ArmySummaryEntry/Rva0037DF2CCopy
need Snapshot vftable declaration reconciliation; Common CarryoverUnit and
SnapshotXfersBfme need actual typed block/tail recovery; GameLogic CarryoverUnit
needs its earlier crc include context reconciled; LinearCampaignAddCarryover
has an STL include cycle; LinearCampaignManager needs a separately coordinated
provider/consumer migration. Contract ambiguities remain evidence, not claims
that the opaque storage has recovered its original names or types.

Global consumer clearance remains for the outgoing batch audit and next
scheduled census. No nightly, link-cycle, boot or game smoke was started.
