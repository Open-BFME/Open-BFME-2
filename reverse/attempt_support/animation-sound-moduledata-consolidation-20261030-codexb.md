# AnimationSound module-data composition, 2026-10-30

Seat: yasinschroeder-codexb. Inspected base: `de459f73ab`.
Approved destination:
`Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

## Routing and declaration prerequisite

The default picker claimed the destination and eight whole-file donors. The
scoped `name_lane.py consolidate` packet was reviewed, including original-path
leads, alternatives, and blockers. Its BFME1 Behavior path is donor evidence,
not permission to change the current Update destination. The supported merger
rebuilds the stale committed TU map in memory: 49 rows are approved for this
TU; seven mixed files remain untouched. No map assignments are regenerated.

The initial supported probe rejects all eight donors. The module-data fragment
has only a constructor-facing class, whereas the seed has only its static
parser declaration. Reconcile these existing declarations and the tree view
before composition. The module-data object remains 0x18 bytes: virtual base
storage occupies +0..7, the existing 12-byte seed tree occupies +8..0x13, and
the float remains at +0x14. The donor's old separate +0x10 word becomes the
last four bytes of the tree. Field identities beyond the seed's existing view
are structural inferences, not recovered donor layout facts.

Both sources now share the tree declaration and the module-data declaration;
the seed learns the existing tree destructor and module-data base/constructor/
destructor declarations, and the donor learns the existing tree methods and
static parser declaration. No body, symbol binding, pin or escape hatch is
added. The tree initializer declaration loses `throw()` to agree with its
matched provider in Common/AnimationSoundTreeFree.cpp (0x004CA13D).

The intermediate composed object demonstrated the reason: its module-data
constructor was 34 bytes with no EH prologue, versus the retail/standalone
63-byte constructor with EH data. Seeing the tree constructor's body together
with its `throw()` initializer declaration lets the compiler omit cleanup.
The standalone objects remain identical in their link facts when that
unsupported no-throw guarantee is removed. This is declaration reconciliation,
not permission to change the provider or claim a donor source identity.

`./build.sh` verifies 21/21 rows across the two sources, ten string literals
plus one empty-string reference, one floating literal and one named import.
Both sources pass the frozen-file check. `eh_verify.py` reports all three EH
graphs EXACT. Before/after object comparisons preserve each source's external
COMDAT bytes and symbolic relocation fingerprints, external definitions,
unresolved names, weak aliases and full reference roots/edges: seed 45 COMDATs,
45 definitions, 44 unresolved names and two weak aliases; donor seven COMDATs,
seven definitions, eight unresolved names and two weak aliases.

The first strict receipt attempt overlapped a merge trial's temporary sources
and was rejected because its preparation inputs moved; no witness was accepted.
The subsequent check succeeds after those trials finish: both explicit providers
are byte-verified with strict reusable receipts; census/index/status are unchanged.

The ordinary preview against census index `12b9e7a7c0` (2026-10-30 10:11)
preserves LINKS for both sources: 1,958 seed bytes plus 73 constructor/EH
bytes, 2,031 authored bytes total. These are predictions, not new census figures.
