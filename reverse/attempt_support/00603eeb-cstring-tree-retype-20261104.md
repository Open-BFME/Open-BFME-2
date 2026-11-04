# 0x00603EEB / 0x00603B9C: the "map<unsigned,void*>" copy path is a C-string tree (2026-11-04)

Served item: code-identity key for `_M_copy` (0x00603B9C) in
`Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_ptr_lower.cpp`.

## State on 2026-11-04 (a1ad5f0db7)

- After `./build.sh` of the source and of the 4 missing ledger objects plus 5 stale
  providers (PorcupineFormationBody, RespawnBody, _com_error,
  FXShaderParameterSourceNamespaceWW3D, STLMallocAlloc0OutOfMemory,
  stlport_modulefactory_map_copy, stlport_modulefactory_map_copyctor_00413EE6,
  stlport_rb_tree_increment, stlport_rb_tree_rebalance),
  `repair_queue.py retire identity` no longer finds the `_M_copy` → `_M_clone_node`
  key. That part of 624094889b works.
- Retirement is still refused because of an unbaselined finding in the same source:
  the copy ctor `??0?$_Rb_tree@IU?$pair@$$CBIPAX@...@QAE@ABV01@@Z` (0x00603EEB) binds
  `??0?$_Rb_tree_base@U?$pair@$$CBIPAX@...` at 0x0030087C, and the copy the link
  keeps is not retail's body.

## Target facts (retail bytes)

- 0x0030087C (36B) base ctor: `push 0; push 0x20; call 0x000307F0`, so the header node is
  0x20 bytes (a 16-byte value). A `pair<const unsigned, void*>` node is 0x18, so
  **no build configuration of the uint/void* type can emit this body**. This explains the
  "this bfmealloc unit's own copies differ" comment in Win32BIGFileSystem.cpp.
- 0x00603B9C `_M_copy` → 0x00413E55 clone → 0x0029E11A create_node (`push 0x20`) →
  0x0041360E `_Construct` (copies 4 + 12 bytes, POD).
- 0x00603B0A (same tree's `_M_insert`, rowed in Win32BIGFileSystem.cpp) calls 0x0029E11A
  and compares keys through 0x006038D4 (`Rva0006038D4CStrLess`, strcmp `setl`), with
  the comparator at tree+8.
- 0x00603EEB has two callers, 0x00603FD2 (`Rva00603FD2` ctor) and 0x0060426C
  (`Rva0060426C` copy ctor, member map at +4). 0x0060426C is the value copy of the outer
  tree 0x006044A0 (create_node 0x00604374 allocates 0x20 at +0x10).

## Structural inference

The tree at 0x00603B0A..0x00603EEB has a `const char*` key, `Rva006038D4Less` ordering and a
12-byte POD mapped value: the inner map of `Rva0060426C`. It is not `map<unsigned,void*>`.
The ledger name is an ICF guess. `_M_copy` and the copy ctor bodies do not encode the
value type, so they byte-verify under either name. `reverse/tu_map.csv` approves
0x00603B9C, 0x00603EEB, 0x007A6B22 and 0x007A6B2A to Win32BIGFileSystem.cpp.

## Remedy (not attempted: too large for one pass)

Retype `Rva0060426C::m_map` and `TreeIntPtr00603FD2` in Win32BIGFileSystem.cpp to
`_Rb_tree<const char*, pair<const char* const, Mapped12>, _Select1st, Rva006038D4Less>`.
Then rehome and rename 0x00603B9C, 0x00603EEB and their funclets, and rename the
placeholder rows 0x00603FC0 (map copy), 0x00603FD2 and 0x00604251, whose signatures
spell the old type. Every member the unit then references needs a definer that
equals retail and a fold pin: base ctor 0x0030087C (+ alloc_proxy ctor 0x0014F3C4),
base dtor 0x0007FAB3, tree dtor 0x00357C6A (+ its `_M_erase` chain), clone 0x00413E55,
create_node 0x0029E11A, `_Construct` 0x0041360E. Win32BIGFileSystem.cpp currently keeps
the uint/void* names decl-only so that stlport_map_int_ptr_lower.cpp provides them.
After the move, `retire identity` on stlport_map_int_ptr_lower.cpp should drop the
`_M_copy` key.
