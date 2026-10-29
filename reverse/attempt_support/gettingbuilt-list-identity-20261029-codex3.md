# GettingBuiltBehavior list node identity

Inspected base `8468a420d3`, 2026-10-29. The default picker claimed
`0x00453B06` and its source lock. No donor source or new application name
was used for this repair.

## Target facts and repair

The 26-byte push-back at `0x00453B06` calls insert at `0x00453AB8`.
That 37-byte body calls the existing `Rva004534A1Create` owner at
`0x004534A1`, links the node and returns through its iterator output.
The creator allocates 28 bytes and calls `Rva0045323CCopy` on node +8;
the latter calls the existing 20-byte `Rva004530ED` copy constructor.
The list-slot and transfer callers already describe that record family.
These are target call/layout facts, not proof of an original element name.

The helper's legacy pointer-list template instead emitted insertion of a
pointer-sized entry. Specializing its node creation to call the existing
record-node owner fixes that emitted insert without changing the row name,
any pin, caller, shared header, ledger coverage or source path. The obsolete
node-allocator emission override is removed. The placeholder list identity
and the transfer caller's existing alias remain future reconciliation work.

## Checks

- `./build.sh` on the helper, `GettingBuiltBehavior.cpp` and
  `GettingBuiltBehaviorXfer.cpp`: 24/24 function rows exact; string, float
  and import checks pass. The helper's frozen-file check passes.
- `eh_verify.py` on the same scope: one EH graph EXACT, none missing.
- `allowed_symbols.py --source` on the helper: its sole push-back reference
  is now **fold** at `0x00453AB8`, with zero wrong bindings. This checks both
  bytes and resolved relocations of the selected insert copy.
- `repair_queue.py retire identity` removes the helper's one key through
  the owning verdict, with zero remaining findings. No hand retirement.
- Ordinary `link_check.py`, index `840db2d676` (2026-10-28 20:44): all three
  units retain LINKS, totaling 2,308 authored bytes (26 + 1,722 + 560),
  unchanged from before the repair. This is debt retirement, not a
  census-linked-byte gain.
- Strict preparation succeeds for the changed helper. The unchanged
  provider TU cannot obtain a reusable strict receipt because its include
  environment contains macro/parent-traversing roots; ordinary scoped byte
  verification covers it. No strict provider-closure claim is made.

Rejected trials were restored: a direct insert bridge changed register/stack
shape; suppressing the local insert alone preserved the push-back bytes and
passed identity retirement, but lost its 26 preview-linked bytes to an
unresolved template symbol. The final node-creation repair preserves both
the native bytes and ordinary preview closure.

External consumer selection and census confirmation remain pending. Carry
the changed insert copy, its record-node provider and callers into the next
normal census. No runtime, ownership or source-file-count gain is claimed.

The staged-tree outgoing batch audit is INCONCLUSIVE (exit 2): index
`840db2d676` predates the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer along with this repair's provider/caller scope
into the next scheduled census. The ordinary three-unit preview does not
establish that wider selection.
