# Devastate canonical module-data header contract

Read-only review of the supplied candidate/proof and its actual canonical include chain: SpecialPowerModuleData.h -> canonical ascii_string.h, ModuleData.h -> canonical Snapshot.h. Relevant exact ledger/registry names were checked. No build, claim, network, tracked edit, actual COFF/native table comparison or current provider sweep. Tracked reads stopped before this report.

## Interface and declaration order

SpecialPowerModuleData is a registered class directly derived from registered ModuleData. The header documents base extent8B, SpecialPowerModuleData extent0x7C and no added virtual slots. Snapshot contributes the first four positions; ModuleData overrides those positions and adds4..30. ModuleData's live interface has31 entries; Snapshot's four-slot pure teardown table is a distinct lifetime table.

ModuleData sets BFME_SNAPSHOT_NAME_SLOT when it first includes Snapshot. The candidate proof's table metadata confirms the selected name surface is **const GetSnapshotName**, with lowercase loadPostProcess and pointer xfer. Capitalized/non-const/reference variants supported for other Snapshot users must not be silently substituted here.

| Slot | Exact current declaration | Definition/default owner |
|---:|---|---|
| 0 | `virtual destructor / compiler deleting entry` | ModuleData declaration; overridden by SpecialPowerModuleData, then leaf declaration |
| 1 | `void loadPostProcess()` | ModuleData inline empty body |
| 2 | `const char *GetSnapshotName() const` | ModuleData declaration, out of line |
| 3 | `void xfer(Xfer *)` | ModuleData inline empty body |
| 4 | `bool slot04() const` | ModuleData inline false |
| 5 | `bool slot05() const` | ModuleData inline false |
| 6 | `bool slot06() const` | ModuleData inline false |
| 7 | `bool slot07() const` | ModuleData inline false |
| 8 | `bool slot08() const` | ModuleData inline false |
| 9 | `bool slot09() const` | ModuleData inline false |
| 10 | `bool slot10() const` | ModuleData inline false |
| 11 | `bool slot11() const` | ModuleData inline false |
| 12 | `bool slot12() const` | ModuleData inline false |
| 13 | `bool slot13() const` | ModuleData inline false |
| 14 | `AsciiString slot14(int) const` | ModuleData declaration, out of line |
| 15 | `bool slot15() const` | ModuleData inline false |
| 16 | `const void *slot16() const` | ModuleData inline null |
| 17 | `const void *slot17() const` | ModuleData inline null |
| 18 | `const void *slot18() const` | ModuleData inline null |
| 19 | `const void *slot19() const` | ModuleData inline null |
| 20 | `const void *slot20() const` | ModuleData inline null |
| 21 | `const HordeModuleData *getHordeModuleData() const` | ModuleData inline null |
| 22 | `const void *slot22() const` | ModuleData inline null |
| 23 | `const void *slot23() const` | ModuleData inline null |
| 24 | `const void *slot24() const` | ModuleData inline null |
| 25 | `const void *slot25() const` | ModuleData inline null |
| 26 | `const void *slot26() const` | ModuleData inline null |
| 27 | `const void *slot27() const` | ModuleData inline null |
| 28 | `const void *slot28() const` | ModuleData inline null |
| 29 | `const void *slot29() const` | ModuleData inline null |
| 30 | `bool slot30() const` | ModuleData inline true |

Exactly28 positions have in-class ModuleData default bodies:1,3,4..13,15,16..29,30. Positions0,2,14 are declarations/externally supplied operations. SpecialPowerModuleData adds no slots; only its destructor overrides position0. The leaf DevastateSpecialPowerModuleData likewise overrides the virtual destructor and inherits the remaining30 slots.

## Snapshot/getter/destructor context

Snapshot's ordinary header form has inline constructor/virtual destructor and pure virtual positions1..3; the constructor-only selector is a different novtable/declaration surface. ModuleData declares its own virtual destructor out of line. Its exact UAE destructor row is49B47C/7B in Common/Rva004ABFD9Dtor.cpp, with a documented Snapshot fold; the current header separates base teardown from the live31-slot interface.

