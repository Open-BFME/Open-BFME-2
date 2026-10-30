# FlammableUpdate CameraMarker vector reconciliation, 2026-10-30

Base: `5dd2fe194c`. The default claimed picker selected FlammableUpdate.cpp
consolidation (nine removable donor candidates, seven mixed sources).

CameraMarkerVecErase.cpp declared three pointer fields directly, whereas the
already matched FlammableUpdateModuleData constructor declares CameraMarkerVec
as a public STLport vector base. The compiler layout planner rejected their
composition because raw m_start at offset zero overlaps the other view's base.
The erase donor now uses that same vector base and its protected _M_finish,
with the same eight-byte CameraMarker class declaration. It declares the
existing _Destroy specialization instead of a private generic template and
removes its unused private random_access_iterator_tag definition. These are
local layout and composition facts, not a claim to recover donor field names.

./build.sh verifies the one 51-byte erase row, including string, float and
import checks. find_declared_unmatched.py remains clean. Saved pre/post objects
have the same one COMDAT fingerprint, one strong definition, two undefined
bindings and no weak aliases. The final CameraMarkerVec layout plan accepts
both files and proposes the union of their methods; the original base-overlap
conflict is gone. Ordinary link preview against index 85f6b7f40c preserves
LINKS for both erase (51 authored bytes) and FlammableUpdate.cpp (544), 595
combined. No census-linked-byte increase is claimed.

The first strict preparation and naming scan refused the concurrent merger's
temporary Code files. On the stable tree, strict current-provider preparation
passed for erase, and the naming planner wrote a fresh snapshot under
build/consolidation/flammable-20261030; its --check passed before the retry.
The packet reports no conflicting erase placement alternative, but its committed
map is stale and placement is only a hint there. tu_skeleton rebuilds the current
approved map in memory; do not commit the map from this lane.

The wider private views still disagree on TreeKey00242F5E field partitioning,
AudioManager virtual slots, UpdateModule/FlammableUpdate base clauses, and
FlammableUpdateModuleData class keys. The seed's duplicate 0x0048C7BF audio-start
placeholder additionally owns its EH rows, so a name-only row deletion would
lose EH coverage. Mixed sources must retain their unrelated rows. Existing
identity, hatch and header debts remain owned by their current sources.

Prerequisite source commit: 3a0b1fea7a (rebased by the runner publisher and handed over).
The original supported dry run (about 34 minutes) accepted no donor beyond the
seed. Its erase rejection was the private random_access_iterator_tag
redefinition against STLport. The supported apply-mode retry completed after about 38 minutes, after the
prerequisite commit and snapshot currency check. It accepted no donor and wrote
no tracked changes: erase now reaches a `bytes` rejection; the other eight
composition errors remain. The full final report accompanies this handoff as
`flammable-camera-vector-20261030-codex3-merge.txt`.

Cached-object inspection narrows the erase boundary to frame-pointer codegen.
The individually exact object has fingerprint `f8a633d0b533`, 51 bytes, starting
`55 8b ec 56 57 8d 45 0b` (EBP frame). The composed object
`build/tu_skeleton/1f6da9c1f8b79d82.obj` has fingerprint `61042581e2a1`, also
51 bytes, starting `56 57 8d 44 24 0f` (ESP-relative frame). Both retain REL32
relocations at offsets 21 and 32 to the identical Assign and _Destroy symbols.
All six cached composed erase copies inspected share that latter fingerprint.
This supports a TU-wide frame-pointer flag prerequisite; it does not prove
that changing the entire TU to /Oy- preserves the seed. Use the supported flag
and consolidation lanes to verify that hypothesis, without a per-function
pragma hatch. No further unchanged full merge trial was started.

History: reverse/attempt_support/consolidation-flammable-frame-20261025-codex.md
already records the iterator-tag rejection and the separate Xfer, missing-member
and ModuleData failures. This pass clears the erase-specific local definition
and layout conflict; it does not reopen those unchanged failures as regressions.

Initial full dry-run boundaries (2026-10-30, before the erase repair):

| Donor | First reported composition failure |
|---|---|
| FlammableUpdateXfer.cpp | C2011 Xfer redefinition and missing IsLightCRC |
| FlammableUpdateCtor.cpp | DamageModuleInterface vftable declaration modifiers disagree |
| FlammableUpdateDtor.cpp | C2011 Coord3D redefinition |
| FlammableUpdatePoolKey.cpp | getModuleNameKey already has a body through donor headers |
| FlammableUpdate_doAflameDamage.cpp | ObjectModule::m_object is private in the header view |
| FlammableUpdateRva0048C7BF.cpp | rva0048C7BF is absent from the header class |
| Rva0048CACCAccumulate.cpp | OS_A and rva0048C8F9 vocabulary missing |
| CameraMarkerVecErase.cpp | C2011 private random_access_iterator_tag redefinition (repaired) |
| FlammableUpdateModuleDataCtor.cpp | Header ModuleData lacks m_damageType and other BFME 2 fields |

These diagnostics concern declaration composition. They do not show that the
individually matched bodies regressed. Reconcile the relevant view in a separate
verified source commit before retrying each unchanged donor. Preserve mixed
files, explicit data/vftable providers, the seed's existing identity key and
unique EH coverage.


Register and path audit: no source was removed or repointed in this pass.
The erase source has no data/identity debt or header-queue key to transfer.
The seed's existing identity key, two alternatenames, three optimize pragmas
and loadPostProcess marker remain untouched. A search for the erase basename
found only the seed's not-yet-merged comment and historical attempt evidence;
no active tooling consumer requires a path change. No canonical header,
source map, pin, hatch baseline or census record was edited.

Checks after the retry: the ledger and final frozen-file checks pass. The
current two-unit ordinary preview still preserves LINKS for 595 authored bytes
against index 85f6b7f40c. Strict preparation covered the erase provider only;
strict closure, census confirmation and runtime behavior remain unverified.
No source-file reduction, debt retirement, ownership gain or new matched bytes
are claimed. Remaining candidates are existing cleanup blockers.
