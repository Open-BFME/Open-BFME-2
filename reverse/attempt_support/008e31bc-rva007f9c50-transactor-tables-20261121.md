# 0x008E31BC — Rva007F9C50 transactor tables (blocked)

Served: link-cycle vtable bridge `??_7Rva007F9C50Base0@@6B@` (0x008E31BC) from
`Code/GameEngine/Source/GameNetwork/Rva007F9C50Dtor.cpp`. The pass test needs all four
tables the destructor touches (0x8E31BC, 0x8E32D0, 0x8E32D4, 0x8E32E4) to stop bridging.

## Target facts (retail bytes)

The destructor `??1Rva007F9C50` at 0x6661A0 (171 bytes, matched) installs 0x8E32E4 at +0,
0x8E32D4 at +4 and 0x8E32D0 at +8. At +0xA3 it restores 0x8E31BC.

| Table | Slots |
|---|---|
| 0x8E32E4 primary | [0] `??_GGen007FA290` 0x6667E0; [1] `Rva007FA2C0::rva007FA3D0` 0x666920; [2] `Rva007FA2C0::rva007FA4D0` 0x666A20; [3] `Rva007FA2C0::send` 0x666B30; [4] `BfmeMgrVPE::rva007F9A40GetOrCreateSlot` 0x665FB0; [5] `Rva007FA2C0::scan` 0x666860 |
| 0x8E32D4 (+4) | `FeslConnectionHandler::onConnectionMade` 0x6656E0, `::onConnectionBroken` 0x665710, `Rva007F91A0Host::apply` 0x665740, `FeslConnectionHandler::rva007F9D00` 0x666250 |
| 0x8E32D0 (+8) | `Rva007FA340::process` 0x666890 |
| 0x8E31BC (Base0 own) | `??_GRva00665C10` 0x665C10, then 5 `__purecall` |

## Inferences

- `Gen007FA290`, `Rva007FA2C0` and `BfmeMgrVPE` are +0 views of one class, `Rva007F9C50`.
  The destructor of `Gen007FA290` is already an alternatename of `??1Rva007F9C50`.
- `FeslConnectionHandler`, `Rva007F91A0Host` and `FeslConnectionHandler` (`rva007F9D00`)
  are its +4 base. Their bodies take `this` at +4.
- Base0 is really `Rva00665C10` (InlineDtorDeletingDtors2.cpp:255): virtual dtor plus five
  pure slots.

## Refusals (rename.py, 2026-11-21)

1. `class --fold Gen007FA290 --into Rva007F9C50`: refused because `Gen007FA290` scopes
   frozen keys in `reverse/hatch_baseline.tsv`. Those keys are the `??3`/`??1Gen007FA290`
   alternatenames (lines ~1936, ~2537) and the present-unmatched `??0Gen007FA290` (~9817).
   The keys can only retire after the fold, so this is a deadlock.
2. `function --to-class Rva007F9C50` for the +4 slots: refused because
   `FeslConnectionHandler` is a readable name, so the move is a naming decision.
3. `function --to-class Rva007F9C50` for primary slots 1–5: refused because
   `?rva007FA4D0@Rva007FA2C0@@QAEXPAVRva007FA5E0Arg@@PAX1I@Z` names a parameter type by
   back-reference. Even if accepted, this move retires no bridge, because slot 0 still needs
   the fold.

## Needed

- A tooling path for the fold when the frozen keys belong to OLD (retire them in the same
  change), or a maintainer decision on the frozen keys.
- A naming decision on whether `FeslConnectionHandler` is the +4 base of `Rva007F9C50`.
- Support in `function --to-class` for back-referenced parameter types.

Prepared unit rewrites (all five primary-slot units plus the Dtor unit) were made in
scratch and are not committed. They are reproducible from the table above.
