# What measures the project, and where it runs

AGENTS.md states the rules. This is what runs without anyone asking, how to read it, and how the
original game runs under automation.

## Recurring jobs

| Job | Where | Trigger | Publishes |
|---|---|---|---|
| Retail byte verification | GitHub, `byte-verification.yml` | every push to `master` | pass or fail for the commit |
| Verification alarm | GitHub, `verification-alarm.yml` | each verification finishing; hourly tick from srv1 | Discord: red, green again, red over 12 hours, stale results |
| Real link | GitHub, `real-link.yml` | srv1, when the last run is 1 hour old (6 once the game boots) | artifact `real-link-<sha>`; one Discord line; srv1 commits `reverse/exit_link_blockers.tsv` |
| Link census | a boat.dev sandbox, started by srv1's `bfme2-runner.timer` | when the last row is 110 minutes old | `reverse/link_census_history.csv`, `reverse/link_status.csv` |
| Link census | `wings02`, `link-census.yml` (levy) | systemd on that machine; the workflow only reports health | failing at "preparation failed" since 2026-10-29 |
| Nightly measurement | GitHub, `nightly-measure.yml` | skipped until `NIGHTLY_ENABLED` is set | image ownership receipts |
| Data ledger refresh | srv1, by hand only (swarm ops job; `bfme2-ledger-refresh.timer` is disabled) | when a measured blocker or a stale-name count calls for it | a ledger commit, or a report on srv1 |

The alarm and the real link post to Discord only while the repository variable `DISCORD_POSTS` is
`true`; it is unset, so they print to their run logs instead. The webhook is the progress channel's.

The data ledger refresh does what db309c3297 and d88c3448da did by hand. It ran hourly with the owner's
approval until 2026-11-09, when the swarm coordinator stopped it: a pass takes 8-18 minutes and input
commits land faster than that, even at the quietest hour. It is now run by hand only when a measured
blocker or a stale-name count calls for it. It
regenerates `reverse/data_ledger.csv` with `tools/data_ledger.py` over a full current object set and
compares `vtable_bridge.plan()` under master's ledger and the new one, item by item (covered tables,
names and RVAs, refusals, unindexed bindings). It publishes only with no loss and a gain, under its
own claim (`ancalgonn-swarm-ledger`), and discards a run when master moves the ledger's inputs
(`Code/`, `tools/`, `reference/`, `vendor/`, the four reverse ledgers) before it lands. Anything else
leaves a report on srv1 and no commit. The procedure and its rules: `~/bfme2-ops/swarm/contract.md`
("Ledger refresh") on srv1.

Whoever next regenerates the ledger, by this job or by hand with `tools/data_ledger.py`, also clears eight
rows at addresses outside the image (0xD8058B24, 0xC141F04D and others; packet P64). e3d59db32a fixed the
tool, and the committed file keeps them until then. They cost nothing live, so a diff removing them is
expected. `___ImageBase` and `__except_list` stay: they are pseudo-symbols.

Regenerate from objects built from your tree, not a downloaded index: `tools/check_csv.py` refuses a new ledger row for a name `reverse/deleted_rows.csv` retired, and its message says what to do.

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

`vtables_bridged` and `vtable_slots_bridged` count generated select-any vtable
copies and their positive virtual slots. `exit_link.py` emits them first, only for
already-defined select-any table names with no supplied strong definition and with every
retail slot resolved through a matched ledger row to an external kept code target.
A name with a strong definition keeps it and is refused alone; the other names bound
at the same retail address are judged on their own copies.
The first external provider in response order must be that row's owner; a later
owner cannot justify using an earlier conflicting copy.
A first kept copy whose slot pointers already match needs no bridge. Missing tables,
ambiguous names, omitted targets and other refused cases are listed in
the artifact's `vtable_bridge_queue.tsv`; `vtable_bridge.json` records the full
decision, including the displaced source-slot names and all their ledger RVAs.
`exit_link.py --blockers ERRORS --blockers-commit SHA` publishes the measured real
result's bridge work to `reverse/vtable_bridge_queue.tsv`, refusals first and then
bridged tables as retirement work. It keeps the existing real-link blockers
unchanged. Diagnostic results cannot publish this queue.

