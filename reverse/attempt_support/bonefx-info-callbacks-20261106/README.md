# BoneFX info hierarchy and native callbacks

Reconcile the constructor/destructor donors' three flat info records with the
seed's existing BoneLocInfo + BaseBoneListInfo hierarchy. The common base is
0x20 and each payload record0x24; onlyOnce remains one byte. Class/member names
come from the existing seed view. Target parser/consumer offsets corroborate
the common prefix; that does not independently establish retail's source-level
inheritance. No owner is renamed and no new TU placement is inferred.

The hierarchy-only trial preserves all six existing rows and both parent EH
graphs, but is not acceptable callback proof: it emits12B derived constructor
wrappers calling a47B BaseBoneListInfo constructor. The original flat donor
also emitted47B info constructors. These callbacks are passed as DIR32 function
pointers inside the matched196B parent, so ordinary parent equality conceals
their different implementations.

Decode the actual native pointers from constructor487797: offsets27/56/86 all
point at4874F4, whose existing Rva004874F4 row is23B; offsets22/51/81 all point
at48BA39, an existing5B string teardown fold. Include the existing canonical
GameClientRandomVariableInlines.h in the constructor donor. Its three zero
stores inline naturally, yielding all three exact23B info constructors and all
three exact5B destructors, with every relocation resolved. No inline body is
invented locally. The emitted19B value constructor independently matches its
existingB4979 owner and retains SELECT_ANY policy, as that owner's source does.
No private renaming, alias, pin or shared-header edit is needed.

The destructor donor needs only the hierarchy; it does not include an unused
value-constructor body. Keep its existing novtable/Snapshot module-data view
and the constructor donor's existing base/table policy. This is a scoped info
and callback repair, not full module-data inheritance or vtable recovery.

Normal build:47/47 across main/update/module-data constructor/destructor; both
changed parent graphs EXACT, all six native callbacks exact at known extents.
The preflight link guard accepts both private candidates. Older-index paired
preview preserves317 own bytes; no census gain is claimed. proof.json records
final source/object hashes, row extents and actual normal-object callbacks.

Planner: build/consolidation/bonefx-20261106 surveyed the complete8-file prefix.
Its stale-map hints are not approval; the fresh tu_skeleton plan rebuilds the
map in memory and approves47 rows/four files, with one additional mixed donor.
The three flat info-view conflicts are reconciled here. Module-data base/
novtable differences and the update donor's declaration surfaces still require
their own verification before the supported merge can remove any file.

Publication567b2048da audit was INCONCLUSIVE: index7bd55416c6 versus base
a8ae5cd6f1520abd3f581701e282c3a2ef240eda, one missing current main receipt.
The existing main's two shadow guard-name inventory findings (S23 atA038C4 and
S24 atA038CC) remain for the owning regeneration; no inventory/baseline is
hand-edited. No real image, menu, save/load or CRC clearance is claimed.
