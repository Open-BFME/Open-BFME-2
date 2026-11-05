### LINK-155: ParticleSystem's base clause and FXParticleSystem's nested views block ParticleSys.cpp (2026-10-30)

Packet 15 (ParticleSystem) reached its first step only. 441f51de64 gives
`ParticleSystemManager` one vfptr-aware view in its three data-bearing donors
(20/20 rows byte-verified): the donor that defines `rva001F9F66` spells it
virtual (`?...@@UAEXXZ`), so the manager's data starts at +4, and the other
views' leading pads moved four bytes to keep `m_uniqueSystemID` at +0x48 and
the template map at +0x88. `tu_views` now *plans* the class for the ten
ParticleSys.cpp files instead of refusing it, but the apply still reverts:
the superset's `BfmeParticleSystemList m_systems` is a by-value member that
only `ParticleSystemManagerFindByID.cpp` defines, so the other nine files
fail C2079 until the list gets a shared declaration.

`ParticleSystem` (16 files) is refused on the base clause. The seed and
eleven donors declare it with no base and no virtuals;
`ParticleSystemConstructor.cpp`, `ParticleSystemDestructor.cpp` and
`ParticleSystemUpdate.cpp` derive it from `FXParticleSystem::ParticleSystemInfo`;
`ParticleSystemLoadPostProcessBfme2.cpp`, `ParticleSystemMake001FCBD7.cpp`
and `rva001F5923Rva001F5923Farm.cpp` declare it polymorphic with no base.
The constructor/factory evidence puts the object at 0x1DC-0x1E0 (the
factory's `new` extent, Make001FCBD7's measured spacing), while the seed's
`isSaveable` row reads a flag at +0x33A; the two cannot be one layout, and
`reverse/vtables.tsv` has no vtable at the constructor's 0xBE1A10 to settle
the base from retail. The packet's own trap applies: settle from bytes and
retail vtables, not a vote.

`FXParticleSystem::ParticleSystemInfo`, `ParticleSystemTemplate` and
`CPUParticle` are namespace-nested classes, which `tu_views` does not model,
so the donors that redefine them still fail C2011
(`Rva001FB201DoXfer.cpp`, `ParticleSystemMake001FCBD7.cpp`,
`ParticleSystemManagerFindTemplate.cpp`,
`ParticleSystemManagerMappedTextureUVs.cpp`).

Measured on master 8361007c44: `tu_skeleton --merge ParticleSys.cpp
--dry-run` accepts 0 donors before and after the manager alignment. The
remaining rejection mix is C2011 (4), C2143/C2061 (6), C2504 (2), C2084 (3),
C2953 (2), C2600 (1) and one link COMDAT, so the packet's 9-sole-donor
premise no longer holds at this master. Next step: a canonical
`Include/GameClient/ParticleSys.h` (ZH path) carrying `ParticleSystem` and
the FXParticleSystem nested types, adopted by the seed and the donors, plus
a shared declaration for the manager's system list.

2026-11-05 consumer follow-up: W3DTankTruckDrawTossEmitters.cpp adopts the canonical ParticleSystem header with explicit setter-view casts; 2/2 rows exact, acceptance retires one header row, preview preserves 356/356 linked bytes. Remaining eight served consumers and verification: [evidence](../../reverse/attempt_support/particle-system-emitter-header-20261105-codex3.md). ParticleSys.cpp consolidation remains open.

2026-11-05: Canonical particle headers now exist; next work is adoption and seed identity reconciliation. `1ce238687a` retires one smart-pointer header key (165B exact; unit LINKS preview); the same donor's canonical handle swap still fails bytes. [Evidence and bounded consolidation probe](../../reverse/attempt_support/particlesys-header-adoption-20261105-codex4.md).

2026-11-05 (claudec): the canonical handle needs an inline dtor (0x002115C5: 77/80 callers are funclets). The inline-lifetime handle header lets the seed (129/129) and CreateSlave adopt, but 10 consumers with private `RvaSmartPtr12` copies fail C2011. Next step: reconcile `RvaSmartPtr12` adoption first. [Evidence](../../reverse/attempt_support/particlesys-handle-inline-dtor-20261105-claudec.md).

2026-11-05 (codex5): seven RvaSmartPtr12 consumers adopt canonical declarations with TU-local inline destruction; seven header rows retired, 37/37 rows exact, 2,131 preview bytes preserved. Shared-header inline destruction changes STLport _Destroy at 0x00211F9A; reconcile that codegen and remaining default-ctor consumers before broader handle adoption. [Evidence](../../reverse/attempt_support/smartptr12-header-adoption-20261105-codex5.md).
2026-11-05 (codexb5): six more `RvaSmartPtr12` consumers adopt with TU-local inline cleanup; 75/75 rows exact, six header keys retired, all 170 external definitions preserved, combined preview keeps 7,252/7,252 bytes. Next: the 25 remaining handle-view rows, including the getter's if-null branch constraint; [evidence](../../reverse/attempt_support/smartptr12-six-consumers-20261105-codexb5.md). ParticleSys.cpp consolidation remains open.


2026-11-06 recovery review: the interrupted createSlaveSystem exported-return proposal remains unverified. Its three affected sources are unchanged since the archived attempt; prior 0x001F9CF3 evidence already identifies the 0x002115C5 shared-destructor naming prerequisite. No repeated build, second body or alias was added. [Recovery disposition and original proposal boundary](../../reverse/attempt_support/particle-slave-export-20261106-c09-seat2.md).


Recovery rebase update: current master now supplies createSlaveSystem and its verified destructor fold. The earlier recovery paragraph is historical and superseded for this export; do not repeat the archived proposal. [Current upstream repair](../../reverse/attempt_support/create-slave-system-export-20261106-noro.md). Automated real-link/runtime confirmation and broader handle-header adoption remain separate.

2026-11-05: Rva000B8F5A.cpp, GPUParticleStorageConstructor.cpp and ScriptEngine.cpp adopt the existing RvaSmartPtr12 header; three header debts retired, 164 function rows and three data rows exact, previews preserve 10,092 bytes, no external definitions removed. Remaining lifetime-contract prerequisite unchanged; [evidence](../../reverse/attempt_support/smartptr-field-consumers-header-20261105-codexb2.md).
