# BitRange consolidation, 2026-11-04

Selection: default `next_work.py --claim`, owner yasinschroeder-codex3.
Base fetched: 84634ff60c; prerequisite commits: 891f40af06 and 9eae3c5586.
The current in-memory TU map approves 0x003ED9B1 for
`Code/GameEngine/Source/Common/BitRange.cpp` through C bracketing with
provisional naming. This grouping does not establish the original class or file name.

## Changes and verification

The first guarded trial accepted no donor. In Rva003ED9B1Merge.cpp,
replacing private STL tree declarations with `<stl/_tree.h>` removed C2039.
The next trial exposed a macro-namespace parsing problem: composition placed the
vector specialization and BitRange declaration after their uses and lost their
terminating semicolons. The equivalent explicit `namespace _STL` block preserves
the declarations. Each prerequisite independently retained the exact 126-byte
body and a clean 126/126-byte link preview.

`tu_skeleton.py --merge` then absorbed that donor, deleting one source and
repointing its one functions.csv and tu_map.csv source cell. The map was not
regenerated. Four existing rows and the moved row all remain matched (253 bytes).
The merge's link guard passed for the census-linked inputs. The final normal
builder verified 5/5 rows; declared-unmatched is clean; EH is EXACT 1/1;
check_csv passes. Code identity (shadow) reports zero new findings; data_check
(shadow) reports zero findings; tu_ownership --staged --shadow passes.
The final link preview is 127 -> 253 bytes in BitRange.cpp against census
2026-11-04 17:56 at 8c757ea0db. These are relocated authored bytes, not a
126-byte census coverage gain; no census was run or headline gain claimed.

The unchanged global-storage include resolves to the same LargeGroupAudio
header from the Common destination. No static definitions or alias pragmas
were removed. The donor has no identity/data/header/ms-header/hatch debt keys.
The destination's Rva003ED658 header row remains, with its copy/unwind lifetime
prerequisite described in LINK-249; that obstacle's next step is unchanged.
The merge tool refreshed header and Microsoft-header reports, with no queue edit.

## Batch path-consumer audit

Audited origin/master 84634ff60c through 9eae3c5586 plus this staged merge.
The complete outgoing path removal set is W3DBridgeCtor.cpp -> W3DBridgeBuffer.cpp
and Rva003ED9B1Merge.cpp -> BitRange.cpp. Searched both old basenames together
under tools/, .githooks/, .github/, Code/, docs/, reverse/ and build.sh.
No active tool, include, workflow or build configuration names either removed
file. Remaining mentions are source-provenance comments, historical obstacle or
attempt evidence, and the census snapshot reverse/link_status.csv, which stays
owned by measurement. The current function and TU-map source columns name the
destinations; protected register keys and header queues continue to name existing
owners. The earlier bridge merge audit remains in bridge-ctor-merge-20261104.md.

## Remaining consolidation prerequisites

The unchanged stlport_rb_tree_BfmeStringRecord004071F7_insert.cpp donor fails
C2766/C2535: allocator<char> is already defined in the composed environment.
LargeGroupAudioKeyList.cpp fails byte matching when composed. Both stay in their
original files with all rows and debt preserved. Six mixed donors remain mixed;
this pass did not split them or change their approvals. Future work should
reconcile each rejected donor in a separately byte-verified commit, then retry
composition. This pass completes one verified file reduction only.
