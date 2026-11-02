# Native CarryoverUnit name override

Native table BDF158 slot +8 points to VA77DC84/RVA37DC84. That complete
six-byte body returns the retail CarryoverUnit literal. The real virtual
GetSnapshotName override now provides an exact twin through add_match's ICF
admission. The old nonvirtual name getter remains in SubsystemNameGetters;
no old provider, row or pin is removed. A fresh in-memory TU map explicitly
approves the Common CarryoverUnit TU at this address; no map is committed.

All twelve source rows and both EH graphs pass normal and strict checks.
An independent immutable-object comparison preserves all sixteen prior code
definitions and existing data, adding only the getter and its 14-byte literal.
The Common table's symbolic +8 name is unchanged, now resolving directly to
the actual definition. Only the redundant getter alternatename disappears;
the owning hatch tool retires it (2833 -> 2832). This clears the last of the
three original CarryoverUnit method aliases, without claiming that unrelated
opaque member representations or synthetic vector helpers have been recovered.

The complete 08:35 index touches/emits the alias only in Common and has no
incoming route to it. Header adopters already preserve their exact full object
graphs. Scoped link prediction remains LINKS; wider publication audit/census
still determines global consumer clearance. No unique/global coverage gain
is claimed for this folded body.
