# Geometry initializer stale-header-queue retirement, 2026-11-05

Inspected revision: `d51d8d64d1`. Both units already include `Code/GameEngine/Include/Common/Geometry.h` and contain no private GeometryInfo declaration. Their queue entries still report an obsolete C2011 duplicate-class error. No source, global storage, identity, compiler profile, ledger or provider changes are required for this retirement.

The owner command passes both units and retires exactly two rows from `reverse/header_queue.tsv`:

```
python3 tools/header_adopt_lane.py accept --class GeometryInfo Code/GameEngine/Source/Common/Rva007ABD4BGeometryInits.cpp Code/GameEngine/Source/Common/Rva007B6610.cpp
PASS Code/GameEngine/Source/Common/Rva007ABD4BGeometryInits.cpp
PASS Code/GameEngine/Source/Common/Rva007B6610.cpp
retired 2 row(s)
```

Acceptance runs the ordinary scoped byte gate on all four existing rows (163 bytes), checks canonical-header inclusion and absence of a private class body, then requires a usable link-preservation verdict. Frozen-file checks pass for both units.

An explicit `tools/link_check.py` preview after acceptance reports LINKS 92 -> 92 bytes for Rva007ABD4BGeometryInits.cpp and LINKS 71 -> 71 bytes for Rva007B6610.cpp, using census `3a95b274a2` from 2026-11-04 22:40. This is a preservation preview, not a new census measurement. Only two stale header-debt rows are retired; no new source recovery, TU merge, storage repair or headline linking gain is claimed.
