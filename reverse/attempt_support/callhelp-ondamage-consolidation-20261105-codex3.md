# CallHelpOnDamage onDamage consolidation

Base: `bd15bd2dac`. Index: 2026-11-05 05:17 at `c95fcfcfcd`;
the fetch kept that local index and imported the published object archive.

The seed's one-slot leaf view and the onDamage donor's flat module-data view
prevented their composition. Both now use the same DamageModule-based leaf
declarations and the constructor's INI-backed module-data layout, including
the real filter member at +0x18. The seed uses the canonical DamageModule
header; no constructor or new virtual-table definition is emitted there.
The donor retains its complete function and its existing local names.

Prerequisite verification:

- `./build.sh` on both files: 16/16 rows exact, including all seven funclet
  rows, the parser data row, string references and floating-point literal.
- Both declared-unmatched checks pass.
- Link previews: seed LINKS 265 -> 265 B; donor LINKS 343 -> 343 B.
- The supported guarded dry run now accepts the seed and onDamage donor
  together, 16 rows. It previously accepted no donors.

A separate constructor trial using the canonical header byte-matched but
introduced the unprovided DamageModule::xfer name through its vtable. The
trial was reverted and logged. Its loadPostProcess provider landed after
the index. The remaining constructor, Xfer, deleting-wrapper and module-data
destructor donors still need separate reconciliation; the latter fails bytes
under the seed flags. No census gain is claimed.

Next: commit these declaration prerequisites, apply the supported merge,
verify the final TU and audit its removed path before publication.
