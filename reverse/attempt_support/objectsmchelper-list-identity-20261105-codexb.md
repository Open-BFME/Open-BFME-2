# ObjectSMCHelper timer-list constructor identity

Inspected revision: `abe23372b65c`; worker: `yasinschroeder-codexb`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper_Rva002927f8.cpp`.

Target facts: retail's 81-byte ObjectSMCHelper constructor at RVA 0x002927F8
calls the 41-byte list-base constructor at 0x0035C9A6. That constructor calls
the allocation proxy at 0x0014F3C4 and `allocator<char>::allocate` at 0x000307F0.
The original object instead emitted a 38-byte Gen_p8pod list-base constructor,
allocating through `__node_alloc<false,0>::allocate`. This is an allocator
configuration mismatch, not evidence of the timer element's original type name.

Adding the existing `reference/shims/bfmealloc` include path makes the list-base
constructor reproduce the whole 41-byte retail body. The proxy specialization
has the complete 11-byte body `8bc18b4c24088908c20800`, with no relocations.
`pin_admission.py --add` accepted its ICF fold onto 0x0014F3C4 using this matched
source as `fold-proof`; the tool admitted one pin/hatch. No type was renamed.

Verification:

- `./build.sh` passes the source's sole matched row, including string, float and
  import checks. The 81-byte constructor's code and relocation names are unchanged.
- `find_declared_unmatched.py` reports all defined functions already matched.
- `pin_consistency.py --check` passes with zero new or stale findings.
- After refreshing the participating Object.cpp provider through `./build.sh`
  (98/98 rows), `repair_queue.py retire identity SOURCE` reports PASS and removes
  the one identity key, with zero findings remaining for this source.
- Current-input `link_check.py SOURCE` remains LINKS, 81 -> 81 authored bytes,
  against the 2026-11-05 15:52 index at `112a456a2c`.

Object comparison: external code definitions decrease from 24 to 22; there are
no added definitions. The removed copies are `__stl_new` and
`__node_alloc<false,0>::allocate`. Seven existing template helpers change:
the list-base constructor/destructor/clear, allocation-proxy allocate/deallocate,
and node allocator allocate/deallocate. The other 15 retained external code
definitions, including ObjectSMCHelper's constructor, are unchanged. The normal
outgoing link audit must judge affected consumers of these helper changes.

This retires one code-identity debt. It does not change census-linked coverage,
claim a real-link or runtime pass, or resolve LINK-333's separate destructor
consolidation prerequisites. Carry this changed-helper scope into the next
normal census if the outgoing audit cannot establish its wider closure.
