# Checkbox dependency cleanup

Inspected base: `7c93954985cd`; preview index: `d92e7e6635`, 2026-10-28
15:58. BFME 1 reference: `e74410b3738a2bb75d626085d9ebfd3406a43ff7`,
covered by the 2026-10-27 freshness receipt. The default picker claimed
0x000A43CD and the W3DCheckBox.cpp file scope.

The recorded wrong-selected blocker is stale for the current provider pair:
W3DCheckBox.cpp already previews LINKS for 948 authored bytes when checked
with Render2DSentenceDrawBFME2.cpp. The latter retains its separate Add_Quad
COMDAT blocker. The same paired result holds after this cleanup; no new
linked-byte gain is claimed.

W3DGadget.h pulls in W3DGameWindow's renderer, although these callbacks only
need GameWindow and the donor's WIN_DRAW_LINE_WIDTH (1.0f) macro. Include
GameWindow.h directly and retain that macro locally, as in the previously
verified horizontal-slider and static-text cleanup. The donor include graph
explains the removable dependency; target byte verification establishes
preservation of BFME 2's callbacks. No new naming or layout claim is made.

Strict provider preparation initially refused the old parent-traversing
DisplayString include: it reached BFME 1's shim outside the inventoried
search roots. An explicit /Ireference/open-bfme-1/inputs/reference/shims
root and qualified w3ddisplaystring/GameClient/DisplayString.h include now
select the same header through a declared search root. Compiler dependency
receipts before and after identify the same BFME 1 DisplayString shim.
The final compile has a version-2 strict reusable receipt.

[Object comparison](checkbox-object-20261028-codex.json): all 39 retained
external COMDAT byte-and-relocation fingerprints are unchanged. Only the
PendingSurfaceStruct vector deleting destructor and vector-construction
iterator disappear. Strong definitions and weak aliases are unchanged;
four unused undefined dependencies disappear and none are added.

Checks: ./build.sh passes all three rows (261, 485 and 204 bytes), frozen-file
checks pass, EH verification finds no EH rows or missing objects, and scoped
data checking has zero findings. link_check --prepare-current verifies the
final source with a strict reusable receipt. Paired ordinary preview retains
LINKS for the checkbox and the existing renderer blocker.

The staged-tree batch audit exits 2, INCONCLUSIVE: index d92e7e6635 predates
the base, and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. Carry the removed-helper scope and this consumer into the
next scheduled census. Full external consumer selection and runtime closure
remain unverified. No census or image-ownership gain is claimed.

Scratch objects and audit: build/checkbox-link-20261028/.
