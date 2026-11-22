# CreateAHero page base vftable 0x00C72B74 (bridge 0x00872B74)

Served bridge `??_7Rva005B2575Base@@6B@`. The retail table has eight slots:
deleting dtor 005B2558, 000B3FD0 (slots 1/3/4), 0047A69C (slots 2/7),
005748AD (slots 5/6). The derived Bonus table 0x00C72BAC is bridged by the
same missing base slots.

Five private placeholder views emit the table: Rva005B253F
(RvaSmallVtableCtors.cpp, Rva005B4A46Dtor.cpp, Rva005B5CF4Dtor.cpp),
Rva005B2575Base (Rva005B2575Dtor.cpp, AptCreateAHeroBonusConstructor.cpp),
Rva005B5420Base (Rva005B5420Dtor.cpp, AptCreateAHeroClassConstructor.cpp),
Rva005B6B93Base (AptCreateAHeroManagerConstructor.cpp) and Rva005B414FBase
(AptCreateAHeroPowers.cpp, WWLib/Rva005B486DTail.cpp). Only Rva005B414FBase
declares all eight slots. The owner pointer at +4 is typed differently per view
(void*, AptCreateAHero*, Rva005B3676Owner*).

`rename.py class --fold Rva005B2575Base --into Rva005B253F --dry-run` refuses
because the table is also named for three other classes. Adding `--with` for
them refuses as well: `??1Rva005B414FBase@@UAE@XZ` is a fold-proof destructor
row at 005B2551, so the tool would treat Rva005B414FBase as a second owner (an
ICF fold of distinct classes), not a third name. Rva005B5420Base and
Rva005B6B93Base carry the same kind of fold-proof destructor rows.

Repair needs the following, in order:
1. A coordinated identity migration. Retire the fold-proof destructor rows of
   the four Base names onto one class through the tombstone path.
2. A fold of the names.
3. A canonical eight-slot header adopted by every view through
   header_adopt_lane.

No source, header or ledger edit is retained. The pass test (the next real link
no longer bridges 0x00872B74/0x00872BAC) remains open.
