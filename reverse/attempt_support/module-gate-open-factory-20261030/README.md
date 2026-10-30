# GateOpenAndClose factory Module view

Use canonical Module in a partial factory view: PrimaryModuleBase occupies four
bytes, Module starts at +4 and occupies eight, and the remaining opaque storage
keeps the complete allocation at 0x4C. The factory's native +4 null-safe return
conversion and call to the existing constructor at 0x0049889C remain exact.

Select the existing BFME_SNAPSHOT_NAME_SLOT header mode before Module. The
constructor installs the nine-slot Module table at VA 0x00C50144 at +4. Its slot2
returns the class name; the legacy crc(Xfer*) surface does not describe that
native slot. Declare the four required Snapshot/name-key roles without bodies.
This is sufficient for the factory view; it does not recover the complete
inheritance hierarchy or provide new implementations for those declarations.

The existing slot1 owner at 0x0049936A is currently named onObjectCreated and
slot2 at 0x004987F4 is modeled as nonvirtual name(). Those naming debts remain;
no alias or pin bridges them. The real xfer and virtual name-key rows are kept.

Private before/trial and final strict-current objects preserve the one 65-byte
factory and EXACT EH. Every non-debug section, loadable definition, relocation
target and unresolved-name set is identical after resolving .sxdata's COFF
symbol-table indices to their unchanged SafeSEH handler names. Those indices
differ between scratch and production objects and are not image addresses.
No new vtable, thunk, function or
data provider is emitted. The native constructor and table are recorded in the
proof. Normal byte/ref checks and owning Module acceptance pass, retiring one
key; preview against ccafe54d1d retains LINKS/65 bytes. No census gain is claimed.
