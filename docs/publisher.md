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
until the blobs in the target's non-ledger scope or the checker change.

Row scope (2026-10-06). Row ledgers are scoped by row: `functions.csv` by
`target_rva`, `symbols.csv` by `name`, `data_rows.csv` by `address`, and the
other union-merged ledgers by whole line. `--scope-from-diff` and the shim emit
tokens such as `reverse/functions.csv#0x00401000`. Units on
different rows overlap only where they share another path. A unit that touches
a file others `#include` (by file name, transitively, as
`header_dependents.py` decides) overlaps every unit that touches one of those
includers. Over the last 7 days of Open-BFME-1's master (7,168 commits, 22% touching
`functions.csv`), 16% of commits overlap another within 15 minutes under row
scope, against 62% under whole-file scope. Replaying those footprints at 300/h
(3% red, blame lines) gives 238/h with p95 48 min on 6 builders under row
scope, against 121/h with p95 228 min under whole-file scope.

Builders and re-verification. Builders are registered per host and operator
(`publisher.py builder --state S NAME --operator OP [--command JSON --home DIR]`)
and sign receipts with their own key. Remote builders fetch candidates from
`stage_remote`. Every high-risk green (headers, baselines, whitelists,
gen_asm/gen_small, checker paths), a `reverify_share` sample of the other
greens, and every lone red are rebuilt by a different operator. Builders that
lose the vote, or whose receipts do not verify, are quarantined
(`quarantine.json`). Several publishers may run against one branch: a push is a
fast-forward compare-and-swap, and the loser regates.

Promotion fixtures. `promote` refuses without exploit and benign fixtures and
without `ledger_cmd`. Generate the set on the head being promoted:
`python3 tools/publisher_fixtures/make_fixtures.py tools/publisher_fixtures/bfme2/cases.json OUT --rev <sha>`,
then promote with `--fixtures OUT` and
`ledger_cmd="bash tools/publisher_fixtures/bfme2/ledger.sh"`
(`PUBLISHER_FULL_GATE=1` adds the full byte gate).

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

## Rollout: shadow, then enforce (2026-10-06)


Two stages, each switched by one committed file, `reverse/publisher_mode` (`off`,
`shadow`, `enforce`). The pre-push hook reads it at the remote tip, never
from the outgoing commits, so a push cannot change its own mode, and the
file is a protected path (Verifier-Change trailer).

**Stage A, shadow (shipped).** The last line of `.githooks/pre-push` runs
`tools/publisher_hook.py` after every other check has passed. The push
goes ahead unchanged. A detached process waits until the push has landed
(the remote-tracking ref contains the tip), then submits the same range to
`refs/submit/<operator>/<unit>` with its diff as scope. It cannot fail or
slow the push; it only logs to `.git/publisher-hook.log`. The hook step
costs about 0.3 s on Windows. A submission takes 0.7-1.1 s in the
background against a local remote. The operator is the git author name,
lowercased, with runs of other characters turned into `-`. In v1 it is
UNAUTHENTICATED: the envelope is signed with a key anyone can derive from
that name (`auth=none-v1`). An operator an admin later issues a real key
to (`publisher.py operator`) can no longer be impersonated that way.

The publisher host runs `tools/publisher_service.py`, one state directory
per repository. In shadow it fetches `refs/heads/master` and
`refs/submit/*` from origin and writes nothing there. It publishes to
branch `publisher-shadow` of a local bare mirror, and its results go to
the mirror's `refs/publisher/results`. The shadow checker follows master
(auto-promotion), so a red unit is one that passed the seat's own hook but
failed the pinned gate. When the service is idle it resets the shadow
branch to master (`resync` event), so drift from units red here or
commits pushed without a submission does not pile up. Per-unit rows
(latency, verdict, red rate over the last 100 gated units, queue depth) go
to `metrics.csv`, one row per minute to `queue.csv`, and the day's
go/no-go to `health-<date>.json`.

