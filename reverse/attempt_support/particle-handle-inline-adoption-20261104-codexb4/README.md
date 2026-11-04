# Particle handle adoption: inline lifetime passes bytes; identity row blocked

Inspected `ffa2d83790` on 2026-11-04. This is an unapplied trial, not a
header-debt retirement or a linking/census gain. `trial.patch` records the
complete three-file candidate. All source and queue changes were restored.

## Target facts and trial

The canonical 12-byte `BfmeParticleSystemHandle.h` declares its destructor
out of line. Each selected private view instead exposes a null guard around
`RvaSmartPtr12::rva0004CBC0()` inline. The existing symbol pin names the
11-byte guarded destructor at RVA 0x002115C5; the unguarded unlink is the
separate 55-byte body at 0x0004CBC0. This identity/layout evidence already
exists in both handle headers and the pin's provenance; no donor spelling
or new original class-name claim is made.

After the supported header swap, retaining that same destructor as an
out-of-class `__forceinline` definition makes all three units byte-exact:

- `ScriptParticleHandleReset.cpp`: 4 ledger rows, including parent 0x0020453C.
- `W3DModelDrawParticles.cpp`: 3 ledger rows, including parent 0x000B6EDE.
- `W3DModelDrawParticleBones.cpp`: 9 ledger rows, including parent 0x000C6E1A.

`./build.sh` on these three paths: `Functions: OK 16/16`, string references
(2 empty refs) and float references (1 literal) pass. Renumbered funclet
labels resolve through the owning parent EH graphs. The ordinary canonical
swap without inline availability fails each of these parents.

`header_adopt_lane.py accept --class BfmeParticleSystemHandle` reports PASS
for all three and temporarily retires three queue rows, including its
ordinary-preview nonloss guard. That acceptance alone is insufficient:
`find_declared_unmatched.py` identifies the newly external destructor
syntax in ScriptParticleHandleReset and W3DModelDrawParticles as unrowed.
The bones file does not report it, so its result must not be generalized
as proof of a complete definition inventory. No absent-from-retail marker
is appropriate: this destructor exists in retail.

Each candidate object defines `??1BfmeParticleSystemHandle@@QAE@XZ`.
The ledger has a placeholder owner and several other folded destructor
identities at 0x002115C5, but no row for this existing pinned identity.
A supported, independently verified identity/fold repair is needed before
applying these trials. Claim acquisition for 0x002115C5 was refused;
`claims.py claim 0x002115C5 --dry-run` identifies the live
`class:LivingWorldManager` scope owned by `halilkkaya-nw-o2`. No row,
pin, owner, hatch, shared header, or competing scope was edited.

## Other selected consumers and next step

The ordinary swaps for DoDrawModule (ambiguous field rename), TankDraw
(data row), TankTruckCreateEmitters and W3DFire also fail. A W3DFire trial
with inline destruction still needs the existing assignment wrapper and
accessor branch shape; it was restored. W3DScriptedModelDrawEventUpdate
has an existing unclaimed marker and was not edited.

Coordinate the native destructor's proper ledger identity after the live
scope is released. Then refresh these patches against current headers,
verify the entire emitted destructor and its unlink relocation, run the
frozen-file check with `--fail`, and rerun byte verification and owning
header acceptance. Do not retire queue rows on the byte/link checks alone.
No new code coverage or census-linked byte gain is asserted.
