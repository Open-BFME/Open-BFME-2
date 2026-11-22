# Item015 complete COFF comparison — 13 proved compiler-local renames only

**Sicher:** every emitted code/data section and the complete linker-visible object graph are unchanged. The raw objects are **not identical**, and Root's historical ROOT-NORMAL-OBJECT-COMPARISON.json remains false and untouched. This new proof explains every difference rather than weakening that comparison.

Original archived object: SHA256 `1ce98e2af3e7eec7db3d74bc63fc2549e388b92e824b42a694faa9b105b3711b`. New Root-built object: `ca22c4eb4528efaa7df97a2e9e71a5328d0facd2c7b4140f32a24ee072ce530b`. Both20211B,98 sections,218 primary symbols. Production source is the prepared0f19945c8ec6296b6276f94cda4770b82ec33579ecd4c0f660395299d8df6e92 candidate; no further edit or compilation was done by the worker.

## Exact comparison, without masks

- All98 section records are identical: names, sizes, alignment, flags, **complete raw bytes**, and **every relocation triple(offset,symbol-index,type)**. This includes all code, data, EH tables/funclets/handler, directives, SafeSEH and any debug/info sections; no section was excluded.
- All56 defined code-function nodes retain their full raw bytes, symbol indices, section/offset, type and storage. Every outgoing relocation retains the same index and therefore the same physical target node. Every public definition/undefined name remains identical.
- All symbol records retain section, offset, type, storage, auxiliary count/data and COFF index. All COMDAT selection/association records and weak-default records are identical. There is no index drift, provider change or altered relocation target.
- Exactly13 **STATIC3** symbol-name fields differ:11 `$L` cleanup labels and2 `$T` EH-data labels. Each numeric suffix decreases by3. All addresses, roles, actual bytes and incoming/outgoing edges are fixed; this is observed compiler-local ID renumbering, not a new name/identity for runtime code.
- Header timestamp: **1795229771 → 1795247897**. Every one of the21 differing raw bytes is explained by the timestamp (if any) and these13 explicitly enumerated inline COFF name fields. Replacing only those timestamp/name-field bytes in the old object reconstructs the new object **exactly**. The comparator asserts this full-file equality; no generic symbol regex normalization or ignored byte ranges are used.

COFF-FULL-GRAPH-COMPARISON.json lists all98 sections/hashes/complete relocation edges, every changed name's unchanged identity attributes and incoming edges, all21 difference offsets and the reconstruction assertion.

## Binding all cleanup labels to actual constructor EH states

The unchanged917B `??0AptSpellStore@@QAE@PAX@Z` is section82. Its unchanged handler is section83+100; its DIR32 at83+101 reaches section94+88(FuncInfo). FuncInfo magic0x19930520 and11 states are unchanged. Its unwind-map relocation at94+96 points to94+0. Both .text$x83 and .xdata$x94 are selection5 ASSOCIATIVE to the same parent82.

|State|Previous state|COFF index|Explicit label mapping|Unchanged code location|Full bytes|
|---:|---:|---:|---|---|---:|
|0|-1|257|`$L12988` → `$L12985`|83+0x0|8|
|1|0|255|`$L12989` → `$L12986`|83+0x8|14|
|2|1|254|`$L12990` → `$L12987`|83+0x16|14|
|3|2|253|`$L12991` → `$L12988`|83+0x24|8|
|4|2|252|`$L12993` → `$L12990`|83+0x2C|8|
|5|2|251|`$L12995` → `$L12992`|83+0x34|8|
|6|2|250|`$L12997` → `$L12994`|83+0x3C|8|
|7|2|249|`$L12999` → `$L12996`|83+0x44|8|
|8|2|248|`$L13001` → `$L12998`|83+0x4C|8|
|9|2|247|`$L13003` → `$L13000`|83+0x54|8|
|10|2|246|`$L13005` → `$L13002`|83+0x5C|8|

The2 data labels are `$T13172`→`$T13169` at the same index306/94+88(FuncInfo), and `$T13176`→`$T13173` at index307/94+0(unwind map). Their references and all table bytes are identical. Full action bytes and every cleanup call's old/new external name and relocation index are recorded; no destructor call or state transition changed.

Root's normal build reports10 stale **ledgered** `$L` pins re-resolved through the parent's exact EH graph. This object contains11 cleanup labels in total; the count of stale ledger rows need not equal the count of local symbols. This comparison covers all11 and does not silently omit the extra action.

## Completion boundary

The object graph supports proceeding with the owning Microsoft-header scoped scan/queue refresh and ordinary commit checks. Source/import/class/header/ABI contracts have not changed, and there is no new call to `_mbscpy`, atoi or strncmp. No source changes, compiler invocation, queue write, Git/claim action or baseline/normalization-tool edit was performed during this review. The16/16 native build is Root's separately preserved result; no new link or runtime result is claimed.
