# Current-object verification of the served tree-base blocker

Inspected `b9047f2d164`, isolated `build/r20`, owner
`codex-01a1071d-root-isolated-r20`. No source, header or symbol-ledger edits.

`next_work.py --claim` served the destructor at `0x00357C6A` in
`Code/Libraries/Source/WWVegas/WWLib/stlport_tree_dtor_00357C6A.cpp`, citing the
missing unsigned/pointer tree-base constructor from real-link run 43489278477,
measured commit `bd2310feee13313e1964729d3b61275a33eb6ace`.

Repair `0e4b2640a1125e9b039f30bf9b05b94f68840eec` already removed the non-retail
helper's map construction/throw and its declaration-only tree-base constructor.
The helper's existing `delete owned` still emits the actual map destructor and
scalar deleting destructor. Git ancestry confirms that repair is absent from
the measured commit and present in the inspected checkout.

Fresh verification:

- `./build.sh` passes all five rows, including the parent-owned EH action and
  handler. All declarations with bodies remain matched or explicitly recorded
  absent from retail.
- `link_check.py --prepare-current` passes; `compile_is_current(strict=True)` is
  true. The object SHA-256 is
  `89c5b5398c704b737980d3e187977c5a9fab0226840d311c77beb4ff3a205fb3`.
- Its only undefined externals are operator delete, `__EH_prolog`,
  `___CxxFrameHandler`, `__except_list` and `_free`. It no longer references any
  `_Rb_tree_base` constructor.
- The scoped ordinary preview reports LINKS, 99 -> 99 bytes, against old index
  `aa7acf764d`. That is a scoped current-object check, not a new census or a
  whole-link clearance.

Scratch proof: `build/root-tree-base-proof.json`; logs:
`build/root-tree-base-baseline.log`, `build/root-tree-base-strict.log`,
`build/root-tree-base-link-before.log`. No new implementation repair was needed.
Do not reinstate the old `0x0030087C` pin: its 32-byte header node is a different
type from this unsigned/pointer tree's 24-byte node.

The published authoritative run remains 3 unresolved, 0 duplicates, no image,
468 initializer bridges and 3,310 vtable bridges / 50,102 slots. Retirement of
this stale blocker awaits the next published real link; no measurement was
launched. No headline gain is attributed to this verification.
