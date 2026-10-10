# AptConnectionScreen deleting owner and natural weak thunk

Target evidence establishes AptConnectionScreen: its 272-byte constructor at
0x005DB6E2 builds the Apt window and listener base at +0x58, and the existing
89-byte destructor at 0x005DB681 unregisters that listener and tears down the
window. The native 28-byte scalar deleting body at 0x005DB7F2 calls this actual
destructor, conditionally calls operator delete for flag bit 0, returns the
receiver, and ends with RET 4.

The existing proper destructor TU naturally emits this whole 28-byte body as
`??_GAptConnectionScreen@@UAEPAXI@Z`. This repair rehomes the old opaque
`??_GRva005DB681@@UAEPAXI@Z` row to that real owner, deletes the obsolete opaque
destructor pin, and removes its fake EmitVtableTag constructor. No new pin,
alias, private class, header, or emission helper is added. Unique C++ gain is
zero; one old pin and one absent-from-retail emitter declaration are removed.

The two current owned homes passed normal 20/20 body gates and then bounded
strict preparation with their own reusable compiler receipts. The witnessed
census at d68a97b48f (2026-10-10 11:55 UTC), updated in memory only for these
two local current objects, shows the old scalar-deleter home loses its sole
unresolved opaque Apt destructor and retains two unrelated vtable losers.
The proper Apt home retains exactly its three inherited unresolved names
(TheNAT and listener slot00/slot01) and one listener vtable loser. Neither home
is claimed LINK clean; this repair does not hide or solve those debts.

The independently bounded 8-byte native entry at 0x005DB6DA subtracts 0x58
from ECX and jumps to 0x005DB7F2. The genuine source naturally emits the
secondary `??_EAptConnectionScreen@@WFI@AEPAXI@Z` thunk with a REL32 relocation
to the primary `_E` weak external. That primary name is COFF storage 105,
auxiliary default index 34 naming `_G`, SEARCH_LIBRARY 2. The fresh census has
no strong, COMDAT, COMMON, alternate, runtime, imported, or stub provider of
primary `_E`. Actual first-kept `_G` order was checked, and its complete 28
bytes and both relocation targets match retail; the constructor's later copy
is also a whole-body relocation twin. The physical weak default yields all
8 native bytes. The unchanged normal byte gate instead reports unresolved
primary `_E`; the attempted 8-byte row was removed automatically. It remains
blocked, with the false reject recorded for a separate verifier fix. Even
when that checker is repaired, the inherited proper-home LINK debts must
be resolved before claiming a new recovery. No `_E` pin is introduced.

`weak-binding-and-owner-control.json` records the exact COFF evidence, native
bytes, relocation contracts, first-copy order, local object digests and
strict currency, plus before/after scoped blockers. Root census receipts
were not copied to this worktree. Prior unchanged whole-source bank evidence
is also preserved in commit f8cb09d80f7f5171ed157740957c789a139b1a81.
