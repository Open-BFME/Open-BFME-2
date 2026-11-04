# AptMyHero helper layout reconciliation, 2026-11-04

Inspected base: `28e11dc681`. Scope: the picker-claimed AptMyHero TU and eight
candidate donors. No source moves, row changes, pins or debt retirements.

## Change and evidence

The existing `AptMyHero.cpp` view of `Rva005B1830` contains a pointer at +0x140
and two 12-byte `Rva005B1830Item` records at +0x174 (sizeof 0x18C).
`AptMyHero_Unresolved.cpp` calls its method in the destructor through an empty
method-only view. These are facts about the existing reconstructed sources;
this change does not establish a recovered source-level class name.

`tu_views.py --dry-run` proposed sharing the layout but supplied only forward
declarations for the holder and item. Its ordinary application reverted the
trial after the caller failed to compile. The array needs a complete element
type. Copied the seed's complete declarations for the item, its eight-byte
`Rva005B129FClass` member, the holder and the helper into the caller. Kept the
existing `Rva005241DF` declaration and all spellings. No external donor facts
or new layout interpretations are used.

## Verification

- `./build.sh .../AptMyHero_Unresolved.cpp`: 16/16 matched; string references
  pass; ten renamed funclet labels verified against their parent EH data.
- `find_declared_unmatched.py`: all defined functions already matched.
- Final `tu_views.py --dry-run`: helper, item, holder and member class all
  already shared in two files; no remaining noncanonical reconciliation plan.
- `class_gate.py` and `check_csv.py`: pass.
- `link_check.py .../AptMyHero_Unresolved.cpp`: LINKS, 1,067 -> 1,067 bytes,
  using the census index dated 2026-11-04 17:48 at `aae83d006b`.
  This is a per-unit prediction, not a new census or a real game link.

## Remaining consolidation prerequisites

The current `tu_skeleton.py --merge .../AptMyHero.cpp --dry-run` accepted no
candidate donors. Its diagnostics include `free` linkage conflicts with
stdlib.h, STLport vector redefinitions, CreateAHeroManager declaration/include
composition failures, and Vector3 composition failures. Canonical adoption is
still required for the seed's registered private views. The tool also retains
six mixed sources and refuses Rva005B01D3Lerp.cpp's unapproved row.

The header queue's camera `Thing` adoption needs position accessor adaptation;
the seed's `Vector3` adoption reports an ambiguous unary minus. Both class
claims are held by peers, so neither class was edited. Next work should use the
current canonical headers and reconcile these compile environments before a
fresh merge trial. No file-count reduction or link gain is claimed.
