# BFME 1 reference verification

Official `Open-BFME/Open-BFME-1` master fetched and verified at `34f59164f6d1efd413c5fd37f4894ec834c3c0fe`.
The committed BFME 2 input before this update was `c1f3b5af79c6e982e4f2934bdb840a4483c59fa9`;
the actual previous verified checkout was `ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f`.

Both full gates ran at the same BFME 2 revision `7b658bf72e8462f3fa0ceff8c5b4d884448f8890`.
Both passed 70,210/70,210 functions and every full-gate check; no update regressions or pre-existing failures.
The normal dependency cache invalidated and recompiled 101 affected units after 18 donor-header changes.
An audit of all affected sources found zero missing resolved include-directory operands before and after.
No header substitutions, verifier changes, or target-layout repairs were required.

The previous detached donor commit is preserved locally as `codex/preserve-ba7-verified-reference`.
The source-layout resolver continues to select `game/`, `inputs/reference/`, and `inputs/toolchains/`.

The refreshed byte sweep found 5,414 unique placements, 5,339 exact independently matched control boundaries,
nine free placements (2,521 bytes), and no eligible exact donor file. The near queue contains three 25-byte
EH leads; these are not standalone clean C++ recoveries. The lift lane lists 230 bodies / 137,120 bytes,
including 150 servable bodies / 93,785 bytes. Lifted bytes are source leads, not recovery credit.

Ignored local full-gate logs and their SHA-256 receipts:

- old: `build/bfme1-old-fixed-publication-full.txt` — `6463d2a688b1ef6eafe5a4604a1ad4a62d5918aeef2461420105fdfac04c75f6`
- new: `build/bfme1-new-fixed-publication-full.txt` — `1e63df1c3d5bf0b31363780a8d30a75db3b5b4aae7676c121ea70b9b8859f24c`

Completed UTC: `2026-10-08T16:07:30.740403+00:00`.

Reproduce with the normal full `python tools/build.py` at each donor checkout and the BFME 2 revision above.
Link-census and runtime tests were not run for this reference update.
