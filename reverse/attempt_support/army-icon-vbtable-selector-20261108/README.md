# Army icon virtual-base table is exact offset data

The picker served Rva005E39F3Ctor.cpp for a no-retail-slots refusal on
??_8Rva005E3BD5@@7BArmyHeroIcon@StrategicInGameUI@@@ at 0x00877C94.
The current object and retail both contain exactly `00000000 24000000`:
two signed virtual-base offsets, 0 and 36, with no code-pointer relocations.
It is an MSVC virtual-base table, not a positive virtual-function table.
All six code rows and both parent EH graphs pass normal verification.

data_ledger deliberately groups both ??_7 and ??_8 under kind=vtable.
vtable_bridge.is_table_row accepts every row of that kind, so its positive
slot planner attempts to bridge this valid offset table and refuses it for
having no code slots. There are 34 vbtable-only ledger rows meeting this
selector condition. No ledger row or generated queue is edited here.
This is a false reject, recorded before any verifier change.

The two real ??_7 tables in the same source remain separate eight-slot
bridge work (LINK-077/LINK-086). Their native targets and class/thunk
ownership still need a real-link confirmation. The ordinary current-object
preview now reports LINKS, 289 -> 289 authored bytes against index
f4727bbd09, unlike the older unresolved snapshots in those entries. This
does not prove their native table slots are unbridged or that the game runs.

A tooling repair should exclude positively identified ??_8-only rows from
the positive-slot planner, while preserving actual ??_7 names, strong
global arrays with ??_7 aliases, and legacy anonymous vtable rows. It needs
regression tests including mixed-name rows and the gate-exploit suite.

The tooling claim is held by yasinschroeder-claudeb2; no tool or test was
edited. The acquired test-file claim and source/table claims were released.
A bounded independent read-only review agrees with the selector boundary and
recommends an end-to-end offset-table test beside a bad/strong ??_7 table,
checking that the actual function-table refusal survives. No tooling fix or
queue clearance is claimed by this handoff.
