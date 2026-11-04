# AptTimeLine vector consolidation prerequisite, 2026-11-04

Inspected master bd70c5a4ce; census index f6d845ecd4 (2026-11-04 13:15).
Scope: StlSweepR3Rva0051F7AD.cpp, assignment at RVA 0x0051F7AD, 206 B.

The approved destination is GameClient/GUI/GUICallbacks/Apt/AptTimeLine.cpp.
The original donor redeclared STLport allocator/vector/__false_type, preventing
composition with the destination's real <vector> include. The cleanup uses
STLport's complete vector for the assignment and its allocation proxy storage.
Only the external allocation owner's opaque specialization remains bounded.
Declaring that member specialization on the complete vector triggers cl 7.1
C1001 (P2 main.c:148); the bounded specialization preserves its native symbol.
A derived false-type tag with a user-provided constructor prevents the extra
zero initialization emitted for STLport's POD tag. No element identity is inferred.

Checks: ./build.sh donor passes 1/1 (206 B), including call relocations;
find_declared_unmatched reports all definitions matched; link_check predicts
LINKS, 206 -> 206 B against the stated index. No census gain is claimed.
The merge dry run now accepts this donor without losing a seed row or link.
StlSweepW4Rva005205DA.cpp remains rejected for its existing 80-byte element
identity conflict (LINK-002); it is unchanged. The scoped planner report was
regenerated after the initial trial, before the prerequisite source edits.
