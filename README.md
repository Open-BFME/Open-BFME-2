# BFME 2 Source Code

Goal: Source code that rebuilds BFME 2's engine binary (`game.dat`) byte-for-byte, and game modernization improvements that you've only seen in your dreams.

Sister project of [Open-BFME-1](https://github.com/Open-BFME/Open-BFME-1) — same engine family, same MSVC 7.1 toolchain, same byte-matching workflow. BFME 1's converted source is this repo's nearest-ancestor reference and rides in as a submodule.

## What?

* If you take a part of the BFME 2 binary, recreate the exact source code that would make that part of the binary, then compile the source code and inject it into the binary, you get the same binary
* Doing this piece by piece will eventually give you a full, open source recreation of BFME 2, and enable some (insane) mods
* The target is `game.dat` — the real engine PE. `lotrbfme2.exe` is only a launcher stub.

## Status

Bootstrapping. Flag calibration against retail is proven: BFME 1-matched bodies
transfer to `game.dat` byte-for-byte (same compiler, same flag families).

## Roadmap

* [ ] BFME 2 Source Code
* [ ] 60/120 FPS (logic/render decoupling — the INI cap unlock just speeds up the game)
* [ ] Memory fix
* [ ] Better crash logs
* [ ] Multi CPU
* [ ] World builder Source Code
* [ ] Bigger maps
* [ ] RotWK support

Off-host delay is already fixed by the community (BFME 2 patch 1.09v3, RotWK 2.02 v9) and is deliberately not on this roadmap.

ping `redbracket` on Discord if there's something else you want to change this roadmap

## How You Can Help

Clone the repo and give your AI agent this exact prompt — measured on six agent
sessions, a vaguer prompt reliably produces zero progress:

> Read AGENTS.md and follow it. Loop: take the served candidate's whole file,
> convert bodies to byte-exact C++, bank each verified body as its own commit,
> and before stopping run `python3 tools/progress.py origin/master` — if C++
> exact is +0 bytes, keep going. Make a PR when you have a few landed bodies.

Each commit in the PR is one verified function, and I will be able to merge it.

!! All such AI-generated PRs are appreciated !!

## Build

The baseline executables are committed directly; the MSVC 7.1 toolchain and the
Zero Hour reference source live in the Open-BFME-1 submodule. A full setup is:

```bash
git clone --recurse-submodules https://github.com/Open-BFME/Open-BFME-2.git
cd Open-BFME-2
./tools/setup_hooks.sh   # enable the pre-commit byte-check (git won't do this from a clone)
./build.sh               # verify every tracked function against retail   (.\build.ps1 on Windows)
```

To check a single function while iterating, pass its file or name — a few seconds instead of the full run:

```bash
./build.sh Code/Libraries/Source/Compression/ZLib/trees.c
```
