# ThingTemplate W3D header adoption, 2026-11-05

Inspected revision: `4f0e20847d`. Scope: the six ThingTemplate header-queue
consumers under `Code/GameEngineDevice/Source/W3DDevice/GameClient/` selected
by `next_work.py --tier header --claim`; claim owner
`yasinschroeder-codex2`. No shared header or ledger identity changed.

## Passing adoptions

Removed private ThingTemplate declarations from these three consumers and
included `Code/GameEngine/Include/Common/ThingTemplate.h`:

| Consumer basename | `./build.sh` matched rows | Current-input link preview |
| --- | ---: | ---: |
| W3DDisplayGatherAnimationDebuggingInfo.cpp | 10/10 | 3,019 -> 3,019 bytes |
| W3DDisplayGatherDebugStats.cpp | 9/9 | 4,083 -> 4,083 bytes |
| W3DTerrainVisualAddFactionBibDrawable.cpp | 4/4 | 1,556 -> 1,556 bytes |

The display helpers read the canonical `m_nameString` storage at +0x64 using
the existing AsciiString buffer representation (text follows its eight-byte
header). This retains retail's single member load. Calling the canonical
string accessor instead added a separate address calculation in these two
consumers. DebugStats now uses canonical `m_isTrainable` at +0x5E7 instead of
the private view's `m_showLevel` spelling. This adopts the existing canonical
field identity; it is not new evidence for that identity.

The terrain helpers read canonical width fields at +0x4D4/+0x4D8 and view
the canonical opaque +0xA0 geometry storage as this TU's existing GeometryInfo.
Retaining the accessor nesting preserves code generation; direct width
expressions did not match. No GeometryInfo layout was newly inferred.

All three builds also passed string, float and import-reference verification.
`find_declared_unmatched.py` passed before and after these changes.
`header_adopt_lane.py accept --class ThingTemplate` passed all three and
retired exactly their three `reverse/header_queue.tsv` rows. Link previews
used the 2026-11-05 15:19 census at `f44cbcf5b0`; these are preservation
checks, not a new census or headline gain. Runner-local logs are
`build/thingtemplate-{animation,debugstats,terrain}-build.log`,
`build/thingtemplate-{display,terrain}-accept.log`, and
`build/thingtemplate-{display,terrain}-link.log`.

## Reverted MapObject trials

Both trials removed the split private ThingTemplateHead/ThingTemplateName
view and included the canonical header, without changing the callers.

- `fastAssignAllUniqueIDs`, RVA 0x0030E390, retail 399 bytes: compiled 397
  bytes. The whole-source build first refused the scoped funclet's exact
  parent-location proof. An explicit parent-symbol build then demonstrated
  a real byte mismatch, so this is not recorded as a false reject.
- `verifyValidUniqueID`, RVA 0x0030E0AA, retail 420 bytes: compiled 418 bytes.
  The first changed byte is the branch displacement at +0xAE; retail's
  `add eax,0x64; mov eax,[eax]` at +0xB6 becomes `mov eax,[eax+0x64]`.
  The funclets still verify, but the parent does not.

The same name-access folding explains both two-byte reductions. Next try
must preserve the original address-adjustment boundary with the canonical
type, then verify the whole parent and EH graph. Do not change flags or
funclet identity to conceal the parent mismatch. The trial is reproducible
by replacing the private split ThingTemplate view with the canonical include
in either original source; no caller edits were made. The commit hook refused
attempt stashes because these addresses already have matched real C++.
The partial verdicts were retracted through `re_log.py`, the stashes removed,
and header-adoption blockers recorded instead. Both Code files were restored, and a combined
`./build.sh` then passed 9/9 rows, including exact parent-EH funclet locations.
Local trial/restoration logs: `build/thingtemplate-map-{fast-build,fast-parent,
verify-build,restored}.log`.

## Unchanged wrapper prerequisite

`Drawable/Draw/Rva0033DCD1.cpp` remains queued: its private ThingTemplate
declares `_STL::vector<ModelConditionInfo>` at +0x358, where the canonical
header has opaque armor-template storage. The automatic adopter refuses that
type mismatch. Equal wrapper bytes and offsets do not establish element
identity. Reconcile the container/callee identity from current owners and
retail evidence before modifying the shared header. No trial was retained.
