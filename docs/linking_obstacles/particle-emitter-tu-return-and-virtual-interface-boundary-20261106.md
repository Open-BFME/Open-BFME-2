### Particle-emitter TU return and virtual-interface boundary (2026-11-06)

Status: Blocked. Inspected revision: `f15737ff46b`.

The fresh native `tu_skeleton.py --merge
Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp --dry-run` reports 87 approved
rows, no accepted donors and two compiler rejections. `ParticleEmitterGetTexture.cpp`
defines the existing 0x001A0D10/33B handle-returning owner, while the seed's header
declares a pointer-returning inline getter (C2556, return-only conflict).
`ParticleEmitterRva001A1500.cpp` owns the existing 0x001A1500/26B virtual forwarder;
the seed's full ParticleEmitterClass hierarchy has no matching member declaration
(C2039). Four mixed sources remain untouched. Zero source files or rows moved.

The older `627efb64099` attempt recorded a blocked merge in the attempt log only.
Subsequent seed/header changes justified this current trial. The native tool
completed normally with exit 2, without source workarounds or changes to gates,
pins, aliases or virtual-signature spellings. Its census-linked list covers the
three input sources against the dated index; it does not clear their current
combined provider/consumer selection or establish a real linked image.

Remaining prerequisites: reconcile the texture-handle ABI with affected
declarations/providers, and establish the virtual forwarder's actual slot/owner
and supported naming/header reconciliation before retrying the merge. Preserve
the existing owners and both donor bodies until the native merge verifies them.
No successful byte/EH/data/provider/consumer merge audit, census gain or runtime
improvement is claimed.

[Current commands, complete native report, planner limits and runtime assessment](../../reverse/attempt_support/part-emt-tu-boundary-20261106-pass3-c02-seat2.md).
The attached planner packet remains investigation context, not TU approval.

Recovery note: this is historical attempt evidence, not a fresh reproduction. Original claims are released.
