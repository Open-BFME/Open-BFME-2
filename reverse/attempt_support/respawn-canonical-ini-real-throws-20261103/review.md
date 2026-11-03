# Respawn canonical INIException metadata review

**Verdict:** the private candidate's four emitted metadata records reproduce the retail INIException graph exactly after resolving each symbolic relocation to its independently supported native owner. The two parser metadata substitutions bind to that same retail ThrowInfo. No metadata or function-provider blocker was found in this bounded review. This is private evidence; root still owns normal source/header acceptance and publication checks.

Inputs are `build/respawn-canonical-parser-proof-20261103/candidate.obj` and its `proof.json`. That proof reports 24 matched rows, no missing/error rows, three exact EH graphs, unchanged ordinary binding properties, and only two parser relocation changes. Their instruction bytes are unchanged. The removal is the old unused empty `INIException()` default constructor; the four additions are compiler-emitted TypeDescriptor, CatchableType, CatchableTypeArray and ThrowInfo definitions.

## Native graph

| Record | Retail RVA | Exact extent | Resolved edges | Result |
| --- | --- | --- | --- | --- |
| ThrowInfo `__TI1?AVINIException@@` | `0x8FE2FC` | 16 bytes | dtor `0x2BD30`, array `0x8FE2F4` | Exact |
| CatchableTypeArray `__CTA1?AVINIException@@` | `0x8FE2F4` | 8 bytes | one entry, type `0x8FE2D8` | Exact |
| CatchableType | `0x8FE2D8` | 28 bytes | TypeDescriptor `0x9A7554`, copy ctor `0x588C5` | Exact |
| TypeDescriptor `??_R0?AVINIException@@@8` | `0x9A7554` | 27 bytes | type_info vftable `0x87C730` | Exact |

CatchableType has properties zero, PMD `(0,-1,0)` and object size eight. The descriptor has zero spare word and the exact `.?AVINIException@@` name. The 27-byte descriptor extent excludes the next native object's bytes. `metadata-proof.json` retains raw COFF bytes, symbolic DIR32 relocations, native bytes and the four exact normalized comparisons.

The existing canonical `Common/INI/FieldParse.h` agrees: INIException has no base or virtuals, message pointer at zero and an int at four; it declares the varargs constructor, copy constructor, destructor and assignment, with no default constructor. Its documented native graph and providers agree with the independently read image.

The parser at `0x4AFC5F` changes only the metadata DIR32 name at body offset 511; the parser at `0x4AFE6C` changes only that name at offset 729. Both native fields contain VA `0xCFE2FC`, i.e. RVA `0x8FE2FC`. This proves the specific static-anchor-to-canonical-TI substitution rather than relying on a relocation-name waiver.

## Provider closure and current receipts

`Code/GameEngine/Source/Common/INI/INIExceptionCtor.cpp` currently supplies the real 9-byte destructor at `0x2BD30` and 21-byte copy constructor at `0x588C5`. The current normal object matches its source/object receipt and every recorded header digest. The destructor calls `operator delete[]`; the copy constructor calls the existing assignment operator at `0x2F6D6`. The saved index (`23b85ddde5`, 2026-11-03 18:36) identifies each typed destructor/copy provider as a sole strong retail provider. No new pin is needed.

The TypeDescriptor edge is also proved, rather than assumed from a runtime spelling. Native vftable `0x87C730` has its one established slot pointing to `0x629048`, the existing 75-byte matched `??_Etype_info@@UAEPAXI@Z`. The current normal `Code/Libraries/Source/CRT/TypeInfoCopyConstructor.cpp` object defines `??_7type_info@@6B@` as a four-byte relocation to that exact function. Its source/object receipt and all header digests are current; object SHA-256 is `7ae8b9adc0b03c85292afc5538a8372c8dd92a34c3cbb886d9c23ecec0ce6462`. No neighboring vftable words are claimed as part of this table.

The removed fake default constructor has only the Respawn seed as provider/touch and no incoming edge in that saved index. This establishes no indexed outside caller loss; it is not a claim that the saved index covers every current image use. `provider-closure.json` records current object/receipt checks and this index scope.

The candidate's route set is intentionally different because the real RTTI graph and typed copy/destructor dependencies are now present. It must not be described as an unchanged-route proof. The exact graph and established live providers explain those changes; root's normal selected-provider and batch checks remain required.

## Ledger and owning cleanup boundary

The existing `reverse/data_ledger.csv` row at `0x8FE2FC` already names canonical `__TI1?AVINIException@@`. The old `_respawnThrowInfoAnchor@Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdate.cpp` is a stale alias token in that row's derived names cell. The ledger's size 2148 is a heuristic bound, not the 16-byte ThrowInfo extent; `defs=24` is aggregate diagnostic data, not alias count.

`tools/data_ledger.py` has no scoped alias-delete operation. The supported preview is:

```
python3 tools/data_ledger.py --out build/respawn-parser-metadata-review-20261103/data_ledger.after.csv
```

Run it only after the adopted source has a current normal verified object, review the whole generated diff and all missing/stale-object diagnostics, and use the owning full regeneration/check path if that diff is suitable. Do not hand-prune this alias or copy a selected edited row into the protected ledger. A deferred derived-ledger refresh should remain explicitly pending. The generator can still render after missing-object warnings and does not independently establish source/header receipts. `data-alias-review.md` records the exact tool boundaries and existing four header-accept commands. No ledger generation or tracked mutation was performed by this review.

All tracked/native reads stopped on completion. Only this scratch evidence was written; no builds, claims, network calls or gate changes were made.
