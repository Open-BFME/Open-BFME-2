# Naming bindings after complete TU absorption

The Connection path-consumer audit found the inferred `msg` parameter at
0x0058BD4F still recorded with the donor source in `reverse/name_basis.csv`.
`rename.landing` reads that source for parameter/local reverts; only actual
file-renaming history redirects it. A TU absorption does not create that
file-rename record, so leaving this column stale breaks the consumer.

Extend `tu_skeleton.repoint_all` for complete donor absorption to repoint
only the naming record's source column, alongside its existing path-keyed
registers. Keep names, basis, evidence strings and append-only voting/outcome
logs unchanged. This does not extend partial-row split routing, whose
per-function ownership requires separate logic.

The regression fixture performs a merge repoint, then resolves the inferred
landing through the real `rename.landing` implementation. It checks the new
source and original placeholder, unchanged quoted historical evidence and
voting bytes, an unrelated source, LF preservation and idempotence.

Validation: pytest over test_tu_skeleton, test_tu_skeleton_carry,
test_tu_skeleton_split, test_rename_carry and test_gate_exploits reports
368 passed, 1 skipped and 78 subtests passed. No check refusal is weakened.
