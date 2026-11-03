### DeflectSpecialPower dtor identity and ctor COMDAT (2026-10-29, seat yasinschroeder-claude2)

Status: dtor repair verified by link_check (prediction, not census). The ctor
merge is still blocked. 0x004C54BE (46 B) and 0x004C5535 (28 B) were rowed as
address-named Rva0025A390FlatDtor in FlatMultiVptrDestructors.cpp. They were
retracted and readmitted with add_match as ??1/??_GDeflectSpecialPower in
DeflectSpecialPower.cpp, their approved TU. The body stores the ctor's six
vtables, then tail-calls ??1Rva00589079 (0x00589079). The view now derives
DeflectSpecialPower straight from Rva00589079. With the intermediate
WeaponModeSpecialPowerUpdateBase view kept, the new dtor emitted an implicit
??1WeaponModeSpecialPowerUpdateBase COMDAT, and the unit fell to 0 linked
bytes ("comdat (first): differs from the first copy in link order").
link_check: DeflectSpecialPower.cpp LINKED 138 -> 468 bytes;
FlatMultiVptrDestructors.cpp 169 -> 95 (the moved dtor bytes). The dead
??1Rva00019565FlatBase pin and its /alternatename were dropped.

Remaining / next check: DeflectSpecialPowerConstructorThunk.cpp (0x004C545D)
cannot merge. Its EH unwind needs the base dtor, and under a shared view it
emits the same differing ??1WeaponModeSpecialPowerUpdateBase COMDAT. Retail
pairs the ctor 0x0058959A (rowed ??0WeaponModeSpecialPowerUpdateBase) with
the dtor 0x00589079 (rowed ??1Rva00589079). Unifying Rva00589079 into
WeaponModeSpecialPowerUpdateBase with rename.py class should let the ctor's
unwind call the rowed dtor. Confirm the census figures after the next census.
