# AssistedTargetingUpdate native profile prerequisite

Target facts: factory allocation is 0x20. Constructor 0x486E8D/84 and
complete destructor 0x486E18/25 install the same primary C4AF64,
Behavior BEFF90 and Update C4B1E0 tables. Their native extents are 13/47/3
slots, independently checked in table-slots.json (63/63 exact).

The constructor now uses canonical UpdateModule and compiler-owned tables.
Its existing scalar callback/constructor cleanup bytes remain exact. The
supported rename.py class --fold reconciles Rva00486E18 lifetime rows with
AssistedTargetingUpdate using these constructor DIR32 bindings. Original
names/layout outside this scoped native view are not claimed recovered.

Native xfer 0x4DF81B/27 performs Version1 then UpdateModule::xfer. add_match
admits the genuine ICF member while retaining the old owner and fold-proof.
The main file uses the same canonical 0x20 class view and no longer emits
the donor CRC/dtor/transfer profile or laser-cache fields. Two obsolete
present-unmatched markers retire through hatch_counters (2243 -> 2241).

Validation: normal build.sh 69/69 across main7, constructor3, mixed59;
key and constructor EH graphs EXACT; normal/private code and properties
agree for both canonical views. Three-source link_check predicts LINKS for
all three, 1919 -> 1929 bytes. This is a preview, never an actual image result.
header_adopt_lane accept was initially blocked when only the constructor
was previewed. Coordinating all three changed sources accepts main+ctor and
passes both canonical sources; the mixed residual remains private. The commit
hook rechecks a retired queue entry individually and rejects its retirement
because that check omits the coordinated sources. Restore the queue entry and
record this false reject; no header debt is retired in this commit.

No source paths move in this prerequisite. A fresh in-memory TU plan now
approves the renamed complete destructor (Z). The split dry run matches both
lifetime rows but its older index cannot resolve the new xfer/selected lifetime
binding. Commit this reconciliation and refresh the local index before the
supported split/merge; do not hand-move the bodies. Existing cached data_ledger
entries still spell old dummy table names/extents; only its owning tool can
regenerate that protected register. Main getModuleNameKey is temporarily
out-of-line to emit without a local destructor; after the supported merge,
restore its original inline compiler-owned static/guard COMDAT form.

Publication audit carried from 6ecd06cf85: INCONCLUSIVE against index e9f0686bd3,
base d815d301c27503f8a8ef8fa1753fe1629c5555f8, one missing current receipt
(AssistedTargetingUpdate.cpp). The scoped checks passed; current outside
consumers and actual real-link/census results still require later measurement.
