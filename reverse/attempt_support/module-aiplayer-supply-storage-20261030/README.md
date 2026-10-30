# AIPlayer canonical Module supply storage

Replace the empty Module placeholder with the registered eight-byte base.
The old empty base contributed no storage to SupplyWarehouseDockUpdate; shorten
that existing view's padding by eight bytes so its box count stays at +0x88.
No getter body, signature, pin, row or shared header is changed.

The complete native Object::findModule body returns the raw module entry.
AIPlayer::findSupplyCenter calls it at 0x004F22B4 and reads the box count from
[EAX+0x88] at 0x004F22C1. Both instructions are recorded alongside the helper.
The source's other Module use is a pointer-presence query and stays unchanged.
This preserves the observed field, not a complete derived hierarchy claim.

Private before/trial compiles retain all 24 rows, EXACT EH and all 82 external
code definitions with identical raw bytes and symbolic relocations. The final
strict-current normal-build object reproduces every retained definition.
Normal verification passes 16 string references, 19 floats and two imports.
The owning Module acceptance tool retires one key; ordinary preview against
ccafe54d1d retains LINKS/3,983 authored bytes. No census gain is claimed.
