# ParticleSystem emitter-header adoption

Date: 2026-11-05. Inspected revision: `077c8e6b48307d9349287c6d2f668a4b2cd7007f`.

Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDrawTossEmitters.cpp`.
The unit now includes the existing canonical `ParticleSystemClass.h` instead of
privately deriving ParticleSystem from `Rva001F3C43Slot`. The three setter calls
cast the returned system pointer to the existing setter view. The named
`destroy` call uses the canonical declaration. No shared header, function row,
pin, alias, compiler flag or source path changes.

## Verification

- `./build.sh <source>`: both functions exact, 191-byte tossEmitters at
  0x000CB5C3 and 165-byte enableEmitters at 0x000CB826. Source claims, string,
  float and import reference checks pass.
- `find_declared_unmatched.py <source>`: all defined functions already matched.
- `header_adopt_lane.py accept --class ParticleSystem <source>`: PASS and
  retires exactly one header-queue row through its owning tool.
- `link_check.py <source>`: LINKS, 356 -> 356 bytes against census
  2026-11-05 05:17 at c95fcfcfcd; current dependency cache, no recompile needed.
- `check_csv.py` and `git diff --check`: pass.

## Remaining cohort

The automatic nine-unit trial restored all rejected sources before this repair.
Eight remain queued: doDrawModule and scripted event update have conservative
field-rename collisions (`next` belongs to other classes); particle bones needs
Matrix3D::Get_Translation; model particles and W3DFire fail byte verification
when canonical inclusion changes their handle surface; W3DTankDraw has a
FieldParse data-check refusal; createEmitters needs its setter call sites
adapted and still has a private inline/volatile handle; W3DFXParticleSystem has
no canonical field matching its private +0x1C4 view. These are trial boundaries,
not claims that the private views or original class identities are correct.
Next: reconcile those surfaces independently without changing shared lifetime
contracts merely to make a consumer pass. No rejected edit is retained.

This is one header-debt retirement, with no census gain or runtime claim.
