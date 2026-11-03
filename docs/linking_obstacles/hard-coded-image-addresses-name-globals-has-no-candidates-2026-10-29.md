### Hard-coded image addresses: name_globals has no candidates (2026-10-29)

Census (d92e7e6635) counts 1,043 addresses, but they sit in three files, not in
casts: `ConstIntGettersAddr.cpp` (1,042, almost all hex words in EH/unwind
tables and comments plus 14 `return 0x00...` getters), `ConstIntGetters2Addr.cpp`
(1) and `Code/gen_small/uw_gen_014.cpp` (8, `gen_uw land`-owned, not hand-editable).
`link_debt.py --report` finds 0 cast literals and `name_globals.py --dry-run`
(also with `--reindex` and with both Addr files named) keeps 0 edits.
Of the 14 getters, 0x00DBD7DC/0x00DBD860/0x00DBD918 are rowed as
`_s_glowEffectActive`/`_s_ringEffectActive`/`_s_fireEffectActive`, but each is a
`static` in `Drawable_Rva00309fb3/00309ffd/0030a040.cpp`: no object defines an
external symbol, so naming them would bind to nothing. Prerequisite: give those
three statics external linkage (verified, with the data ledger owner moved
through its tool), then `return (int)&Name;` in the getters. 0x00E032DC is only
the address-named `g_Va00E032DC` hatch; the other 10 values have no ledger row.
No source change made.
