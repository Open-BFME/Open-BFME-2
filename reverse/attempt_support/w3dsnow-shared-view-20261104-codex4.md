# Shared W3DSnow resource, blend and state views

2026-11-04, yasinschroeder-codex4; follows 4341bf3730's canonical
Overridable adoption. All sources and the shared header are claimed by this seat.

The shared resource view now includes canonical Overridable instead of its
private class. WeatherSetting padding shrinks by four to preserve all observed
field offsets after the canonical base grows from 0C to 10. The existing
blend/state donor declarations establish weather flag 6C, duration 70 and
receiver float storage 6C/70; those are exposed without assigning new semantic
member names. Existing integer bit-copy fields retain their types, and the
blend/state bodies access their already-established float views by casts.
Base/derived size checks remain 74/B0. Both donors include the shared resource
view, removing their incompatible WeatherSetting, OVERRIDE and W3DSnowManager
copies. Canonical Overridable remains explicitly included in each consumer,
as required by the header adoption lane's structural check.

The explicit-next walks continue to call the existing out-of-line nonconst
friend_getFinalOverride, not the shared recursive inline getter. No compiler
flag other than the required ascii shim include directory changes; no new pin,
alias, hatch, generated body or source path is introduced.

Verification:

- ./build.sh on seed plus both donors: 23/23 exact, seven float literals and
  the one empty string reference verified; import references clear.
- EH data: 3/3 EXACT. Frozen-source check passes all three consumers.
- header_adopt_lane.py accept --class Overridable: all three PASS; no further
  header-queue row retired (the two donor rows retired in 4341bf3730).
- Normal merge dry-run now accepts seed, blend and state (previously zero).
  Other whole donors still reject incompatible private views/templates;
  RenderAsQuads remains mixed. The supported planner was regenerated. No TU map
  was regenerated or committed and no merge has yet been applied in this commit.
- The header has only these three active source consumers, checked with rg.

Logs: build/codex4-snow-shared-final.log,
build/codex4-snow-shared-accept.log, build/codex4-snow-shared-eh.log,
build/codex4-snow-shared-dry-run.log, build/codex4-snow-planner-refresh.log.
The successful dry-run precedes only the equivalent explicit includes and a
comment added for final header acceptance; the applied merge must recheck its
current composition and link guard. Next: normal tu_skeleton merge followed by
byte/EH/data/link and source-path consumer audit; no measured linking gain is
claimed here.
