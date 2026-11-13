# Prepared naming proof: implementation remains blocked

This is a no-change tooling handoff, not a fix or game progress. No production
Code, header queue, vote, fingerprint, naming ledger, baseline or verifier was
changed. Neither fingerprint consumer has a prepared-transition exception.
In particular, this record does not authorize the old production votes.

## Checkout and reproduction

Worktree: `C:/Users/clemens/.t3/worktrees/Open-BFME-2/t3-3d261ad7-5b6ceff36cd7f08b`.
Owner: `codex-01a1071d-prepared-proof-r25`. Synchronized normally from master to
`a518c2c963fd4c5fa7d15e196f5a29cf5eac16a3`. Read AGENTS.md again after the pull,
docs/claims.md, naming/history rules, verifier rules, the r23 handoff, its patch
and runnable regression, and published root20 evidence at records commit
`3d881969a60848351abed424df3fcaa75dca243d`.

The fresh r23 reproduction on this revision is **4 failed, 13 passed** in
46.51 seconds. All four failures are the required acceptance cases: staged,
outgoing range, unknown-base whole history, and exact adding-commit
`rename.fingerprint_bound`. Fresh synthetic seats use normal next/submit;
one registered combined application stages source, original fingerprints,
votes and landed outcomes together without a records-first commit. The
fixture injects compilation; it is not native byte-verification evidence.

The thirteen passing controls retain the old refusals, including the
fully recomputed manifest/proposal/registry counterexample. Their refusals
currently rely on the original/final source mismatch. They do not establish
the safety of a future exception or test an implemented durable witness.

The [runnable contract](prepared-proof-20261113-r25/contract.py.txt),
[unapplied regression patch](prepared-proof-20261113-r25/regression.patch.txt),
and [machine-readable results](prepared-proof-20261113-r25/results.json) are
preserved in this commit. Copy the contract to
`build/r25-prepared-proof/test_prepared_vote_staging.py` to run it from this
checkout; its root calculation expects that depth. The patch's
`git apply --check` succeeds, but it is intentionally not applied to the
production test suite: its four acceptance tests still fail, without xfails.
Full local logs are under `build/r25-prepared-proof/`.

## Concrete remaining proof boundary

No implementation of an adequate independent replay was completed. No
authenticated durable prepared-transaction receipt authority was found in
the inspected naming, build-receipt, history or compiler-profile machinery.
The existing strict object/dependency receipts test local cache consistency;
their hashes do not authenticate who verified a historical prepared change.

The following specific interfaces still need implementation together:

1. Capture the combined transaction inside `rename.run_batch`, before its
   successful journal is deleted. Its `RunBatchResult.plans` exposes the
   individual name plans, not the combined preparation's original preimages.
   `name_lane.apply_respell_batches` currently appends outcomes only after
   `run_batch` returns. Publishing a self-asserted witness at that point does
   not make the arbitrary caller-supplied prepared C++ independently valid.
2. Make a durable witness bind the actual parent commit/preimage blobs,
   complete prepared input and final source sets/blobs, ordinary respell
   requests, unchanged RVA ownership and row attributes, approval IDs, and
   every consumed original key/hash/worker/session/source tuple. Hashes and
   landed rows are untrusted input to replay, never authority. No missing
   original fingerprint may be reconstructed from history.
3. Recompute distinct-worker agreement and run ordinary identity, canonical,
   protection, collision and planning checks on the bound preimage. Planning
   alone is insufficient: `_batch_source_edits` accepts arbitrary prepared
   bytes, and `plan_function(..., respell=True)` cannot establish a body
   transformation from the mangled signature. A signature-only token rule
   also cannot prove root20's scalar-return/body change.
4. Independently verify those prepared bytes. A native replay must bind and
   reproduce compiler executable/profile, command/options, retail verifier,
   ledger/pin/data inputs, includes and include-search inventory, reference
   gitlinks, and all required byte/data/relocation/post-build checks. It must
   fail if those inputs or trusted verifier code cannot be recovered. A JSON
   `verified` flag, local registry, transcript or recomputed dependency
   hashes cannot replace that execution. Test verifier injection must remain
   at a trusted fixture boundary, never selectable by a submitted witness.
5. Execute trusted code on an isolated historical snapshot, not the target's
   tools or current worktree. `rename.build_verify` selects build tooling
   under `ctx.root`; importing a trusted rename module alone does not pin
   that execution. `commit_checks` also permits missing tools for fixture
   roots. A replay must not accidentally inherit that fixture leniency.
   Replaying the ordinary full application recursively invokes class_gate;
   resolving that recursion must not introduce a caller-controlled skip or
   success mode. No such mode was added here.
6. Share the independently established relation among staged additions,
   every outgoing adding commit (all history for unknown base), and exact
   historical `fingerprint_bound`. Preserve its append-once test, trusted
   history preflight and later source-staleness protections. The result must
   reject altered original rows, invalid carry, wrong identity/approval,
   forged outcomes, changed sources, tampered/missing proof, and unavailable
   trusted verification/history even when untrusted hashes are recomputed.

These are implementation requirements, not a claim that replay is impossible.
The task did not complete them. The prepared source mismatch remains refused
at both consumers; `carry_verified_votes` retains its pure identifier contract.

## Validation and environment

`tools/check_csv.py` passes: 101125 function rows, 9276 symbols, 2363 data rows.
`find_declared_unmatched.py` on all seven claimed tooling/test scopes reports
all defined functions already matched. No Code area was edited or built.

The default Python lacks capstone. A private
`build/r25-prepared-proof/venv` uses the repository's nightly constraints plus
pytest; no shared Python configuration or parent environment scripts were
changed. Normal `worktree_setup.py prepare` succeeds after the read-only
check identified missing per-worktree configuration and donor-pin retention.
No safe.directory exception was introduced.

The related suites finished **901 passed, 34 failed, 2 skipped** in 800.23s:
test_name_lane_respell_batch, test_vote_sources_push, test_class_gate,
test_name_lane, test_rename_respell, test_git_trust and test_gate_exploits.
Thirty-two failures launched Windows system32 WSL Bash (access denied): the
initial PATH prefix mistakenly named a nonexistent Program Files Git install.
The two remaining failures are the prior unrelated CRLF-sensitive tests:
`test_unrowed_resolution_accepts_only_added_definition_and_preserves_ordinary_rename`
and `test_six_resolved_definitions_admit_sequentially_and_verify_peer_sizes`.
Neither was modified or hidden. Gate-exploit cases: **93 passed, 1 skipped**;
the skip is `test_audit_red_team_escapes[NOTSET]`, an empty parameter set.

After correcting only the child environment's PATH to
`C:/Users/clemens/scoop/apps/git/current/cmd` and this private venv's Scripts
directory, the complete test_vote_sources_push/test_git_trust rerun finished
**113 passed, 1 skipped, 0 failed** in 112.22s. Both runs set
GIT_CEILING_DIRECTORIES to this worktree to keep no-repository fixtures outside
its repository. No setting was persisted. The remaining history-suite skip
is its platform-specific path spelling test, covered by its real-commit test.

Per-suite outcomes, failure names, skips and artifact hashes are recorded in
`results.json`. The records-only commit uses normal hooks and tools/push.py,
the existing common-git account clock and landing lease. No hook bypass,
nightly, link-cycle, boot, game-smoke, shadow publisher, production naming
adoption, parent ROOT/build/r20 edit, or subagent was used.
