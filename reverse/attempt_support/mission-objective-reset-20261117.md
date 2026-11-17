# Mission-objective subsystem reset

Native destructor00426745 installs subsystem tableC3C408 and the secondary
Snapshot tableC3C3F8. The latter's getter00426737 returns the complete literal
MissionObjectiveTracker. Its object at+10 is deleted and cleared by the
existing96-byte destructor. The subsystem base's canonical slot9 is reset;
retail puts00426680 there.

The constructor/destructor view now overrides reset with global deletion of
that same owned object and a null store. Its complete33 bytes and call target
match the existing independent provider. Ordinary verification passes17/17
across the owner and that provider. No pin or alias was added, and the existing
fifteen owner rows, field layout and Snapshot lookalike remain unchanged.
This repairs one primary-table binding; it does not retire the three-table
workpackage or claim unique authored growth.

Snapshot probes are scratch evidence only. Deriving the old proxy from the
canonical Snapshot preserves14/15 rows but makes the forced vector-delete
alias75 bytes instead of native74; forceinline does not fix it. Removing the
obsolete forced emitter preserves14/14, and its canonical keeper passes3/3,
but the tombstone register file is held by another worker. A direct canonical
Snapshot base with the old emitter kept separately preserves15/15 in private;
that alternative still needs a consumer/table audit. None of those prototype
or cleanup changes is retained here. The generated alias, its existing pin and
the synthetic anchor remain for their owning cleanup transaction.

Private artifacts: continuation-20261117d-tracker-reset-probe.json,
snapshot-shared-probe.json, snapshot-forceinline-probe.json,
snapshot-retired-emitter-probe.json and snapshot-direct-probe.json under build/.

## Canonical Snapshot adoption and name callback

The subsequent direct-base candidate is now retained: canonical Snapshot replaces
the one-slot private base for the live owner and its adjusting-destructor view.
The constructor references the canonical secondary-table qualifier. Native
C3C3F8 slot2 supplies the six-byte MissionObjectiveTracker getter. Existing
legacy vector-delete emitter and its row/pin remain separately unchanged.
Normal build and strict provider preparation pass45/45 over all three consumers;
scoped link preview is3/3 LINKS against index8b06c04cd2 (18:16), with its one
source-change warning. File-summed preview1398B is neither a real link receipt
nor unique authored growth. Empty post-load/init/update and transfer remain
open; this does not claim complete native tables or bridge retirement.

## Remaining transfer receiver layout

A canonical Xfer/Version probe preserves all17 live owner rows and emits the
complete165-byte native transfer instruction sequence, except five field
displacements: complete-owner+10 versus retail secondary-receiver+4. Native
secondary+C and complete-owned+10 agree; no layout adjustment is hidden in
the source. Reversing base order loses destructor, two funclets, reset and
transfer (13/18 exact), so it is rejected. Neither probe is retained.
The shared empty callbackB3FD0 and deleted_rows retirement register remain
claimed by another contributor. Base and primary/secondary tables are not
complete, and no bridge retirement is claimed. Scratch evidence:
continuation-20261117d-transfer-probe.json and transfer-base-order-probe.json.

## Correct Snapshot transfer override

The earlier receiver-layout conclusion is superseded. PlayerList.h selects
BFME_SNAPSHOT_CAPITALIZED_SLOTS before Snapshot.h: the actual virtual API is
DoXfer(Xfer*). The lowercase xfer probe introduced a new primary virtual,
so its five complete-object displacements did not describe an override.
The correct DoXfer compiles all165 native bytes exactly using the secondary
receiver and its+4 owned field. No field-offset manipulation is needed.
It uses canonical Xfer/Version, transfers version/presence, and reconstructs
the16B nested object only while loading, as the existing provider does.

The second producer selects that same Snapshot surface and declares DoXfer.
All27 of its original rows remain exact. Comparing every emitted vftable
before/after changes ONLY Rva00426745's secondary slot3 from purecall to
the actual DoXfer symbol. All other table extents, bytes and targets agree.
Normal owner/second-producer/constructor verification passes46/46.

The original transfer provider, old vector-delete emitter and pin remain.
Empty post-load/init/update bindings and their held common body remain
open; no complete three-table or real-link bridge clearance is claimed.
Scratch evidence: transfer-capital-probe.json and
transfer-capital-opaque-results.json under continuation-20261117d in build/.
