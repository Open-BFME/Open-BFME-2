# Highlight filter TU prerequisites (2026-11-02, halilkkaya-codex)

Base: 1291df600d4fba21e9a60ef84de93c18d033f5ea. Scope: device screen-filter TU.

Target facts: native shutdown FB8EB releases the consumed words at +04/+08,
clears the vector header at +18 and releases +2C/+24/+28/+30. Existing
postRender FAC37 consumes the same words through the seed's storage spelling.
This change shares that spelling with shutdown; it does not recover the
shader-word lifetime identity, introduce a constructor/table, or rename a row.
The existing int[3] kernel header is viewed as the existing vector only for
clear; COM words use the donor's existing Release slot interface.

Validation: ./build.sh passes 13/13 rows, string/float/import checks and
existing EH graphs. find_declared_unmatched passes both units. All 43
external COMDAT definitions (code and data) retain their normalized bytes
and relocation identities; shutdown-definitions.json records the comparison.
Paired link_check against 984a4cdc4d (2026-11-02 08:35) retains LINKS 3286 B.
Dry-run now accepts seed plus shutdown (13 rows); PreRender and Slot6 still
need declaration reconciliation. No header queue key is retired here.

## Applied merge

The supported tu_skeleton merge accepts seed and shutdown, removes one file
and repoints its single row. 13/13 rows and frozen-file verification pass.
The original 43 external COMDAT definitions become 43: the bfmealloc
include context selects the by-value __false_type __copy_ptrs overload in
place of const-reference and changes the emitted Gen_p12pod erase helper.
The two differences were explicitly carried into the consumer comparison;
they are not described as unchanged definitions.

link_check.py checked 1279 current sources defining/referencing the original
50 providers across the four candidate files (deleted census sources excluded).
Its 31 failing units have existing obstacles. A separate same-cohort comparison
overlays the two saved pre-edit objects for the before state and current
objects for after, preserving actual before/after row ownership and link order.
1248 units stay clean, no unit loses LINKS and no new finding appears.
The two untouched candidate satellites remain LINKS. The destination is
3286 B, preserving the original seed3165 + shutdown121; no census gain claimed.
Ordinary dependency receipts are current for all1279 objects;114 have strict
receipts. This comparison is an ordinary preview, not a strict outgoing audit.
All full-build99289 rows,2259 data rows and full gate passed during setup.

Tooling compatibility audit, base1291df600d through this merge: searched the
removed path/basename across tools, hooks, workflows, Code, docs and reverse.
No active path consumer remains. Preserved references are merged-source
provenance and historical p12-erase/pod-erase evidence. Core functions/map
source cells are tool-repointed (map only repointed, not regenerated).
No donor key remains in identity/data/hatch/override/header/MS queues, data
ledger, symbols fold proofs or doxygen input registry. Header/MS queue refresh
ran through tu_skeleton's refresh_reports; there was no debt to transfer or
retire. No header_queue prerequisite commit is needed.

Remaining: PreRender declarations disagree at init/shutdown/preRender and
its Gaussian settings view needs +0C size; Slot6 needs receiver declarations
and the canonical DX8Wrapper interface. No guesses applied to these satellites.
The shared docs/linking_obstacles.md file is held by
codex-01a1071d-root-recovery-oct11; this scoped handoff preserves the result
for the lead to add without editing that claimed file.

## Init/preRender declaration prerequisite

Base3d7bb371e5. Matched native init FA935 consumes the same textures24/28,
surfaces2C/30, shader words04/08 and kernel18 as the existing seed; its
Gaussian settings size is +0C. Select those consumed words through the seed
spelling and retain the native shutdown-slot dispatch at +4 (slot04). The
seed's previously declaration-only slot0 is now its existing rowed init;
preRender uses the existing enum signature. No table/lifetime provider is
emitted. The seed's padding now exposes the already consumed +0C size word.

15/15rows, literal/import/float and frozen-file checks pass. Strict preparation
of both sources succeeds. All43seed definitions and six of seven PreRender
definitions retain their full bytes/relocations. The accessor's old surface
return decoration becomes the existing canonical device return decoration;
the old name's only indexed touching source is PreRender itself. No outside
consumer loses that provider. All three current candidate units retain LINKS
(4134B total). No header_queue entry is retired. A fresh supported dry-run
accepts seed plus PreRender,15rows; Slot6 remains rejected.
