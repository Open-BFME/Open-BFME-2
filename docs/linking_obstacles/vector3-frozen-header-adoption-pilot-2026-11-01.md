### Vector3 frozen-header adoption pilot (2026-11-01)

Fourteen private definitions replaced by the established Vector3Data.h;
62 function rows and 2 data rows pass normal verification, full-object runtime
equality is retained, and all 14 owning queue rows pass acceptance and retire.
Combined ordinary link predictions preserve 11,724 linked bytes against index
46c2713cfd; current whole-program linking remains unproved.
One consumer needs a scoped Coord3D/Vector3 field rename; five other byte-passing
trials add inline providers and were conservatively restored, rather than
treated as proven regressions. [Pilot and remaining prerequisites](../../reverse/attempt_support/vector3-adoption-pilot-20261101.md).
2026-11-05: the header's out-of-line operator= was the shared byte blocker (retail inlines it; 0x00169FB0 is an uncalled COMDAT); it is inline now and 8 more units adopted. [Inline assignment and remaining cohort](../../reverse/attempt_support/vector3-inline-assignment-adoption-20261105.md).
