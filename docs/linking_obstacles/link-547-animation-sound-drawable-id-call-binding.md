### LINK-547: AnimationSoundClientBehavior calls an unprovided Drawable ID getter name

Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: `9497d7bad5`.
Evidence / completed: [Scoped byte checks and object-symbol comparison](../../reverse/attempt_support/animation-sound-drawable-id-link-20261105-codexb5.md); `updateAnimationSounds` now calls the existing rowed `Rva0055A88BDwordField::get` provider, preserving the `DrawableID` audio-constructor overload.
Remaining / next check: rerun the real link in its authorized workflow and confirm AnimationSoundClientBehavior.cpp no longer reports `?getID@Drawable@@QBE?AW4DrawableID@@XZ`; other consumers of that missing name remain outside this repair.
Clearance: pending real-link verification; the scoped preview remains LINKS at 2,316 bytes, and all 31 function rows plus one data row verify.
Census confirmation: awaiting; no headline gain claimed.
