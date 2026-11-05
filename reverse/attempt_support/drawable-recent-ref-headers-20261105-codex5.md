# Drawable recent-reference header adoption

Inspected revision: `2d3c0bbc357090e5608729028a8aa780c4b9b2ae`.
Scope: `Code/GameEngine/Source/GameClient/DrawableRecentRefSlots.cpp` only.

The existing matched routine at RVA `0x002766F8` is 103 bytes. Its retail
accesses place three eight-byte reference/frame pairs at Drawable +0x38C.
The purpose and original names of those pairs remain unproven.

The source now includes the registered Drawable and OpaqueRefElement4 headers
instead of declaring private copies. A local field view retains the already
established pair layout inside Drawable's canonical opaque storage. The
reference comparison uses the canonical `referent` member. No shared header,
ledger identity, extent, pin, alias or source path changed.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/DrawableRecentRefSlots.cpp`:
  1/1 matched, with string, float and import checks passing.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class Drawable` and `--class OpaqueRefElement4`
  on this source both PASS and each retire their one owning queue row.
- Current-object `link_check.py`: LINKS, 103 -> 103 bytes against the census
  index dated 2026-11-05 05:17 at `c95fcfcfcd`. This is a preview; no new
  census or real-link result is claimed.
- Before/after COFF external-symbol inspection preserves all old definitions
  and references. Header inclusion adds the array-constructor helper
  `??_H@YGXPAXIHP6EPAX0@Z@Z` and a reference to the existing
  `BfmeClientFramesPerSecond` global; the preview accepts both.
- No source-specific data, identity or hatch baseline keys were found.

Direct pointer/array-reference views based on the canonical opaque member
changed register allocation and the loop shape. Those trials were replaced
by the verified field-view spelling; no nonmatching trial remains in Code/.
The other queued Drawable and OpaqueRefElement4 consumers are outside this scope.
