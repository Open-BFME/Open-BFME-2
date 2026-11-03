# W3DSnow inherited interface prerequisite, 2026-11-03

Base: f3c6c3451d. Owner: yasinschroeder-codex4. Default picker selected
W3DSnow.cpp consolidation and claimed its seven source files; the resource
header was claimed separately. No reference revision was changed.

Target facts: W3DSnowManager's retail table at VA 0x00BC8144 has fifteen
entries: the fourteen SubsystemInterface slots followed by updateIniSettings
at +0x38. The seed previously emitted only the first two entries (8 bytes).
The canonical SubsystemInterface.h already supplies the inherited slots under
BFME_SUBSYSTEM_SLOTS. SnowManager occupies 0x74 bytes and its derived manager
0xB0, checked by the existing compile-time extent assertions.

Change: the resource view derives SnowManager from that canonical interface,
keeps its observed fields at their existing offsets, and declares the rowed
reset/update/updateIniSettings overrides. The reset donor includes the same
view instead of declaring two partial classes. No names, pins or aliases are
added or removed. The reset donor's m_a8 access uses the shared m_A8 spelling.
This is a declaration/layout reconciliation, not a new identity claim.

Verification:
- Baseline seed/sub-box byte gate: 21/21. Changed seed/reset byte gate: 21/21;
  all defined functions are matched in both changed units.
- EH verification: 3/3 exact. Shadow data check: two sources, zero findings.
- Reset emits the same code symbols, bytes and relocation names as before.
  The seed keeps every prior named code definition; the nine added code
  definitions are the canonical subsystem's inline slots. Local EH labels
  renumber; the parent EH graph verification remains exact.
- The emitted W3DSnowManager vtable grows from 8 to 60 bytes, with reset at
  +0x24, update at +0x28 and updateIniSettings at +0x38. Its original two
  entries retain their relocation names.
- Before and after ordinary link previews: seed 1,356 authored bytes and reset
  28 bytes, both LINKS, using census index 8661f15284 (2026-11-03 20:03).
  Fetching the official index retained that same current local index.
- Normal merge dry-run changes from no accepted composition to seed + reset
  accepted. All other donors retain their known class/template prerequisites;
  RenderAsQuads remains mixed. No rejected body was edited.

Local logs: build/codex4-snow-before.log,
build/codex4-snow-interface-build.log, build/codex4-snow-link-before.log,
build/codex4-snow-link-after.log, build/codex4-snow-interface-merge.log and
build/codex4-snow-code-comparison.json. The evidence planner was read before
editing; its stale-map warning is handled by tu_skeleton rebuilding routing
in memory, never by committing a regenerated map.

Next: apply the verified reset merge in its own commit. This prerequisite
changes no census headline and claims no new byte coverage or runtime result.
