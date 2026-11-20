# BFME1 upstream input verification: f956f041 -> fc05a785

Account halilkkaya; shared freshness record `bfme1-last-check-halilkkaya.txt` was last
written 2026-11-02 (older than the 168-hour window of docs/matching.md, "BFME 1 reference
updates"), so this account's check was due.

- Upstream: official `Open-BFME/Open-BFME-1` `master` at
  `fc05a78570a8969aec5f5e6efc046a43d881e21a` (fetched 2026-11-20).
- Committed reference at BFME2 `b796529e5b73def000270de537fb45d648b26c6f`:
  `f956f041626b7cdedec401bbe55282ccee1a3fe8` (McMickey93's 8dbc620394c, 2026-11-18).
- Upstream is a fast-forward of the pin: 94 commits, 2,365 files changed (header moves under
  `game/GameEngine/Include/Common/Enums/` and the progress cards among them).

Verification at unchanged BFME2 source `b796529e5b7`:

- An unstaged checkout of the candidate was refused by the native pin guard
  (`reference/open-bfme-1 is checked out at a commit other than the one this tree pins`);
  nothing was built against it.
- With the candidate gitlink staged normally, the full `./build.sh` passed:
  `Functions: OK 102328/102328 matched across 17481 source file(s)`, string, float,
  import, DIR32, pin, module-registry, source-claim and data-row checks OK
  (`Data rows: OK (2361 row(s) byte-verified)`), `FULL GATE: OK`.
- No failure to compare against the previous inputs, so no update regression and no
  pre-existing failure to report separately.
- No verifier, baseline, dependency fallback, donor source or compiler override changed.
  This account holds no cached donor sweep or compile-trial results to refresh.

Upstream donor `// cl:` lines BFME2 refuses at `fc05a785` (`cl_flags.problems`, the
snippet in docs/matching.md): 27 of 17,746 donor sources, the same count as at
`946f3c05a1` (bare include directories without `/I`, and `/FAsc` `/Fa<path>` listings).
They are upstream cleanup items for Open-BFME-1.

This update counts zero source tasks, zero function bytes and zero linked bytes.
