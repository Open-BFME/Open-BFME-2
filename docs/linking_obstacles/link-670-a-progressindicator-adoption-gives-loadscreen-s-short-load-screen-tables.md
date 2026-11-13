### LINK-670: a ProgressIndicator adoption gives LoadScreen.cpp's short load-screen tables a second slot the other short copies lack
Status: Open (needs a family reconciliation; two units, 1,186 B). Updated: 2026-11-13 (seat halilkkaya-rg1); base
`d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Symptom.** Census 2026-11-13 04:18 (`6e37424cf7`) "yes", census 07:05 (`b25a313d87`) "no":
- LoadScreen.cpp, 1,046 B: comdat `??_7Rva0035615D@@6B@` differs from the first copy (OpaqueScalarDeletingDtorsB06.cpp).
- Rva003560EDDtor.cpp, 140 B: comdat `??_7Rva003560ED@@6B@` differs from the first copy (LoadScreen.cpp).

**Cause.** "Register canonical ProgressIndicator, adopt it in 4 units" (`4e4d96c6ad0`, StarkillerHDX; in
`b25a313d87`, not in `6e37424cf7`). LoadScreen.cpp's private `Rva00355D66 : ProgressIndicator` view now gets the
canonical base, which declares `virtual void slot1(int) = 0` (retail's ProgressIndicator table 0x00814E4C is
[dtor, `__purecall`], so the header is right). LoadScreen.cpp's Rva003560ED and Rva0035615D tables went from 1 slot
to 2 ([`??_E`, `__purecall`]). The other emitters, Rva003560EDDtor.cpp, OpaqueScalarDeletingDtorsB06.cpp and
Rva003561BEDtor.cpp, keep flattened `Rva00355D66 { virtual ~Rva00355D66(); char m_pad[12]; }` views and emit
1 slot. Census order puts LoadScreen.cpp first for Rva003560ED and B06 first for Rva0035615D, so a different unit
loses each table.

**Retail (target facts).** Neither shape is retail. 0x00814EA4 (Rva003560ED) has 6 slots: `??_E` 0x00356708,
0x00355DF4 (`?rva00355DF4@Rva003560ED@@UAEXH@Z`), 0x00356724, 0x00355DDD, 0x00355E20, 0x0050B5C6.
0x00814EBC (Rva0035615D) has 6 slots: `??_E` 0x0035686D, 0x00355DF4, 0x00356889, 0x00355E85, 0x00355E20,
0x00355E4C. Every non-destructor slot already has a matched row, mostly in Rva003560EDEngineRefresh.cpp. All four
units' views are private copies of the registered Rva00355D66 (`GameClient/Rva00355D66.h`, 6 slots spelled
`vslot01`, `init`, `vslot03`, `processProgress`, `vslot05`). The rows spell the overrides with placeholder names
(`rva00355DF4`, ...), so no unit can override the canonical slots yet.

**Fix (not applied).** Adopt the canonical Rva00355D66 in the four emitters (LoadScreen.cpp, Rva003560EDDtor.cpp,
OpaqueScalarDeletingDtorsB06.cpp, Rva003561BEDtor.cpp). Rename the slot rows to the canonical slot names of their
classes (`rename.py --to-class`), and declare the overrides, so that every copy is retail's 6-slot table. A
one-unit patch that makes the copies agree again, by flattening LoadScreen.cpp's view off ProgressIndicator or by
adding a pure slot 1 to the three flattened views, only trades one short copy for another. That was not done.
