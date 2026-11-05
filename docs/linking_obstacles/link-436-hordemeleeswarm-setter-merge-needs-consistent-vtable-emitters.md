### LINK-436: HordeMeleeSwarm setter merge needs consistent vtable emitters

Status: Blocked. Updated: 2026-11-05; inspected revision: 7b65b04886.
The constructor TU and `FamilyDeletingDtors_Rva005843DA.cpp` emit incompatible `HordeMeleeSwarm` vtable views when the two setter declarations are added. The merger refuses `breaks another unit's copy of ??_7HordeMeleeSwarm@@6B@` despite the ordinary three-unit LINKS preview. Restore the declaration trial; reconcile the complete native table and both emitters before retrying. No clearance or census gain.
Evidence: [trial, correction and remaining prerequisites](../../reverse/attempt_support/horde-swarm-setter-consolidation-20261105.md).
