# Emission constructor header adoption, 2026-11-04

Inspected source revision: `e5bfff3f4e`.

The two constructor units under
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/` now include the
canonical CylindricalEmissionVelocityInfo, OrthoEmissionVelocityInfo,
SphericalEmissionVelocityInfo and TerrainFireEmissionInfo headers instead of
their private class bodies. EmissionInfoDefaultCtors.cpp also adopts
DefaultPhysicsModuleInfo. Constructor accesses use the headers' offset-based
member names; this does not establish original member spellings.

DefaultPhysicsModuleInfo needs the existing Coord3DInline.h companion before
its header: an ordinary Coord3D declaration produces an out-of-line zero()
call, while retail has inline stores. The companion restores the exact body.
The spherical inline constructor/destructor and existing anchor remain.
Both existing link-wide alternatename directives remain unchanged.

## Verification and retirement

- `./build.sh` on both files: 13/13 functions exact; string, float and import
  checks pass. The existing unwind label is renumbered from $L704 to $L798;
  parent EH data verifies its unchanged retail location 0x00799A5F.
- `find_declared_unmatched.py`: exit 0; only the already registered default
  constructor anchor remains an unclaimed definition.
- `eh_verify.py`: EXACT 5; no nonexact graph or missing object.
- `data_check.py`: zero shadow findings. Converged enforcement: 11 addresses,
  zero second names and zero unjudged rows.
- `tu_ownership.py --staged`: exit 0, no findings.
- `check_csv.py`: OK, 99,434 function rows, 9,338 symbols and 2,269 data rows.
- `link_check.py --prepare-current` on the two providers: strict reusable
  receipts and normal byte verification pass; no census/index/status update.
- `header_adopt_lane.py accept` passes both units for each of the four emission
  classes and the default unit for DefaultPhysicsModuleInfo. It retires nine
  header-queue rows through the owning lane. No other debt register changes.

Before and after ordinary previews use census `a62ac1c10b`, dated
2026-11-04 07:28: EmissionInfoCopyCtors.cpp LINKS 212 bytes and
EmissionInfoDefaultCtors.cpp LINKS 653 bytes, preserving 865/865 authored
bytes. These predictions do not claim new census linking coverage.

## Consumer qualification and remaining scope

The staged-source batch audit compared HEAD with the staged tree, using both
byte-verified source paths. It exits 2:

```text
link batch audit: INCONCLUSIVE baseline: index at a62ac1c10b, outgoing base HEAD; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/AIBaseBuilder.cpp
```

Full provider selection and consumer preservation remain unverified. Carry
these two constructor providers and their indexed consumers, including
Common/AIBaseBuilder.cpp, into the next scheduled census/current-receipt audit.
This does not establish that AIBaseBuilder has an include-inventory defect.

The main GameClient/FXParticleSystem.cpp unit retains its cylindrical queue
row. An isolated automatic adoption trial still fails C2264 at its existing
EmissionVelocityInfo constructor use; its private base declaration must be
reconciled with the canonical base before retrying the derived header. The
trial retained no changes to that source. No shared header, function ledger,
pin, source path or census history is changed by this repair.
