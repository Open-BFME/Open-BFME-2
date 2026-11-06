# Assisted snapshot-name getter split audit

Scope is ONLY moving
`?GetSnapshotName@AssistedTargetingUpdate@@MBEPBDXZ`, RVA 0x486E76/6,
from `Code/GameEngine/Source/Common/ModuleNameGetters.cpp` to
`Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp`.
The old source remains; this is not a vanished-source audit.

**Result: no active broken consumer or stale target-specific key found.**

The split was observed applied. functions.csv and tu_map.csv both name the
destination for 0x486E76, with approved TU placement. There are 48 matched
residual rows and 14 destination rows. Only the destination defines this getter;
the residual class declaration is not a second provider.

Case-insensitive searches for the exact decorated getter and `486E76` covered
active tools/, .githooks/, .github/, all Code/ source/header/config content,
reverse/ ledgers/registers/queues, docs/, and remaining root build/config/source
registries. Generic references to ModuleNameGetters.cpp and its encoded object
stem were checked in active tools/hooks/workflows and doxygen configuration.
Build scratch/worktrees, .git/, vendor/reference inputs were excluded from the
broad scan. Large ledgers were searched or streamed through narrow name/RVA
filters, never loaded wholesale.

No target-symbol/RVA-to-old-source hardcoding was found. No affected
identity/header/MS-header/data/gate/hatch/unclaimed key names 0x486E76 or this
getter under the old source. No data_rows/data_converged/name-basis ownership
cell requires transfer for this target. Generic old-source consumers remain
valid because ModuleNameGetters.cpp still exists with 48 matched rows.

One existing fold-proof intentionally remains:
`?GetSnapshotName@SupplyTruckAIUpdate@@MBEPBDXZ` at 0x4A6A3A names
`fold-proof=Code/GameEngine/Source/Common/ModuleNameGetters.cpp`. The actual
`?name@SupplyTruckAIUpdate@@QBEPBDXZ` provider remains at that address in the
residual source, so this proof is unaffected. No fold-proof depends on the
moved Assisted getter remaining there.

Intentional historical mentions include the old address-name tier and rename
tombstone, re_attempts.log's native-view prerequisite receipt, immutable
table-slot proofs, and the earlier split attempt handoff. The TU-map evidence
string's historical `Common/AssistedTargetingUpdate.cpp` spelling is evidence,
not a current source column or compiler path. Preserve these records. No raw EA
filename string needs rewriting for this symbol-only move.

Only this untracked scratch audit was written. No tracked/index changes,
builds, claims, network or publication were performed. Parent retains final
byte/EH/provider-consumer checks and publication responsibility.
