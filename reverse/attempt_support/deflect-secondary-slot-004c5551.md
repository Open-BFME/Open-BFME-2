# DeflectSpecialPower secondary interface, slot zero

Real-link receipt 468fa6d64e and master f2c7fcd942. The constructor and destructor install the nine-word retail table at VA 0x00C5D98C at object offset +0x20. The two compiled spellings are listed in reverse/vtable_bridge_queue.tsv for RVA 0x0085D98C. The destructor unit's one-slot copy names the undefined Rva00589079_E1::fe().

A scratch VC7.1 build of DeflectSpecialPower.cpp used a five-int pure virtual fe on the E1 interface and an override with that signature on DeflectSpecialPower. The override tests m_active, then m_pending, reads the pointer at complete-object offset +8, sets m_pending and calls the existing bfmeSetWakeBJ callee on the complete object with that pointer and 1. The trial emitted ?fe@DeflectSpecialPower@@UAEXHHHHH@Z, 32 bytes, identical to retail outside its single REL32 at offset 25. The relocation names the existing pin at RVA 0x0044DF71, also retail's target. The compiled body accesses the flags at secondary-this +0x1c/+0x1d and returns with ret 0x14. The five int spellings retain the matched row's existing ABI; their semantic types are unknown.

The official rename.py function --rva 0x004C5551 --to-class DeflectSpecialPower --new fe --prepared ... --dry-run refuses at the constructor installer: zero other slots in its compiled table resolve to the retail table. The original row remains intact. Investigate the constructor and destructor views together and recover independent evidence for another slot before attempting the move. Common folded getters at slot 1 and slot 2 have several identities already; their addresses alone do not establish a class member. No new pin, stub, alias or production source edit.

## Second slot

SpecialPowerUpdateInterface.h records independent retail callers for the second slot, isSpecialAbility() const. In the Deflect table the word at RVA 0x0085D990 points to 0x0047A699 (xor al, al; ret). VC7.1 emits the same 3-byte body for the concrete override. The constructor and destructor have distinct secondary-table names; both reference the same decorated override at offset 4. The first-slot repair uses this separate witness.

## Verified repair on 5126f08a90

Both objects now install the same first two callbacks. The constructor's DIR32 relocation is at 0x004C545D + 0x2E and the destructor's at 0x004C54BE + 0x17. Both retail operands are VA 0x00C5D98C. COFF offsets 0 and 4 in their respective secondary tables resolve to DeflectSpecialPower::fe and DeflectSpecialPower::isSpecialAbility. The 32-byte first body matches retail including the REL32 to UpdateModule::setWakeFrame (0x0044DF71); the 3-byte second body matches exactly. Removed the superseded bfmeSetWakeBJ pin and linker alias. The first callback keeps the five dword arguments of the existing row. The other seven retail slots still require reconstruction.

The official rename.py --to-class verifier accepted the rebuilt constructor and destructor. Scoped build: 53/53 functions and one data row across six TUs. link_check: 6/6 LINKS, 3523 to 3526 bytes on reference index 60189f9ced. The three bytes are a folded row. Confirmation that the unresolved symbol has disappeared from the whole program awaits the next real link.
