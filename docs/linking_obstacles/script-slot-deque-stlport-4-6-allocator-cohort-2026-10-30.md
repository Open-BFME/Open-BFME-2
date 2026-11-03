### Script-slot deque STLport 4.6 allocator cohort (2026-10-30)

At base `c16862543a`, BfmeOwnerZKRelink.cpp and its three slot-view users
move together to STLport 4.6. The native pointer-slot allocator at 00068E15
is admitted under its emitted non-const signature; the obsolete const row
is retired. Its complete 28-byte body and GameMemory relocation equal the
existing integer ICF owner. Both deque callers retain their native target.
All 48 rows and five EH graphs remain exact; strict preparation passes.
The final joint preview retains 4/4 LINKS and 3,085 bytes against index
`85f6b7f40c`. The four-unit control comparison preserves every
retained external COMDAT after allocator-signature normalization; six old
unrowed helper copies disappear per unit. The saved index lists only these
four units as owners/direct consumers of those helpers. This repairs the
cohort's migration prerequisite, with no new unique bytes or census gain.
The outgoing audit is INCONCLUSIVE: the index predates the base and eleven
affected source objects lack current receipts, first
ScriptEngine/Rva003B573ERva003B7F46.cpp. Carry the removed providers and
affected consumer scope into the next scheduled census; full closure remains
unverified.
[Native proof, object deltas and verification boundary](../../reverse/attempt_support/script-slot-stlport46-20261030-codexb4/README.md).

The commit hook verifies 673/673 functions and 112 exact EH rows across its
19 affected units. It exposes an existing shadow binding conflict in
`deallocateEntry` at 003B66D8: the unchanged 131-byte body and all relocations
call the AsciiString destructor at retail 00036410, matching its existing pin,
while the function row names 0048BA39. Reconcile the native StringBase and
AsciiString destructor owners/fold identity before retiring this conflict.
Neither identity nor any baseline is changed by this migration.
