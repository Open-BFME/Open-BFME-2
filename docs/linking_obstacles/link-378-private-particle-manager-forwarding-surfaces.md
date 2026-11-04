### LINK-378: private ParticleSystemManager forwarding surfaces
Status: Cleared for the two header-adoption rows below. Updated: 2026-11-04; inspected revision: d9a128b6d0.
Scope: Rva0004CB1EParticleForward.cpp and W3DDisplaySmallSlots.cpp under Code/GameEngineDevice/Source/W3DDevice/GameClient/.
Completed: replace private slot declarations with canonical doParticles/update calls; owning header acceptance retires two queue rows, preserving all 11 native rows / 579 bytes and all external definitions/references.
Evidence: [target facts, before/after objects and checks](../../reverse/attempt_support/particle-manager-forwarders-20261104-codexb5/README.md).
Remaining / next check: the other twenty queued manager consumers need their storage, handle ABI and nested-type prerequisites; broader current provider/consumer selection remains unverified.
Clearance: private manager surfaces removed in these two units only; both whole-source byte checks, frozen-file checks, strict receipts and header acceptance pass.
Census confirmation: awaiting the next normal census; no new linking coverage or runtime claim.
