# HordeTransportContainDamage decision, qc-12
Base1731a4153f; queue5409; no source edit or adoption.
The single slot0 conflict is resolved by distinguishing primary and secondary
receivers, not by majority. Native constructor4BB130 installs primaryC59E70,
behaviorC597F8@C and damageC59E64@10. Primary slot4 is the name-key body4BB0EB;
primary slot0 is deleting destructor4BB15A. Secondary damage slot0 is4BB176,
whose existing exact callback uses owner[ECX-8] at complete-object offset8.
Thus neither competing getModuleNameKey/rva004BB176 is primary slot0.

Native factory250E9C pushes14hex for allocation before calling4BB130. The
constructor source's comment claiming a34hex allocation is stale; actual size
is20decimal, independently corroborating the current contract. Do not copy
that comment into an ABI. The complete three secondary entries are recorded;
the primary five-entry prefix is not presented as the complete behavior ABI.

Real blocker: class:DamageModule, not a queued attribute. Native DamageModule
ctor4B9704 constructs the BehaviorModule hierarchy and a secondary interface.
No canonical DamageModule header is registered. The served constructor uses
explicit raw vtable stores and an empty nonpolymorphic base view; the callback
uses only its secondary receiver. Neither is a safe complete canonical class.
Full native inherited getter/profile closure is prerequisite, as required by
the coordinator's root-adoption warning. No root adoption or new base default.
Both served sources unchanged; frozen checks required. No tool/hatch changes,
new original names, bytes or linking credit. Shared obstacle register remains
held elsewhere; this README is the proposed entry. Native proof attached;
no external donor establishes target size or table identities.
