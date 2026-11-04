# QuadStrip2D vector-copy reconciliation, 2026-11-04

Starting revision: `cfc7744266`. Scope: `Rva005386F5Copy.cpp` and its
`QuadStrip2D.cpp` consumer; no row, symbol or retail type-name changes.

The consolidation planner assigns the copy constructor at `0x005386F5` to
`Code/GameEngine/Source/Common/QuadStrip2D.cpp`. The initial merge dry run
rejected its private `_STL` declarations; `tu_views --dry-run` also found
that the consumer's three own pointers overlapped the donor's vector base.

Replaced the donor's private allocator/vector/base/type-tag declarations with
`<vector>` and declaration-only specializations for its existing callees.
The consumer now uses the same real `_Vector_base<BfmeE16>` inheritance and
12-byte layout. This does not establish the original element or class names.

Retail facts: `0x005385F3` (38 bytes) loops over `_Construct` at `0x00469C61`
(18 bytes), which null-checks then calls `0x0004254E` (31 bytes). That leaf
copies four dwords and returns. None allocates, calls an import or throws.
The specialization's `throw()` therefore preserves the retail worker's
contract and avoids introducing base-destructor unwind into the caller.
A derived, user-constructed empty tag preserves temporary stack-slot reuse;
a plain default-initialized local allocated a separate stack byte. Disabling
exceptions also matched, but was unnecessary with the proven callee contract.

Validation before reconciliation commit:

- `./build.sh` both sources: 18/18 rows exact; EH handler and funclet verified.
- `find_declared_unmatched.py` both sources: all defined functions matched.
- `link_check.py` both sources: both LINKS, current prediction 1,188 bytes.
  Census baseline 1,157 bytes at `a62ac1c10b` (2026-11-04 07:28).
  The 31-byte difference is the previously added folded copy row; this
  reconciliation adds no rows and claims no headline census improvement.

The other donor, `W3DAnimationInfoVectorInsert.cpp`, remains byte-rejected by
composition. Its element identity is the existing LINK-198 prerequisite;
no changes to that donor or its identity debt are part of this repair.
