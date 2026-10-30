# ObjectCreationUpgrade canonical Module factory view

Apply the established declaration-only factory pattern: retain the existing
eight-byte primary view, use canonical Module8 at +8, and reduce trailing opaque
storage from 0x24 to 0x20. Allocation stays 0x30 and the returned Module pointer
stays +8. The existing 68-byte constructor at 0x004B40A6 calls UpdateModule
at +8 and installs the Module table at VA 0x00C5762C there.

Select BFME_SNAPSHOT_NAME_SLOT and declare the four required Snapshot/key roles
without bodies. Slot2 returns ObjectCreationUpgrade's name. Existing static key
and nonvirtual name spellings remain identity debt; no implementation, alias
or pin is added. The complete Update/Upgrade hierarchy is not recovered here.
The existing public module-data factory declaration is preserved.

Private and final strict-current builds retain the complete 65-byte factory
and EXACT EH. All non-debug sections, definitions, relocation targets and
unresolved-name sets are identical after resolving SafeSEH symbol indices.
No new table or thunk is emitted. Normal checks and owning Module acceptance
pass, retiring one key. Preview against ccafe54d1d preserves LINKS/65 bytes;
no coverage or census gain is claimed.
