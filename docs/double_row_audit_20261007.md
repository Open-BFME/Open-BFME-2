# October 5 duplicate-row report: October 7 repair

The supplied report listed 108 retail addresses. At revision b294724742,
104 still had multiple matched rows; four had already been consolidated.
The repair retires 118 redundant claims, deletes 27 source units left without
owned bodies, and removes redundant definitions from 24 retained units.
Five further caller units are updated; two independently owned copy-helper
instantiations remain explicitly emitted.

Each reported address now has one reconstruction owner in
`reverse/body_owners.csv`. Its evidence field preserves the retained row's
basis and uncertainty. Many address-derived owner names remain provisional:
consolidation is not evidence that those classes have recovered real names.
Where both candidates were shape-based, one owner was retained without
promoting either speculative name. The shared 0x002C17D6 template helper keeps
one claim; an independently emitted dependency is not proof of a second
retail instantiation identity.

Deleted claims are tombstoned in `reverse/deleted_rows.csv`, preventing union
merges from restoring them. `check_csv.py` also checks the recorded owner,
source and extent and rejects another spelling at an audited address.
Supported renames or source rehoming require updating the owner evidence.
Unrelated folded functions are outside this audit and retain their existing
validation behavior. The registry records ownership, not additional coverage.

Two surviving reserve/set callers and five additional dependent bodies now call
the retained owner declarations.
The surviving 0x0014FA47 wrapper calls the retained STLport fill helper, with
its exact calling convention and compiler shape verified by the byte gate.

The obsolete fill-helper alias pin was removed after its callers were updated.

Regression tests cover replacement and duplicate owner spellings, missing
owners, rehoming, incorrect extents/status, duplicate registry entries, and
unrelated folds. The full byte gate remains the acceptance test for the
retained bodies and all their callers; ledger counts alone are not proof.
