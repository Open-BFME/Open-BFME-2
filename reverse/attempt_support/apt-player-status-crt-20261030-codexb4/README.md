# AptPlayerStatus destructor unused CRT declarations

Inspected base: `3134afceb4`. Claimed source:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPlayerStatusDtor.cpp`.

## Change and evidence

The source declares `memset` and imported `sprintf`, but never references
either name outside those declarations. Remove both unused prototypes.
No replacement include is required. This changes no recovered class layout,
callee identity, compiler flag, shared header, ledger row, pin or source path.

The owning Microsoft-header scanner reports zero local definitions and uses
`refresh_queue` to remove only this source's row, preserving unrelated queue
entries. That retires two findings, including the conflicting `sprintf` ABI
declaration. The computePath and WallUpgradeUpdate attempts are separately
recorded and retain their source and queue entries.

## Verification

- Frozen-source checks pass before and after the edit.
- Normal before/after builds verify all six function rows and the string
  reference. Three funclets are resolved through the exact same-source parent
  EH locations after compiler-local label renumbering.
- [External object facts](object-comparison.json), collected through
  `link_census.object_facts` with a neutral verdict callback, are identical:
  19 COMDAT fingerprints/sizes, one exclusive definition, 19 undefined names
  and one weak alias. This is a comparison, not a substitute for retail byte
  verification.
- `eh_verify.py`: one EH graph, EXACT; no baseline or missing object.
- `link_check.py --prepare-current`: one explicit provider byte-verified with
  a strict reusable receipt. Ordinary preview retains LINKS, 263 -> 263
  authored bytes, against index `85f6b7f40c` (2026-10-29 15:08).

The staged outgoing-batch audit covers five providers, including the three
earlier commits. It exits 2, INCONCLUSIVE: the index predates outgoing base
`2a2dd9996b`, and `LinearCampaignManager.cpp` lacks a current strict receipt.
The earlier [Region3D handoff](../region3d-view-header-20261030-codexb4/README.md)
records its unsupported include-inventory prerequisite and normal campaign
verification. This attempt does not change that compiler input or bypass the
receipt boundary. Carry these providers and their affected consumers into
the next scheduled census; full consumer selection/loss verification remains
unproven.

The parent at RVA `0x004E4655` remains 240 bytes. The existing vector-destructor
ICF fold at `0x0007FAB3` remains the same row with the same proof. No matching,
census-linking or image-ownership gain is claimed. Runtime smoke and the
nightly census were not run.
