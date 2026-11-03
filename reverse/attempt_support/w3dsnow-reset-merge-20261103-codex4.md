# W3DSnow reset consolidation, 2026-11-03

Owner: yasinschroeder-codex4. Prerequisite: a54af64a0b, which reconciles the
shared snow interface without changing matched bodies. The default picker
claimed the seven-file W3DSnow scope; the shared resource header was claimed
separately. The supported consolidation planner was regenerated after the
prerequisite. Routing is rebuilt in memory; no regenerated TU map is committed.

## Additional donor trial (reverted)

The four-row Code/GameEngine/Source/GameClient/W3DSnowManager.cpp donor was
verified before editing: 4/4 bytes exact and ordinary link preview LINKS,
312 authored bytes. Its update/updateIniSettings declarations were temporarily
replaced by the shared resource view. The trial exposed the existing +0x10
time and +0x18 period fields and retained integer resource-copy views of
+0x14/+0x48/+0x4C. Both float-pointer reads and anonymous integer/float unions
were tried for those last fields. The original donor already establishes the
float accesses; this experiment adds no field-name or donor-identity proof.

Both trials left updateIniSettings and its two funclets exact, and retained all
21 seed/reset rows, but changed update (RVA 0x000949D9, 187 bytes). The oldTime
and conversion temporary exchanged stack slots; the compiled update used XMM1
and kept oldTime in XMM0 across successive accumulator expressions, instead of
the target's repeated stack reads and XMM0 operations. Both trials reproduced
that difference. The shared-header include also requires bfme2_ascii ahead of
the donor reference include paths to avoid two AsciiString definitions.

All trial source/header changes were reverted to the already-published
prerequisite. No nonmatching reconstruction remains under Code/. Local inputs
and logs are build/codex4-snow-update-candidate.cpp,
build/codex4-snow-update-candidate.h,
build/codex4-snow-update-before.log,
build/codex4-snow-update-shared-build.log, and
build/codex4-snow-update-link-before.log. Next for this donor: isolate which
shared declaration changes VC8's allocation before attempting a larger merge;
template deduplication by itself is insufficient. This is a consolidation
boundary on an existing matched body, not a matching regression.

## Applied merge and verification

The normal tu_skeleton merge accepted the seed and reset donor, absorbed the
28-byte reset at RVA 0x00093B3F, and removed one .cpp. Five other whole-file
donors remain rejected for their existing private views/templates; the
RenderAsQuads donor remains mixed. The tool moved only reset's source column
in functions.csv and tu_map.csv. The map was not regenerated. The hatch tool
ran its total-keeping update and produced no register diff. No alias or pin
was removed. The merged TU has 21 matched ledger rows covering 20 distinct
RVAs; the pre-existing $L1631/uw_0076007a pair shares RVA 0x0076007A.

- Final byte gate: 25/25 across the merged TU and the reverted update donor;
  string and float reference checks pass. Frozen-source check is clean.
- Exception data: 3/3 exact. Data check: zero findings. CSV validation and
  staged TU ownership check pass.
- Before/after COFF comparison: the two prior objects' union and the merged
  object both define the same 37 external code symbols and five external data
  symbols. Every definition retains identical bytes and relocation names,
  including the vtable. The moved reset provider retains its symbol identity.
- Ordinary link preview: merged TU LINKS, 1,384 authored bytes, equal to the
  former seed's 1,356 plus reset's 28. This is preservation in a prediction,
  not a new census result or a measured linking gain.

Local logs: build/codex4-snow-reset-merge.log,
build/codex4-snow-reset-final-build.log, build/codex4-snow-reset-data.log,
build/codex4-snow-reset-eh.log, build/codex4-snow-reset-link.log, and
build/codex4-snow-merge-comparison.json.

## Tooling and ownership audit

Audited the complete pending path change against a54af64a0b: reset donor to
W3DSnow.cpp. Searched its full path/basename across tools, hooks, workflows,
Code, reverse, docs and build.sh. There are no active hard-coded tooling or
include consumers. Remaining references are the generated origin comment,
append-only file-name provenance in name_basis.csv, the recorded link_status
census, and historical attempt-support evidence. These are retained as history;
the current ledger and TU source columns name the merged owner.

The merge's owning refresh_reports path refreshed Microsoft-header inventory
for the destination and removed donor, producing no queue diff. Neither source
had header-adoption rows, identity/data debt, flag overrides, data-ledger or
body-owner keys, or fold-proof pins to transfer. The only scoped hatch entry
remains the seed's two existing g_Va00BBB8D8 address-global occurrences. Its
count is unchanged. Provider/consumer preservation is supported by the exact
COFF comparisons and ordinary link preview above; the publisher's outgoing
link-batch audit remains the landing check. No runtime or census run was started.
