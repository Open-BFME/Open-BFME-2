# ThreatFinder Snapshot include repair, 2026-11-02

The consolidated ThreatFinderUpdate.cpp included reference/shims/moduledata/Common/Snapshot.h with five parent traversals. From its current Object/Update directory that resolves under Code/reference, which does not exist. The correct existing root reference path needs six. The change adds that one traversal; no alternate search path, header policy, row, source owner or body is changed.

The failure was exposed by the ordinary Object header dependent-source gate. With the real existing Snapshot header restored, normal and strict verification pass all20 rows, both data rows, the string and two float constants. Compiler funclet renumbering is checked through the parent EH graphs. This is a source compile regression repair, not a new match or census/runtime claim. The pending SupplyTruck work was explicitly checkpointed outside this commit.
