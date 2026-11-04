# W3DSnow blend/state canonical Overridable adoption

2026-11-04, yasinschroeder-codex4; starting revision 9ab05ac463.
The default picker claimed W3DSnow.cpp and its five remaining whole donors.
The supported planner and normal merge dry-run confirm 31 approved rows,
RenderAsQuads mixed, and zero accepted whole donors. tu_views changes nothing:
canonical Overridable adoption and incompatible class/template views remain.

The earlier sol-b5-snow-blend-prerequisite trial exposed an extra override hop
when getFinalOverride's inline definition becomes visible. Both existing blend
and state methods now include the canonical Overridable header, use its inline
getNextOverride accessor, and call the existing nonconst out-of-line
friend_getFinalOverride on the mutable next object. The const cast selects that
accessor, whose verified owner is ThingFactoryNewOverride.cpp at RVA 001E35DF;
the const overload at 00288609 has a different body and is not appropriate.
These calls retain the original 001E35DF target and original override-walk CFG.
No accessor, pin, alias, or compiler directive was added. WeatherSetting's
padding starts at canonical base extent 10 instead of private extent 8;
its observed enabled/duration fields remain at 6C/70.

Verification:

- Before and after ./build.sh: both rows exact (360 and 189 bytes); string,
  float and import reference checks pass.
- Frozen-source check: both units clear. Data identity: zero findings.
- header_adopt_lane.py accept --class Overridable on the pair: PASS/PASS;
  the owning tool retires exactly two header_queue.tsv rows.
- Ordinary before/after link_check preview: both LINKS, unchanged predicted
  360 + 188 = 548 census-linked bytes against f12552d0a7, 2026-11-04 20:47.
  This is preservation in a preview, not a new census or runtime measurement.

Local logs: build/codex4-snow-before.log,
build/codex4-snow-canonical-build.log, build/codex4-snow-accept.log,
build/codex4-snow-link-before.log, build/codex4-snow-link-after.log,
build/codex4-snow-dry-run.log and build/codex4-snow-views.log.

Next consolidation prerequisite: adopt the canonical base in the shared resource
view and reconcile the remaining WeatherSetting/OVERRIDE/W3DSnowManager storage
views before the normal merge can absorb blend/state. No files merged here;
private views in the other donors remain queued, and no debt outside the two
accepted rows is retired.
