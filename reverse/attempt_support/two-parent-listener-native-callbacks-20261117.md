# Two-parent listener callbacks

Native observer table86D298 slot3 reaches56A9ED, the7B byte clear through
secondary receiver+9. The canonical listener lies at complete+14, so this
is complete field1D. Declaring the existing canonical slot3(int) override
on Rva0056B0BF lets MSVC emit the native secondary-base receiver naturally.
Constructor and destructor views are synchronized; destructor field extent
now includes the same three constructor-proven bools1C/1D/1E. No pin added.
Private constructor6/6 and destructor6/6 retain all original coverage.
Normal paired verification passes12/12.

A combined probe for observer slot2 first hits a real C++ name collision:
LivingWorldBattleListener::slot2(int) returns void, while inherited canonical
Rva0056AC26Base2::slot2(int) returns bool. Neither shared header is changed.
A correct method cannot override just one through the current neutral names.
This is a contract naming prerequisite, not a demonstrated false reject.
Remaining primary and secondary candidates are being examined separately.

Primary table86D2E8 slot1 at4543C6 is now the concrete bool getter for
constructor-proven field1E. Its complete4 bytes match the original provider;
normal paired verification passes13/13 after this independent admission.

The native17B guard56A9B5 is now owned by the same complete class: it
requires1C and1D, then sets1E. Native primary setter56A9C6 and observer
callback56A9DE both pass this complete receiver. The outlined boundary is
kept explicitly, matching the original provider and avoiding an inlined
replacement. All14 paired rows remain exact after this separate admission.

Primary slot3 at56A9C6 now sets1C then calls its own outlined17B guard.
Its complete9 bytes preserve the native tail jump; paired15/15 exact.
