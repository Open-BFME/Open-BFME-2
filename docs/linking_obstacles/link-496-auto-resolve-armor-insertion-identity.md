### LINK-496: Auto-resolve armor parser binds a non-retail subscript copy
Status: Cleared for the parser's registered insertion identity and current-object link preview. Updated: 2026-11-05; inspected revision: `892820c8d4`.
Evidence / affected unit: `Code/GameEngine/Source/GameClient/GUI/Rva00427157Ctor.cpp`, `LivingWorldAutoResolveArmorStore::parseArmorDefinition` at `0x00427392`; [repair evidence](../../reverse/attempt_support/auto-resolve-armor-insertion-20261105/README.md).
Completed: call the existing matched `ObjectLookupMap::findSlot` owner at `0x0041F4E5` through the pointer-map ABI view; the owning retirement command removes the last identity key, with no remaining findings for this source.
Clearance: 13/13 code rows, one data row and three EXACT EH parents preserved; no new COMDAT variant; LINKS 691 -> 691 bytes against index `c95fcfcfcd` (2026-11-05 05:17).
Remaining / next check: no insertion-identity prerequisite remains; LINK-095's separate generated-funclet destructor prerequisite is unchanged.
Census confirmation: awaiting the scheduled census; no new headline claimed.
