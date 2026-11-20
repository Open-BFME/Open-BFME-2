# DebugIO interface and ODS tables, 2026-11-20

The queue assigned the `DebugIOInterface` table at `0x007C0990` and the
`DebugIOOds` table at `0x007C09AC` to `DebugIOOds_Create.cpp`. The five
emitting units now share the seven-slot base. The factory and destructor
provider also share the ODS declaration. Distinct header names avoid
ambiguity with the donor includes. The staged dependency check reaches
exactly these five translation units.

- `Debug::GetInput` tests the `bool HasInput()` result through slot 2 before
  calling `Read`. Both retail tables target the three-byte false return
  at `0x0073B660` for that slot.
- ODS slot 6 is the 20-byte fold at `0x000386C0`. It calls the deleting
  destructor with flag zero, then calls `DebugFreeMemory` at `0x0003E3C0`.
  ODS slots 4 and 5 use the one-byte return at `0x0069E440` and the
  three-byte `ret 0x14` at `0x00743080`.
- All 52 function rows, 10 exception-handling graphs, 41 string literals,
  one empty string, and 33 imports verify. The five current provider receipts
  preserve 5,274 scoped bytes. The preview counts 5,302 after the five folds.
  Its reference census is `c390153944` from 2026-11-20 21:32 UTC.
- The local bridge comparator agrees with all seven slots in each of the five
  interface copies and both ODS copies, and in Flat's table at `0x007C0ACC`.
  Net matches after its slot 4 flush fold at `0x0069E440`.
- The verified run 390 image predates this change. It linked with zero
  unresolved or duplicate symbols, 431 initializer bridges and 3,009 vtable
  bridges across 44,451 slots. Run 405 produced one unresolved symbol and one
  duplicate and wrote no image. Separate source fixes for those two errors
  landed before this batch. Confirmation of the four DebugIO table names
  awaits an authoritative image containing this batch.

`DebugIOConBase` and `Rva0003F330` remain separate emitted names at the
interface table's retail address. Resolve the console provider and its
cleanup identity together under [LINK-137](../../docs/linking_obstacles/link-137-console-cleanup-identity-repair-changes-interface-comdat.md).
The rowed 48-byte `Rva00419C7F` destructor still relocates to
`DebugIOConBase` at +0x22. Both standalone console fragments emit a framed
34-byte base deleting destructor. The shared interface owner emits the
frameless 31-byte body and the nine-byte base constructor. Retiring the
console name needs the outside reference and the competing destructor
copies resolved together. The constructor fold also needs a supported
ownership transfer and reconciliation of the redundant slot-2 name.
The ODS factory's existing `Read` fold at `0x0003FD80` is mapped to the
Flat TU. A whole-file ODS merge still needs that placement reconciled.
