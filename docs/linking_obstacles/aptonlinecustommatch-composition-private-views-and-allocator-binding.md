### AptOnlineCustomMatch composition: private views and allocator binding

Status: Open. Updated: 2026-10-29; inspected base c8871e52ab. The supported
merge probe accepted no donors: the seed and several donors have incompatible
private declarations, and the response-pump composition loses its
`?free@_STL@@YAXPAX@Z` binding. The class-view planner initially failed to
compile the response pump because it includes WinSock2.h without opting into
the Platform SDK. Adding the opt-in restores a fresh layout compile; all 75
rows, string and import checks pass, and link preview retains 9,173 bytes at
index 840db2d676. Reconcile the class views and allocator binding before
retrying the supported merge. No census gain or composition clearance claimed.
