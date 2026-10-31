# Physics transform: use the existing Vector4 storage header

Base `c38e282bad`. File and Vector4 class scopes were reserved before editing.
The original 875-byte `Drawable::applyPhysicsXform` at `0027BB65` passes its
normal gate before the change. Read the source's native guard, matrix layout
and SSE scheduling evidence, the class contract and the existing canonical
`Code/Libraries/Source/WWVegas/WWMath/Vector4Data.h`.

Replace only the private four-float Vector4 with that header. Each Matrix3D
row still occupies 16 bytes with X/Y/Z/W at +0/+4/+8/+C. The private Matrix3D
and Vector3 views, imports, flags and existing physics ABI remain unchanged.

A direct rewrite of the 48 constant component accesses to public fields
keeps the body length but changes the native SSE load/store schedule. It is
not retained. A TU-local static force-inline component accessor using the
same `(&X)[index]` operation as the old member accessor restores every byte
and relocation. This helper has no emitted standalone function; the sole
code function remains the original native-exact physics method. The old
private Vector4 assignment/accessor declarations are removed; no provider
or undefined runtime call is added, removed or rebound. No shared header,
pin, alias, data row, source path, compiler flag or baseline is modified.

The normal whole-file gate, frozen-definition check and strict preparation
pass. The owning `header_adopt_lane.py accept --class Vector4` retires exactly
this source's one queue key. The bounded `3c7a254a38` preview (2026-10-31
13:43) retains LINKS/875 authored bytes; this is one header-debt item retired,
not new recovered or census-linked bytes. Broader outgoing consumer audit
and scheduled census confirmation remain separate; no runtime result is claimed.

Original source/object, unsuccessful direct-field build, successful component
variant, actual-object comparison, strict preparation and acceptance output
are preserved under ignored `build/two-each-no-qwen-20261031-1559` and the
matching create-only diagnostic package at `W:/OpenBFME/diagnostics/`.
Qwen and other local models remained off; verification keeps the shared
ten-worker limit and does not alter an Unreal process.
