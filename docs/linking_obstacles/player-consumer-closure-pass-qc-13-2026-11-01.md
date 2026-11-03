### Player consumer closure pass qc-13 (2026-11-01)

Nine additional units adopt Player (75 code rows); the existing placement consumer
retains six rows through lexical pointer storage. The normal header gate passes
1090/1090 rows across117 units and32 data rows. Emitted code/data, virtual providers,
weak bindings and library directives are preserved; four callers add only an
unreferenced copy of the existing canonical index getter. No new census gain or
root-provider closure is claimed. PlayerListCtor and GrantUpgradeCreate_onCreate
remain Snapshot-profile prerequisites. Original and adopted setLocalPlayer both
predict93->0 on unresolved PointGroup rva006C0800. A named getDefaultTeam row reads
+160 while other caller views read+2EC, so these views were not unified by name.
[Scope, native tables and preservation evidence](../../reverse/attempt_support/qc13-player-consumers/README.md).
