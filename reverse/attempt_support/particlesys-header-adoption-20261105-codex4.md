# ParticleSys header adoption, 2026-11-05 (codex4)

Scope: `Code/GameEngine/Source/GameClient/System/ParticleSystemTemplateCreateSlave.cpp`,
row `?rva001F9CF3@ParticleSystemTemplate@FXParticleSystem@@QBE?AVBfmeParticleSystemHandle@@_N@Z`,
retail interval `0x001F9CF3..0x001F9D98` (165 bytes).

## Completed

Commit `1ce238687a` replaces this donor's private `RvaSmartPtr12` declaration
with `Include/Common/RvaSmartPtr12.h`. `./build.sh` verifies 1/1 rows;
`find_declared_unmatched.py` passes before and after. The registered-header
acceptance tool passes and retires one header-queue row. No shared header changes.

`link_check.py` reports LINKS, LINKED 165 -> 165 bytes against census
2026-11-05 05:17 at `c95fcfcfcd`. This is a unit preview, not a census gain.
The commit was handed to the fleet publisher.

## Remaining handle adoption

After that cleanup, `header_adopt_lane.py adopt --class BfmeParticleSystemHandle
--header Code/GameEngine/Include/GameClient/BfmeParticleSystemHandle.h --apply`
on the same donor gets through field preparation (`ptr` -> `m_system`,
`prev` -> `m_previous`, `next` -> `m_next`) but fails byte verification of
its sole 165-byte row. The tool restores the original source. A subsequent
`./build.sh` verifies 1/1 rows, and the frozen-file check remains clean.
The handle's header-queue key remains registered.

Structural observation, not an isolated explanation for the mismatch: the
private wrapper spells copy, assignment and destruction inline through
`RvaSmartPtr12`; the canonical handle declares these operations out of line
and gives its copy/destructor explicit `throw()` contracts. Inspect the
compiled caller and its lifetime/EH operations before changing shared headers.
No failed body is left in Code and no partial byte-match score is claimed.

## Consolidation prerequisites

The view survey identifies the registered ParticleSystemManager,
ParticleSystem, BfmeParticleSystemHandle and RvaSmartPtr12 headers as header-lane
work. Existing canonical `ParticleSystemClass.h` and `FXParticleSystemInfo.h`
mean LINK-155's historical request to create those declarations is partly
superseded; the seed still carries private nested FXParticleSystem classes.

The canonical ParticleSystem header documents the seed's +0x33A isSaveable
layout conflict. Current ledger rows at `0x002AA223` include both
`ParticleSystem::isSaveable` in ParticleSys.cpp and `Player::isPlayerObserver`
in Player.cpp. Their identical seven bytes alone do not establish a common
class layout. Reconcile identity from the class/caller evidence rather than
extending the canonical 0x1DC particle object to fit that offset.

The broad `tu_skeleton.py --merge .../ParticleSys.cpp --dry-run` probe,
started on `0094922657`, was interrupted after more than 15 minutes while
compiling candidate compositions. It returned no final accepted/rejected
report. No merge result or donor count is claimed from that run; its temporary
source was removed by the tool. No source paths or ledger owners moved.

After stopping the probe, the supported System-subtree consolidation planner
completed and `consolidate --check build/consolidation/particlesys` passed.
Its ParticleSys investigation group has 25 files and 92 static blockers,
including duplicate types, compiler settings and stale committed TU-map
inputs. The seed's placement packet treats most routing as hints; the
create-slave row has unresolved placement and no alternative path evidence.
These investigation groups are not the merge tool's approved donor set.
No regenerated map is committed and no new path approval is inferred.
