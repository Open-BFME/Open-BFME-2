# Claims

AGENTS.md ("Hard rules: claims") states the rules. This is the mechanism, moved
from AGENTS.md in 2026-10.

## Taking a claim

`python3 tools/claims.py claim 0xRVA` claims a retail body (claim every RVA in a
batch). The pickers' `--claim` (`tools/next_work.py --claim`,
`tools/list_naked_candidates.py Code --claim`, `tools/repair_queue.py ms-headers
--claim`, `next_work.py --tier dx --claim`) claims while selecting and retries if
another worker won the race. Body edits take their RVA and an atomic per-file
lock together; class-wide work takes `class:NAME`, file-wide work `file:PATH`
(`claims.py claim class:NAME`).

Queues skip work whose footprint meets another seat's live claim in either claim
namespace: `refs/claims/`, or `refs/heads/claims/` on hosts set by
`bfme.claimNamespace`. Use one namespace per fleet. An orchestrator sets a
stable, distinct `BFME_CLAIM_OWNER` for each seat.

Claims are refs on origin. They expire after four hours and do not change
`master` publication. `python3 tools/claims.py list` shows owners.

One claim does pace publication: the landing window `lease:landing`
(`tools/push_lease.py`, 30-minute TTL). The pre-push hook takes it before a
full-gate or carried push to master and releases it if the hook fails; every
other push to master waits at the end of its hook while another seat holds it,
until the holder's commit is on origin/master or the TTL passes. Check it with
`python3 tools/push_lease.py status`. A crashed holder blocks no one past the
TTL, and unreachable claims never block a push.

## Settling and releasing

A verified `add_match` or `add_match_batch` keeps the claim and queues the row.
The claim is released once origin/master holds the row, the blobs of every file
the verified compile read and any `reverse/symbols.csv` pins you added. A debt
item's claim is released once origin/master no longer holds its debt lines.
Release any other scope claim by hand after the push.

The pickers' `--claim` and `claims.py claim` settle such landings (`claim` keeps
the RVAs it was asked for held); `python3 tools/claims.py release --landed` does
it on demand after a push. A landing that cannot be shown (an untracked or
ignored header) keeps its claim until it expires.

Release a banked, blocked or abandoned body with `claims.py release 0xRVA`.

During steady work, releases ride on the next acquisition. The pickers'
settlement queues every release (landed bodies, finished scopes and the file locks they leave unneeded)
and the seat's next claim push carries it in the same atomic transaction; what
no claim push takes is pushed once when the picker exits. `claims.py release`
deletes a body and its file locks in one atomic push. A task costs one claim
push plus its direct master push in steady work (previously up to four total).
The final settlement without a next claim costs one extra push; opportunistic
GC and contention retries are additional maintenance traffic.

## Collecting expired claims

`python3 tools/claims.py gc` deletes claim and lock refs whose record expired
more than an hour ago (`--grace-minutes`, never below 60), in atomic batches
(`--batch`, default 150, also bounded by Windows' command line) paced by
`--max-per-minute` (default 600), capped by
`--max`; `--dry-run` lists them. Each ref is deleted only at the sha gc read
(`--force-with-lease`), so a claim renewed or taken over meanwhile survives,
and only the configured write namespace is touched. Settlement also runs a
random slice of 50 at most once per 10 minutes per host (`BFME_CLAIM_GC=off`
disables it), so no machine owns collection.

## Pacing

Contended claim pushes and fetches retry with full-jitter exponential backoff
(base 0.5 s, capped at 30 s). Each host spaces its claim pushes through a
shared bucket under the machine-wide temp dir: 60 per minute per remote with a
burst of 8 (`BFME_CLAIM_PUSHES_PER_MINUTE`, 0 unpaced; `BFME_CLAIM_HOST_DIR`
moves the state files).

## Renewing

Renew before expiry with `claims.py renew 0xRVA` when work lasts longer than four
hours. Renewing keeps the lease, so a queued landing still releases; re-running
`claim` on your own live claim also preserves its lease. If `renew` reports a
claim not renewed (taken over, not yours or not claimed), stop editing that work:
reclaim it or switch to other work.

`renew` and `release` also act on claims this checkout took before 2026-10-09
under the old `<user>@<host>` owner.

## When origin is unreachable

`claims.py claim` claims nothing and exits 2. The pickers then warn and serve the
work unclaimed, skipping any work origin showed another worker holding.
