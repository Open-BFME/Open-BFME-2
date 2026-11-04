# ParticleSystemManager forwarding surfaces

Inspected base: `d9a128b6d08a6e93b2372880cb570a49bc274033`.
Claim: `class:ParticleSystemManager`, owner `yasinschroeder-codexb5`.

## Change and evidence

Two already-matched units replace private ParticleSystemManager virtual
surfaces with the registered `Code/GameEngine/Include/GameClient/ParticleSys.h`.
No function, class, global, member or parameter is renamed.

| Unit under Code/GameEngineDevice/Source/W3DDevice/GameClient/ | Existing rows | Existing bytes | Canonical call |
| --- | ---: | ---: | --- |
| Rva0004CB1EParticleForward.cpp | 1 | 20 | slot 16 / +0x40: doParticles(RenderInfoClass &) |
| W3DDisplaySmallSlots.cpp | 10 | 559 | slot 10 / +0x28: update() |

Target facts: the existing canonical header documents the primary-table slot
order, including slot 16's reference argument proven by the RenderInfoClass
rows. The forwarder retains its integer parameter ABI and converts the passed
pointer value at this boundary. Its complete 20-byte body and global relocation
remain identical. The display method still calls slot +0x28. No new donor
source or donor naming claim is involved.

Baseline objects were saved after successful ordinary builds and before each
source edit. Read-only `build.read_object_symbol_bytes` comparisons cover every
previously emitted named code symbol, including its full section tail and
relocation tuples. All remain identical. The twelve external code definitions
(one forwarder, ten display methods and the existing device getter) remain;
`link_census.object_symbols` reports identical external definitions, references
and weak externals. No linker aliases are removed. The forwarder gains the
seven existing ASCII aliases inherited from the canonical header's unchanged
include closure; none is authored in either edited source. Full comparison:
[object-comparison.json](object-comparison.json).

## Verification

- Before and after: ordinary `./build.sh` passes for each whole source, preserving
  all eleven existing rows / 579 bytes, plus literal, float and import checks.
- `find_declared_unmatched.py` passes for each source before and after edits.
- `header_adopt_lane.py accept --class ParticleSystemManager SOURCE` passes for
  each source and itself retires the two owning rows from `reverse/header_queue.tsv`.
- `link_check.py --prepare-current SOURCE` passes separately for both explicit
  sources with strict reusable compiler receipts and normal byte gates.
- Ordinary `link_check.py` overlays both current objects against census index
  `3a95b274a2` (2026-11-04 22:40): both LINKS; forwarder 20 -> 20 bytes,
  display 559 -> 559 bytes, cohort 579 -> 579 bytes. This bounded preview
  preserves the indexed state; it is not a new census or full current link.
- `link_check.py --new-variants` passes for both current objects.
- No source path, row, pin, class contract, shared header or hatch register changes.

The other twenty queued ParticleSystemManager consumers remain outside this
repair: opaque storage, private lookup/handle ABI, nested FXParticleSystem
surfaces and other header dependencies still need separate work. This is a
header-debt reduction, with no new census coverage or runtime claim.
