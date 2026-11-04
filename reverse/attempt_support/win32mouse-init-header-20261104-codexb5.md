# Win32Mouse init: canonical Mouse adoption

Base: `d422180d26318697615a581fc38f16df97d2826a`.
Scope: `Code/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_reset.cpp`.

The private four-byte Mouse declaration placed a derived padding member over
storage that the canonical Mouse owns. Include the existing canonical header
and express the same byte store at +0x4F9C through its opaque `field4F14` storage.
The existing `Win32Mouse::init` and `Mouse::init` identities remain unchanged;
the old comment still described their superseded reset names and is corrected.
No layout or member identity beyond the existing header is inferred.

Checks:

- `./build.sh Code/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_reset.cpp`:
  1/1 matched, including the complete 17-byte body and reference checks.
- `find_declared_unmatched.py` on that source: all definitions matched.
- `header_adopt_lane.py accept --class Mouse` on that source: PASS; the owning
  tool retired its one row from `reverse/header_queue.tsv`.
- `link_check.py --prepare-current` on that source: strict reusable receipt
  passes for the one explicit provider.
- Ordinary `link_check.py` preview: LINKS, 17 -> 17 bytes against the published
  2026-11-04 07:28 census at `a62ac1c10b`. This is preservation evidence, not a
  new census measurement or a real-link claim.

No source paths, pins, aliases or other debt registers change.
