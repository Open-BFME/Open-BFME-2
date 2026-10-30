# Health-bar canonical Module storage

Replace the oversized private Module with canonical Module8 and an explicitly
partial primary storage view. The unchanged UpgradeMux interface remains at
module+0x24. Native 0x0027614A calls the existing 81-byte WallUpgradeUpdate
lookup at 0x004AB1F5; 0x00276154 forms its return+0x24. The lookup returns the
raw Object::findModule result, whose existing owner is 0x0028B6D6. Keep both
lookup and interface prototypes; this does not recover the complete hierarchy.

Fresh private before/trial compilation and final strict-current preparation
retain the exact 472-byte row and all eleven external code definitions. All
loadable definitions, non-debug sections, relocations and undefined names are
identical. The owning Module acceptance tool retires one header key; ordinary
preview retains LINKS/472 bytes against ccafe54d1d. The health-address/ST0
scheduling view and target flags are unchanged. No census gain, implementation,
table, thunk, pin or path move. Native facts and object fingerprints are in
proof.json; this adoption uses no donor facts.
