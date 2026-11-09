### LINK-654: four registration tables need real classes with a folded deleting destructor

Status: open (2026-11-09).

Target facts: retail tables VA 0x00C63398, 0x00C745A0, 0x00C74698 and
0x00C7475C (rows `?spawnArmyVtable@@3QBQBXB`, `?increaseCommandPointsVtable`,
`?strengthenArmyVtable`, `?upgradeTroopsVtable`, 8 B each, matched in
`Code/GameEngine/Source/GameClient/GUI/Rva007B4874Registrations.cpp`) are installed
by the startup initializers 0x007B33C5, 0x007B481D, 0x007B4874 and 0x007B48CB.
Slot 0 of all four is the shared deleting destructor 0x005C43E7
(`??_GRva005C47A3@@UAEPAXI@Z`); slot 1 is a per-kind factory rowed as a free
`__stdcall` function (0x004FAC99, 0x0052B58F, 0x0052B5C6) or a non-virtual member
(0x0052B5FD). The ledger also binds compiler names `??_7Rva004FA623@@6B@` and
`??_7Rva005C43CF/459E/47F0Registration@@6B@` to these addresses.

Why the real link refuses them: the hand-written arrays are strong definitions
(`reverse/vtable_bridge_queue.tsv`, reason strong-definition). Their slots are
already correct relocations, so the refusal does not lose bytes; the 52c8626a4d
remedy (repoint to a SELECT_ANY compiler table) does not apply because these
addresses have matched data rows of their own and no compiler table exists yet.

Prerequisites (structural inference): declare each registration as a class over
`Rva0052B894Registration`/`Rva005C47A3` with a virtual destructor and one factory
virtual; respell the four factory rows as those virtual members (thiscall that
ignores `this` and pops one argument has the same bytes as the current stdcall
spelling: check each body); admit each derived `??_G` onto 0x005C43E7 as an ICF
fold with `fold-proof=` through `tools/pin_admission.py --add`; then rename the
data rows to the emitted `??_7` names and confirm the four initializers still
byte-match with the derived constructor inlined. Not attempted: no source change
landed.

2026-11-09 prerequisite recovery: the supported class-fold transaction
reconciled `Rva0052B894Registration` with the table's existing `Rva0052B668`
identity across all four consumers, including constructor 0x0052B894 and its
EH handler 0x007970C2. All 32 rows, four data rows and five literals verify;
each source's own link verdict is LINKS (1,133 bytes unchanged against census
5b5011469d). See
`reverse/attempt_support/registration-base-identity-20261109.md`.

The original hierarchy suggestion above needs correction: the 4-byte base has
table 0x008686BC with slots [0x0052B668, purecall 0x0003B810]. The common
0x005C47A3 destructor is shared code for the four derived registrations, not
an evidenced intermediate base. Reconcile the existing 0x0052B588 setter-shaped
owner as the base destructor; extend the base's short compiler table with its
pure factory slot. All four derived factories must override one compatible
identifier/signature. Their dispatcher `Rva0052B634ArmyActionPrime.cpp` is a
mandatory additional consumer; migrate its three helper pins and alternatenames
with the factory identities. Free/stdcall rows need reviewed prepared ordinary
respells. Genuine 5-byte derived-destructor folds can use `add_match.py
--icf-owner`; they do not meet fold-pin admission's concrete-byte threshold.
The four strong tables remain unresolved; no bridge or image gain is claimed.
