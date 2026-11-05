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
Remaining: LightClass was peer-held during this pass; its partial header claim was released and
its original view is untouched. Full RTS2D/interface identity remains separate.
Global consumer selection and runtime are not inferred from this scope;
carry source and affected consumers into the next scheduled census.
Census or real-link gain: not claimed.
[Object invariants, native tables and owning verdicts](../../reverse/attempt_support/display-init-shared-headers-20261105/readme.md).

Rebase receipt: source4aa32ca6e244819ecb76df7a1ad337eafcb79b77 on60cc40eb3a.
After upstream's Vector3Data.h change, repeated strict15/15,21 unchanged
object fingerprints, EXACT EH and LINKS1599->1599 pass. Header-dependency
check returns0. Outgoing batch audit remains INCONCLUSIVE: older indexc95fcfcfcd
and no current affected-consumer receipt for
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp.
Retained diagnostics delimit this adoption proof; full consumer/census
clearance and runtime remain prerequisites, not inferred successes.
