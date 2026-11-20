# DynamicPortalBehaviour native tables

Run 386 bridged six class tables. The lifetime source now includes the
registered UpgradeModule and CreateModuleInterface declarations, and its
constructor stores the new names at the same retail offsets. The native
objects keep every expected table extent.

| Retail RVA | Object offset | Extent | Native result |
|---|---:|---:|---|
| `0x008427A8` | `+0x20` | 16 bytes | All four Create slot relocations reach matched owners. |
| `0x008427B8` | `+0x1C` | 4 bytes | The existing alternatename still serves the Die callback. |
| `0x008427C0` | `+0x10` | 72 bytes | All 18 UpgradeMux slot relocations reach matched owners. |
| `0x00842808` | `+0x0C` | 188 bytes | The four usual interface getters now match. Slot 45 still differs. |
| `0x008428C4` | `+0x00` | 48 bytes | Slot 2 still names the inherited UpgradeModule getter. |
| `0x00858790` | `+0x18` | 12 bytes | DynamicPortalBehaviour's copy now has all three exact targets. Other classes share this retail address. |

The four Create folds and the 13-byte getDie fold were verified by
add_match. The obsolete one-byte Create placeholder had only one
cached COFF consumer, the table this change replaces. The five-source
build passed 60 function rows. The final commit hook confirmed six exact EH graphs. The final scoped link check passed all
five sources and counted 2,375 bytes, including 29 bytes of existing
folded bodies. The ten snapshot header consumers passed 494 rows and
two data rows.

The primary retail getter at `0x00460BCD` returns the class-name literal
in six bytes. The registered header now declares the first three
Snapshot virtuals at the actual object prefix, preserving the object
size and offsets. The owning transfer refuses without approval of
`Code/GameEngine/Include/GameLogic/Module/DynamicPortalBehaviour.h|slot|DynamicPortalBehaviour@0x00C428C4|2`.
Prepared compiler inputs are under build/root-resume-20261120/dynamic-portal.

The Die callback is a unique 19-byte row at `0x00460A85`. The observed
base construction table at `0x00C1C780` and getDie's +0x1C return
identify DieModuleInterface. Its canonical onDie signature takes
`const DamageInfo *`. The present owner takes `void *`. The owning
move cannot change that parameter, and the typed name lacks approval.
Slot 45 of the Behavior table is the already matched
`mapLoadPostProcess(const Dict *)` at `0x00461284`. The shared Behavior
declarations use `slot45(int)`. The typed method appends a virtual when
declared independently. Its shared declaration and default provider
need coordinated convergence.

Bridge clearance awaits an authoritative run containing these commits.
