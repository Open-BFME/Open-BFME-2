# W3DPropDraw native-interface preflight

Served two-table175B cohort at7CD328. Unchanged normal baseline passes10/10
code rows plus its48-byte field-parse data row. No source change is retained.

Straight header_adopt DrawModule fails its data-row gate; private preparation
also proves donor Common/Module.h already defines Module and DrawableModule,
so adding canonical DrawModule.h collides on both class definitions. This is
a real include-chain conflict, not a demonstrated false reject.

Replacing the donor preamble with canonical W3DPropDrawClass, DrawModule,
BfmeModuleData, INI and FieldParse headers preserves8/10. The two misses share
ModuleData teardown: out-of-line base cleanup replaces native inline Snapshot
restore and changes the unwind location. Using the established row owner's
inline ModuleData destructor that invokes canonical Snapshot restores10/10.
The native data table's slot14 model-name copy (CED14,16B) and slot17 this
return (47A6A9,3B) then compile exactly:12/12 in private, all existing rows
preserved. Neither callback is admitted and no source or ledger is changed.

Landing the complete view still needs canonical W3DPropDraw callbacks to be
provided under their declarations, replacement of the static-rvaCEEE6 name
provider with the native virtual key declaration, and the corresponding
consumer/link audit. Shared B3FD0,47A69C,47A699 and the deleted_rows register
are claimed by another contributor; no lease or name-retirement workaround
is taken. The real-link bridge pass test is still open.

Scratch evidence: continuation-20261117d-prop-adopt-private.json,
prop-minimal-probe.json, prop-minimal-diffs.log and prop-lifetime-probe.json
in build/. Canonical headers were not edited.
