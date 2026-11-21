# Rva007F6D60Child vtable bridge (0x008E2DE0): handoff

Queue item: vtable-bridge `??_7Rva007F6D60Child@@6B@` at 0x008E2DE0, an 11-slot
table. The kept copy comes from
`Code/GameEngine/Source/GameNetwork/Rva007F6D60ChildConstructor.cpp`. Slot 0 is an
unrowed `??_E`, and slots 1-10 are `__purecall`. Three other units bind the same
name: BfmeThingDGDDestructor.cpp, Rva007F55F0Teardown.cpp and BfmeConv1325.cpp.

## Retail slot targets and their current rows (target facts and ledger)

| slot | retail | ledger row(s) at that address |
|---|---|---|
| 0 | 0x006634E0 | `?bfmeDelTWB@BfmeThingTWB@@QAEPAXE@Z` (BfmeConv1325.cpp), a deleting destructor spelled as a non-virtual member of another class |
| 1 | 0x00661E40 | `?copyWord24@Rva007F6D60Child@@QBEPAIPAI@Z` (Rva00661E40CopyWordFinish.cpp) |
| 2 | 0x0013ED30 | none |
| 3 | 0x00144010 | shared body: `SimpleVecClass<K>::Length`, `NarrowStrLenSource::getLength`, ... (ICF) |
| 4 | 0x00143D80 | `?get@Rva00143D80DwordField@@QBEHXZ` (Disp8DwordFieldGetters.cpp) |
| 5 | 0x0013E8F0 | none |
| 6 | 0x00661E50 | `?copyWord18@Rva007F6D60Child@@QBEPAIPAI@Z` |
| 7 | 0x0066D490 | `?get@Rva0066D490DwordField@@QBEHXZ` |
| 8 | 0x00661E60 | `?get@Rva00661E60DwordField@@QBEHXZ` |
| 9 | 0x0066D630 | `?get@Rva0066D630DwordField@@QBEHXZ` |
| 10 | 0x00661E70 | `?get@Rva00661E70LeaField@@QBEPAXXZ` (Disp8LeaFieldGetters.cpp) |

## Why it is not landed

Every slot body is rowed as a non-virtual (`QBE`/`QAE`) member of a private
placeholder class, or of an unrelated class. The fix therefore needs naming-lane
work:

- `rename.py class --fold` of `Rva00143D80DwordField`, `Rva0066D490DwordField`,
  `Rva00661E60DwordField`, `Rva0066D630DwordField`, `Rva00661E70LeaField` and
  `BfmeThingTWB` into `Rva007F6D60Child`, or its base where a slot is inherited.
- `function --virtual` per slot. Slot 0's `?bfmeDelTWB` is a deleting destructor
  and must become `??_G`/`??_E`.
- Rows for 0x0013ED30 and 0x0013E8F0.
- An ICF-twin row for slot 3 (`add_match --icf-owner`).

Each placeholder class's getter file also hosts unrelated classes' getters,
whose `fold` blast radius must be checked first. Only after that can the class
views in the four units (and a shared header) declare the slots.
