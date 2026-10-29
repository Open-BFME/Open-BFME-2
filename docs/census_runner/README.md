# BFME 2 census runner

Setup: `SETUP.md`. Copy this file next to `runner.sh` on the host.

## What one cycle does

`runner.sh` runs under one flock (`runner.lock`):

1. `git pull --rebase origin master` in `repo/`. It refuses to run on a dirty
   tree, and keeps `reference/open-bfme-1` at its pin.
2. If the local link index derives from an older census than the last row of
   `reverse/link_census_history.csv`, and the published index is that census,
   it re-fetches the index (`tools/link_check.py --fetch-index`).
3. **Census.** This runs when the last history row (anyone's census) is at least
   `CENSUS_MIN_AGE` (110) minutes old and HEAD isn't that row's commit:
   - it runs `python3 tools/link_census.py --build --history`;
   - it commits `reverse/link_census_history.csv` and `reverse/link_status.csv`
     as `link_census: census <UTC> at <sha>` through `.githooks`;
   - it pushes to master, with pull --rebase plus a retry, at least
     `PUSH_SPACING` seconds after this account's last push (read from the
     GitHub events API);
   - then it runs `tools/link_check.py --publish-index`.

   If another census lands meanwhile and the push can't rebase, this census
   commit is dropped and the next cycle decides again.
4. **Follower.** Otherwise, and only when master moved since the last update, it
   runs `python3 tools/link_check.py --update-index`, then `--publish-index`.

`bfme2-runner.timer` starts the service 20 minutes after the previous cycle ends
(10 minutes after boot). A census cycle takes about 1 hour or more, depending on
the host.

## Layout

| Path | What it holds |
|---|---|
| `repo/` | the clone (`core.hooksPath=.githooks`, submodule at depth 1) |
| `venv/` | Python with `capstone`, `pefile`, `numpy`, `unicorn`, `pytest` at `.github/nightly-constraints.txt` versions |
| `wine/` | the `WINEPREFIX` for MSVC 7.1 |
| `logs/` | `cycle-<UTC>.log`, one per cycle, deleted after 14 days |
| `status.txt` | the last update, census, push and publish (UTC, rc, seconds, head), the census figures, and the last error |

`runner.sh` reads the runner directory from its own location (override with
`BFME2_RUNNER_DIR`) and the GitHub login from `gh` (override with `GH_ACCOUNT`).

## Control

```bash
systemctl --user stop bfme2-runner.timer bfme2-runner.service   # stop now
systemctl --user disable --now bfme2-runner.timer               # stop for good
systemctl --user enable --now bfme2-runner.timer                # resume
systemctl --user start bfme2-runner.service                     # one cycle now
systemctl --user list-timers bfme2-runner.timer                 # next run
journalctl --user -u bfme2-runner.service -n 50                 # unit log
cat ~/bfme2-runner/status.txt
```

Set tunables in a drop-in with `systemctl --user edit bfme2-runner.service`,
using `Environment=`:
- `BUILD_POOL` (8)
- `CENSUS_MIN_AGE` (110 min)
- `PUSH_SPACING` (300 s)
- `MemoryHigh=` / `MemoryMax=`

Never run here: `tools/nightly_measure.py`, `tools/boot_smoke.py`,
`tools/link_cycle.py`, the nightly workflow or the shadow publisher.
