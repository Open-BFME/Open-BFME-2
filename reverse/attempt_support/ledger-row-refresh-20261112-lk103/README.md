# Four stale data_ledger rows hid boot-path vtables from the bridge (seat halilkkaya-lk103, 2026-11-12)

Base `36e2968e498`. Each row below is `tools/data_ledger.py --out` output at that tree, copied by exact
address into `reverse/data_ledger.csv`. No other row changed (the full regeneration differs in 386 rows;
its bridge effect is exactly these four, measured below).

| address | committed | regenerated | why the committed row is stale |
|---|---|---|---|
| 0x0081B5D0 | size 1 | size 16 | "Give three FX module copy ctors their retail tables, not one-byte stand-ins" grew `_Rva003AE03D_v0C`'s data row 1 -> 16 |
| 0x0081B5E0 | size 1 | size 16 | same commit, `_Rva003AE03D_v0` |
| 0x0081C8F0 | kind string | kind vtable | "Store the +0x0C FX tables, not the string "HZz", in four ctors" removed the `??_C@_03DEOAGKCL@HZz?$AA@` binding; the owned `_s_vtable0C` is bound there now |
| 0x0083702C | size 4 | size 20 | the verified data row `??_7Rva005E626DListener@@6B@` is 20 bytes (5 slots); retail words 0x0083702C..0x0083703F are five .text pointers, 0x00837040 is a string |

`vtable_bridge.table_rows` only bridges `kind=vtable` rows and bounds each table by the row's size, so:

- 0x0081C8F0: `??_7Rva003AC8D7Object@@6BRva003AC8D7Slot2@@@` (ModuleTemplateCloneSlots.cpp, one placeholder slot
  `s0`) was neither bridged nor refused. The inline factory 0x003AC8D7 stores it at +0x0C (boot walk #11729, tier 5
  under BFMECRCWriter). Retail has 4 slots: the -0x0C deleting adjustor 0x003A5A48, 0x000B3FD0, 0x003AC930, the
  xfer adjustor 0x003AC936.
- 0x0081B5D0 / 0x0081B5E0: `??_7Rva003A59C3@@6B@` and `??_7Rva003A59C3@@6BRva003A59C3B0A@@@` (stored by
  `??0Rva003A59C3`, walk #11781) were refused `unbounded-retail-row` and kept their compiled copies, whose slots
  differ from retail (slot 1 `?s0@Rva003A59C3B3` where retail has 0x000B3FD0; slot 0 of the second copy is the
  `??_G`, not retail's `??_E`).
- 0x0083702C: eight names, stored by LivingWorldLogic's listener ctors (walk #28667, tier 1 under GEinit#243
  `??0LivingWorldLogic`) and the StrategicInGameUI observers (#30706..#38898), were bridged at 1 slot or kept as
  "correct" at 1 slot. `??_7Rva0083702CObserver@@6B@` keeps `__purecall` in slots 2..4 where retail has the empty
  0x0047A69C body; `??_7Rva005E5FObserver@@6B@` kept one slot. Any call through slots 1..4 left the table.

## Bridge plan (offline `vtable_bridge.plan()` over exit_link's inputs, HEAD's tool; lk74_snap/lk74_cmp)

| plan | bridged | retail tables | slots | refused | already correct | mismatching source slots |
|---|---:|---:|---:|---:|---:|---:|
| committed ledger | 3377 | 2531 | 50619 | 35 | 2185 | 37955 |
| four rows refreshed | 3382 | 2534 | 50657 | 33 | 2183 | 37989 |
| full regeneration | 3382 | 2534 | 50657 | 33 | 2183 | 37989 |

Changes (four rows vs committed): newly bridged 0x0081B5D0 `??_7Rva003A59C3@@6B@`, 0x0081B5E0
`??_7Rva003A59C3@@6BRva003A59C3B0A@@@`, 0x0081C8F0 `??_7Rva003AC8D7Object@@6BRva003AC8D7Slot2@@@`, 0x0083702C
`??_7Rva005E5FObserver@@6B@` and `??_7Rva0083702CObserver@@6B@` (both previously "correct" against a 1-slot
extent); the six other 0x0083702C names stay bridged, now at 5 slots. Refusals gone: the two
`unbounded-retail-row` entries above. Nothing else bridged, refused or lost. Four rows vs the full regeneration:
identical plan.

The boot-path walker (`boot-path-audit-20261107-lk55.py --max-tier 5`) shows exactly these stores changing
status (0x00C1B5D0/0x00C1B5E0 refused -> bridged(4), 0x00C1C8F0 none -> bridged(4), 0x00C3702C bridged(1) ->
bridged(5)); no other store changes.
