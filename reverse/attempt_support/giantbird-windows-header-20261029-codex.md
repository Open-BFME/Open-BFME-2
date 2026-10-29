# GiantBirdAIUpdate Windows macro cleanup

Inspected base `9ddec6b7fb`, 2026-10-29. The default picker selected the
Microsoft-header queue entry for
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp`.
The file scope is claimed by `yasinschroeder-codex`.

## Retained change

Opt into the supported Platform SDK and include windows.h after the existing
STL includes. Remove local NULL, TRUE, FALSE, max and min definitions. The
owning auditor's scoped refresh_queue reduces this entry from six findings to
one; the remaining free ABI conflict stays registered. No row, symbol, source
path or class identity changes.

## Remaining CRT prerequisite

Replacing the local free declaration with stdlib.h was tested and reverted.
The update row at 0x0036B103 then fails: the direct E8 call becomes FF 15
through the CRT IAT, adding one byte and shifting subsequent instructions.
The other five rows still match. This is a real code-generation difference,
not a verifier refusal. Keep the direct-call declaration until the allocator
binding can be represented through an appropriate existing header while
preserving the complete body and consumers. No nonmatching trial is retained.

## Verification

- Before and after: ./build.sh verifies all six function/EH/funclet rows;
  thirteen floating literals and all reference checks pass.
- Strict preparation through link_check.py --prepare-current passes.
- Both EH graphs are EXACT. Frozen-file checks pass before and after.
- Converged data check: eleven addresses, no second names or unjudged rows.
- The saved pre-edit and final objects have identical 55 external COMDAT
  fingerprints/sizes, identical relocation graphs and identical sets of
  87 external definitions/references. Generated local EH labels are allowed
  to renumber and are checked through the parent's exact EH graph.
- Ordinary preview retains LINKS 1,791 -> 1,791 authored bytes against index
  85f6b7f40c (2026-10-29 15:08). This is no new census gain.
- The staged-tree batch audit is INCONCLUSIVE: index 85f6b7f40c predates
  the source base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry that consumer and this provider into the next
  scheduled census; consumer-wide clearance is not claimed.
