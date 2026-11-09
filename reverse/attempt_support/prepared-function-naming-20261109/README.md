# Prepared function naming through normal submission

Ordinary function respells already accept a new qualified owner and parameter
types through prepared C++. Normal naming submission applied only the new
identifier, which could strand that subsequent operation behind the stricter
same-identifier signature guard. The source repair motivating this change
remains separate and waits for genuine naming approval.

`submit --respell-batch MANIFEST` binds served ordinary-function keys to full
target spellings and proposed sources. Identifier votes remain blind and
independent. All group members must have current approvals and pass ordinary
selection/claim constraints before one existing rename.run_batch transaction
applies the prepared operation. Every approved identifier must match its
target's identifier. Registered keys never fall through to identifier-only
application, and a partial planner/verification failure restores the group.

Intent lives in the Git common directory, outside disposable build inputs.
Its manifest, proposed bytes and source snapshots are hash-bound. Missing,
changed or retargeted inputs withhold application. Normal build cleanup cannot
erase intent and authorize an intermediate rename. Bindings are immutable for
their old keys; no manual registry reset is introduced. Other approvals selected
on a structurally prepared source await a fresh source-fingerprint check.

Seventeen new focused cases pass, including normal two-voter submission,
fresh reviewer processes and two one-key blind automatic-review jobs completing
one atomic pair. They cover pending approvals, stale/missing inputs, corrupt
bindings, retargeting, changed approved identifiers, rollback, per-file mode,
build cleanup, ordinary application and unrelated approval fingerprints.

Parent verification of the focused cases, test_rename_respell.py and required
test_gate_exploits.py passes 147 tests with one existing catalogued-escape skip.
The independent tooling worker's broader name_lane/name_review/header/registered/
donor suite reports 559 passed and two failures. Loading unmodified HEAD versions
of both name_lane and name_review reproduces those same failures:

- test_unrowed_resolution_accepts_only_added_definition_and_preserves_ordinary_rename
- test_six_resolved_definitions_admit_sequentially_and_verify_peer_sizes

Both refuse at data_rows.py with `unrowed admission allows added definitions
only; resolved lines changed or removed`. This is a pre-existing fixture/admission
limit, not a reason to weaken that check. No related admission code is changed.
Test children omit the publication-only GIT_CONFIG_* hook override so temporary
repositories use their own configuration; publication retains normal hooks.

No game source, function/data ledger, approval, vote, pin, alias, baseline or
verification admission changes in this support commit. The existing ordinary
rename engine performs the eventual source transaction and all of its checks.
