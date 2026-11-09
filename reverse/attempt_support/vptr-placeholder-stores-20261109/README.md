# vptr stores bound to a non-table address, image 22121599ec

Read-only, 2026-11-09, from diagnostic image `local-...-diagnostic-link-22121599ec...`, its map and retail's `game.dat`:
for each kept row copy, each `mov [mem], imm32` where retail's immediate is a `vtable` row of `reverse/data_ledger.csv`
and the image's immediate lies inside no `??_7` symbol. Stores are paired by order within a row; rows whose store
counts differ are skipped. vptr stores where the image stores a non-table address: 186 in 84 rows. The byte gate masks these relocations. A row here makes its object's
next virtual call through that pointer read a data word as a table. Lead list: each needs its real table named, which
LINK-514 and LINK-625 track by class. TemporarilyDefectUpdate (0x004CC6AF) is fixed by P115.
