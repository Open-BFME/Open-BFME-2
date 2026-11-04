# AptSkirmish donor header adoption (2026-11-04)

Base: `b1b2653dd795c0300d520a68d738bca2079c86d7`.

- `AptSkirmishDestructor.cpp`: replace the unused opaque `AptMpGameSetup`
  declaration with its canonical header. `./build.sh` passes all 12 rows.
- `AptSkirmishCallbacks_OnUpdateData.cpp`: replace the private
  `GameWindowManager` virtual-slot view with its canonical header, included
  after `CreateAHeroManager.h` establishes the full subsystem interface.
  `./build.sh` passes the one row.
- `header_adopt_lane.py accept --class AptMpGameSetup` and
  `--class GameWindowManager`, respectively, pass and retire the two sources'
  header-queue rows. No data or identity debt is retired.
- Both sources pass `find_declared_unmatched.py`; `check_csv.py` and
  `git diff --check` pass.
- Staged `data_check.py` reports no findings. The shadow code-identity gate
  reports the existing LINK-185 `$L1594` binding to `Rva0031455E` at
  `0x0052163E`; no binding or identity register changed here.
- After `link_check.py --fetch-index`, the two-source preview preserves
  351 + 324 = 675 authored linked bytes against census 2026-11-04 02:25,
  index `5a13f2cd61`. This is a preview, not a new census or real-link result.

The consolidation dry-run accepted no donor. Seed/donor class-view conflicts
and the existing GameInfo/deleteObject interface mismatch remain. No source
paths or ledger rows moved. LINK-185's profile-wrapper provider conflict and
its next step are unchanged; this adoption does not repair that binding.
