### BehaviorModuleBase donor adoption (2026-10-31, fleet qc-11)

At base `1e7935bf82`, BridgeBehaviorCtor.cpp and AISpecialPowerUpdateDtor.cpp
now include the existing ObjectModule/BehaviorModule headers instead of their
synthetic BehaviorModuleBase/BehaviorModuleOther/BehaviorModule chain.
Retail evidence: ObjectModule ctor RVA 0x00306AA7 stores ModuleData at +4 and
Object at +8; BehaviorModule ctor 0x00253330 calls it and installs its secondary
interface at +0x0C. Its primary table RVA 0x007EEA7C has 12 slots and its
secondary table 0x007EE9C0 has 47. UpdateModule ctor 0x00253390 installs the
third interface at +0x10 and initializes +0x14/+0x18/+0x1C; destructor
0x0024A797 restores those same three subobjects. These are target-image facts,
not names or layout inferred from a donor. Existing header comments preserve
the separate donor-name evidence.

Scoped builds retain all seven rows (Bridge: 3, AISpecialPower: 4), including
the verified EH funclet renumberings. `header_adopt_lane.py accept` passes
both sources for ObjectModule and BehaviorModule with the published census
index at `7300bffea9`, including explicit per-unit link-preservation verdicts.
No header, source path, pin, alias, or census figure changes. The remaining
private UpdateModuleInterface/UpdateModule views and other merge prerequisites
remain outside this bounded adoption. Carry these consumers into the next
normal census; this is not a new linked-coverage measurement.

The outgoing link-batch audit remains INCONCLUSIVE: after strict preparation
of these two sources, the older index still lacks a current receipt for affected
consumer `Code/GameEngine/Source/Common/AIGameTeam.cpp`. Broader consumer
preservation is unverified; the passing adoption verdicts cover the two donors.
