# Canonical Drawable in ObjectCreationUpgrade::update

Private proof only, 2026-11-03. Replace the private Drawable declaration (only fadeIn(unsigned int)) with ../../../../Include/GameClient/Drawable.h at its existing location after Common/Upgrade.h. No method call, body, layout view, field name or compiler flag changes. Candidate retains root's explicit BehaviorModule.h include immediately after UpdateModule.h, and the previously published canonical Thing adoption and native math evaluation order.

Sanctioned tu_skeleton.Verifier passes all three current source rows for both control and candidate: native update0x004B42DB/753B plus local-static rollback0x0078EB92/13B and handler0x0078EB9F/10B. No missing RVAs or verifier errors. The private objects both define17 external code/data definitions. Their complete ordinary bytes and symbolic relocation contexts compare identically: zero additions, removals or changed definitions. This comparison does not claim full local/.sxdata identity or final whole-image selection.

Canonical Drawable derives canonical Thing and Snapshot and exposes the same fadeIn(unsigned int) signature. Its include controls Snapshot naming macros before a later module include, but the concrete private proof shows no emitted external code/data change in this TU. This is a pointer consumer, not a Drawable constructor/destructor/layout recovery. No new vtable or object provider is emitted by this swap. Do not claim sourcefile reduction or a census gain.

The current original source passes find_declared_unmatched.py. Root should apply the exact candidate only while its control hash still matches current source, then run normal byte/data/EH, strict/link acceptance, and owning header_adopt_lane.py accept --class Drawable. Candidate.cpp, control.cpp, control.obj, candidate.obj and proof.json are scratch evidence, not tracked source or progress. No tracked source, ledger, claims or shared build-cache mutation was performed by this helper.

Tracked application: the exact candidate was applied only after its control
SHA256 matched current source. Normal3/3 verification and owning Drawable
acceptance pass; one header-queue record is retired through that tool. Strict
reusable receipt passes. No new body, path move, pin or data owner is claimed.
The base-header commit hook also reported a shadow wrong-name finding for the
compiler static guard at RVA0x00A03E08; no data register is retired or renamed
here. Preserve that independent data-identity follow-up and census boundary.
