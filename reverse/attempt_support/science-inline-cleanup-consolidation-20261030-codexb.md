# Science cleanup composition and placement evidence (2026-10-30)

Base: `1651fed293`. Scope: `Code/GameEngine/Source/Common/RTS/Science.cpp`
and its approved two-row `Common/Rva001FF6D7List.cpp` donor.

## Placement investigation

The default picker served three provisional Science TU rows. None is a missing
body: all have current matched owners. They remain provisional; this pass adds
no TU evidence or approval.

- `001FF354` is the 22-byte reload-latch consumer on `Rva001FF909`, whose
  sibling `001FF625` emits the Sciences reload message. The map's K class
  bracket is insufficient placement evidence by itself. The message establishes
  subsystem behavior, not a recovered donor class or a source-file location.
- `001FF36A` is a 63-byte pool initializer: fields at +0, +0C, +10 and +14
  receive defaults/callbacks/context, and a missing +4 block calls the rowed
  `002E8548` grower. Its Science assignment is an address bracket; its original
  class and TU remain unproven.
- `001FF3A9` is a four-byte slot-zero virtual forwarder, with a proven folded
  twin in `RvaLookupFieldOrZeroFamily.cpp` and callers in unrelated subsystems.
  The WorldBuilder InGameHelpBox::Show lead does not uniquely name this folded
  body or place its generic owner in Science.cpp.

Further approval needs independent source-path or receiver/type evidence.
No placeholder is renamed from a same-byte or same-name lead in this pass.

## Compiler-context prerequisite

The fresh in-memory map has 65 approved rows in five clean sources, with eleven
mixed sources retained. The initial supported dry run accepts no donor: the
parser has private ScienceStore declaration conflicts; both STL donors and the
list donor lose code bytes.

For the list donor, a bounded seed/list composition verifies 21/22 rows. Only
`001FF6AE` changes: after its call to `001FF55F`, MSVC knows the visible
recursive callee preserves EDX and keeps the receiver there. Retail instead
saves/restores ESI. Marking the recursive cleanup declaration `inline` restores
all 22 rows. `noinline` on either declaration or definition leaves the same
mismatch; `inline` on either restores the exact caller. This is compiler-context
evidence, not recovery of the helper's original class or method name.

Only the seed's declaration changes. The standalone seed still verifies all
20 rows and has exactly the same external object facts: 64 COMDAT identities,
64 definitions, 34 unresolved names, no weak aliases, 37 reference roots and
48 reference-graph entries. Each COMDAT identity includes its normalized body,
relocation targets and size; all sets/edges are unchanged. The existing
22-row seed/list baseline passed before the change.

The pool ownership obstacle recorded on 2026-10-28 has since been repaired
upstream: the full 24-byte pool is matched in AIPathfind.cpp and the overlapping
interior-pointer row is gone. Current merge diagnosis reaches byte comparison
instead of that old provider refusal. Preserve the older report as history.

Scratch experiments and output are under `build/science-20261030-codexb/`:
`diagnose.py`, `variants.py`, `compare.py`, `inline-build.txt` and
`inline-dry-run.txt`. These are local evidence, not new matched progress.

The supported inline dry run accepts precisely the seed/list pair (22 rows),
with the census-linked-unit guard passing; it still rejects the parser and both
STL donors. Strict preparation subsequently verifies 22/22 rows with reusable
receipts. An initial preparation overlapped the dry-run's temporary Code files
and correctly refused its moving inventory; the sequential run passes.

Ordinary preview against the published `12b9e7a7c0` index retains LINKS for
the list donor (70 authored bytes). The seed preview retains its existing
duplicate ScienceMemo `_Rb_tree_base` constructor from older, already-absorbed
census providers. Its complete external object facts are unchanged, so this is
not a new loss caused by the declaration. The next census must judge current
consolidated owners. No linked-byte increase is claimed.

The staged-tree consumer audit is INCONCLUSIVE against refreshed index
`e1f7c1dd18`, which predates the outgoing base. The first affected consumer
without a current receipt is
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. Carry this
consumer and the composition into the next census; local object identity does
not substitute for complete consumer/link closure.
