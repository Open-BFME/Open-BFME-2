# W3DFloorDraw merge: publication ordering blocker

2026-11-04; worker yasinschroeder-codexb4; model gpt-6.1-sol.

Header prerequisites passed: the main floor-draw source and xfer source now
include the canonical W3DFloorDraw header. Their scoped builds matched 19/19
and 1/1 rows. header_adopt_lane.py accept passed both W3DFloorDraw rows and
the main source's FieldParse and MultiIniFieldParse rows, retiring four queue
entries through the owning tool with linked-byte preservation.

After those adoptions, tu_skeleton.py --merge --dry-run accepted the main
source, W3DFloorDrawXfer.cpp and W3DFloorDrawPoolKey.cpp. Application reused
the verified plan: 23/23 rows exact, five EH parents EXACT, CSV/frozen-source/
staged-TU-ownership checks passing. The current six-unit merge link guard
passed. Two donor files were removed, four ledger sources repointed and
two data-ledger owners transferred. Destination grouping is approved by
the current in-memory map; its path remains provisional, not proven retail
filename evidence. No pins, aliases or hatches changed.

Publication of merge b4b295f925 was refused before runner handover:

    repair_queue: .../W3DFloorDrawXfer.cpp: its reverse/header_queue.tsv row
    (W3DFloorDraw) went with the source; a vanished unit is a regression to
    investigate, not an adoption
    PRE-PUSH FAILED: retired debt has no passing outgoing verdict

This is a false rejection of the earlier passing adoption: the source exists
and passes accept in the adoption commit, then a later merge removes it in
the same outgoing range. No check was edited or bypassed. A new commit
reverts only the merge and preserves both header-adoption commits, so their
retired rows can be judged on surviving source files. The blocked attempt
is recorded through re_log.py. No source-file reduction is retained here.

Next: once the four adoption retirements are on origin/master, run the
supported consolidation planner and merge dry run again. Absorb the xfer
and pool-key donors in a later outgoing batch. The ctor still references
its private m_10 slot/owner view; the destructor and draw-module donors
need terrain/drawable declaration reconciliation; the ModuleData views
also disagree on class key. Seven mixed sources remain outside this merge.

The completed path-consumer audit found no active removed-basename consumer
in tools, hooks, workflows, Code, docs or root build configuration. Only
provenance comments and historical measurement/evidence records retained
old paths. Active identity/data/header/Microsoft-header/flag/hatch/body-owner
registers required no additional changes; data_ledger carried the two owners.
After the revert there are no source-path moves in this session's final tree.
No census, real-link or image-ownership improvement is claimed.
