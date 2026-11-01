# ScriptActions local-cache data-index prerequisite

The current `ScriptActions_rva003C31F3.cpp` already reads `TheControlBar` and
defines `ScriptActions::Rva003C31F3Do`; no source change was needed. Normal
verification passes all three rows (217-byte parent, 13-byte cleanup and
10-byte EH handler), including the compiler-owned guard cleanup.

The two registered data keys refer to the former free-function guard and
`g_bfmeWorldRV`. Retirement is refused because the current member's `autoKey`
at RVA A02DD0 is outside the register while `data_ledger.csv` still gives it
the former free-function spelling. The guard at A02DD4 already has the member
spelling. A fresh `tools/data_ledger.py --out` derivation selects the current
member's cache without any source change. It also reports 6,621 changed,
12,535 added and 178 removed addresses across the index; this investigation
does not publish that unrelated refresh or hand-edit selected index rows.

A private explicit-data-row trial was also refused: the cache is COFF STATIC
(storage class 3), whereas `data_rows.verify_row` requires an EXTERNAL owner.
No data ownership row, register key, source or gate was changed. Next step is
a supported data-index refresh covering the compiler-local cache; then rerun
the owning `repair_queue.py retire data` command. This is an index prerequisite,
not lost code coverage or evidence of a source regression.

Local evidence: `build/sole-current-data-ledger-20261101.csv`, its generation
log, `build/probe-script-local-key-data-20261101.py`, and
`build/sole-script-controlbar-build-20261101.log` (if retained). The generated
index is descriptive evidence, not independent byte ownership verification.

Publication boundary carried forward from the browser GUID and Selection
prerequisite batch: its affected-consumer audit was INCONCLUSIVE because the
published index predates the outgoing base and the affected
`Code/GameEngine/Source/Common/AIBaseBuilder.cpp` strict receipt is not current.
Scoped byte checks and previews do not clear that broader boundary; carry it
into the next census.
