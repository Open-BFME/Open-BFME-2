# RenderObj constructor merge audit

Batch base: `85b46a09f34220f2b5c6b55bdbac33a595d943b5`; prerequisite commit: `c7add74f7c`. The final merge is recorded by this commit.

`tu_skeleton.py --merge` used its guarded accepted composition: rendobj.cpp plus RenderObjCtor.cpp. The 262-byte default constructor at RVA 0x0013BF00 moves into its approved TU. One source file is removed; 26/26 rows remain exact. The only tu_map edit repoints that row's source column; the map is not regenerated. Seven mixed sources and the three rejected donors remain intact.

Verification: scoped build, declared-unmatched and check_csv pass. The final four-unit preview LINKS for the merged TU and the three remaining donors. Its 3,626 authored bytes equal the combined premerge bytes (the preview's apparent +262 is the moved constructor, not a gain). Index: c95fcfcfcd, 2026-11-05 05:17. The merge guard also preserves the constructor donor's previously linking status. The final preview reports an unreferenced MultiListObjectClass constructor difference; carry affected-provider closure into the outgoing batch audit and next census. No global link or census result is claimed.

Debt/queues: narrow searches find no code-identity, data-debt, header-queue or Microsoft-header-queue keys for either source. The merge tool refreshes affected queues and transfers the constructor's four pragma occurrences through hatch_counters --update; their total is unchanged. No debt is retired and no alternatename is removed. The donor has no data rows or EH rows; all 26 code rows are current.

Tooling compatibility audit: the only outgoing path removal is Code/Libraries/Source/WWVegas/WW3D2/RenderObjCtor.cpp. Searched the old path/basename across tools, hooks, workflows, Code, local shims, docs and reverse registries. The single tooling hit is a synthetic path in test_tu_structure.py's fixture (not a read of the source). Other hits are census history, attempt evidence and source-provenance comments. Preserve these historical references. No active include, config or tool needs repointing beyond the merge tool's functions.csv and tu_map source-column changes. See path-consumers.txt. The original evidence planner was reviewed before edits; its snapshot is intentionally stale after source/ledger changes and was not reused as approval.

Remaining: RenderObjCopy.cpp and Filename_From_Asset_Name.cpp fail the merge's byte comparison; RenderObjIntersect.cpp would introduce a duplicate RayCollisionTestClass constructor. Reconcile those independently before another merge. No rejected body is left in Code.
