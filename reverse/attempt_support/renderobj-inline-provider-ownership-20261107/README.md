# RenderObjClass shared-body ownership

The served MeshClass table at retail RVA 0x007D35A8 was blocked by shared
RenderObjClass providers (LINK-619). Commit fdf8f1b9fe recovered the unrelated
float setter behind the false Set_ObjectScale alias. This follow-up removes
four redundant bodies from the canonical rendobj.h, retaining their virtual
declarations and the verified distlod.cpp owners:

| Method | Retail RVA | Mesh slot |
| --- | --- | --- |
| Get_Current_LOD | 0x0007E4AF | 84 |
| _bfme_ro_flag111 | 0x0006CFBD | 114 |
| _bfme_ro_flag113 | 0x0006CFDA | 116 |
| _bfme_ro_flag115 | 0x0006CFF7 | 118 |

These competing COMDATs had the same loaded bytes and relocations but different
alignment flags (0x60101020 versus the owner's 0x60501020). The bridge's strict
comparison is unchanged. The actual owner selects the unchanged BFME 1
rendobj.h, so removing bodies from the canonical header leaves its definitions
intact. This is an emission/ownership repair, not evidence of original TU
placement. No row, pin, alias, compiler flag or source path changes.

## Verification and scope

- Private candidates: 30/30 BaseHeightMapConstructor rows and 15/15
  MeshClassLifetime rows. private_probe.py reads the pre-change header from
  fdf8f1b9fe and writes only private candidates under build/. It was rerun
  successfully after applying the real header edit.
- Normal targeted build: 57/57 across those sources, distlod.cpp and
  RenderObjCollision.cpp. Normal build of the 21 known canonical-header
  emitter units: 849/849, including parent-proven renumbered funclets;
  4 data rows, 21 string references, 284 compiler floats and 8 imports pass.
- current_providers.py inspects the current objects of all 23 indexed
  providers for the seven previously blocked names, preserving index order.
  Each of the four changed names has one remaining definition, its owner.
  The unchanged Bounding_Box, Bounding_Sphere and Set_ObjectScale names have
  exact first-provider twins, including flags, bytes and relocations.
- The compiled Mesh table remains 516 bytes/129 slots, with the affected
  pointer names at the slots above. The narrow source-slot diagnostic retains
  59 other name/address discrepancies, mostly names with no ledger address;
  it is not a complete source-table or whole-image proof.
- Ordinary link_check preview at index 9c81acd297 (2026-11-07 13:23):
  MeshClassLifetime, distlod and BaseHeightMapConstructor all LINKS,
  conserving their 2,294 authored bytes. This is a prediction, not a census.
- header_dependents.py bounds the changed header to 291 ledger source units.
  The normal commit and push hooks verify the affected cohort and outgoing
  consumer selection; their logs remain the publication receipts.

No new real image or runtime result is claimed. The next real link must check
the MeshClass/RenderObjClass table outcomes and remaining source identities.
The previous setter push's broader audit was INCONCLUSIVE: index 9c81acd297
versus outgoing base 009791f6a9183bdf2a15fa583f1c30927c4b7013, with 23 consumers
without current receipts (first BaseHeightMapConstructor.cpp). Carry the broad
consumer/selection check into the next census; the byte/EH checks passed.

Target facts (retail RVAs, bytes and slot indices), current compiler facts
(definitions/flags/relocations), and the ownership inference above are separate.
The donor header's selection proves which source supplies these compiled
bodies; it does not establish retail's original source location.
