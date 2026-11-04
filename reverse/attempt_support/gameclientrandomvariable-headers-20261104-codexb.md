# GameClientRandomVariable canonical header adoption

Inspected base: db163cbec3752ba9defab8ae447785d570bf9e0f, 2026-11-04.
Provider index: fetched with `link_check.py --fetch-index`; retained the newer
local census index, measured 2026-11-04 02:25 at 5a13f2cd61 (18,018 objects).
All linking numbers below are ordinary previews, not new census measurements.

The claimed header cohort had 19 queued sources. Eleven private class views
are replaced by the registered 12-byte GameClientRandomVariable declaration.
Rva0055B266Xfer.cpp already included that declaration and only needed its stale
queue row accepted. `header_adopt_lane.py accept --class
GameClientRandomVariable` retired 12 rows through the owning tool. Seven
source trials remain unchanged and queued for the prerequisites below.
No ledger, pin, alternatename or hatch is added or removed.

## Target facts and implementation

The existing canonical header records the target evidence for the three-word
layout, constructor RVA 0x000B4979 and assignment RVA 0x0000353A. The existing
constructor implementation is shared in GameClientRandomVariableInlines.h;
consumer byte checks require zero initialization to inline.
ClientRandomValue.cpp keeps its rowed constructor through its existing inline
anchor and retains the original strong assignment definition. All seven
provider rows (120 bytes) still match and its link preview retains 120 bytes.

Rva001F69B1ParticleDrawBinder.cpp's old 16-byte private value type encoded an
alpha-key stride, not the value's size. Its access now preserves the explicit
0x10 stride and casts each value at that key's start. Target corroboration is
the existing RandomAlphaKeyframe in WWMath/color.cpp: 12-byte value followed by
a four-byte frame. ParticleSys.cpp's old 32-byte private type similarly hid
padding between the values at +0x14 and +0x34. Explicit 0x14-byte pads after
each canonical member keep the next field at +0x54. Both source files retain
every byte match. These are local layout repairs, not donor layout claims.

## Verification

- `./build.sh` on the 19 cohort sources plus ClientRandomValue.cpp: 638/638
  function rows exact; three data rows, 40 string literals plus two empty
  strings, 36 float literals and one named import verified. The final sources
  were rebuilt after the original-source control described below.
- `find_declared_unmatched.py` passes the cohort, provider and new inline
  header. No unrowed production body was introduced.
- Final acceptance passes the 12 queued units without adding the provider to
  the preview input set. With ClientRandomValue.cpp included, the preview is
  13/13 clean, 10,831 -> 10,831 bytes. The assignment provider's original strong
  definition is retained; no new assignment COMDAT is emitted by this batch.
- All 20 pristine HEAD sources were temporarily restored, built normally and
  checked against the same index; the working changes were then restored and
  byte verified again. This control reproduces the same three vtable failures
  as the adoption trial: 17/20 clean, 20,363 -> 19,334 preview bytes. Thus the
  unresolved constructor previews are present before this change. No census
  gain or complete consumer closure is claimed.

## Remaining header rows: vtable prerequisite

Under Code/GameEngine/Source/GameClient/System/FXParticleSystem/:

| Source | Constructor RVA / size | Preview bytes |
| --- | --- | --- |
| DefaultUpdateModuleInfoDefaultCtor.cpp | 0x0055F529 / 339 | 349 -> 0 |
| LightningDrawModuleInfoDefaultCtor.cpp | 0x0056142E / 171 | 181 -> 0 |
| RenderObjectUpdateModuleInfoDefaultCtor.cpp | 0x00561F99 / 489 | 499 -> 0 |

Each adoption trial replaces only its private random-variable class with the
canonical declaration and inline header, and byte matches its constructor,
EH handler and funclet. Each fails `header_adopt_lane.py accept` on its own
`??_7<Class>@FXParticleSystem@@6B@` COMDAT: "differs from the first copy in link
order (no retail address)". Original-source controls reproduce those failures.
All three trials were reverted; their debt was not retired.

Next: identify the first-selected vtable providers, compare their relocation
slots against the native tables and reconcile the complete Snapshot override
contracts before retrying these three header rows. The older Lightning
handoff already identified incomplete post-load overrides:
[2026-10-13 evidence](lightning-info-snapshot-link-20261013/readme.md).
Do not reshape a table merely to equal a non-retail first provider. Carry the
three unchanged units into the next scheduled census; no new census was run.

## Conflicting debt verdict: inline assignment cohort

Four trials additionally needed the existing three-dword assignment body to
inline: FXParticleSystem.cpp, INIBfmeSettingsParsers.cpp,
Rva003AEE16CopyCtor.cpp and ParticleSystemConstructor.cpp. The trial companion
defined assignment inline using the provider's existing Raw block copy;
ClientRandomValue.cpp included that companion instead of its original strong
definition, and its existing anchor also called assignment to retain its row.
All bytes and the combined acceptance with that changed provider passed:
17/17 clean, 19,334 -> 19,334 preview bytes including these four units.

The commit hook's `repair_queue.verify_removed_debt` instead checks the removed
header-debt cohort, which omits ClientRandomValue.cpp because it owns no
removed queue row. Its index still has the old strong assignment definition;
the cohort preview reports duplicate `??4GameClientRandomVariable@@QAEAAV0@ABV0@@Z`
and predicts linked-byte losses. Both the combined acceptance and debt-only
rejection were reproduced. This is recorded as a false-reject lead, not
repaired in the source commit. Reconcile acceptance and hook preview inputs
before retrying the four rows. All four source trials and queue removals were
reverted; the inline assignment trial was removed and its original strong
provider restored. The remaining constructor-only batch passes acceptance
without supplying additional provider units to the debt cohort.
