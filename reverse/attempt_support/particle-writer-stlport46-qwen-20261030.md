# Particle template writer STLport 4.6 migration

Base: 724f3a7ffc (2026-10-30). The default picker claimed
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleSystemTemplateWriteINI.cpp`.
Its 19-byte library lead was discovery evidence for one existing destructor;
the complete TU had not been trialled. It was not proof that the original
whole file used any particular header configuration.

## Supported change

The unmodified 4.5.3 control passes all eight rows. Changing only the marker
to `// stlport46` fails C2244/C1506 on the old proxy allocate specialization.
The 4.6 header and existing bfmealloc overlay inherit allocate/deallocate
instead of declaring those proxy members in the selected compiler mode.
Remove the two obsolete proxy specializations; retain all other suppression
declarations and original compiler flags. This follows the already recorded
[ostringstream migration](ostringstream-stlport46-link-20261029-codexb4.md).
No shared header or patch layer is changed.

Every one of the eight existing rows gains `migrated=stlport-4.6` through
`add_match.py --replace-existing`, preserving its prior notes. Names, RVAs,
extents and source ownership remain the same. The five compiler cleanup
labels renumber from $L15793..$L15797 to $L12797..$L12801; the existing parent
graph binds their retail destinations without a new ordinal alias or pin.

## Verification and remaining provider scope

- Whole-file normal build passes 8/8 rows (1,113 ledger bytes), 23 literals
  plus one empty-string reference, and the parent EH graph is EXACT.
- Defined-unmatched and CSV checks pass. The owning STLport migration queue
  no longer serves the file. This is migration of existing coverage.
- Strict two-source preparation with the unchanged native narrow allocator
  owner `Common/NarrowStringRecordCopyBFME2.cpp` passes 42/42 rows.
- Ordinary preview against ccafe54d1d (2026-10-30 15:43) retains the selected
  file's 1,067 authored LINKS bytes before and after. The native allocator
  owner and migrated writer jointly retain 2/2 LINKS and 1,917 authored bytes.
  Three pre-existing unreferenced helper diagnostics remain unchanged.
- External code definitions change 26 -> 27. All 26 retained byte sequences
  and relocation records are identical; no code definition is removed.
  The added non-const allocator<char>::deallocate is an unreferenced 22-byte
  /Oy- copy with a free relocation. It is not the rowed 20-byte native body
  at 0x0046264A. The bounded preview still selects the existing native owner;
  it does not establish full-image consumer selection. No identity-debt
  retirement or whole-family clearance is claimed. Carry this new copy and
  its provider/consumer selection into the next scheduled census/audit.

A declaration-only `template <> allocator<char>::deallocate` trial is rejected
with C2910/C1506: the existing bfmealloc overlay already explicitly specializes
the allocator<char> class. That trial is restored; no shared-header workaround,
flag change, baseline allowance or new escape hatch is retained. Do not repeat
the same specialization trial against unchanged overlay inputs.

Full consumer selection/loss verification and census confirmation remain open.
These bounded previews are not headline census measurements, a complete engine
link or a game runtime test. No smoke/nightly workflow was started.

## Local helper pilot

Qwen2.5-Coder-7B-Instruct GGUF Q4_K_M, revision
13fb94bfda8c8cf22497dc57b78f391a9acb426a, supplied an advisory migration plan.
The mechanical marker/whole-file validation advice was useful. Its assertion
that a 19-byte trial establishes the original whole TU's configuration was
rejected. Its proposed definition of the inherited proxy allocate method was
also rejected without application. The host used the existing recipe and
actual headers for the repair. A later CPU review overstated whole-codebase
correctness; only the scoped results above are accepted.

Helper replies are not EA identity evidence, blind naming votes or passed
tests. Reproducible local requests/results and runtime/resource measurements
are under `W:/OpenBFME/diagnostics/qwen-helper-20261030-191640`; before/after
objects, all eight verified ledger updates, compiler diagnostics, EH/strict
checks and previews are under `build/qwen-helper-20261030-191640`.
No measured development-time saving or autonomous repair is claimed.
