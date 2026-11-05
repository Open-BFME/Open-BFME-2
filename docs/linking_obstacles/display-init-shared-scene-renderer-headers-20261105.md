### Shared scene and renderer definitions in display initialization (2026-11-05)

Status: Cleared for the two scoped header adoptions. Base cadc5ea134a.
Scope: W3DDisplayInit.cpp's existing15 native/EH rows.
Completed: use unchanged Render2DClass.h and RTS3DScene.h; remove four private
class bodies. Constructor-only interface/2D views follow their rowed owners,
keeping108/11C/818 allocation sizes and existing global pointer identities.
All21 old code/data definition and relocation fingerprints are identical;
no new definition or virtual table is emitted. Full parent EH is EXACT.
Normal/strict15-row, reference and new-variant checks pass; ordinary preview
retains LINKS1599B against indexc95fcfcfcd (05:17 Nov5). Owning acceptances
retire two queue rows. No source path, pin, signature, flag or shared header changes.
Remaining: LightClass is peer-held, its partial header claim was released and
its original view is untouched. Full RTS2D/interface identity remains separate.
Global consumer selection and runtime are not inferred from this scope;
carry source and affected consumers into the next scheduled census.
Census or real-link gain: not claimed.
[Object invariants, native tables and owning verdicts](../../reverse/attempt_support/display-init-shared-headers-20261105/readme.md).
