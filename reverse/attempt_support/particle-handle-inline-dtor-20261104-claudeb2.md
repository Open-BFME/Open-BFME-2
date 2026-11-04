# Particle-system handle destructor: inline in some TUs, out of line in others (2026-11-04, claudeb2)

Base: `9cea0fba8b`. Scope: the header-queue rows of `BfmeParticleSystemHandle`
(about 17 `FAIL` rows) and `RvaSmartPtr12`. Scratch builds only; nothing here
landed except the two adoptions named at the end.

## Target facts

- `destroyParticleSystemByID` (0x001F5B79) inlines the handle destructor:
  `mov ecx,[ebp-18h]; ... cmp dword [ebp-18h],0; je; lea ecx,[ebp-18h];
  call 0x0004CBC0`. 0x003FDC46 does the same.
- 0x002115C5 (11 bytes, `cmp [ecx],0 / je / jmp 0x0004CBC0`) is reached by
  only two direct calls (0x00211ED9, 0x00212AD6); the rest are funclet jumps.
- `_STL::_Destroy<RvaSmartPtr12>` (0x00211F9A, 9 bytes) is
  `mov ecx,[esp+4]; jmp 0x002115C5`.
- No LTCG (`docs/recipes.md`, Rich header), so no cross-TU inlining.

## Compiler fact (MSVC 13.10.3077, scratch)

With `~RvaSmartPtr12()` defined inline in `RvaSmartPtr12.h`, STLport's
`__pointer->~_Tp()` in DestroyInstances.cpp compiles to `push 0; call ??_G...`
(an emitted scalar deleting destructor), not retail's `jmp ??1`. All other 78
consumers of the header compiled and matched; DestroyInstances.cpp failed on
0x00211F9A only.

## Consequences

- `RvaSmartPtr12.h` must keep its out-of-line `~RvaSmartPtr12() throw();`.
- The FAIL rows need a class whose destructor is inline. An out-of-class
  `inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle()` in the unit
  byte-matches ParticleSys.cpp (129/129, header_adopt_lane accept PASS), but
  the pre-commit unrowed-definition check refuses it (only dllimport
  `__forceinline` specializations are exempt).
- So `BfmeParticleSystemHandle.h` itself should define the destructor inline.
  Its body calls the 0x0004CBC0 unlink, whose ledger name is
  `RvaSmartPtr12::rva0004CBC0`, so the header must include `RvaSmartPtr12.h`.
  14 consumers of `BfmeParticleSystemHandle.h` / `ParticleSystemClass.h` still
  define a private `RvaSmartPtr12` and would stop compiling; some of those
  (0x003FDC46's unit) give their private copy an inline destructor, i.e. they
  really need the handle class, not `RvaSmartPtr12`.
- Next step: move those 14 consumers to the canonical classes (private copies
  with an inline destructor become `BfmeParticleSystemHandle`), then make the
  header destructor inline in the same commit, and re-run the FAIL rows'
  `header_adopt_lane.py accept`.

Landed alongside: `RvaSmartPtr12.h` adopted in
`Code/GameEngine/Source/Common/System/SmartPtrCopyCtor.cpp`;
`Rva001F458BText.h` adopted in ParticleSys.cpp.

## Later finding (same session)

- Six more consumers inline the destructor too: CPUParticleLoadPostProcess
  (0x001F6201: `cmp [ebp-20h],0; je; call 0x0004CBC0`), DefaultModuleHeadBase
  (0x003A57E7, member modelled trivial for that reason),
  ParticleSystemLoadPostProcessBfme2 and W3DModelDrawParticles (private
  handle with inline destructor). None of them can take `RvaSmartPtr12.h` as
  long as its destructor is out of line: a derived inline-destructor handle
  would add the base destructor call.
- 0x002115C5 is already an ICF fold of six `??1` names (ledger fold-proofs),
  so retail plausibly had two layout-identical classes: one with an out-of-line
  destructor (the `_Destroy` instance's) and the particle handle with an
  inline one, both using unlink 0x0004CBC0. The obstacle is the unlink's
  owner: it is named `RvaSmartPtr12::rva0004CBC0`, so an inline handle
  destructor needs the complete `RvaSmartPtr12` in `BfmeParticleSystemHandle.h`.
  Untried alternative: move the unlink (and attach) to the handle class via
  `tools/rename.py` and let `RvaSmartPtr12` call them through it.
- `SmartPtrAttach.cpp` adopted `RvaSmartPtr12.h` (1/1, accept PASS).
