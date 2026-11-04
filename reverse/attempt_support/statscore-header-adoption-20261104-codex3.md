# Statistics-core header adoption, 2026-11-04

Base: `6b19bc334fc6875e3b69ed86a2714149432866c4`.
Header: `Code/GameEngine/Include/GameNetwork/Rva00553E47StatsCore.h`.

## Accepted consumers

`GameNetwork/GameSpy/PeerDefs.cpp` replaces its private definition with the
header. Its two constant-index short-map accesses now name the corresponding
canonical fields, `m_maps04_0` and `m_maps04_1`. The consumer's existing
size checks remain unchanged.

`GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp` replaces its opaque
private definition with the header and opts into STLport so the header's map
types compile. Its derived extents and external method declarations are retained.

Verification:

- `./build.sh` over both consumers: 144/144 rows exact, five data rows exact,
  52 funclet pins verified, 19 literals and seven empty-string references
  verified, two named imports verified.
- `find_declared_unmatched.py` over the three queued sources: no refusal.
- `header_adopt_lane.py accept --class Rva00553E47StatsCore` over the two
  consumers: both PASS; the tool retired precisely their two queue rows.
- Ordinary `link_check.py` over both consumers: both LINKS, preserving
  7,255 and 666 bytes respectively against the 2026-11-04 02:25 census at
  `5a13f2cd61`. This is prediction and preservation, not a new census gain.
- `git diff --check`: passed.

## Owner prerequisite, trial reverted

The third queued source, `GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp`,
currently emits the implicit nonvirtual destructor at RVA `0x00383D71` (271 B).
The canonical header declares that destructor out of line. A direct header swap
therefore stops emitting the existing row. Adding an explicit empty definition
restores emission but introduces a vptr store at body offset `0x12`:

```text
retail:   ... 89 75 f0 8d 8e 30 01 00 00 ...
compiled: ... 89 75 f0 c7 06 <vftable relocation> 8d 8e 30 01 00 00 ...
```

That trial fails only the destructor (305/306 function rows exact). No attempted
owner/header/ledger change remains. Restoring the original owner passes 306/306
function rows, three complete STLport constructor folds, three data rows,
52 literals, 13 empty-string references, 23 compiler float literals and 14 imports.
The owner's header-queue row remains.

Next: reconcile the canonical header's declared destructor with the owner's
implicit lifetime emission, while preserving all existing consumer bindings and
the native destructor/EH graph. Do not repeat an explicit empty destructor or
remove the shared declaration without checking all consumers.
