# Nested-vector constructor link repair

Base: `58059061af`. Target: `0x002BC339`, with its public fill wrapper
`0x002BBC5F` and EH handler `0x0077686B` in
`Code/GameEngine/Source/Common/Rva0019D850NestedVectorRelease_Rva002bc339.cpp`.

The original unit byte-matched all three rows but failed the link preview on
two emitted callees: its allocation base used the node allocator, and the
harvested inner `_Vector_base` destructor pin named retail's full vector
destructor at `0x002BBB57`.

## Evidence and repair

Target facts: `0x005C8C37` is the 60-byte allocation base. Its allocator proxy
constructor calls `0x0014F3C4`, then its 28-byte allocator calls `0x00395928`,
which scales the count by 12 and calls BFME's allocator at `0x000307F0`.
The allocator-only shim emits this shape without replacing the fill helpers.

Target lifetime facts: the 63-byte destructor at `0x002BBB57` calls the range
destructor at `0x002BB6BE`. That body steps 20 bytes and calls `0x002B6B4C`,
whose buffer pointer is at offset 8. The existing typed provider is
`stlport_destroy_member20_2bb6be.cpp`. The original record name remains unknown;
the local element representation records only its 20-byte extent. A vector
destructor specialization forwards its range to the existing provider.

With `/EHsc`, the destructor was 59 bytes: the compiler omitted an EH state
transition around C allocation calls. `/EHs` produces the complete 63-byte
body. `pin_admission.py --add` accepted the vector destructor fold at
`0x002BBB57`, including the associative EH graph. The incorrect base-destructor
pin was removed, leaving the total pin count unchanged.

The fill worker and LivingWorldLogic only need the vector header/type spelling.
They now forward-declare the element instead of defining conflicting 12-byte
layouts. Neither source path nor ledger row ownership changes.

## Verification

- `./build.sh`: 3/3 rows in the constructor unit, 174/174 across the fill
  worker and LivingWorldLogic; string, float and import checks pass.
- `eh_verify.py`: 37 EXACT graphs across the constructor and LivingWorldLogic.
- `find_declared_unmatched.py`: all three changed sources pass.
- `check_csv.py` and `pin_consistency.py --check`: pass.
- Four-source `link_check.py`, census index `85f6b7f40c` from
  2026-10-29 15:08: constructor LINKS 0 -> 127 authored bytes;
  LivingWorldLogic retains 20,081, fill worker retains 37, and range-destroy
  provider retains 272. These are predictions, not census gains.
- `repair_queue.py retire identity` retired the wrong base-destructor binding.
  The allocation-base key remains: code identity classifies its same-object
  allocator helpers as unknown. No second debt retirement is claimed.

## Remaining work

The generated cleanups at `0x0077685B` and `0x00776863` remain untouched.
Their existing FuncInfo parent is `0x002BC339`, whose graph remains EXACT.
The inner vector destructor prerequisite for `0x00776863` is now proven.
`0x0077685B` still needs the outer base destructor identity at `0x0007FAB3`;
that address was held by another worker during this pass. Both cleanup rows
and the parent are approved for `LivingWorldLogic.cpp` in the current TU map:
consolidate the parent into its approved unit before moving the cleanup rows.

The strict staged-tree batch audit exited 2: its index records commit
`85f6b7f40c`, behind this base, and all three changed sources lack current
census-grade receipts. This comparison is unverified; the ordinary byte and
link checks above do not replace it. Carry the repair and affected consumers
into the next maintainer census and repeat the strict comparison with current
receipts.
