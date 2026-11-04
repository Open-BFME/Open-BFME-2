# Sphere callback canonical info headers

Inspected base: `2974791b3ec4f752bb409ee10d1c57f4be6a79b1`.
Source: `Code/GameEngine/Source/GameClient/System/FXParticleSystem/fxpsemitterspherevolumemodule.cpp`.
Row: `?getPosition@SphereEmissionVolumeModule@FXParticleSystem@@UAE?AUCoord3D@@MMMM@Z`,
RVA `0x0055D48C`, 129 bytes.

Replaced the two private info views with the existing canonical
`EmissionVolumeInfo.h` and `SphereEmissionVolumeInfo.h`, included at global
scope. The callback uses the canonical inherited byte `m_04` for the hollow
test; the radius remains `m_radius`. The retained layout assertions still
prove the module's primary span is `0x1c` and its total size is `0x28`.
The existing header's target evidence places the tested byte at module
`+0x20` and radius at `+0x24`. No new member spelling or donor identity is
inferred here.

Checks:

- `find_declared_unmatched.py SOURCE`: all definitions matched, before and after.
- `./build.sh SOURCE`: 1/1 function matched; the full path literal verified.
- `class_cleanup.runtime_graph` / `same_runtime` against the saved pre-edit
  object: identical non-debug bytes, relocation bindings, external definitions,
  COMDAT policies and weak bindings (5 sections, 4 external definitions).
- Ordinary `link_check.py SOURCE`: baseline and final preview retain LINKS,
  129 -> 129 authored bytes against the 2026-11-04 07:28 census at `a62ac1c10b`.
- Separate `header_adopt_lane.py accept --class EmissionVolumeInfo SOURCE`
  and `--class SphereEmissionVolumeInfo SOURCE` both pass and each retire
  exactly one queue row. No queue row was removed by hand.

The automatic six-file EmissionVolumeInfo trial restored every candidate:
copy constructors still need inline base-copy emission in LightningEmissionInfo,
PointEmissionVolumeModuleCtor_Rva003abf85 and fx_particle_system; the automatic
include placement also produced nested namespace / Snapshot diagnostics.
FXParticleSystem.cpp and Rva003AF7FESlots.cpp remain unchanged. Their queue
rows remain for their existing prerequisites. Only this callback's two rows
are retired; no census, real-link or runtime gain is claimed.
