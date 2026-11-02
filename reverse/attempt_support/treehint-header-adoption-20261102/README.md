# TreeHintRef header adoption: water renderables

The assigned twelve-source cohort first ran through the ordinary adoption
tool. It refused all twelve and left their sources unchanged. Original
private baselines independently match every unique native address (Water
has 23 rows at 22 addresses, and FXShaderParameterBinder has 61 at 60 because
of existing shared folds; this is not a failed row).

W3DWaterAreaRenderables.cpp needed no field rewrite: its declaration-only
TreeHintRef00217D4C contains a pointer named p that this source never reads.
The automatic conservative rename p -> m_ptr collided with an unrelated
WATER_AREA_REF macro field. Replacing only that private declaration with
the existing canonical AptRefTarget.h include avoids any field rename.
The shared header is unchanged. No guessed layout or new callback/refcount
semantics is added.

All 23 native rows pass normal and strict checks, all five parent EH graphs
are EXACT, and all 79 complete external code definitions preserve bytes and
symbolic relocations with no added or removed name. The owning accept tool
passes and retires exactly one header-queue row. The current bounded preview
retains LINKS 1,168 -> 1,168 bytes at index 984a4cdc4d (2026-11-02 08:35).
This is one debt/private-copy removal, not a new census or authored-byte gain.

The other eleven sources remain original and queued. Their shared causes
are recorded in cohort-refusals.log: explicit vptr/extended referent fields
need compatible views, callback-valued constructors need their actual
target representation, and owning destructor/assignment visibility changes
native code generation. Do not repeat this unchanged automatic cohort or
add methods to the canonical header by guessing their semantics. The useful
next steps are per-family target/ABI reconciliation followed by owning
acceptance; a header include alone does not establish compatibility.

Earlier sphere publication 06685c8a62 preserved 3/3 native rows through
pre-push checks. Its wider audit was INCONCLUSIVE against 984a4cdc4d versus
outgoing base 3799c53a99, first lacking a current sphereobj receipt. A fresh
post-publication strict preparation now makes both strict compile currency
and census object_current true. It does not turn that prior audit into global
clearance; the next scheduled census must judge the complete current tree.
