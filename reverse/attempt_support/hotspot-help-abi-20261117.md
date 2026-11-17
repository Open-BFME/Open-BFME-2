# Hot-spot help bridge: nonvirtual teardown prerequisite

The default picker serves table RVA 0x00877960 in Rva005E0B0FDtor.cpp.
Its five native slots are three instances of the empty RET4 body at
0x0047A69C, callback 0x005E0B8F and OnHotSpotRollOver at 0x005E0C6D.
The constructor source InGameHotSpotSimpleHelp.cpp already records that
these callbacks, not a destructor, occupy the native table. The shared
Rva0086E330Base header instead declares a virtual destructor as its sole
slot, and the destructor view therefore emits a short wrong table.

A scratch-only experiment replaces that base virtual destructor with an
ordinary empty callback and nonvirtual destructor, and makes the derived
destructor nonvirtual. Under their resulting proper decorations the complete
128-byte destructor at 0x005E0B0F and nine-byte base constructor at
0x005E1871 both still byte-match. The compiler stops emitting
??_GRva005E0B0F@@UAEPAXI@Z, however. The existing 28-byte ledger row at
0x005CB301 must be preserved, so this experiment was not applied.

Native disassembly of 0x005CB301 confirms a direct call to 0x005E0B0F,
a flag-bit test on the stack, optional global operator delete, and return
of this. It has the deleting-helper body even though the native callback
table has no deleting-destructor slot. The next repair must recover that
helper's ownership/emission or use an evidence-gated identity transfer;
it must not delete its row, add a manual alias, or retain a fictitious
virtual destructor in the callback table merely to force emission.

No tracked source or shared header was changed. The source's existing
Rva0086E330Base constructor anchor is already marked absent from retail;
adding deletion behavior there would manufacture an emitter and is not
part of this proposed repair. Snapshot the current shared-header consumers
and acquire them before changing the generated contract/header.
