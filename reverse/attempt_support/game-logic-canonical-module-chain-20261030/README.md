# GameLogic canonical module hierarchy

Use the canonical Module, ObjectModule and BehaviorModule headers, removing
the four private base/interface copies. The old view put a displaced primary
slot in Module and another unknown slot in UpdateModule. Canonical
BehaviorModule already supplies the two native primary slots10/11; remove
the old UpdateModule placeholder so its phase query remains primary slot12.
The native post-load caller at 0x00242DE0 calls interface slot9 (+0x24), and
0x00242E25 calls primary slot12 (+0x30). Fields at +0x14/+0x18/+0x1C remain
unchanged. This does not reconstruct the complete UpdateModule class.

Target facts are in the existing 108-byte ObjectModule constructor at
0x00306AA7, 42-byte BehaviorModule constructor at 0x00253330 and native
BehaviorModule table at VA0x00BEEA7C. No donor method order is substituted.
All 88 source rows and 13 parent EH graphs pass private and normal checks.
All 289 external code bodies/relocations and all non-debug sections,
loadable definitions and undefined names are identical. Direct includes
also satisfy the adoption tool's explicit-header requirement.

The same TU already uses the canonical GameLogic header and its now-declared
progress methods, so the historical GameLogic discovery failure is stale.
The owning acceptance tool retires Module, ObjectModule and GameLogic keys
(three total). The ordinary
preview preserves LINKS/6,378 current authored bytes against ccafe54d1d;
the index's smaller old 5,574-byte extent predates unrelated merged rows,
so this hierarchy adoption claims no recovered or census linking gain.
The Team header key remains for a separately verified field adoption.
