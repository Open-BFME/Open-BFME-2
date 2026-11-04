# WaterTracks Thing adoption, 2026-11-04

Inspected revision: `dba4e36e1e95`. Scope: the three Thing adoption candidates
served by `next_work.py --claim`, with the Region3D class/header claimed before
editing that dependency.

## Completed

`W3DWaterTracks.cpp` now includes canonical Thing and Region3D. Its previous
`region.h` include resolved to the BFME 1 WWMath header, whose `coord3d.h`
declares a different Coord3D class. Including Thing alongside it produces C2011
against BFME 2's canonical Coord3D. The adoption tool reported this through the
waveTypeInfo data verification compile, not as an initializer mismatch.

Target facts: the matched 16-byte WaterTracksObj bounding-box getter at
`0x000FE369` calls the Region3D copy constructor owned by `region.cpp` at
`0x0009AC04`. Canonical Region3D normally defines that copy inline. The new
`BFME_REGION3D_COPY_CTOR_DECL` option declares it out of line for this consumer,
preserving the existing call and data layout. The ordinary inline form remains
the default for other consumers. No function identity, pin, alias or source path
changed.

Checks:

- The unchanged WaterTracks source passed its scoped build before repair.
- The repaired source passed `./build.sh`: 24/24 matched functions, the 264-byte
  waveTypeInfo data row, five funclet label resolutions, four literal strings
  plus two empty-string references, 27 float literals and three named imports.
- `find_declared_unmatched.py` passed the source and Region3D header before and
  after editing; `git diff --check` passed.
- `header_adopt_lane.py accept --class Thing` passed WaterTracks and retired its
  one queue row. That verdict includes the ordinary per-unit link-preview
  preservation guard; it is not a new census or a strict-closure receipt.

Local raw logs: `build/thing-watertracks-original.log`,
`build/thing-watertracks-compiler.log`, `build/thing-watertracks-canonical.log`
and `build/thing-watertracks-accept.log`.

## Other selected files

The automatic adoption trial restored both files without accepting them:

- `W3DShrubBuffer.cpp`: field mapping rejects scalar `Thing::m_x` at +0x38
  (4 bytes) against canonical `m_cachedPos` (12 bytes). Its private view also
  includes later ID/radius fields. Next: separate the base coordinates from
  the extended object view before another adoption trial.
- `W3DGhostObjectScene.cpp`: field mapping rejects `m_unrecovered04` at +4
  (52 bytes). Its private Thing extends to 0x64, while canonical Thing is 0x60;
  Object's secondary-provider placement must be reconciled before a manual
  trial. This is a layout prerequisite, not a byte-verified repair.

Both pre-compilation refusals were recorded with `re_log.py`; their queue rows
remain. LINK-018 remains open beyond the repaired WaterTracks consumer. No new
census-linked bytes, source-file reduction or image-ownership result is claimed.