**This host** (`publisher_state\` next to the worktrees; both repos;
setup already run):

    publisher_state\run_publisher.cmd      start both (supervised, restarts on exit)
    publisher_state\stop_publisher.cmd     stop both after the current step
    py -3 publisher_state\bfme2\bin\publisher_service.py status --state publisher_state\bfme2
    py -3 publisher_state\bfme2\bin\publisher_service.py health --state publisher_state\bfme2 [--hours 24]

`run_publisher.sh` does the same from Git Bash. Builders: 8 for BFME2 and
4 for BFME1, each gate at `BUILD_POOL=2`, so at most 24 compiles at once
on 24 cores. A builder's HOME is its scratch dir, so `publisher_gate.py`
hard-links its `~/.cache/open-bfme-build.lock` to the host's. Full builds
(more than 8 TUs: header, toolchain and wide units) therefore serialize
with every other clone's full builds on this PC. Per-file verifies take
no lock and compete for cores only. Fleets building on this PC slow the
gates; nothing else interferes. BFME2's `reference/open-bfme-1` comes from
`state\toolchains\<gitlink sha>`, a clone the service provisions for every
head and for any unit that moves the gitlink.

**Measured on this PC** (24 cores; the 40 consecutive BFME2 master commits
ending at ce152db5a5 replayed as units through the real gate on cold
builders; all green). Without scope serialization: 8 batches of 5 gated in
parallel, 89 s wall (1,618 units/h as a burst), 51 s per gate, p95 latency
89 s. With `serialize_scopes` (the publisher default), 26 of 30 batches
held one unit: 977 s wall, 147 units/h, p95 latency 907 s. Every unit edits
`reverse/functions.csv`, BFME2 averages 93-130 units/h and peaks at 271/h,
so the default cannot carry a peak. The bfme2 shadow state on this PC runs
with `serialize_scopes=false` until ledger scope is row-level (see the
scope rules above).

**When this PC is off** nothing is lost. Shadow: seats push as before and
submissions pile up on `refs/submit/*`. On restart they are ingested in
landing order, and the gap shows as queue depth, not as latency. Enforce:
pushes are refused and queued in the same way; master stops moving until
the service is back, then drains the backlog.

**Go/no-go for stage B** (`health`, 24 h window, all must pass): at least
100 units finished; queue at most 40 at the end, mean depth in the last
quarter at most 10 above the first, and at least 95% of enqueued units
finished; p95 latency at most 30 min; red rate at most 3%, with every red
unit looked at; at most 5% did not apply; a heartbeat row for 95% of the
minutes; at most 5 errors and no refused receipt. Get GO on two
consecutive days that include a fleet peak.

**Stage B, enforce (prepared, not run).** In order:

1. Promote the checker by hand (`publisher.py promote --state DIR <master
   sha> --fixtures ...`). Auto-promotion stops in enforce.
2. Land a commit that sets `reverse/publisher_mode` to `enforce` (Verifier-Change). From
   then on the hook submits synchronously and refuses the push (exit 3)
   with `PUBLISHER-QUEUED <unit>` and how to check:
   `python3 tools/publisher_hook.py status <unit>` (queued / pending /
   landed / rejected, read from `refs/publisher/results` on origin). A seat
   that keeps working on top of queued commits gets them left out of its
   next unit, which is ordered `after` them. After a rejection: fix,
   `git pull --rebase`, push again; identical bytes are the same unit.
3. Within a minute the service sees the mode, fast-forwards origin master
   itself, deletes the submit refs it ingested and publishes results.
4. Admin, so `--no-verify` and other accounts cannot bypass the hook. This
   is classic branch protection: it covers only branches matching
   `master`, so `refs/submit/*` and `refs/claims/*` stay writable, and the
   existing "Protect master" ruleset (no force push, no deletion) stays as
   it is. `enforce_admins` is required because two other org admins push.

       gh api -X PUT repos/Open-BFME/Open-BFME-2/branches/master/protection --input - <<'JSON'
       {"required_status_checks": null, "enforce_admins": true,
        "required_pull_request_reviews": null,
        "restrictions": {"users": ["Ancalgonn"], "teams": [], "apps": []},
        "allow_force_pushes": false, "allow_deletions": false}
       JSON

   Prove it: a push to master from any other account fails, and a push to
   `refs/submit/x/y` from that account succeeds. Ancalgonn is also the
   publisher's account. If a fleet on this PC pushes as Ancalgonn, only
   its hook stops it (enforce mode). A dedicated bot account in the
   restriction list closes that gap.

**Rollback.** Land `reverse/publisher_mode` = `shadow` (or `off`). The service keeps
origin as its target until the units queued under enforce have landed,
then goes back to the mirror. Remove the protection with
`gh api -X DELETE repos/Open-BFME/Open-BFME-2/branches/master/protection`.
