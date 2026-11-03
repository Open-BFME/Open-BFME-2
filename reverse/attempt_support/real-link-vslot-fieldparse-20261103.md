# Vslot AG: define the three native FieldParse tables

Base: 007bf15b24. Seat: halilkkaya-codex. Source:
Code/GameEngine/Source/Common/VslotSmallBodiesAG_Rva00131CF2.cpp.

The three existing field-parse builders pass VA C74540, C74630 and C74704.
Their declared globals had no definitions. Recover the complete tables from
retail, including the zero terminator, as ordinary const FieldParse arrays.
Do not infer the enclosing application class from the old placeholder names.

| VA | Bytes | Native fields / offsets |
| --- | ---: | --- |
| C74540 | 48 | Type / 08; Amount / 0C |
| C74630 | 64 | StrengtheningRange / 08; BonusKey / 0C; Bonus / 10 |
| C74704 | 48 | NumUpgradesPerTurn / 08; UpgradeableUnits / 0C |

Callbacks are the already rowed INI::parseIndexList (2EC4E), parseInt (2EF56),
parseAsciiString (2F11E), parseAsciiStringVectorAppend (2E896) and
LivingWorldAutoResolveBattleBonusTable::iniAppendBonusToTable (3F777F).
These names come from the current ledger; the native pointers independently
establish the binding. The parser's application-class spelling is not new
recovered-name evidence. The complete user-data arrays are TACTICAL/WORLD/null
at C74534 and THIS_TERRIORITY/ALL_ARMIES/null at C745E4. Preserve the retail
TERRIORITY typo. Both TU-local arrays are recursively verified by content and
compiler-proven extent, without a pin or additional external global.

Three matched data rows own exactly 160 bytes. Data verification proves their
sizes, every literal, callback and user-data pointer, all offsets and all zero
sentinels without masking. The ten existing code rows are unchanged; no old
external provider disappears. Only the three named data globals and pooled
string literals are newly external. No compiler flag, header or source path
changes, no pin or escape hatch is added.

Normal six-source checks pass 154 function rows and the three data rows,
80 literals, 17 empty-string references, three float literals and 24 imports.
Scope includes this unit, INI.cpp, LivingWorldAutoResolveBattleBonus.cpp,
BfmeConv1341.cpp, Rva0023C7F5Get.cpp and Rva005D4E6FCheck.cpp. True base/tip
A/B restores both source and the data ledger: the same five peers LINKS for
9,873 bytes; this unit stays blocked, with unresolveds reduced seven to four.
Scoped DIR32 passes 154 rows plus 62 current witnesses (213 symbols), without
new or whitelisted conflicts. find_declared_unmatched and check_csv pass.
No real-link rerun, census-linked or runtime credit is claimed. The index is
984a4cdc4d, November 2 08:35. Logs/snapshots: build/seat-link/vslot/.

Remaining boundaries:

- rva00130FCE is requested as bool but its existing provider returns int;
  direct conversion changes the caller's native tail jump.
- rva0023C7F5 is requested as a two-argument member, but the existing provider
  is declared stdcall and ignores both arguments and ECX.
- Gen_003bcb40::m and Rva005C4352Base::buildFieldParse request the shared
  RET4 slot at 47A69C. Its claim is held by AIUpdateInterface/LocomotorSet.
  A chained command mistakenly continued after that refusal; the empty-helper
  trial then inlined and changed two old callers. The normal gate refused it,
  and source/ledger were fully restored before the table-only repair. No
  helper alias row or code change at the held address is retained.
