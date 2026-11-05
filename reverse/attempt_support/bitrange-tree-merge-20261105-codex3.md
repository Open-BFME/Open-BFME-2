# BitRange tree-donor consolidation, 2026-11-05

Base: origin/master a83333646e; starting HEAD 5fa8f0a42f.
Owner: yasinschroeder-codex3; default next_work.py --claim selection.
Prerequisite commit: 7997b866de.

The Common consolidation planner was regenerated and its BitRange packet reviewed.
It reports unresolved routing in its stale committed-map view, macro context and
quoted-include review. tu_skeleton rebuilt current assignments in memory and
approved the three moved rows for Common/BitRange.cpp by C bracketing within the
provisional group. The grouping does not prove the original class or TU name.
The committed map changes only three source cells, not assignment evidence.

## Repair and result

The original merge dry run rejected the tree donor with C2766/C2535: its private
allocator<char> specialization duplicated the existing bfmealloc shim. The
separate prerequisite replaces that specialization with the existing shim include
path. Normal build: 3/3 exact, 322 bytes; local link preview: LINKS 322/322.

The next supported dry run accepts BitRange.cpp and the tree donor. Applied with
tu_skeleton.py --merge, deleting exactly one source:
Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_BfmeStringRecord004071F7_insert.cpp
-> Code/GameEngine/Source/Common/BitRange.cpp.

Moved rows: 0x003ED70D (149), 0x003ED8B1 (153), 0x003EDA2F (20).
Normal build: all 8 rows exact, 575 bytes. Declared-unmatched passes, retaining
one pre-existing counted create_node marker. EH: EXACT 1/1. check_csv passes;
tu_ownership --staged --shadow reports no finding. The merge's census-linked
provider/consumer guard passes. Local link_check against the 2026-11-05 05:17
c95fcfcfcd census index reports BitRange LINKS 253 -> 575 and the unchanged
LargeGroupAudioKeyList LINKS 191 -> 191. Its unreferenced iterator diagnostic
is not a blocker. These previews relocate already matched bytes; no census or
headline linking increase is claimed.

The tool repoints functions.csv and tu_map.csv, and transfers the donor's one
present_unmatched hatch with hatch_counters --update (total kept). No identity,
data, header or Microsoft-header key belonged to the removed donor. The
Rva003ED658 header queue row in BitRange stays; LINK-249's member-lifetime
prerequisite is unchanged. The merge refreshed header/Microsoft-header reports
without changing their queues. No pins, aliases or data definitions were removed.
The tree comparator, construct and allocator bindings keep their existing names.

## Batch path-consumer audit

Audited origin/master a83333646e through 7997b866de plus this staged merge.
The complete pending source-path removal set contains only the tree donor above.
Searched its full path and basename in tools/, .githooks/, .github/, Code/,
docs/ and reverse/. There is no active tool, include or build configuration
consumer. Remaining mentions are source provenance comments, historical attempt
evidence and the measurement-owned reverse/link_status.csv census snapshot.
Current function/TU-map source cells and hatch ownership name BitRange.cpp.
The existing Common relative storage include resolves to the same LargeGroupAudio
header. ascii_string.h resolves through the existing bfme2_ascii include path;
the allocator now resolves through bfmealloc in both environments. No shared
header was edited. Existing pending GettingBuilt header-adoption work changes
no source path and is preserved.

## Remaining work

LargeGroupAudioKeyList.cpp still fails byte matching under composition and stays
unchanged; six mixed donors stay mixed. This pass does not retry their bodies,
split files, retire debt, or alter approvals. The tree allocator compile obstacle
is resolved and one source file is removed. The audio donor needs its own verified
compiler-environment reconciliation before another merge attempt.