ModuleData::GetSnapshotName is a declaration-only **const** slot2 override. Its exact row is65212/6B in Common/SubsystemNameGetters.cpp. Slot14 returns AsciiString by value with one int argument, and remains declaration-only; no exact slot14 row or pin was found by this narrow lookup. An inherited generic getter or default's placement does not prove a new leaf-specific descriptive name.

SpecialPowerModuleData's constructor/destructor remain out of line. Its complete UAE destructor owns49334F/115B in SpecialPowerModuleDataDtor.cpp. The candidate leaf declares public virtual `~DevastateSpecialPowerModuleData`; the exact complete UAE destructor is already rowed4C8537/56B in DevastateSpecialPowerModuleDataDtor.cpp. This is distinct from the other behavior class's protected `DevastateSpecialPower::~DevastateSpecialPower` existing unmatched marker.

The supplied candidate metadata has a124-byte/31-slot leaf table. Its position0 spelling is `??_EDevastateSpecialPowerModuleData@@UAEPAXI@Z`, while existing nearby scalar-deleting ownership uses a _G spelling. This review does not equate those helpers or certify the selected target; the parent owns actual native/COFF/table/provider comparison. Position0 is a deleting entry, not the complete destructor body itself.

## Native facts versus naming evidence

The canonical header explicitly labels native constructor/factory/table/parser/destructor observations as target facts. It documents common-table slot behavior:1 B3FD0,2 65212,3 47A69C; false slots4..13/15 at47A699; AsciiString-returning14 atB69A1; null slots16..29 atD43D0; true30 at50B5C6. This audit reports those existing documented facts, without revalidating them against Devastate's actual native table.

Neutral slot04..slot30 names identify positions/defaults, not recovered original application method names. The getHordeModuleData name has the header's separate Carryover slot21/caller-access evidence. The header attributes SpecialPower member names m_specialPowerTemplate, m_updateModuleStartsAttack and m_startsPaused to Zero Hour source; other fields remain neutral storage even where INI tokens identify a role. Matching storage/table shape does not prove additional donor types or original names.

The candidate retains an old constructor explanation saying the string member has no declared destructor. That statement no longer describes its canonical AsciiString declaration. The supplied exact EH result is the current evidence; the old comment is not a valid explanation of this candidate's lifetime scheduling.

## Frozen/inline ownership boundary

Unlike the two AsciiString copies reviewed separately (already exactly rowed at654A/18B and48BA39/5B), the28 newly emitted ModuleData default decorations have **no exact functions.csv or symbols.csv binding** in the narrow lookup. They are existing registered canonical in-class definitions, not28 newly verified ledger rows.

The frozen checker reads supplied .cpp definitions, not recursively preprocessed in-class header bodies. Including this existing header therefore does not itself demand28 new Devastate rows or marker comments. This is not permission to call those defaults independently byte-verified, to claim recovered coverage, or to ignore new physical providers/table edges. Their complete bytes, native slot identities, selected-copy behavior, inherited virtual signatures and affected consumers are material parts of the parent's header-adoption/provider verification. Any future explicit RVA ownership/ICF admission must use its supported path and current TU evidence.

Do not add present-unmatched markers (counted hatches), claim absent-from-retail merely because exact rows are missing, or introduce a private canonical copy to avoid emission. Existing canonical inline code is not a reason to invent rows/pins or change checker behavior. Keep the unchanged Devastate behavior-destructor marker as separate existing debt unless its own identity/row is properly resolved.

The supplied proof reports7 matched rows, no missing/errors, two EXACT EH graphs,30 added definitions (28 ModuleData defaults plus2 AsciiString copies), one changed leaf table, no changed retained code or binding_changes, and routes_identical=false. Those are private proof facts, not tests rerun here. No native table, full provider or full-image clearance is claimed by this report.
