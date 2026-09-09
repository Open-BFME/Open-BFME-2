# Contributing

Several agents push to `origin/master` continuously. Keep each change small,
verified and easy to rebase. `docs/matching.md` covers byte matching,
`docs/structural.md` manual RE. Prose trimmed from these docs lives in git
history, one `git show` away.

## Work selection

An explicit request or assigned lane overrides the queue:

1. `git pull --rebase origin master`
2. `python3 tools/check_csv.py` — repair ledger errors before other work
3. `python3 tools/list_naked_candidates.py Code` serves a byte-true dump from
   `Code/gen_asm/`, boundary already proven. **Converting dumps to real C++ is
   the default work.**
4. `python3 tools/next_work.py` for identity/structural work; it explains its
   own tiers.
5. `python3 tools/place_bodies.py <sources>` mines the units the ledger already
   compiles. A TU emits far more than the one function it was written to land,
   and the rest was invisible only because the export table had no address for
   it; the tool finds those addresses by masked byte search and reads each
   placed body's call sites for its callees. Re-run it after every wave — each
   pin unblocks the next body — and prune what `./build.sh` refuses to a
   fixpoint, recording the refusal in `reverse/place_denylist.txt`.

A tier reporting zero candidates is exhausted, not broken. Regenerate with
`tools/drift_classify.py`, `tools/anchor_unclaimed.py`, `./build.sh`.

Finish or revert each body before the next.

## BFME 1 reference freshness

When initializing `reference/open-bfme-1`, and before BFME 2 work if the last
successful check is missing or over 24 hours old, fetch official
`Open-BFME/Open-BFME-1` `master` and update the clean submodule to that HEAD.
Compare commits, not commit dates: upstream need not have a commit today.
Preserve dirty or unpublished submodule work and report any blocked update.
Record the successful check time locally in ignored `build/bfme1-last-check.txt`;
do not repeat the check per transfer. After a pointer change, run BFME 2's full
build verification and include the verified pointer in the next commit batch.

## Work the file, not the row

`next_work.py` lists every other queued candidate in the same source file.
**That file is your unit of work** — drain it first. Measured land rate: 19.5%
solo, 46.5% with ten or more siblings landed together, because the layout,
offsets and callee pins from the first body are what the next one needs. A
shared header edit costs a full gate: edit every dependent body, pay once.

## Convert, verify, commit, push — per body

1. Make the smallest source and ledger change for one function.
2. `./build.sh <file-or-symbol>`. If a command returns a process or session ID,
   poll it; never launch a duplicate build.
3. Stage explicit paths only: `git add <specific-paths>`, never `git add .`.
   Check every new ledger source is tracked.
4. Commit normally. **Never bypass hooks.**
5. `git pull --rebase origin master`, `git push`, then pull --rebase again. On
   rejection: rebase, recheck the ledger, retry, final pull (Subject to the batching and retry limits in #6).

6. This step governs when to run #5 and limits its retries. Normally, publish after 1 verified commit. Keep substantive changes in separate atomic, verified commits; batching changes push frequency only.

On a non-fast-forward push rejection caused by `origin/master` advancing, rebase, recheck the ledger, complete any required verification, and retry once.

If that retry is also rejected because `origin/master` advanced again, accumulate 2 verified commits since the last publication attempt before trying again. If contention continues, accumulate 3–5 verified commits between publication attempts. 

Once there are 5 verified unpublished commits, do not increase the batch size further solely as a result of `origin/master` advancing. Keep the existing batch, rebase, recheck, verify as required, and attempt publication again until published.

Attempt publication sooner if 10 minutes have elapsed since the last publication attempt, the assigned work is exhausted, or the session is ending. Finish any in-progress verification first.

Before each publication attempt, rebase onto current `origin/master`, recheck the ledger, and complete any required verification. 

After 3 consecutive publication attempts succeed without rejection, reduce the batch size one level: 3–5 → 2 → 1.

Header, vendored-reference and shared-shim edits — and a resolved merge — trigger the full gate in the hook; poll it, don't relaunch, and never filter a gate through a pipeline that hides its exit code.

Before pushing, `python3 tools/progress.py origin/master` prints what your
session added. `+0.00 pp` is the common outcome — do not stop there; take
another body from the file you were served, and if it is exhausted say so with
the figure and reason.

## Anti-lift policy

Clean C++ is preferred; MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). Lifting a dump into a
`__declspec(naked)`/`__emit` .cpp is **not** a conversion: it byte-matches by
construction, scores +0, and deletes the body the next converter needed. The
naked body must be **gone**, replaced by real C++. `tools/conversion_gate.py`
enforces this in both hooks, and the push hook scans your whole outgoing range
— a blocked push may name a historical lift, not yours. Never `--no-verify`.

