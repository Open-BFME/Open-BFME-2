# Devastate canonical ModuleData base and leaf-table review

**Verdict: the scoped table repair is supported.** The candidate replaces the incomplete one-slot leaf table with the native 31-slot interface. All ordered operations are accounted for by actual native targets, current existing providers and the registered canonical contract. Root's unmodified private LinkGuard reports prepare `None`, verdict `[]`. No remaining table/provider blocker was found; main normal verification and owning header acceptance remain required after application.

Inputs are `build/devastate-seed-canonical-data-proof-20261104/{candidate.cpp.txt,candidate.obj,proof.json,link-guard.json}`. The source control hash is `686eae8d1cd4f0dbfb13f45cdf4fba97b776311ce611a84083d8b630ccc92791`. Existing private results are seven exact rows and two exact EH graphs. All prior ordinary definitions and binding properties remain identical except the leaf vtable, which changes from four bytes/one relocation to 124 bytes/31 relocations. The two AsciiString additions have their separate native/provider proof in `../devastate-ascii-provider-review-20261104/`.

## Actual native leaf table

The image table starts at VA `0xC5E518` (RVA `0x85E518`). Its 31 code entries occupy exactly 124 bytes; the following DWORD is zero. The derived data ledger's 128-byte bound includes that following word and is not proof of a 32nd virtual method.

| Slots | Native RVA | Candidate operation / verification |
| --- | --- | --- |
| 0 | `0x4C851B` | weak `_E` default resolves to existing scalar deleting `_G`; full 28-byte body exact |
| 1 | `0xB3FD0` | canonical loadPostProcess, exact `C3` |
| 2 | `0x65212` | const GetSnapshotName, exact six-byte getter and exact `ModuleData` literal |
| 3 | `0x47A69C` | canonical xfer, exact `C2 04 00` |
| 4–13, 15 | `0x47A699` | existing neutral boolean defaults, exact `32 C0 C3` |
| 14 | `0xB69A1` | existing typed AsciiString-returning default; full 28 bytes and symbolic relocations match current native-owner object |
| 16–29 | `0xD43D0` | existing pointer defaults including getHordeModuleData at 21, exact `33 C0 C3` |
| 30 | `0x50B5C6` | existing boolean default, exact `B0 01 C3` |

All 31 candidate DIR32 fields appear at those exact ordered slot offsets. This preserves the correct Snapshot **name** slot at index 2; it does not select the alternative crc profile. The neutral slot names remain neutral: exact default behavior and interface placement do not recover their original semantic names.

## Leaf lifetime and out-of-line edges

The actual COFF weak pair maps `??_EDevastateSpecialPowerModuleData@@UAEPAXI@Z` to `??_GDevastateSpecialPowerModuleData@@UAEPAXI@Z`. The latter is the existing row at `0x4C851B`, owned by SpecialPowerModuleDeletingDtors.cpp. Its candidate 28-byte body is exactly native after resolving REL32 calls to the real complete destructor at `0x4C8537` and operator delete at `0x2FD60`. The weak decoration is not a second body or a claim that the complete destructor is the deleting operation.

The complete 56-byte `??1DevastateSpecialPowerModuleData@@UAE@XZ` row remains in DevastateSpecialPowerModuleDataDtor.cpp. Both current normal owner objects have matching source/object receipts and every recorded header digest. No lifetime function is removed, renamed or rehomed by this candidate.

Slot 2's current SubsystemNameGetters.cpp provider has a fresh source/object/all-header receipt. Its `B8 imm32 C3` getter resolves to native literal VA `0xBC5AFC`, with the exact COFF/native `ModuleData\0` contents.

Slot 14 is only declared by the canonical header; the seed does not invent a new body. The current W3DLaserDraw.cpp typed copy is exactly the same full 28 bytes and two symbolic relocations as the current rowed `Rva000B69A1.cpp` provider: DIR32 to `AsciiString::TheEmptyString`, REL32 to the StringBase copy constructor. Both source/object/all-header receipts are current. This proves the existing operation and ABI behavior, without asserting that the placeholder owner's original class/name has been recovered.

## The 28 defaults and selection scope

All 28 added ModuleData inline bodies individually equal the bytes at their actual native slot targets; none has a relocation. One current normal OpenContainModuleDataCtor.cpp object supplies all 28 exact payloads and all identical EXTERNAL `.text` SELECT_ANY properties, with current source/object/all-header receipts. Its saved index position 5,900 precedes the Devastate position 13,310. The index also contains earlier identical copies for each default.

These are existing canonical in-class bodies, **not** 28 methods with exact ledger-name/pin bindings. No new row or marker follows simply from their additional emission. `header-contract.md` records all 31 declarations and the frozen-checker boundary. The named AsciiString pair differs: those two operations already have exact global rows.

The saved index and root's clean guard are from `23b85ddde5`, 2026-11-03 18:36. The default-copy index verdicts are unclassified (`None`); this review supplies actual native-byte and current-provider evidence rather than upgrading those index verdicts by assertion. This is a scoped proof, not a fresh whole-image census or global provider clearance. Route sets change through the real inherited interface and existing header bindings; they are not identical.

## Application notes

This is a material data/interface repair as well as canonical-header adoption. Keep header debt retirement on its owning accept path. The separate existing protected Devastate destructor marker remains unchanged debt. Correct the stale constructor comment saying the string member has no declared destructor: canonical AsciiString does declare one, even though the measured parent EH graph remains exact.

Detailed native fields, bodies, normal object hashes/receipt checks, saved provider positions and root's guard result are in `provider-table-proof.json`; `summary.json` is the compact result. All tracked/native reads stopped before report generation. No compilation, claim, network, tracked edit or push was performed by this reviewer.
