# GeometryUpgrade consolidation recheck

The supported picker reserved the seed, GeometryUpgradeDtor.cpp and
GeometryUpgradeModuleDataCtor.cpp. The naming planner was regenerated under
the Upgrade subsystem. All three sources pass the unmatched-definition check.
The supported fresh-map dry run reports 31 approved rows but accepts no donor.
The mixed ConstIntGetters4.cpp stays outside the scope.

The module-data constructor still fails composition with C2600: the seed's
GeometryUpgradeModuleData view declares no constructor. It is novtable over
Snapshot plus opaque inherited state; the constructor's independently verified
view needs the actual 253487 base call and derived vtable. Adding a declaration
alone does not establish that hierarchy. The behavior destructor still fails
bytes: its novtable/StringBase view preserves the native 53-byte no-derived-
vptr body, while the seed constructor needs four derived table stores and an
AsciiString member. A blanket novtable change would lose the constructor.

These are the same structural prerequisites documented by the October 30
string-vector correction. The source changes from that correction remain
intact. No source/header, ledger, map, flag, pin or register was changed here.
No scoped debt or active tooling path consumer needs a transfer. Any future
view repair must also verify the field-table consumer and existing vector
base/destructor providers.

Against the refreshed index (14:31, 86db074988, census 39dfbbdb50), all three
current units predict LINKS and retain 1,435 bytes: seed 1,231, behavior dtor
63 and module-data constructor 141. No new linking or source-file gain is
claimed. This is a current prerequisite handoff, not a newly discovered loss.
