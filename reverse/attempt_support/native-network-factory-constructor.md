# Native network factory: allocation and constructor evidence

Target: `?createNewPingerInterface@PingerInterface@@SAPAV1@XZ`, RVA
`0x005590FC`, 53 bytes. Its unwind and handler rows are `0x007994EA` and
`0x007994F4`. Existing constructor provider:
`Code/GameEngine/Source/GameNetwork/BFMENetwork.cpp`,
`??0BFMENetwork@@QAE@XZ`, RVA `0x00558EC1`, 173 bytes.

Retail instructions push `0xA8` at `0x00559107`, call the allocator at
`0x0002FDA0`, and call the constructor at `0x00558EC1` from `0x00559120`.
The factory returns the allocation without a base adjustment. This supports
the bounded allocation view and call binding, not an identification of the
donor's Pinger members or interface semantics. BFMENetwork is not listed as
a canonical shared class at the repair base `8d0a3acc4c`.

Verification:

- `./build.sh Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_PingerInterface_createNewPingerInterface.cpp`: 3/3 rows, source claims and reference checks pass.
- `tools/eh_verify.py` on that source: 1 EXACT, no missing graph.
- Before/after COFF: same 53 factory bytes; only relocation at offset 37
  changes from `??0Pinger@@QAE@XZ` to `??0BFMENetwork@@QAE@XZ`.
- Defined-symbol comparison: zero added/removed definitions, only the
  factory's relocation-bearing definition changes.
- `tools/link_check.py` on the factory and existing provider: 2/2 LINKS,
  exit 0. The published index is older (`0534e78db3`); retain this limitation.

Local evidence is in `build/decal-diagnostic/pinger-factory-before.cpp`,
`pinger-factory-before.obj`, and `pinger-factory-build.log`.
No new body, alias, pin, escape hatch or provider was introduced. The old
Pinger pin is not retired by this change. A fresh real link and runtime
checks remain necessary; this repair alone does not establish a working game.
