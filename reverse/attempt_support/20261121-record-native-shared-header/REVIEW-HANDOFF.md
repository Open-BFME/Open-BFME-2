# Independent review: actual native Rva001EB15A header adoption

Sicher within the scoped evidence: **review_passed=true**, with no blocking findings. Snapshot is HEAD `9a39def1d3bc41048f8a2b1f555f8e436ea31124` plus the exact eight uncommitted paths below. This is a read-only review: zero compiler, claim, production, shared-object/index/cache or Git mutations. Private copies of the five already-existing current objects and sidecars are retained here for reproducibility.

## Actual change and semantics

The only tracked source edits replace five local Rva001EB15A declarations with includes of the one native-generated header; canonical_classes.csv gains one row. The new header and its native contract are untracked Root-owned inputs. No function body, flags, directives, ledger, pins, data/alias ownership, other header or gate/register policy is edited. The actual patch is `ACTUAL-UNCOMMITTED.patch.txt`; the exact generated header/contract are copied here.

The canonical struct is a nonvirtual 24-byte record: int fields at +0/+4/+8, genuine UnicodeString at +C, AsciiString at +10 and one-byte bool at +14. The existing native contract's five-view consensus has no queued disagreement or base/vslot. Its generated size/no-vptr/offset assertions agree with the previously evaluated native layout assertions; all five current sources pass the native owner. The empty trailing three bytes are natural alignment, not an invented field. Offset-generated class/field names remain provisional; no original EA names or original access-specifier claim is made.

The three APIs are genuine declaration-only default construction, const-reference copy construction and destruction, with existing providers. Tracker loses its old `__declspec(noinline)` declaration; Carryover now sees an explicit copy declaration and Freelist an explicit destructor declaration. These are visible declaration reconciliations, not added bodies. Current actual COFFs confirm no changed lifetime emission, call target, vtable, initializer or provider selection. Carryover's former private field visibility becomes canonical struct visibility; this has no emitted effect in the verified family.

## All five current native objects, without recompiling

| Source | Closest bound frozen pre-header source/object | Runtime nodes before/after | SafeSEH before/after | Complete runtime graph |
|---|---|---:|---:|---|
| CarryoverUnit.cpp | dcbd bool candidate, exact source banked at86df and identical at9a39 | 29/29 | 2/2 | equal |
| UnitRevivalTracker.cpp | 8ceca name-alignment candidate, exact source banked at9a39 | 79/79 | 8/8 | equal |
| Rva0037DF2CCopy.cpp | 86df typed-record candidate, exact source banked at8ceca and identical at9a39 | 8/8 | 1/1 | equal |
| ObjectConstructor.cpp | 86df typed-record candidate, exact source banked at8ceca and identical at9a39 | 226/226 | 1/1 | equal |
| FreelistPool.cpp | dcbd bool candidate, exact source banked at86df and identical at9a39 | 37/37 | 3/3 | equal |

Each baseline's frozen production-source hash equals `git show 9a39:<path>` exactly, and its COFF/sidecar matches the immutable trial receipt. Copy/Object baseline objects contain the explicitly recorded nonemitting diagnostic typedef assertions; no substitute compiler run was made. Every actually opened pre-header input remains hash-identical. All five current native `build/match` objects pass the native read-only `compile_is_current` check, actual object MD5/source/dependency/command receipts and identical original compiler profile flags. Current input hashes are bound separately, including the new header. No global provider/index inventory was required or performed.

Across all 379 runtime sections there are zero added, removed or changed nodes, bytes, actual relocation destinations, external definitions, COMDAT selections, weak DEFAULT/undefined contracts, CRT roots or directives. Every ordered bound SafeSEH sequence remains equal. This comparison excludes debug sections and maps compiler-local label/section indices to unique physical section identities; it does not mask bytes or invent symbol aliases. The raw object hashes are not asserted identical. `GRAPH-COMPARISON.json` records all bindings, identities, deltas (none) and the immutable pure graph-reader hash; `CURRENT-*.obj` preserves the actual reviewed objects.

The removed Tracker noinline declaration specifically preserves its one external default-ctor relocation: UnitRevivalEntry's ThingTemplate constructor at offset128 still targets `??0Rva001EB15A@@QAE@XZ`, with no local definition before or after. The real default-ctor provider remains in Freelist. The prior 54-byte destructor ANY2->NODUP1 change was already banked before9a39; this header diff introduces zero further selection changes. The generated virtual-probe child is assertion-only and emits no new vtable/helper/data node in these objects.

## Native proof attribution and limits

Root's `record-shared-header-apply.log`, state JSON and `build/header_lane/Rva001EB15A.json` show native `run --generate --variants data+includes --apply`:5/5 sources passed, no failure and zero queued units. Contract queue is also empty. The normal source build passes145/145 existing rows, strings/floats and owning EH-local-label checks; native link_check passes5/5. These runs were performed by Root, not repeated by the reviewer.

The reported8,036->8,052 (+16) predicted LINKED bytes are already present in the pre-header `record-fields-normal-link-before.log` (Carryover475->491); they are not new coverage or improvement from this adoption. link_check is a scoped prediction against its bound census, not a new authoritative full-image link or runtime/menu/skirmish/save-load proof. The unrelated BfmeFixedStorage128 queue record remains unchanged.

Exactly eight dirty paths are accounted for: the five named sources, generated header, native contract and canonical registry. Nothing was staged/committed/published by the reviewer. Root's ordinary explicit commit hook, any required dependent-source gate and later real link remain authoritative. This prerequisite earns **0 new bodies, 0 new C++ bytes, 0 completed original UnitRevival tasks**. PC remains on.

## Key bindings

- Header SHA256: `e3235cda746c74fcb4111b1e3ee23c7ff90cabbec5a56dd1d860efa048f469cf`.
- Native contract SHA256: `b8f8ac879d69288fd82b1909733d531d39609176600555b55fcaaa2d66ae342a`.
- `SUMMARY.json` exposes `base` and `review_passed` for Root's bank script. `MANIFEST.json` freezes the review files; no further edits follow handoff.
