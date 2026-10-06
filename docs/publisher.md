# Publisher (tools/publisher.py, 2026-10-05)

The publisher is the only writer of master. Seats submit units; isolated
builders gate them with a pinned checker; the publisher fast-forwards master
only to a tip whose signed receipt names exactly the current head. Design,
limits and commands are in the module docstring. The files are
Open-BFME-1's (`publisher.py`, `publisher_load.py`, `publisher_pre_push.sh`)
copied unchanged in code; nothing imports Open-BFME-1 at run time.

Capacity at 300 units/h. The gate model is 60 s + 20 s per unit per batch
(Fable's 8 minutes per 20-unit batch); `publisher_load.py simulate`, 6 h:

| red units | blame lines | builders | units/h | p95 wait |
|---|---|---|---|---|
| 1% | no | 4 | 290 | 16 min |
| 3% | no | 8 | 291 | 15 min |
| 3% | yes (90%) | 6 | 283 | 14 min |
| 10% | either | 8 | 130-146 | over 3 h, queue grows |

One builder tops out near 180 units/h even with no red units. Red units cost
the most, so the checker should print `PUBLISHER-BLAME: <path>` for each path
it fails. The publisher then probes the blamed unit alone instead of
bisecting. Operators above 20% red lose half their rate and the spare
capacity (slow lane).

Scope rules (2026-10-06). Every unit declares the globs it may touch
(`submit --scope GLOB ... [--forbid GLOB]`, or `--scope-from-diff`); there
are no exempt paths, so ledgers, headers, build files, tools/ and .githooks/
must be declared like sources. Two units with overlapping scopes are never in
flight together (serialized, not rejected). A unit whose rebased diff leaves
its scope is rejected with the paths (`out-of-scope`). After `retry_limit`
(3) gate failures with the same approach (its +/- lines outside ledger files)
for the same target, an equivalent submission is refused (`retry-limit`)
until the blobs in the target's scope or the checker change. Cost: whole-file
ledger scope serializes every unit that edits the same ledger. With 8 builders
at 3% red the simulator gives 281/h when no unit shares a ledger, 270/h at
10%, 231/h at 30% (queue grows) and 159/h at 60%. Units that each append
ledger rows therefore need row-level ledger scope
(`serialize_scopes` turns the rule off) before the publisher carries the
fleet.

## Cutover runbook (admins)

1. **Publisher host.** It holds the bot's push credential: a GitHub App or
   deploy key that is the only bypass actor on master. Builders run as
   another OS user (`builder_prefix`, e.g. `["sudo","-u","builder"]`) with no
   credential. Build hosts need the toolchain and a warm `build/`
   (`clean_keep`).
2. **Init.**
   `python3 tools/publisher.py init --state /srv/pub --target <origin URL>
   --set 'checker_paths=["tools",".githooks","build.sh","build.ps1"]'
   --set 'toolchain_paths=["reference/open-bfme-1","reference/shims"]' --set builders=8
   --set 'submit_remote="<origin URL>"'`, and `--set gate=...` to
   `printf "refs/heads/master %s refs/heads/master %s
" "$LANDING_TIP"
   "$LANDING_BASE" | bash .githooks/pre-push origin origin`.
   The gate runs the bundle's `.githooks/pre-push`, overlaid on the candidate
   and hidden from `git diff` (skip-worktree).
3. **Operators.** Run `publisher.py operator --state /srv/pub <name>
   --rate <units/h> --burst <n> [--infra]` once per operator fleet. Send the
   printed key file to that fleet's host only. The key identifies the
   operator; commit authors are ignored.
4. **Checker.** Keep the exploit fixtures (`fixtures.json`: patch plus
   `reject`/`pass`) on the publisher host. Set `ledger_cmd` to the full-ledger
   check. Then run `publisher.py promote --state /srv/pub <master sha>
   --fixtures <dir> [--accept-diff <file>]`. A later verifier commit counts
   only after its own promotion; landing on master does not make it trusted.
5. **Shadow.** Before the flip, drain into a scratch branch (`--set
   'branch="publisher-shadow"'`) for a day. Compare its receipts and
   rejections with direct pushes.
6. **Ruleset (the flip).** In repository rules, add a branch ruleset on
   `master` that restricts updates, blocks force pushes and deletions, and
   bypasses only the publisher bot. `refs/submit/*` stays writable, as
   `refs/claims/*` is today. Prove it: a `--no-verify` push and a GitHub API
   fast-forward of master must both fail. Until then a direct push still
   lands, and the publisher only logs `foreign_push`
   (`test_no_verify_direct_push_is_only_stopped_by_the_admin_ruleset`).
7. **Fleets.** Replace `git push` with `python3 tools/publisher.py submit
   --operator <name> --key-file <key> --remote origin --scope <glob> ... <base>..HEAD` and read
   `PUBLISHER-SUBMITTED`/the unit id. Hosts that still push can install
   `tools/publisher_pre_push.sh`, which turns a push to master into a
   submission. Any script that fast-forwards master through the API must move to `submit`.
8. **Run.** `publisher.py drain --state /srv/pub` under a supervisor;
   `status` prints queue depth per operator, p50/p95 wait and builders busy.
   Exit criterion: queue depth flat for 24 h at peak load.
9. **Rollback.** Delete the ruleset; seats push as before. The journal and
   receipts stay; on restart the publisher settles a half-done publication.
