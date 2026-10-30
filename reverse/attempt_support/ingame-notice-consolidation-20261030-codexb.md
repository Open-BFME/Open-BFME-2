# IngameNoticeDisplay consolidation

Inspected base: `d453af1733`, 2026-10-30. The supported picker claimed
`Code/GameEngine/Source/Common/Bfme/IngameNoticeDisplay.cpp` and its sole
whole-file donor, `IngameNoticeDisplay_reset.cpp` in the same directory.

## Prerequisite

The supported merge dry run rejected reset because its private class used
different field names and omitted the seed's SubsystemInterface base. The
donor now includes the canonical base header and uses the seed's declaration
and field names. The descriptor store retains its existing offset view through
a cast; no descriptor layout or recovered field name is claimed.

The original two sources pass `./build.sh`: 22 function rows and two data rows.
Both preview LINKS against census index `85f6b7f40c` (2026-10-29 15:08), for
628 and 68 authored bytes respectively. After reconciliation reset still
matches its complete 68-byte body. Its two normalized COMDAT fingerprints
(`538e0d467efe` for reset, `218cde81ae4c` for for_each), definitions, external
references and weak/include records are unchanged. The base header contributes
seven AsciiString aliases already present in the destination's object.
Declared-unmatched checks pass before and after the edit.

The pre-edit naming planner covered Common/Bfme. Both sources are unresolved
with no alternative destination. The seed flags pragma/include context and
the data/hatch registers; the reset donor has no planner blockers. The
WorldBuilder/BFME1 GUI path is a lead, not target placement proof. Placement
comes from the supported merger's current in-memory TU map, not that planner
hint or the stale committed map. Three mixed sources remain outside this move:
Rva004E5A24Ctor.cpp, Rva004E5A78Method.cpp and GameClient/GUI/IngameNoticeDisplay.cpp.

Neither whole-file source owns a header-queue, Microsoft-header-queue,
code-identity or data-check-baseline key. The separate mixed GUI source's
iswspace header debt remains outside this scope. The destination already owns
two linker-alias hatches and its data-ledger entries; no debt is retired here.
