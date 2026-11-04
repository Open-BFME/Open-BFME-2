# GeometryInfo setter and parser canonical header adoption, 2026-11-04

Inspected revision: `2974791b3ec4f752bb409ee10d1c57f4be6a79b1`.

Replace three private GeometryInfo declarations with the existing canonical
`Code/GameEngine/Include/Common/Geometry.h`. Include it before Snapshot is
configured, use canonical `m_isSmall`, and cast the native vector storage at
`field2c` to the existing source-local vector views. Shape declarations and
compiler profiles remain as before; this makes no new shape identity/layout
claim. The setter also drops its duplicate GeometryType enumeration.

| Source under Code/GameEngine/Source/Common/System/ | Retail RVAs | Matched bytes |
| --- | --- | ---: |
| GeometryInfoSet.cpp | 0x006BFF50 | 223 |
| GeometryParseActiveAndOffset.cpp | 0x006BD590, 0x006BD610 | 125 |
| GeometryParseDimensions.cpp | 0x006BD5D0, 0x006BE9D0, 0x006BEA00, 0x006BEA60, 0x006BEAB0 | 321 |

Verification:

- Baseline normal `./build.sh` across the three paths: 8/8 exact.
- Final normal builds: setter 1/1 exact; both parser sources 7/7 exact.
  A first parser trial bound the vector cast to a local reference, which
  changed register allocation and hoisted the end pointer. Repeating the cast
  at each access preserves the original loads and all seven parser bodies.
- Normal object facts before and after are equal for all three sources:
  normalized COMDAT digests/sizes, exclusive definitions, undefined symbols,
  and weak externals. [Exact shared facts](object-facts.json) were captured
  with `build.obj_path` and `link_census.object_facts`; retail verdicts were
  omitted from this equality comparison and independently verified by builds.
- `find_declared_unmatched.py` passes all three sources before and after.
- `header_adopt_lane.py accept --class GeometryInfo` on the three paths:
  PASS for each; retired exactly three `reverse/header_queue.tsv` rows through
  the owning tool. No other debt register was changed.
- [Current-object link preview](link-check.txt): 3/3 LINKS, LINKED 669 -> 669
  bytes, published index `a62ac1c10b` dated 2026-11-04 07:28. No census gain
  claimed.

This removes three private GeometryInfo views as a consolidation prerequisite.
The broader Geometry.cpp merge remains blocked by other private shape views
and incompatible compiler profiles. No source move, pin, alias, shared-header
or gate change; the setter's existing identity-debt key remains registered.
