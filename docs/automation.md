# What measures the project, and where it runs

AGENTS.md states the rules. This is what runs without anyone asking, how to read it, and how the
original game runs under automation.

## Recurring jobs

| Job | Where | Trigger | Publishes |
|---|---|---|---|
| Retail byte verification | GitHub, `byte-verification.yml` | every push to `master` | pass or fail for the commit |
| Verification alarm | GitHub, `verification-alarm.yml` | each verification finishing; hourly tick from srv1 | Discord: red, green again, red over 12 hours, stale results |
| Real link | GitHub, `real-link.yml` | srv1, when the last run is 1 hour old (6 once the game boots) | artifact `real-link-<sha>`; one Discord line; srv1 commits `reverse/exit_link_blockers.tsv` |
| Link census | srv1, `bfme2-runner.timer` | when the last row is 110 minutes old | `reverse/link_census_history.csv`, `reverse/link_status.csv` |
| Link census | `wings02`, `link-census.yml` (levy) | systemd on that machine; the workflow only reports health | failing at "preparation failed" since 2026-10-29 |
| Nightly measurement | GitHub, `nightly-measure.yml` | skipped until `NIGHTLY_ENABLED` is set | image ownership receipts |

The alarm and the real link post to Discord only while the repository variable `DISCORD_POSTS` is
`true`; it is unset, so they print to their run logs instead. The webhook is the progress channel's.

GitHub's scheduler is not dependable here: a `*/5` job fires every five to seven hours, and the first
scheduled `real-link.yml` ran 8 hours after its first slot. Their `schedule:` lines stay, but
`bfme2-dispatch.timer` on srv1 is what starts them on time. Do not put anything that matters on a
GitHub schedule alone.

## Reading the real link

`tools/exit_link.py --link` links every kept object with no `/FORCE`, stubs or fillers at a
non-retail base. Only this measures a buildable game; the census's "linked" is per file under
`/FORCE`. The artifact holds `scoreboard.json` (the summary), `errors.tsv` (each linker error with
the source that referenced it), `result.json` and `link.log`.

`authoritative: false` means `exit_link.py` refused and the workflow measured anyway, skipping only
the omission proof named in `refusal`. The numbers are real, but the result cannot count as the
exit test until the refusal clears.

`initializers_bridged` counts retail's static initializers no object registers. Without them a linked
game never builds those globals, so `exit_link.py` registers them from a table it generates in
retail's order (`retail_initializers.obj`). That lets an image start, but it is not the source: the
count must reach 0 for the exit test.

`image_report.json` compares the kept objects with retail on what the linker cannot see
(`tools/image_report.py`): initializers registered, vtable lengths, data contents, FieldParse tables,
duplicate globals and globals constructed in storage smaller than the ledger's gap. These all pass a link and fail at run time. Its `rows` lists name each case.

## When the census stops publishing

Look at the last cycle in `journalctl --user -u bfme2-runner.service` on srv1:

- `compile failed:` (rc 245): a TU does not compile there. Absolute includes did this.
- `N compiled objects have no census proof` (rc 1): the object compiled, but
  `census_receipts.snapshot` could not preprocess it, and it has no include inventory to fall back
  on. Run the snapshot on one named file and read its exception; `cl -E` fails on things `cl -c`
  only warns about. A cycle takes two hours to reach this point, so check it directly.

## The original game under automation

The maintainer's sandbox is `~/bfme2-retail/` on srv1, private because it holds the game files.
Wine 9, Xvfb and llvmpipe, with no GPU. `smoke.sh TAG tool.py args...` runs a harness tool through
Windows Python in a win64 prefix. Seats do not run these unless a maintainer gives them a sandbox.

- `Options.ini` must be in `My Battle for Middle-earth II Files`, and the EA registry keys must be
  set through `KEY_WOW64_32KEY`; otherwise the game crashes in its CPU benchmark.
- `PrintWindow` returns black under Wine, so there both harnesses copy the window's client area
  from the screen, which is the Xvfb root (`capture: xvfb-root`). A window not wholly on that
  screen, or with any Win32 window above it overlapping its client area before or after the copy,
  is not captured, and a missing or black picture is `no-picture`. Native X windows cannot be
  seen from Windows Python, so the capture also needs `BFME_PRIVATE_DISPLAY` equal to `DISPLAY`:
  the game queue sets it for the Xvfb it starts for one game, with its own auth cookie. Give Xvfb a
  screen larger than the window (2048x1536 for 1024x768): on 1400x1050 the menu bar lay off screen.
  Retail on 2026-11-05: the intro movies run until about 2-3 minutes, `boot_smoke.py --retail
  --timeout 300` reports `reached-menu` (menu bar 0.74), and `game_smoke.py skirmish --retail`
  passes with a picture (225 logic frames).
- Retail on 2026-11-03: main menu reached; a seeded skirmish gives 30 distinct CRCs over frames
  25-750; the same seed twice gives identical CRCs; `--perturb-frame 300` is caught, with the 12
  earlier CRCs matching and all 18 later ones differing; `save` works.
- `reload --player` passes, and load is repeatable. Retail saves at frame 125, plays to 175, and calls
  its own in-game load (0x002DF2F6), which returns 0 after reading all 35 chunks and resumes at 125. Two
  independent runs agreed on all 6 CRCs before the load and all 22 after it, frames 125-650. Compare a
  load between runs, never with the save: the first CRC after a load differs from the CRC at the save,
  and the random state differs too, because a load does not restore it. Whether anything else differs
  across a load is not shown; the block CRCs each include the seed, so they all differ.
- `load` (`-file`) restores a `--player` save to its frame, but in two runs the logic then stayed at
  the next frame, 129, to the end. Use `reload`. A `blank-window` outcome hid this, so check the frames.
- Do not load a save made with the local slot as observer, the default `save` setup: retail throws in
  `CHUNK_TeamFactory`, returns 3 and quits, then crashes at 0x538ADD in a static destructor on the way
  out. That crash and the one at 0x66386D with AI came from that setup, not from Wine.
- Our own build runs with `--real-image build/exit_link/exit.exe` on either harness
  (`tools/real_image.py`, contract in `build/drift_review/swarm/contract.md`). The image, its map
  and `image_receipt.json` must agree by hash; `real_image.py check EXE --addresses` shows the
  check and where every harness address lands. An address is placed only through a byte-checked
  body, never by retail's RVA, so a body that differs refuses the run (`image-refused`). The image
  must import `SHGetSpecialFolderPathW`, `GetVersion` and `GetVersionExA` by name: the appdata and
  version lies patch those import slots.
- Only srv1's game queue runs the game (owner's approval, 2026-11-04): the `bfme2-game-queue`
  user unit, `~/bfme2-ops/swarm/game-queue/bin/game-queue.py`. It boots each new real-link image
  artifact, runs queued jobs one at a time from a `git archive` of the job's harness SHA, and
  writes one receipt per run to `~/bfme2-ops/swarm/receipts/`. A harness SHA not on `master` is
  marked `harness-unlanded`. During a run the prefix has no `Z:` drive, only the game, Python, the
  checkout, the job's files and the sandbox appdata, on a private Xvfb. That isolation is weak (the
  same user and network) until the owner adds a restricted user.
