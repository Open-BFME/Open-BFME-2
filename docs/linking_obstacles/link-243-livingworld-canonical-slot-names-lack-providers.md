### LINK-243: LivingWorld canonical slot names lack providers
Status: Open. Updated: 2026-11-04; inspected revision: db9cef1ff8.
Evidence / affected units: `Code/GameEngine/Include/GameLogic/LivingWorldClass.h` gives the
nonpure slots of LivingWorld's table 0x007FE508 neutral names (GetSnapshotName, xfer,
loadPostProcess, vslot16, v19, slot20, vslot27, vslot33..vslot39). A unit that emits
LivingWorld's or a derived vtable against the header references them, but their bodies are rowed
under placeholder classes: 0x002BE8CE `?Rva002BE8CEGet@@YAHXZ`, 0x002BE833
`?rva002BE833@Rva002BE833@@...`, 0x002BFBF0 `?rva002BFBF0@Rva002BFBF0@@...` (also
`?slot4@Rva0030C1FCOwner@@...`: a shared body), 0x002BE7FA `?rva002BE7FA@Rva002BE7FA@@...`,
0x0009AA01 `?set@Rva0009AA01ByteSlot@@...`, 0x002C021A, 0x004A18C0, 0x0009D6E8, 0x0009D6ED,
0x0009D6F1, 0x002886A2, 0x0009D6F5 (disp8 setter/getter families) and 0x002BEFE5.
`link_check.py` on
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0009D55BProductCtor_Rva0009D55BProduct.cpp`
adopted on the header (21/21 rows byte-match) predicts LINKED 2,801 -> 0 bytes with those 14
symbols unresolved, so that adoption was reverted.
Completed: LivingWorld_ZoomInTo.cpp and LivingWorldSetActive.cpp adopt the header, and
Rva0009D55BProductCtor.cpp's queue row is retired (accepted).
Remaining / next check: move each slot body into LivingWorld with `rename.py function --rva
<addr> --to-class LivingWorld --new <slot name>`, preparing LivingWorld.cpp (the constructor
0x002C0120, the table's installer) so its view declares the slot; shared bodies (0x002BFBF0 and any
disp8 family address another class's table holds) will be refused and need their own decision.
LivingWorld.cpp itself does not yet adopt the header (its +0x1C is an 8-byte member where the
header has two floats), and LivingWorldDtor.cpp needs the header's +0x28/+0x98/+0xAC members typed
and an inline listener-list teardown the out-of-line Rva00330757Member destructor does not give.
Clearance: pending.
Census confirmation: not claimed.
