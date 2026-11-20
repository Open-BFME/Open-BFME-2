# Fold Rva0044ECCE into SpecialAbilityUpdateModuleData: 19 prepared units verify

Seat halilkkaya-vt3, 2026-11-20, base f18a74f8b52 (branch seat-vt-1120). Not applied.

## Target facts
- Retail vftable 0x00C3F2A8: SpecialAbilityUpdateModuleData's constructor 0x0044EB54 installs it as its own
  (its only +0 store). The destructor 0x0044ECCE (rowed `??1Rva0044ECCE@@UAE@XZ`) stores it at +0, then
  Snapshot's 0x00BBB554 (ModuleData's and Snapshot's destructors are inline). Slot 0 is 0x0044EF42, rowed
  `??_GRva0044ECCE@@UAEPAXI@Z`.
- The data ledger names the table `??_7Rva0044ECCE@@6B@` and `??_7SpecialAbilityUpdateModuleData@@6B@`;
  both copies are bridged (30 and 31 mismatching slots at f18a74f8b52).

## What was tried
`rename.py class --fold Rva0044ECCE --into SpecialAbilityUpdateModuleData --max-files 40` with every unit
that spells Rva0044ECCE `--prepared` on the registered header
`GameLogic/Module/SpecialAbilityUpdateModuleData.h`:
- 18 units have one shape: a stand-in `class Rva0044ECCE { virtual ~Rva0044ECCE(); pad to 0xC8 }` under a
  derived module data class (mostly `__declspec(novtable)`), or the 5-byte `Rva004C6CC1` tail jump in the
  three grab-bags. `prep_saumd.py.txt` swaps the stand-in for the header's `#include` and respells the
  placeholder, mangled spellings in comments included. GiveUpgradeUpdate.cpp also reads the stand-in's
  `m_38`: it now passes `(int)...->m_specialPowerTemplate` (the header's +0x38 field).
- Rva0044ECCEDtor.cpp defines `SpecialAbilityUpdateModuleData::~SpecialAbilityUpdateModuleData()` over the
  header (clears +0x38/+0x3C; the compiler tears down the five AsciiStrings and five sound references) and
  adds `inline ModuleData::~ModuleData() {}`, since retail inlines it.

Result: `Functions: OK 247/247 matched across 19 source file(s)`, with the prepared-unit proofs.

## What blocks it
SpecialAbilityUpdate.cpp spells the placeholder only in three tu-skeleton marker comments
(`??1Rva0044ECCE@@UAE@XZ`, `??_GRva0044ECCE@@UAEPAXI@Z`, `__ehhandler$??1Rva0044ECCE@@UAE@XZ`).
The planner then requires that unit `--prepared` on the header too. It cannot be prepared yet: it keeps a
private `SpecialAbilityUpdateModuleData` copy that header_adopt_lane refuses (header_queue.tsv: its `m_packSound` is
`OpaqueRefElement4`, the header's is `OpaqueRefPtr`). With the markers respelled outside the transaction,
name_dependents refuses the unstaged edit. Recorded as a false reject in re_attempts.log.

Next step, either:
- the planner treats a comment-only spelling as a comment rewrite rather than a unit to prepare; or
- SpecialAbilityUpdate.cpp adopts the header first.

Then apply the fold with these 19 prepared files. The `*.cpp.txt` files are those files, byte for byte.

The fold alone puts 0x00C3F2A8 under one name and resolves its slot 0. Its other 30 mismatches are the
inherited ModuleData slots that SpecialAbilityUpdateModuleData.cpp's view leaves `__purecall`.
