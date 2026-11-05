# Header debt transfer into an already queued destination

At 76ed9a41d2 the W3DShrubBuffer dry run accepts Rva000E9BACDtor.cpp,
31 rows total, but the previously recorded commit-msg false reject remains
in repair_queue._debt_transferred. It subtracts (class, source) pairs and
cannot recognize a new RVA-bearing row under an existing destination pair.
See w3dshrubbuffer-destructor-merge-20261105-codexb.md for the original refusal.

The verifier now also recognizes newly carried queued RVAs at an existing
pair, only when all donor ledger rows move to that destination and none stays
at the source. Empty RVA sets, unchanged destination RVAs, partial ledger
moves, moves to another unit, and worktree-only queue changes give no proof.
New destination pairs retain the existing transfer rules. No register is edited
or debt retired in this tooling commit. The actual merge is separate.

Validation: the three positive regression cases fail with the old verifier;
the corrected verifier passes all 18 index/tree transfer cases. The combined
repair-queue and exploit suites pass 312 tests, skip one, and encounter one
existing fixture failure: test_a_header_row_leaves_the_queue_only_when_acceptance_passes
lacks reverse/symbols.csv for symbol-dependency discovery. The same single test
fails against the unchanged HEAD verifier (recorded locally in
build/codexb4-debt-baseline-test.log). All exploit cases pass. The 18 transfer
cases were rerun after adding explicit outgoing-tree coverage.
