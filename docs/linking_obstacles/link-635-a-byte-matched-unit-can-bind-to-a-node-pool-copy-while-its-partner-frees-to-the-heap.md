### LINK-635: a byte-matched unit can bind to a node-pool allocator copy while its partner frees to the heap

**Status: Open (check gap; twelve units repaired, P37, P38 and P44). Updated: 2026-11-08; inspected revision: 3c5bff6a9b (diagnostic
image) (crash-triage seat2, P37, P38; crash-prevention seat4, P44). Family:
[LINK-630](link-630-a-byte-matched-row-whose-calls-bind-to-local-unrowed-comdats.md).**

- **Gap:** `reference/shims/bfmealloc/README.md` records that retail's containers allocate through the raw allocator
  0x000307F0 and free through `_free` 0x00030830. A stlport unit without a `bfmealloc` root still emits stock
  `allocator<T>` copies, which use `__node_alloc`. Its rowed bodies byte-match retail because the call targets are masked,
  so the gate passes, and at link the copy is a local COMDAT. One element type can then allocate from the pool and free to
  the heap, or the reverse, depending on which units emit which side. Neither the byte gate nor `link_check` reports it.
- **Why it matters:**
  - **Pool to heap:** `_S_refill` returns a chunk's first object as an ordinary node, and that pointer is the chunk's heap
    pointer. Freeing it through `_free` would return the whole pool chunk to the heap while the pool keeps carving it.
  - **Heap to pool:** a heap block pushed on a pool free list is handed out again as a node while the heap still owns it,
    which is its own corruption path. This entry has no boot receipt for that path; it is inferred from the allocators.
- **Case (P37, crash, cleared):** `SidesList::SidesList` -> `TeamsInfoRec::TeamsInfoRec` -> `vector<Rva00196D90Element>(n)`
  (0x0032BDE7) -> `__node_alloc::allocate` made the pool's first chunk, 0x21712128, heap header 0x289. `SidesList::clear` ->
  `TeamsInfoRec::clear` -> `vector<BfmeThingUBB>::~vector` -> `_free` freed that pointer, one object spelled under two element
  types (receipt 2026-11-08T101057Z-boot_smoke-82cc0b4654b1). The heap re-carved the chunk: rank 1's RankInfo at 0x21712270 sat
  inside it, `list<ControlBarScheme*>` nodes overwrote its SciencesGranted vector during `ControlBarSchemeManager::init`
  (receipt 2026-11-08T075343Z-boot_smoke-693f2aeeaef9), and `Player::rva002AE252` walked off a page.
  **Repair (P37):** `bfmealloc_alloconly` on `Rva00196D90MemberConstructor_Rva0032bde7.cpp`. Verification, scope one image with
  diagnostics: receipt 2026-11-08T111958Z-boot_smoke-023afde5b726 keeps rank 1's vector zero and passes PlayerList.
- **Repair (P38, does not clear P37):** `/Ireference/shims/bfmealloc_alloconly` on the five units below. It holds only the allocator change;
  the full `bfmealloc` root moves three rows in `EvaMessageVectorAssign.cpp` through its `_algobase` copy helpers.

  | Direction | Element type | Unit repaired |
  |---|---|---|
  | pool to heap | `EvaMessageInfo` | `EvaMessageVectorAssign.cpp` |
  | pool to heap | `_Rb_tree_node<pair<AsciiString,bool>>`, `<AsciiString,MapMetaData>` | `MapCache_ctor_Thunk.cpp` |
  | heap to pool | `BfmeAsciiScalarValue8` | `StringContainerRecordCopyBFME2.cpp` |
  | heap to pool | `Rva005E2B0EElement` | `StrategicInGameUIRegionDetailsStructuresPage.cpp` |
  | heap to pool | `SaveMapPreview` | `SaveMapPreviewCopy.cpp` |

- **Proposed check:** compare call graphs, not type names: list rows whose image body reaches the node pool within a bounded
  depth while retail's body at the row's address does not. A scan pairing allocate and deallocate per element type cannot see
  P37's pair, and cannot classify the 90 functions in image 224133c092 with inlined node-allocator calls. A seed of the graph
  form flags both the P37 and P38 units and lists 39 rows on image 8ada236aeb (before P38); those rows are not yet vetted.
- **P44 (2026-11-08, crash-prevention seat4, bytes and objects only, no boot):** crash triage's `p37_family.py`, vetted on image 3c5bff6a9b,
  flagged 27 rows: 15 `$L` label collisions, the pool's own handler, and 11 rows in six element types, now on
  `bfmealloc_alloconly`: `list<ControlBarScheme*>`, `list<Rva00242EE7Obj*>`, `list<Rva005CD018Obj*>`, `list<Rva00293486Record>`,
  `vector<Elem003AF9E0>`, `vector<W3DAnimationInfo>`. A row's own unit having the root is not enough: `list<ControlBarScheme*>`'s
  rows had it, but the image took `_M_create_node` from another unit's COMDAT. So the check has to judge every link input's
  copy of a name, not the row's source. `p37_family.py` was never a full check: bounded depth, direct calls only.
