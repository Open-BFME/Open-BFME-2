### RenderObjIntersectSphere math header cleanup (2026-10-29)

The local sqrtf wrapper is replaced by the Microsoft math header in
`Code/Libraries/Source/WWVegas/WW3D2/RenderObjIntersectSphere.cpp`. All three
rows match, and the unit retains LINKS for 562 bytes against index
`85f6b7f40c`. The preview reports an unreferenced 7-byte `_sqrtf` copy,
different from the majority 17-byte copy; it is not a blocker in that preview.
Check affected consumers in the outgoing link audit and the next census. No
census gain or consumer-wide clearance is claimed.
