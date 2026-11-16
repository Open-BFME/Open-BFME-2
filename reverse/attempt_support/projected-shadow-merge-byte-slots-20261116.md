# Projected-shadow merge after bounds/manager reconciliation

The declaration prerequisite verifies 81/81 functions, 11 exact EH graphs and
13,804 preview bytes. Official focused tu_skeleton dry-run now compiles both
donor combinations, but neither is byte-exact. No merge has been applied.

Measured differences in the composer's existing objects:

- Reader layerHeightRva001086EC (164 bytes): first difference at +19 is the
  Get_User_Data virtual-call displacement, actual 0x158 versus retail 0x15C.
  The subsequent call has the same one-slot discrepancy.
- Writer rva0010DA71 (1218 bytes): first difference at +945 is a virtual-call
  displacement, actual 0x17C versus retail 0x180.
- Writer rva0010DF33: merged body is 1337 bytes versus retail 1359. Its first
  conditional branch displacement differs at +55; that is a consequence of
  body-length change, not sufficient evidence of the underlying cause.
- Reader rva0010C841 also differs. The best reader combination matches 77 rows;
  remaining misses and absent donor rows are in merge-byte-misses.json.

The destination still includes unqualified rendobj.h through donor include
paths. Reader uses the registered canonical header; include guards let the
first declaration determine the composed TU. The consistent one-slot delta is
therefore evidence for testing canonical RenderObjClass in the destination.
It is a hypothesis until the merged bodies verify, not permission to alter
vtable slots or patch call bytes. No change to that scope was attempted:
class:RenderObjClass and class:CameraClass are currently held through nleigh's
part_buf.cpp claim. StringClass, WW3D and DX8Wrapper also remain peer-held.

The preceding Camera experiment in projected-shadow-camera-adoption-20261116.md
must still be respected: retaining caller rows while adding a wrong getter
COMDAT is not acceptable. Recheck every added/changed provider in any retry.

Local evidence is in the managed decal-merge worktree under
build/decal-diagnostic/manager-bounds-* and merge-byte-misses.json. Objects
044c045df5b6be7d.obj and 5a59cedef6e419f8.obj in build/tu_skeleton supplied the
measurements above; compile_function was used only to inspect existing objects,
not to compile through build.py. No runtime success is claimed.

## Consolidation handoff after rebase, 2026-11-16

The official composer now absorbs both writer and reader into the approved TU.
Final validation: 91/91 functions, 12/12 EH graphs; one COFF definition per
drawStartX/Y and drawEdgeX/Y, used by both readers and both writers. Canonical
RefCountPtr adoption preserved every external provider fingerprint. Branch
codex/decal-merge is rebased onto b8ecb5c9c7; game execution remains untested.

Publication is not cleared: link_batch_audit exits 2 (INCONCLUSIVE), even after
strict current receipts for the destination and W3DShadow. Latest published
census is 0534e78db3 at 16:28; the baseline is older than master and the audit
also lacks a receipt for 0CreateAHeroManager21FE49.cpp. Next: resolve the
baseline/consumer evidence through official tooling, review the two renamed
compiler guard shadow findings, then publish only with tools/push.py and test
the resulting real-link image on Windows. No baseline exception or forced link.
Full evidence and preserved shadow findings: docs/linking_obstacles/
link-661-split-storage-tu-local-statics-across-one-function-files.md and
build/decal-diagnostic/final-link-batch-audit.log.

Follow-up: CreateAHero now has a strict receipt (27/27); the audit's provider
scope reaches 4,588 consumers, 4,587 without strict receipts. Its documented
exit-2 policy allows a normal hooked push with linking explicitly UNVERIFIED,
unlike exit 1 for proven loss. User approval for the whole local batch is
pending; do not confuse the still-passing scoped preview with full validation.
