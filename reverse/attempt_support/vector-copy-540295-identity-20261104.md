# Vector copy 0x00540295: construct camera-track keys

Inspected revision: `c0177ca98afc2f41d501fa841d3eef38ed4115b0`.
Source: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorRva00540295CopyCtor.cpp`.

## Target facts and existing ownership

The 71-byte vector copy constructor at 0x00540295 calls the 38-byte copy
worker at 0x005400B4. That worker advances by 40 bytes and calls the 18-byte
`_Construct<Rva0054000B, Rva0054000B>` at 0x00540070. The latter calls the
29-byte element copy constructor at 0x00540036, which copies an integer and
calls the 51-byte inner scalar/block copy constructor at 0x0053FF5F.
This chain does not allocate or throw.

Those callees already have rows. The source's size-only
`Rva00540295Element` view instead instantiated a trivial byte-copy worker,
whose symbol was pinned to 0x005400B4. The pin reproduced the constructor's
displacement but its compiled worker was not retail's body. This was the
source's one registered `wrong` code-identity finding.

The ledger also has constructor rows at 0x00540295 under
`Rva00540295Words` and `Rva0054000B`. No row is added, removed, renamed or
moved here. Their ownership cleanup is separate. The application's original
element name remains unknown; the camera-track interpretation comes from
the existing target-derived owners, not an external donor source.

## Repair

Specialize the existing view's copy worker as a C++ loop calling the rowed
typed `_Construct` through pointer casts. Declare that construction worker
`throw()` because the target copy chain above cannot throw. This retains
the constructor's existing exception/code-generation behavior without
changing compiler flags, pins or linker aliases.

A declaration-only copy worker changed exception and empty-tag handling.
Disabling exception handling restored the constructor only with a visible
allocator getter, but then changed the allocation base's emitted body.
Those trials were discarded. The final loop and exception contract keep
the original compiler flags and existing allocator implementations.

## Verification

- `./build.sh` on the edited source: **1/1 exact**; string, float and import
  checks pass. `find_declared_unmatched.py`: all defined functions matched.
- Read the already-built object through `build.compile_function` (no manual
  compilation/cache write): the constructor's emitted copy worker is exact
  at **0x005400B4 / 38 B**, allocation base at **0x0053FF92 / 60 B**, and
  allocator getter at **0x0021983A / 7 B**, with no unresolved relocations.
- Refreshed the identity check's 158 missing objects and 9 stale providers
  through one scoped `./build.sh` invocation: **908/908 exact across 167
  sources**, 24 data rows verified; string, float and import checks pass.
- `repair_queue.py retire identity` on the source: **PASS, one key retired,
  zero remaining**, with no new findings. No register line was hand-deleted.
- `link_check.py` with the published index **2026-11-04 11:27 at
  3a8028f34e**: **6/6 LINKS, 543 -> 543 B**. Scope: edited constructor,
  `stlport_uninitialized_copy_rva0054000b.cpp`,
  `stlport_construct_rva0054000b.cpp`,
  `stlport_vector_pod40_lower_bound.cpp`,
  `stlport_vector_pod40_allocator.cpp`, and the constructor consumer
  `Code/GameEngine/Source/GameLogic/Object/Behavior/Rva00540517CopyCtor.cpp`.

This retires one identity-debt key. It claims no census, real-link or image
ownership improvement. No source paths change.
