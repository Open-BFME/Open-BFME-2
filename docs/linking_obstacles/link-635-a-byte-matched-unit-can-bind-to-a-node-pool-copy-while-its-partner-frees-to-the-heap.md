### LINK-635: a byte-matched unit can bind to a node-pool allocator copy while its partner frees to the heap

**Status: Open (check gap; five units repaired, P38). Updated: 2026-11-08; inspected revision: 224133c092 (diagnostic
image) (crash-triage seat2, P37, P38). Family:
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
- **Case (P37, crash, cause still open):** rank 1's RankInfo at 0x21712270 is overlapped by the pool's chunk at 0x21712128
  (0x280 bytes); `_S_refill` then `list<ControlBarScheme*>` nodes overwrite its SciencesGranted vector during
  `ControlBarSchemeManager::init` (receipt 2026-11-08T075343Z-boot_smoke-693f2aeeaef9), and `Player::rva002AE252` walks
  off a page. The heap header below the chunk already reads 0x11 when first observed (receipt
  2026-11-08T083558Z-boot_smoke-8929915d61b4), but no free is on record and the first user is unidentified. **The P38
  repair does not clear it:** receipt 2026-11-08T091110Z-boot_smoke-079162d29578 carries the same flag on the two pool-to-heap
  units and crashes identically. The chunk appears after TheEva and before MapCache, so those units did not make it.
- **Repair (P38):** `/Ireference/shims/bfmealloc_alloconly` on the five units below. It holds only the allocator change;
  the full `bfmealloc` root moves three rows in `EvaMessageVectorAssign.cpp` through its `_algobase` copy helpers.

  | Direction | Element type | Unit repaired |
  |---|---|---|
  | pool to heap | `EvaMessageInfo` | `EvaMessageVectorAssign.cpp` |
  | pool to heap | `_Rb_tree_node<pair<AsciiString,bool>>`, `<AsciiString,MapMetaData>` | `MapCache_ctor_Thunk.cpp` |
  | heap to pool | `BfmeAsciiScalarValue8` | `StringContainerRecordCopyBFME2.cpp` |
  | heap to pool | `Rva005E2B0EElement` | `StrategicInGameUIRegionDetailsStructuresPage.cpp` |
  | heap to pool | `SaveMapPreview` | `SaveMapPreviewCopy.cpp` |

- **Proposed check:** classify every linked allocate and deallocate copy per element type by allocator family, and flag a
  split. A scan of plain allocator copies is not enough: in image 224133c092 node-allocator call sites sit in 250 functions,
  90 of them inlined into bodies such as `_M_create_node` and `_M_initialize_map`, which such a scan cannot classify. The P37
  type was not among the six splits the plain scan found, so a check has to pass that case before it is relied on.