The link tier serves this family immediately after real-link blockers, grouped
by source with a `file:` claim and no byte credit. Tables without a known existing
source stay visible in an ownership-investigation item claiming
`file:reverse/data_ledger.csv`; no Code owner is guessed. The pass test is the next
published real link no longer bridging or refusing those tables while retaining
their ledger coverage. The dispatcher stages both committed queue files.

These copies are a runtime bridge, not recovered class definitions. G1 requires both
vtable counters and `initializers_bridged` to be zero in addition to its other
requirements. Missing counters in an older result are unknown, not zero. The image
receipt carries the vtable counts, so the linked-image report preserves them under
`inputs.receipt` while continuing to judge the actual winning object and bytes.

`image_report.json` compares the kept objects with retail on what the linker cannot see
(`tools/image_report.py`): initializers registered, vtable lengths, data contents, FieldParse tables,
duplicate globals and globals constructed in storage smaller than the ledger's gap. These all pass a link and fail at run time. Its `rows` lists name each case.

## When the census stops publishing

Look at the last cycle in `journalctl --user -u bfme2-runner.service` on srv1. Since 2026-11-06 the census's compile and links run on a boat.dev sandbox that srv1 starts for each census and deletes after it; srv1 still commits, pushes and publishes. `boat unavailable; census skipped` means no census ran (no sandbox, or too few plan hours left), and the next cycle tries again; the census never falls back to srv1. Then:

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
  Retail on 2026-11-08, one run per timeout: the title splash at 5 s, a black window at 10 s,
  intro movies from 15 s to 180 s, the menu at 300 s. So `title-splash` past about 10 s is short of
  retail, and `loading-screen` means only another picture short of the menu: it does not prove
  loading. `hang-on-<picture>` is that picture with the main thread spinning in the game's own
  code over the run's last 30 seconds, within 64 bytes (`main_thread_span` in smoke.json). This is a
  heuristic, not proof that progress stopped: a long copy or decompression inside the image can
  satisfy it. In the other direction, a wider spin, a spin in a system DLL or a deadlock in a wait
  keep the more favourable picture label, so `title-splash` or `loading-screen` does not prove the
  run was still moving. It takes no sample as evidence when the thread could not be cleanly suspended
  and resumed, and a thread it cannot resume makes the run a `debugger-error`. More than 2 failed reads
  over the span, or more than 3 seconds between two good samples, withhold the label: `failures` and
  `largest_gap` in `main_thread_span`. A crash already delivered at the deadline counts, and one
  arriving just past it can too, deliberately: a run ends at the first look that finds nothing
  pending, and a stream of events can hold it open at most 2 s longer. A thread parked outside
  the image gets no hang label because retail waits in a system call for 29 s at a stretch while
  a movie plays. Receipts before this change say `loading-screen` for all of these.
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
- srv1 can also build a diagnostic image itself and queue its boot, from a `swarm/*` branch or a commit on
  `master`: `~/bfme2-ops/swarm/local-link/local_link.py request REF --label L` (an ops script, not in this
  repository; `vet` and `history` are its other reports). It has two workers, each with its own checkout and wine
  prefix. Requests start in order but finish in whatever order their links do, and a worker that dies can repeat a
  request, so match a result to its request by the receipt's `ref` and `image_commit`, never by which is
  newest. Its `local-*` images are deleted only once they have a receipt and are outside both the newest 50 and the
  last 72 hours, and can be rebuilt from their commit and branch; receipts are kept.
- A diagnostic link does not fail on an unresolved name: `diagnostic_stubs.obj` defines it as a trap in `.text`. So a run-time
  hook or counter with a wrong symbol links cleanly, then measures nothing, or stops in a way that looks like the game's.
  Inside `extern "C"`, `__identifier("__imp__free")` decorates to `___imp__free`, a stub, not the slot. Before reading such a
  run, look each hooked name up in its `exit.map`: `diagnostic_stubs.obj` means that hook is void, and a receipt's
  `stubbed_name` means the stop is at a stub. Give a counter a planted positive control, or a zero means nothing.
