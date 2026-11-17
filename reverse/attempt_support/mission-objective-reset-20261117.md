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
