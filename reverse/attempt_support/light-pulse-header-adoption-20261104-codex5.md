# Light-pulse scene/vector header adoption, 2026-11-04

Starting revision: `0ec9ae5374`. Scope:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCreateLightPulse.cpp`,
`W3DDisplay::createLightPulse`, RVA `0x0004423C`, 233 bytes.

The claimed RTS3DScene cohort's automatic adoption trial restored all eleven
sources. This consumer was rejected because a token-wide Vector3 `x/y/z`
replacement would also alter Coord3D's distinct `x/y/z` fields. The manual
adoption removes both private Vector3 and RTS3DScene definitions and explicitly
includes their existing shared headers. Only accesses through Vector3 locals
and pointers use `X/Y/Z`; `pos->x/y/z` retains Coord3D's declared spelling.
There are no row, symbol, pin, alias or shared-header changes.

Verification:

- `./build.sh` this source: 1/1 rows exact, including float/import/string checks.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class RTS3DScene` and `--class Vector3`:
  passing structural, byte and link-preservation verdicts; the owning tool
  removes both corresponding header-queue rows.
- The current-object link preview preserves 233/233 bytes against the
  2026-11-04 16:16 census at `2f0cb97f52`. This is a prediction, with no new
  census or headline linked-byte claim.

The other ten automatically rejected files are unchanged. Their existing
header-queue entries remain; no other debt is retired by this patch.

## Audit of the complete pending source-path batch

The outgoing range `c7d8498c81..0ec9ae5374` contains one source-path change:
`Rva005386F5Copy.cpp` absorbed into `QuadStrip2D.cpp` by `7e5cd47fcd`.
This adoption adds no path move. Rechecked the removed path, basename and
class token across tools, hooks, workflows, Code, docs and active reverse
registers before this publication. No active path consumer remains.
`reverse/link_status.csv` is historical census output; origin comments,
AptTimeLine/LivingWorldCampaign provenance and ledger notes intentionally
retain the old name. Existing class references are symbols, not file paths.
The merge's debt/queue, provider/consumer and byte/link checks are recorded in
[its audit](quadstrip2d-copy-stl-20261104.md). No further consumer update is
needed; the normal outgoing batch hook remains the publication check.
