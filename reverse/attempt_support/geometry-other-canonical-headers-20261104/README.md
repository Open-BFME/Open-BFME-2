# GeometryOther parser canonical header adoption, 2026-11-04

Inspected revision: `78e46ac0e6d76ca53e5fa40d83e8bbf5b1357dd7`.

`Code/GameEngine/Source/Common/System/GeometryParseOther.cpp` now includes
canonical GeometryInfo and INI headers instead of declaring private copies.
The GeometryType enumeration comes from Geometry.h. The parser uses
`m_isSmall` and casts the existing opaque `field2c[0]` shape pointer to its
unchanged source-local GeometryShape view. This does not recover the shape
class's original name or change its layout.

Keep INI::getSepsColon inline in this TU using the canonical `m_sepsColon`
field at +0x420. The initial direct-field trial changed two loop loads from
EAX to ECX; preserving the original accessor's inline scope restores the
native register choices. No new out-of-line getter is emitted.

Verification:

- Normal baseline and final `./build.sh` both match 3/3 rows: retail
  0x006BFA00 (47 bytes), 0x006BFA30 (45 bytes), 0x006C01B0 (500 bytes).
- String references: 8 literals verified; float/import references pass.
- `find_declared_unmatched.py --fail` passes; `check_csv.py` passes.
- [Object facts](object-facts.json), read through `build.obj_path` and
  `link_census.object_facts`, are identical before and after: 27 normalized
  COMDAT digests/sizes, one exclusive definition, 12 undefined externals and
  no weak externals. Retail verdicts are omitted from this equality test;
  byte verification is independent.
- `link_check.py` reports LINKS, LINKED 592 -> 592 bytes using the published
  census index dated 2026-11-04 22:01 at 3fbce7bcb2. This is a per-unit preview,
  with no census gain claimed.
- Scoped naming review retained all four inventoried parser bindings (`ini`,
  `store`, `token`, `value`). The constructor-style local `geometry` is also
  meaningful and is outside the regex inventory; no names were changed.
- `header_adopt_lane.py accept --class GeometryInfo` and `--class INI` each
  pass and retire exactly their own one header-queue row.

The wider Geometry.cpp merge still needs other private shape views and
compiler profiles reconciled. The selected BfmeVec440 grouping remains
unapproved (its current plan has zero approved rows); no row was moved or
renamed. No source path, shared header, pin, alias or gate changed.
