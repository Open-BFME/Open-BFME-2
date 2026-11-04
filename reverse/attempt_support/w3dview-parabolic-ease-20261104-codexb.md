# W3DView ParabolicEase view reconciliation

Inspected revision: `9cdb32d233`; owner: `yasinschroeder-codexb`.
The default picker claimed W3DView.cpp and its 43 whole-file donors.
The supported consolidation planner completed without missing inputs.

The previous completed merger trial is recorded in
[the existing handoff](w3dview-consolidation-20261104-codexb5.md).
Its recommendation was to reconcile compiler rejects before another exhaustive
trial. This change resolves one private-view conflict, without moving sources.

## Change and evidence boundary

Three donors under `Code/GameEngineDevice/Source/W3DDevice/GameClient/`
now spell the same ParabolicEase declaration:

- W3DViewCameraModFinalPitchBfme.cpp previously used a struct with two floats.
- W3DViewMoveAlongSpline.cpp used a class with those floats and the evaluator.
- W3DViewZoomCamera.cpp used an empty class with only the setter declaration.
  Seven explicit padding bytes after each empty member supplied the remaining
  space. Replace that padding with the two float members.

The byte-verified setter at RVA 0x0030E51F stores floats at +0/+4, and the
byte-verified evaluator at 0x0030E5D1 reads them. Existing donor views and the
Zero Hour header independently use two floats. These facts support this
observed eight-byte prefix; they do not prove the complete original class.
The class spelling agrees with the existing setter/evaluator providers.
No parameter or return type uses this class by value in the changed units.

After correcting the empty view's occupied space and the struct/class key,
`tu_views.py W3DView.cpp --class ParabolicEase --no-merge-check` applied the
same union of existing method declarations and fields to all three donors.
The tool verified layouts, byte builds, unmatched definitions and external
symbols. The final dry-run reports ParabolicEase already shared.

## Verification

- Before and after: `./build.sh` on all three sources passes 5/5 matched
  functions, one compiler float literal and no skipped literals/imports.
- `find_declared_unmatched.py --fail` passes all three sources.
- Compiler CodeView: ParabolicEase is 8 bytes. PitchCameraInfo and
  ZoomCameraInfo remain 0x28 bytes; their ease members start at +0x1C and
  their active flags at +0x24. PitchCameraInfo's second flag stays +0x25.
- `class_cleanup.same_runtime` passes the original and final objects for
  every source, covering all non-debug section bytes, relocations, external
  definitions, weak defaults and COMDAT selection policies. Respective
  section/definition counts: zoom 10/8, final pitch 2/1, spline 8/7; no weak
  externals. Thus relocation masking does not conceal a callee change.
- Census-only baseline and final current-object link previews both report
  LINKS: zoom 428 -> 428 bytes, final pitch 176 -> 176, spline 529 -> 529.
  Index fetched by `link_check.py --fetch-index`: 2026-11-04 16:16 at
  `2f0cb97f52`. These are previews, not a new census or a linking gain.
- Scoped searches find no header/MS-header, data, identity or hatch keys for
  the three changed paths, and ParabolicEase is not a registered canonical
  class. No debt is retired and no alias is removed.

## Remaining work

No full merger trial was repeated and no source-file reduction is claimed.
The seed still imports a different reference ParabolicEase declaration through
W3DView.h; reconciling the three private views alone does not repair that
include boundary. W3DView's anonymous aggregate and incompatible private
views, canonical-header adoption, the other compiler rejects and the recorded
byte/COMDAT-selection rejects still need their own verified repairs. Keep the
merger's link guard when retrying.
