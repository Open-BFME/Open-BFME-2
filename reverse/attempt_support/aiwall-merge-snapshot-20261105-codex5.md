# AIWall merge snapshot rejection, 2026-11-05

Inspected revision: ed17a7ae6f (the published class reconciliation).
The prerequisites in [the earlier handoff](aiwall-consolidation-prerequisites-20261103/README.md)
are repaired; [the repair evidence](aiwall-class-reconciliation-20261105-codex5.md)
records 56/56 exact code rows, four data rows and three passing current-object
link previews (5,513 bytes preserved). No new census or real link is claimed.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/SkirmishAI/AIWallBuilder/AIWall.cpp --dry-run`
now reaches its link guard, but exits 2 without applying a merge. It reports:

```text
duplicate ??0Rva004EB5E9@@QAE@H@Z
no longer defines ??0Rva004EB583@@QAE@H@Z, which the census still references
```

The index provider snapshot is c95fcfcfcd, 2026-11-05 05:17; its underlying
census is c2a9f8e0d7, 03:49. Targeted inspection with `link_check.load_index()`
shows the old constructor defined by Rva004EB583Ctor.cpp, and touched only by
that donor and AIWallBuilder.cpp. The unified constructor is still a COMDAT
in the snapshot's AIWallBuilder.cpp: the removed forwarding wrapper.

`link_census.object_facts()` on the three current, byte-verified objects shows:

| Object | Old constructor | Unified constructor |
| --- | --- | --- |
| AIWall.cpp | Neither defines nor references | Neither defines nor references |
| AIWallBuilder.cpp | Neither defines nor references | Undefined reference only |
| Rva004EB583Ctor.cpp | Neither defines nor references | Sole definition |

The merge guard replaces the seed and donor while retaining the snapshot's
caller. It therefore retains both the obsolete caller reference and obsolete
wrapper definition. The normal three-object link preview replaces the caller
as well and passes. This is a stale-snapshot rejection of the repaired cohort;
it does not establish a current source regression. No guard, index or baseline
was changed to force admission, and no failed reconstruction remains in Code/.

Next: obtain a provider index incorporating ed17a7ae6f (including the caller),
then retry the supported merge and perform the full path-consumer/register/
header/provider audit before publishing any move. Whole-ledger `--update-index`
was not run in this scoped pass. The 18-row OpaqueScalarDeletingDtorsB11.cpp
and one-row stlport_sort_rva004ebe74.cpp mixed donors remain separate work.

The prerequisite hook's shadow diagnostics also remain evidence, not retired
debt: the compatible pointer-vector constructor folds to the existing POD
constructor body; existing BfmeE8/PolygonTrigger template copies and the seed's
wallTriggerSerial data identity need their own identity/data work. No new pin,
alias or converged-data binding was introduced.
