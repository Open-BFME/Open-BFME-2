# GameTextInterface: three queued consumers adopt the canonical header

2026-11-04; base `057f9091ed`. Header `Code/GameEngine/Include/GameClient/GameText.h`
is unchanged. This is consumer adoption, not a new class contract or name recovery.

- `LANAPIOnGameStartTimer.cpp`: replace the seventeen padded slots and `slot44`
  with the canonical declaration and `fetchPtr(const char *, bool *)`. Both timer
  labels retain the native +0x44 dispatch and UnicodeString formatting ABI.
- `AptDisplayStringAllocation_ctor_Rva004D5A4D.cpp`: replace the unused private
  GameTextInterface declaration and donor string wrappers with canonical BFME2
  headers. The only row is the 17-byte `setSize`; the donor constructor stays absent.
- `W3DDisplayStringManager.cpp`: replace its private text interface with the
  canonical header. Its used AsciiString fetch overload retains slot 14.

`header_adopt_lane.py accept --class GameTextInterface` passed all three units
and retired exactly their three rows from `reverse/header_queue.tsv`.
`./build.sh` over the cohort passed 22/22 rows, the one data row, six string
literals, one float literal and import checks. Renumbered EH funclets were
verified through their parent EH graphs. `find_declared_unmatched.py` and
`check_csv.py` passed. No source paths, ledger rows, pins or hatches changed.

Combined `link_check.py` against census 2026-11-04 02:25 at `5a13f2cd61` reports
all three LINKS: 169 -> 169, 17 -> 17 and 914 -> 914 owned bytes respectively,
preserving 1,100 census-linked bytes. This preview establishes no new census,
real-link or runtime result. The pure-slot conclusion in LINK-172 is unchanged;
this adoption introduces no new obstacle or changed prerequisite there.
