# GeometryInfo height-query canonical header adoption, 2026-11-04

Inspected source revision: `3bd933dda5`. Scope: `Code/GameEngine/Source/Common/GeometryInfo_getMaxHeightAbovePosition.cpp`, retail RVAs `0x006BD7C0` (101 bytes) and `0x006BD830` (108 bytes).

Replace the private GeometryInfo and duplicate GeometryType enum with `Code/GameEngine/Include/Common/Geometry.h`. Retain the existing 0x24-byte shape view as a source-local declaration; access the canonical native vector begin/end slots `field2c[0]` and `[1]` through that view. No claim of recovered shape identity or field names. No header, ledger, pin, alias, compiler profile or source path changes.

Verification:

- Before and after `./build.sh Code/GameEngine/Source/Common/GeometryInfo_getMaxHeightAbovePosition.cpp`: both bodies exact, 2/2 matched; four compiler float literals verified.
- `tools/link_census.py` object facts from the normal pre-change and post-change objects are equal: four COMDAT copies with equal normalized digests/sizes, two exclusive definitions, one undefined external, no weak externals. [Exact facts](object-facts.json). Retail verdicts were deliberately omitted from this equality check; the normal build verifies retail independently.
- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/Common/GeometryInfo_getMaxHeightAbovePosition.cpp`: all defined functions already matched.
- `python3 tools/header_adopt_lane.py accept --class GeometryInfo Code/GameEngine/Source/Common/GeometryInfo_getMaxHeightAbovePosition.cpp`: PASS; retired exactly one header queue row through its owner tool.
- `python3 tools/link_check.py Code/GameEngine/Source/Common/GeometryInfo_getMaxHeightAbovePosition.cpp`: LINKS; LINKED 209 -> 209 bytes, using published census index `a62ac1c10b` from 2026-11-04 07:28. Preview only; no new census or headline gain claimed.

Consolidation prerequisite context: the supported Geometry.cpp dry run still accepts zero donors. Regional flag mismatches remain, along with GeometryShape overlap and BfmeElem60 float/int conflicts. The supported tu_views pass verified two shared transform views but did not increase accepted donors; those trial source edits were restored. No failed reconstruction remains in Code. The planner flags routing/profile prerequisites and supplies no merge approval. This change retires one canonical-header debt only; it does not merge a source or resolve the broader Geometry obstacle.
