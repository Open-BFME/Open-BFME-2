# Rva005E3DE8 consolidation trial and duplicate alias cleanup

Inspected revision: `854c4a4184592c3e70454991ff3fe53d34a10167`.
Scope: `Code/Libraries/Source/WWVegas/WWLib/SBServer.cpp` and
`Code/Libraries/Source/WWVegas/WWLib/Rva005E3DE8Ctor.cpp`.

## Consolidation result

The default picker claimed these files for a one-donor merge. The evidence
planner was run under `Code/Libraries/Source/WWVegas/WWLib/`; its routing hints
are not proof of an original source name. No path or ledger row moved.

`tu_views.py SBServer.cpp --dry-run` finds the shared `Rva0022167C` view
compatible, but refuses `Rva005E3DE8`: the seed's `m_at00` at offset zero lies
under the constructor view's bases (own data starts at offset eight).
`tu_skeleton.py --merge SBServer.cpp --dry-run` accepts no donor and fails
with C2600 when defining the constructor absent from the retained seed view.

The constructor at RVA `0x005E3D95` uses a polymorphic `Rva00221635` base and
initializes its own AsciiString at offset eight. The seed's already matched
destructor at `0x005E3DE8` uses an opaque eight-byte member followed by an
AsciiString. The existing constructor comment explains that exposing the
polymorphic view to that destructor changes its vptr-store code generation.
This trial does not prove a new unified class declaration. Before retrying,
reconcile these views while independently preserving both bodies and their EH
graphs; adding the missing constructor declaration alone does not reconcile
the base initializer or layout. Both source files remain in place.

## Cleanup and verification

The constructor contained two identical
`/alternatename:?pure@Rva005E3DE8@@UAEXXZ=??_GRva005E3DE8@@QAEPAXI@Z`
directives. Remove the second directive and its duplicate explanatory comment.
The first directive stays in the same object, preserving this alias for every
consumer at link scope. No assertion that the alias is dead is needed.

`./build.sh Code/Libraries/Source/WWVegas/WWLib/Rva005E3DE8Ctor.cpp` passes
before and after: all three rows (83-byte constructor, eight-byte unwind
funclet, ten-byte EH handler), string, float and import checks pass.
`find_declared_unmatched.py --fail` passes for both source files.

COFF comparison using `link_census.comdat_bodies` and `object_references`
finds all seven COMDAT digests and the complete reference graph unchanged.
Every section's contents and relocations remain identical except `.drectve`
and `.debug$S`. The directives shrink from 736 to 668 bytes, exactly one copy
of the alias; removing that copy leaves the same directive token sequence.
The debug difference is the cached donor object's original output path
(`Z:\home\claude\bfme2-runner\repo`) versus this checkout's output path
(`Z:\work\Open-BFME-2`).

Object SHA-256 before:
`8dc4f4179a73212969a6467693ad58b1ddb2f15337d8632298e7a57ca230266a`.
After:
`f95cdbbac06aea7f1c00123806d2ef7e7f71b99cc755ef1c01ef21bc01f12eb7`.

`hatch_counters.py --update` lowers the constructor's alias count from two to
one and the registered alternatename total from 2,805 to 2,804. No other
register key changes. This is hatch cleanup; consolidation remains blocked.

`check_csv.py` passes. After fetching the published index, the current-object
`link_check.py Rva005E3DE8Ctor.cpp` preview reports LINKS, 92 -> 92 authored
bytes, against the 2026-11-04 20:47 census at `f12552d0a7`. This is a local
preview; no new census or source-file reduction is claimed. The existing
LINK-135 entry's SBServer provider discussion is unaffected.
