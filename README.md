# BFME 2 Source Code

Goal: Source code that rebuilds BFME 2's engine binary (`game.dat`) byte-for-byte, and game modernization improvements that you've only seen in your dreams.

[Join our Discord to participate!](https://discord.gg/wCvA2XqPUT)

## What?

* We rewrote the game's code one small piece at a time, and each piece turns back into the exact same bytes as the original game.dat (BFME 2, version 1.06). That stage, byte matching, is complete.
* The work now (Phase 2) is making those pieces link into one program: closing the symbols the whole-program link still has to stub, merging the one-function files back into the source files the original was built from, giving every class one header, retiring recorded debt, and replacing generated and placeholder code with real C++ and real names.
* The goal is a game that links with no stubs and no `/FORCE`, boots to the menu, plays a skirmish and saves and loads. Then the whole game is open source, and we can fix bugs and make mods.

[![BFME 2: road to a finished decomp](docs/progress.svg)](tools/progress.py)

[![rules-v2](docs/progress_v2.svg)](tools/progress_v2.py)

### How each figure is measured

Every figure is computed from the repository at a commit or read from a recorded link-census row (`reverse/link_census_history.csv`): no clock, no predictions. `python3 tools/progress.py` prints the same figures. The card is redrawn every hour, on the exact tree it is pushed onto; an arrow is the change since the last Discord post, which goes out daily and, between daily posts, whenever a "Does it work?" figure (or the game-data note beside byte match) moves.

* **Byte match**: bytes that rebuild to the original game.dat's exact bytes, divided by all of its program code (`.text` minus 0xCC padding): our C++, library source, generated C++, attached prebuilt libraries, reviewed assembly and verified data in `.text` (`BYTE-MATCHED`). Program code only: game data and assets read "not measured yet" until the image-ownership history (`tools/image_ownership.py record`) holds a row.
* **Linking**: the newest link census's `LINKING`: executable game code in source files that link cleanly under the census's rules, divided by the census tree's executable game code (libraries and embedded data excluded from both). It measures units, not a normal build of the game (the census links under `/FORCE`), and holds still between censuses. "Problems recorded" adds up every category that census recorded against a link without shortcuts (`LINK PROBLEMS`): from its history row, unresolved names (DLL imports included), hard-coded image addresses and names defined twice; from the `reverse/link_status.csv` it wrote, losing COMDAT copies (a file's copy differs from the original's and nothing supplies the original's) and wrongly selected providers (a name the link resolved to a definition proven not the original's). The count is left off when that file is not the newest census's. A census rule change shows "accounting changed" instead of an arrow, and "being re-measured" while `tools/link_census.py` already counts under rules no census has used yet.
* **Next milestone**: first normal build, then the first playtest. It moves on only when a census or link_cycle record shows the exit test, a whole-program link with no `/FORCE` and no stubs; no such record exists yet, and fewer recorded problems do not move it.
* **Hand-written code**: authored C++ divided by executable game code (program code minus vendored and prebuilt libraries and embedded data). Generated C++ and reviewed assembly do not count (`AUTHORED C++`). `GAME CODE C++*` in `tools/progress.py` also counts them; it describes how the code is stored, not whether the game works, so it is not on the card.
* **Readable names**: declared names in `Code/` (files, types, functions, members, globals, parameters, locals) that are not placeholders, divided by all declared names (`tools/name_metric.py`). Not proof of original EA names.
* **Shortcuts removed**: (32,858 − escape-hatch items now) / 32,858, the items at the start of Phase 2, from the shrink-only register `reverse/hatch_baseline.tsv`: pins, `/alternatename`, address-named globals, `present-unmatched` markers, `#pragma optimize`, `class-gate: allow`, `object-symbol=` rows, selectany and `__emit` (`SHORTCUTS`). Raw assembly `db` bytes (`asm_bytes`) are bytes, not items, and are reported apart: 67,972 bytes on 2026-10-28.
* **Original file layout**: (23,488 − files now) / (23,488 − T), counting `.cpp`, `.c` and `.asm` files under `Code/` (23,488 at the start of Phase 2). T is the number of translation units the committed `reverse/tu_map.csv` names (2,264 on 2026-10-28): the map's current estimate, not a proven count. A change of T shows "accounting changed" (`FILE LAYOUT`).
* **Shared class definitions**: (77,814 − duplicate class copies now) / 77,814, the duplicates at the start of Phase 2. A private copy is a class or struct body a matched, hand-written `.cpp`/`.c` file declares for itself (`tools/class_views.py`'s survey); duplicates are every copy of a class with a canonical header (`reverse/canonical_classes.csv`) and all but one copy of any other class (`SHARED CLASSES`).

The start of Phase 2 is commit `e041aec055` (2026-10-25); `python3 tools/readme_progress.py --check-baselines` recounts its three starting figures.

<details open>
<summary><b>Progress over time and code map</b></summary>

[Interactive report](https://open-bfme.github.io/Open-BFME-2/)

![Progress chart](docs/progress_chart.svg)

![Code map](docs/progress_map.svg)

</details>

## Status

Byte matching of `.text` is complete (`python3 tools/progress.py`: BYTE-MATCHED
100%). Phase 2, linking and cleanup, is the open work; its exit test is in
[`docs/verifier_upgrade_plan.md`](docs/verifier_upgrade_plan.md) (step 12). Where
it stood on 2026-10-25:

* the census's Linking figure is the card's Linking row; the whole-program link at retail
  addresses still needed 1,810 stub symbols (a local link cycle of that day; no
  bundle with the stub list is published yet);
* about 23,300 source files under `Code/`, mostly one function each, against the
  few hundred translation units retail was built from; 15,529 of the 91,361
  rows in `reverse/tu_map.csv` are approved for a translation unit and 22,045
  are only proposed.

`python3 tools/next_work.py --claim` serves this work: gate debt first, then link
repair, stub closure, class headers, translation-unit approval and merges, data
and code identity, Microsoft-header and DirectX migration, each by a stated
share (`TIER_WEIGHTS` in `tools/next_work.py`).

## Roadmap

* [ ] BFME 2 Source Code
* [ ] 60/120 FPS
* [ ] Memory fix
* [ ] Better crash logs
* [ ] Multi CPU
* [ ] World builder Source Code
* [ ] Bigger maps
* [ ] RotWK support

Off-host delay is already fixed by the community (BFME 2 patch 1.09v3, RotWK 2.02 v9), so it is deliberately not on this roadmap.

## How You Can Help

Clone the repo and give your AI agent this prompt:

> Read AGENTS.md and follow it. Loop: run `python3 tools/next_work.py --claim`,
> work the served item (and the rest of its file) until its pass test passes,
> verify with `./build.sh`, and commit each verified change on its own. Make a
> PR when you have a few landed changes.

Byte matching is finished, so "convert a body to byte-exact C++" is no longer the
usual task: the picker serves Phase 2 work (see Status). Each commit in the PR is
one verified change, and I will be able to land it.

!! All such AI-generated PRs are appreciated !!

## Build

The baseline executables are committed directly; the MSVC 7.1 toolchain and the
Zero Hour reference source live in the Open-BFME-1 submodule, so clone with
submodules:

```bash
git clone --recurse-submodules https://github.com/Open-BFME/Open-BFME-2.git
cd Open-BFME-2
./tools/setup_hooks.sh   # enable the pre-commit byte-check (git won't do this from a clone)
./build.sh               # verify every tracked function against retail   (.\build.ps1 on Windows)
```

Units marked `// dxsdk` compile against the DirectX 9.0c SDK (August 2005), vendored in `vendor/dxsdk-aug2005/` (see its `PROVENANCE.txt`).

`setup_hooks.sh` also registers `tools/merge_rows.py` as the merge driver for the
ledgers in `reverse/`, so a rebase does not bring back rows the other side deleted
or edited. A clone that skipped it gets the driver on its first commit attempt that
reaches the pre-commit hook, if the hook can write `.git/config` (it makes three
attempts, then leaves it for a later commit). A clone that only pulls keeps git's
built-in union merge, unless it is a linked worktree: worktrees share one config, so
one registers for all. A worktree older than the driver then merges ledgers as
built-in union did, which needs `git merge-file --diff-algorithm` (git 2.44 or newer);
with an older git that merge stops on a conflict. To check:
`git config --get merge.union.driver` prints a command naming `tools/merge_rows.py`,
or nothing if the driver is not registered.

To check a single function while iterating, pass its file or name — a few seconds instead of the full run:

```bash
./build.sh Code/Libraries/Source/Compression/ZLib/trees.c
```
