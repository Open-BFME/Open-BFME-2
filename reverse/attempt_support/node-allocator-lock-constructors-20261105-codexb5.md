# STLport allocator guard constructor identities

Inspected base: `23774d42ee`. Scope: the two existing rows in
`Code/GameEngine/Source/Common/BfmeConv1424.cpp` (61 bytes total).

## Target facts

- `0x00026C10`, 28 bytes, was `BfmeThingVLY::bfmeCtorVLY`.
- `0x00026C30`, 33 bytes, was `BfmeThingVLZ::bfmeCtorVLZ`.
- The original source already selects `_Node_Alloc_Lock<false,0>::_S_lock`
  and `<true,0>::_S_lock`, respectively, and calls the rowed
  `_STLP_mutex_base::_M_acquire_lock` through the existing view.
- Both original rows pass the scoped builder before edits. The same two
  extents pass as real constructors after replacing the placeholder classes.
  No address, extent, source path, lock symbol or callee symbol is changed.
- Searches found no other Code declaration, ledger owner or pin using either
  old placeholder class. Both old row names receive deletion tombstones.

## Upstream facts and identity inference

`vendor/stlport/stl/_config.h:56` identifies STLport 4.5.2.
`vendor/stlport/stl/_alloc.c:126-150` defines `_STL::_Node_Alloc_Lock`;
its constructor at lines 130-137 conditionally acquires `_S_lock` according
only to the `__threads` template argument. This explains both specializations,
their static identities, their only call and their compiler-returned `this`.
The replacement uses that real constructor identity, not a donor source-path
claim. The source retains its existing mutex view to preserve relocation targets.

The resulting rows are
`??0?$_Node_Alloc_Lock@$0A@$0A@@_STL@@QAE@XZ` and
`??0?$_Node_Alloc_Lock@$00$0A@@_STL@@QAE@XZ`.
This changes an ordinary pointer-returning placeholder method to a constructor,
which `rename.py` cannot express (docs/naming.md, signature-change refusal).
The documented manual canonical correction path is used: source and row names,
tombstones and `re_log.py` evidence, without an invented name-basis record.

## Placement and limits

The picker claimed proposed TU `BfmeThingVLZ.cpp`; that destination does not
exist. Its approved plan contains zero rows. The consolidation planner reports
both rows unresolved, with internal-linkage review and the existing
`flag_overrides.csv` key as blockers. No TU-map regeneration or source move is
committed, and no TU-approval, file-count, linked-byte or runtime gain is claimed.
A supported original-TU anchor remains required before consolidation.

## Verification

- `./build.sh Code/GameEngine/Source/Common/BfmeConv1424.cpp`: 2/2 exact,
  before and after the identity correction; string, float and import checks pass.
- `find_declared_unmatched.py`: all defined functions are already matched.
- `check_csv.py`: passes with 99,452 function rows, unchanged in count.
- `link_check.py --prepare-current`: strict reusable receipt established for the
  one explicit source, with 2/2 rows byte-verified; census/index/status unchanged.
- `link_check.py --new-variants`: exit 0; no new divergent COMDAT variant refused.
