# Old const allocator provider/consumer audit

Read-only bounded discovery, 2026-11-03. Full object hashes, receipts, exact code/relocations, caller names and row witnesses are in `provider-consumers.json`; rerunnable scratch reader is `provider_consumers.py`.

## Results

- The saved index is 2026-11-02 08:35 / `984a4cdc4d`, based on census 06:54 / `357ce2a88f`. It has no per-object reference contributions. Discovery is bounded to its 17 exact-name touching objects, all available in the current cache; no claim is made about new sources absent from that old index.
- Across 16 outside sources: 46 actual runtime code relocations to the 17 old QBE names; all are E8 calls or E9 tail jumps. 17 edges belong to matched caller rows; seven edges target a name not defined in their own object. The remaining edges have a same-object provider.
- Nineteen outside QBE provider copies cover 12 of the 17 names. Every complete body and symbolic relocation list equals root's immutable exact control object. This is a body/provider fact, not approved TU placement or final COMDAT/link selection.
- Fifteen of the 17 cached objects have matching source/object/recorded-dependency MD5s. This does not establish current compiler-command or include-search inventory, and no strict-current receipt is manufactured.
- Freshness exceptions: `StlportVectorGrowthFootprints.cpp` source differs from its receipt (object matches); `StlportReserveRva004DA039.cpp` object differs from its receipt (source/dependencies match). All objects and sidecars were stable during this bounded read.

## Per-name alternatives

Full WWLib prefix for filenames below: `Code/Libraries/Source/WWVegas/WWLib/`.

| Native row | Element | Outside provider copies | Qualified copies* | Outside caller sources |
|---|---|---:|---:|---:|
| 0x0007E364 | BfmePod44 | 2 | 2 | 3 |
| 0x004103BE | BfmePod52 | 1 | 1 | 1 |
| 0x0029B27B | BfmePod60 | 0 | 0 | 0 |
| 0x00360C45 | BfmePod148 | 0 | 0 | 0 |
| 0x001EAEBD | BfmePod172 | 2 | 2 | 2 |
| 0x000B407F | BfmePod180 | 0 | 0 | 0 |
| 0x0040A673 | BfmePod104 | 2 | 2 | 3 |
| 0x00329D34 | BfmePod128 | 3 | 2 | 3 |
| 0x0014DB83 | BfmePod76 | 1 | 1 | 1 |
| 0x0004551D | BfmePod92 | 0 | 0 | 0 |
| 0x002194AD | CreateAHeroSubClass@CreateAHeroManager | 1 | 0 | 1 |
| 0x000B40CB | BfmePod248 | 2 | 1 | 2 |
| 0x000B409E | BfmePod252 | 1 | 0 | 1 |
| 0x002CF069 | BfmePod260 | 0 | 0 | 0 |
| 0x004D94B3 | BfmePod340 | 1 | 1 | 2 |
| 0x004E4E5A | BfmePod68 | 1 | 1 | 1 |
| 0x0023D35B | BfmePod88 | 2 | 2 | 2 |

*Qualified means only source/object/recorded-dependency equality, not full strict-current validity.

The five names with no outside provider or caller found are BfmePod60, 148, 180, 92, 260. Pod148/180/92 have local runtime callers in the migrating unit; Pod60/260 have no runtime incoming in these inspected objects. These are index-bounded observations, not proof of global nonuse/dead-stripping.

CreateAHeroSubClass and BfmePod252 have only the source-stale GrowthFootprints outside copy. Those two alternatives therefore are not currently source-authenticated. Pod128 and Pod248 also have GrowthFootprints copies but have other hash-qualified identical providers.

## Exact outside provider sources by element

- UBfmePod44: `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp`, `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod44_allocate_copy.cpp`
- UBfmePod52: `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp`
- UBfmePod172: `Code/Libraries/Source/WWVegas/WWLib/Rva001EBD3BFinish.cpp`, `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod172_allocate_copy.cpp`
- UBfmePod104: `Code/Libraries/Source/WWVegas/WWLib/StlportCopyRva003F610F.cpp`, `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod104_allocate_copy.cpp`
- UBfmePod128: `Code/GameEngine/Source/GameLogic/Map/SidesList.cpp`, `Code/GameEngine/Source/GameLogic/Map/SidesListCastleBuildLists.cpp`, `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp` [source-stale]
- UBfmePod76: `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp`
- VCreateAHeroSubClass@CreateAHeroManager: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp` [source-stale]
- UBfmePod248: `Code/Libraries/Source/WWVegas/WWLib/StlportPod248CopyBackward.cpp`, `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp` [source-stale]
- UBfmePod252: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp` [source-stale]
- UBfmePod340: `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod340_allocate_copy.cpp`
- UBfmePod68: `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp`
- UBfmePod88: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorInsertOverflowRva004E38DA.cpp`, `Code/Libraries/Source/WWVegas/WWLib/stlport_uninitialized_copy12.cpp`

## Outside runtime caller sources

- `Code/GameEngine/Source/GameLogic/Map/SidesList.cpp`: 2 edges / 1 allocator names.
- `Code/GameEngine/Source/GameLogic/Map/SidesListCastleBuildLists.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/Rva001EBD3BFinish.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/StlportCopyRva003F610F.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/StlportPod248CopyBackward.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/StlportReserveRva004DA039.cpp`: 1 edges / 1 allocator names [receipt hash exception].
- `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp`: 8 edges / 4 allocator names [receipt hash exception].
- `Code/Libraries/Source/WWVegas/WWLib/StlportVectorInsertOverflowFamily.cpp`: 4 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/StlportVectorInsertOverflowRva004E38DA.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp`: 8 edges / 4 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_malloc_bodies.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_uninitialized_copy12.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod104_allocate_copy.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod172_allocate_copy.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod340_allocate_copy.cpp`: 2 edges / 1 allocator names.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod44_allocate_copy.cpp`: 3 edges / 1 allocator names.

The seven undefined-target edges are: the rowed reserve 0x004DA039 -> BfmePod340 (one, receipt object mismatch); StlportVectorInsertOverflowFamily -> BfmePod104 (four, including two same-RVA rowed 183B overflow names at 0x003B9184 and two unrowed proxy copies); stlport_pod_vector_malloc_bodies -> BfmePod44 (two unrowed proxy/overflow copies). Exact spellings/relocation offsets are archived in JSON.

## TU approval boundary

The committed map's recorded functions fingerprint does not equal current normalized functions.csv. Thus this audit establishes **no fresh rehome approval**. Narrow committed records: Pod60 at 0x0029B27B says approved `Code/GameEngine/Source/GameClient/InGameUI.cpp`; Pod92 at 0x0004551D says proposed `Code/GameEngine/Source/Common/SubTitleWindow.cpp`; the other 15 addresses have blank TU/confidence. Even the one committed approved value must not be used while stale.

A supported fresh in-memory map is required before any actual move. No regenerated map, shared picker cache, Code, ledger or check was written. Do not infer permission to rehome QBE rows into their alternative emitters merely because identical bodies already appear there. Consumer migration, old-provider retention/admission, source placement and normal verification remain root's decisions.

No compilation, tracked edits, claims, Git operation or network performed.
