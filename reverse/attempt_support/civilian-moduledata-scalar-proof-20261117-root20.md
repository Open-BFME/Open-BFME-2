# Civilian module-data adoption: unused scalar-field proof required

Inspected 2026-11-17 at9dcb0c7478c. Picker served the31-slot
`CivilianSpawnUpdateModuleData` table848530 in `CivilianSpawnUpdate.cpp`.
The unchanged normal baseline passes15/15functionrows and1data row.

Retail constructor47FA55 installs the derived table; delay is at+8, filter+C,
limit+10, vector+14. Canonical ModuleData is8bytes. Moving the existing delay
word from the private12-byte base into the derived class preserves all offsets
and the complete original runtime object graph. This preparation was restored.

The owning `header_adopt_lane.prepare_unit` then refuses:

```
field renames: ModuleData::m_unsourced04 (+0x4) is void*;
the canonical ModuleData::m_moduleTagNameKey is enum
```

The old pointer-typed word is unused in this source. It is not safe to rename or
retype that private declaration merely to silence this check. A separate verifier
repair must prove unused scalar storage and complete field/declaration ownership.
The header-lane tool file is currently held by the separate generator repair seat;
a concrete counterexample and hostile-regression design were handed to that seat.

For evidence only, a source-restoring native compile of the canonical class swap
and derived delay field emits31slots/124bytes. All42original external text
section definitions remain exactly equal in bytes, relocations and COMDAT policy.
It emits neither `??0ModuleData` nor a ModuleData default table; thus the constructor
COMDAT emitted by the2026-11-05 experiment is absent in this candidate. This is not
a current whole-link clearance. The normal constructor cleanup target49B47C and all
existing providers still require ordinary full row/EH verification after admission.
No check was changed, no candidate admitted, and no source, header, pin, ledger or
queue change is retained. The normal original object is still receipt-current.

Future proof must keep the member offsets/size20hex, native78-byte constructor,
28-byte deleting destructor, all existing rows/data/EH and exact31retail bindings.
The independent63-byte destructor/constructor-peer merge issues in LINK489 remain
separate. Include ordering must preserve Snapshot's NAMEslot. Refresh scoped link
providers/strict receipts before acceptance; await a scheduled real run for bridge
absence. No real link, smoke or runtime measurement was started here.

[Native layouts, emitted slots, preserved text definitions and artifact hashes](civilian-moduledata-scalar-proof-20261117-root20.json).
