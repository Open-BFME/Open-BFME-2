# What measures the project, and where it runs

AGENTS.md states the rules. This is what runs without anyone asking, how to read it, and how the
original game runs under automation.

## Recurring jobs

| Job | Where | Trigger | Publishes |
|---|---|---|---|
| Retail byte verification | GitHub, `byte-verification.yml` | every push to `master` | pass or fail for the commit |
| Verification alarm | GitHub, `verification-alarm.yml` | each verification finishing; hourly tick from srv1 | Discord: red, green again, red over 12 hours, stale results |
| Real link | GitHub, `real-link.yml` | srv1, when the last run is 6 hours old | artifact `real-link-<sha>`; one Discord line; srv1 commits `reverse/exit_link_blockers.tsv` |
| Link census | srv1, `bfme2-runner.timer` | when the last row is 110 minutes old | `reverse/link_census_history.csv`, `reverse/link_status.csv` |
| Link census | `wings02`, `link-census.yml` (levy) | systemd on that machine; the workflow only reports health | failing at "preparation failed" since 2026-10-29 |
| Nightly measurement | GitHub, `nightly-measure.yml` | skipped until `NIGHTLY_ENABLED` is set | image ownership receipts |

The alarm and the real link post to Discord only while the repository variable `DISCORD_POSTS` is
`true`; it is unset, so they print to their run logs instead. The webhook is the progress channel's.

GitHub's scheduler is not dependable here: a `*/5` job fires every five to seven hours, and
`real-link.yml` and `verification-alarm.yml` have never fired on theirs. Their `schedule:` lines
stay, but `bfme2-dispatch.timer` on srv1 is what starts them. Do not put anything that matters on
a GitHub schedule alone.

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
(`tools/image_report.py`): initializers registered, vtable lengths, data contents, FieldParse tables
and duplicate globals. These all pass a link and fail at run time. Its `rows` lists name each case.

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
- `PrintWindow` returns black under Wine, so a `no-picture` or `blank-window` outcome there says
  nothing about the game. Judge by the CRCs.
- Retail on 2026-11-03: main menu reached; a seeded skirmish gives 30 distinct CRCs over frames
  25-750; the same seed twice gives identical CRCs; `--perturb-frame 300` is caught, with the 12
  earlier CRCs matching and all 18 later ones differing; `save` works.
- **`load` does not pass yet.** With AI it crashes at 0x66386D in `Team::iterate_TeamMemberList`
  from `SkirmishAIManager`; without AI at 0x538ADD in `DX8IndexBufferClass`'s destructor. Not yet
  tried on Windows, so the cause is unknown. Until this clears, a desync result is usable but a
  save/load result is not.
- The harness cannot judge our own build until the real link produces an image, and it needs a
  `pieces_map` to read one laid out differently from retail.
