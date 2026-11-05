# ParticleSys.cpp: canonical BfmeParticleSystemHandle needs an inline destructor (2026-11-05, claudec)

Scope: the prerequisites for `tu_skeleton.py --merge Code/GameEngine/Source/GameClient/System/ParticleSys.cpp`.
Model: claude-opus-5-5.

## Dry run (master 465532bc38 plus local header commits)

`build/ps_dry.txt` reported 381 approved rows, 0 accepted, 38 rejected, 15 adopt_first, 18 mixed,
5 refused and 32 reconcile_classes, with the result "blocked: no verified merge of two or more donors".
These are the root causes:

- Donors carry private copies of the canonical classes `ParticleSystem` (`Include/GameClient/ParticleSystemClass.h`),
  `ParticleSystemManager` (`ParticleSys.h`), `BfmeParticleSystemHandle`, `RvaSmartPtr12` and `GameClient`.
- Namespace-nested `FXParticleSystem::*` views fail with C2011.
- Donors that define `BFME_SNAPSHOT_NONCONST_NAME_SLOT` hit the `#error` in `ParticleSys.h`.
- The seed holds a namespaced `FXParticleSystem::ParticleSystemManager` and a global private manager subset.
  Because of the namespaced manager, the automated header adopt fails.

## Target facts: the handle destructor is inline

- 0x002115C5 (11 bytes) is the ICF fold of every 11-byte "if (+0) unlink" handle destructor. Of its 80 callers,
  77 are EH funclets (inline-destructor unwind actions).
- Its 3 direct callers are compiler and STL plumbing: 0x00211ED9, 0x00211F9A (`_STL::_Destroy<RvaSmartPtr12>`,
  DestroyInstances.cpp, /O1) and 0x00212AD6. None of them includes the handle header.
- So the canonical handle's destructor is inline, and the out-of-line copy is the COMDAT that /O1 emitted.
  The canonical header currently declares it out of line, and no row defines it. The canonical handle's copy,
  assignment and raw constructors have no rows either. This is why codex4's CreateSlave swap fails.

## Attempt (reverted; diff not kept in-tree)

I made `BfmeParticleSystemHandle.h` include `Common/RvaSmartPtr12.h` and inline the lifetime functions as
forwards to the rowed RvaSmartPtr12 bodies (0x0004CBF7, 0x0004CC19, 0x0004CC3D, 0x0004CBC0):

- The seed ParticleSys.cpp built 129/129 with the canonical handle in place of its private one, and
  `header_adopt_lane.py accept --class BfmeParticleSystemHandle` passed.
- ParticleSystemTemplateCreateSlave.cpp built 1/1 and accept passed.
- These six handle-header consumers stayed exact: W3DTankTruckDrawTossEmitters, W3DScriptedModelDrawDestructor,
  ParticleSystemRva001F4A22, SmartPtrCopyCtor, SmartPtrDestroyDelete and Rva003FC7FCClear.
- These ten consumers of the handle or ParticleSystemClass header define a private `RvaSmartPtr12` and fail with
  C2011: W3DTruckDrawDtor, Rva003FDC46, ParticleSystemHandle_dtor, Rva0056224FCtor, Rva0055F840Ctor,
  DefaultModuleHeadBase, RenderParticleConstructor, Rva001F5BBE, Rva000B8F5A and GPUParticleStorageConstructor.
  Several of them use private member names (`system`, `m_ptr`, `next`) and inline destructors.

I reverted the attempt because it needs `class:RvaSmartPtr12`, which another seat held.

## Next step

1. Reconcile the `RvaSmartPtr12` header queue (about 21 rows). Decide whether the canonical `RvaSmartPtr12.h`
   destructor is also inline, since the ICF fold covers both names, and adopt the private copies.
2. Re-apply the inline-lifetime handle header above. This unblocks the seed and the CreateSlave handle adoption.
3. The seed's namespaced `FXParticleSystem::ParticleSystemManager` stays a separate obstacle for the manager adopt.
