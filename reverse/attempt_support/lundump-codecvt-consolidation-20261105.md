# Lua/STLport consolidation boundary

Inspected revision: b7847a306e, 2026-11-05.

The default picker claimed `Code/Libraries/Source/Lua/lundump.c` and
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_codecvt_virtuals.cpp`.
The current in-memory plan lists 19 Lua functions plus the six-byte
`codecvt<char,char,mbstate_t>::do_encoding` body at RVA 0x00756B00,
bracketed by `_TestSize` and `_LoadHeader`. That contiguity approval does
not establish that the STLport source can compile inside this C TU.

`name_lane.py consolidate --under Code/Libraries/Source/Lua/` surveyed
29 sources and found no investigation groups. The committed TU map is stale;
`tu_skeleton.py` rebuilt its inputs in memory. No map was written.

`tu_skeleton.py --merge Code/Libraries/Source/Lua/lundump.c --dry-run`
rejected the STLport donor with `no baseline match`, accepted no donors,
and returned 2 (`no verified merge of two or more donors`). Its verifier
preserves the destination suffix, so the C++ donor is tested as C.
The donor defines namespace-scoped codecvt template members and includes
`<locale>`; its language requirements differ from the vendored Lua C source.

Independent `./build.sh` of the STLport donor passed all 10 rows, including
the ICF twins. Both sources passed `find_declared_unmatched.py`.
This is a composition boundary, not evidence of a byte-match regression.
No source, ledger, debt register or provider binding changed.

Next step: filter incompatible-language consolidation candidates, or establish
an evidence-backed row-level ownership plan before considering a split.
Do not convert the vendored Lua TU to C++ to absorb a folded STLport body.