Ghidra boundaries, xrefs and vtables are identity evidence; decompiled C is
not byte-match proof. After several failed shapes or ~30 minutes without byte
progress take a fresh candidate, never leaving a nonmatching reconstruction in
`Code/`. Record the verdict:
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>`
(never hand-edit `reverse/re_attempts.log`); cite the real boundary and
include `t=<minutes>` and your model.

**Close, not exact? Bank the body.**
`partial '<what is wrong>' --stash <your .cpp> --score <0..1>` keeps the
candidate servable and starts the next agent from your body, not cold. Both
flags are required: over 95 rows, a `partial` describing the near miss without
banking it landed 5.1% against 7.5% for silence. No body, no `partial` —
record `blocked`.

## Placement and integrity

- Game source under `Code/`; MASM dumps in `Code/masm_dumps/`; scratch
  untracked under `build/`. Banked attempts (`reverse/attempts/<rva>.cpp`) are
  evidence, never progress: nothing compiles them, `add_match` deletes one on
  landing, `check_csv` flags leftovers.
- Prefer TU-scoped shims over shared-header edits.
- Progress = `matched` `reverse/functions.csv` rows backed by real source and
  byte verification. Markers and prose are not.
- **Landing a `reverse/symbols.csv` pin?** It is an ADDITIVE candidate list:
  the resolver keeps the first pinned address that reproduces retail, so a pin
  naming the *wrong* function still byte-matches and a green gate proves
  nothing about it. Run `tools/pin_consistency.py --symbol <name>` before you
  pin and `--check` after. `reverse/pin_consistency_baseline.csv` is the
  known-bad backlog and may only shrink — never add a line to get green. A
  harvested pin is a candidate, not an address: resolve the thunk and check it
  against the ledger's own body before spending a name on it.
- No fallback paths; they conceal mismatches.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv`
  wholesale; use `rg` or narrow filters.
- Preserve unrelated dirty-tree work; revert only your own attempt.

## Generated claims

`gen-*` rows (`Code/gen_small/`, `Code/gen_asm/`) are byte-true placeholders,
not progress. Recovering a real identity means writing clean C++ at its proper
`Code/` path and repointing the row:
`tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>` for
`gen_asm` dumps (`--replace-existing` when the name is unchanged). `check_csv`
rejects a gen-* row sharing a range with a real-name row; the placeholder
yields.

**Never edit a file under `Code/gen_asm/`**: repoint the row and leave the
orphaned `PROC`, which keeps converters conflict-free there.
`Code/gen_small/uw_gen_*.cpp` is owned end to end by `tools/gen_uw.py land` —
never hand-edit it, and never infer a funclet's `parent=` from adjacency; a
guessed parent is invented identity.

After landing a batch, sweep your own rows: one body per address. A duplicate
range among them is an over-claim, not an ICF alias.

## Vendored third-party claims

`vendored=<lib>-<ver>` rows carry the upstream's real identities, never `gen-`
prefixes; the header comment names the exact release. Library sources live at
their official BFME paths, and pristine C TUs compile against
`reference/shims/gamespy/`, never a real Platform SDK.
