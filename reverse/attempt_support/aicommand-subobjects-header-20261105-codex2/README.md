# AICommandInterface subobject consumers, 2026-11-05

Base: `69671f0adef2b0e396e4ce3a210e4a0fd67398a8`.
Claim owner: `yasinschroeder-codex2`; selected class cohort: 17 files.

Four consumers now include the existing canonical `AIUpdate.h` instead of
private `AICommandInterface` declarations. Native command receivers use the
subobject at +0x20; opaque AI-holder declarations and explicit subobject casts
preserve those calls without instantiating the abstract interface as a member.
`Rva00495801Arg` retains its existing predicate slot surface. The tactic's
existing derived Coord3D companion must precede AIUpdate.h so its complete
Coord3DBase and conversion surface remain visible. No shared header changes.
These are target call/layout facts, backed by unchanged byte-verified bodies
and the existing canonical header's constructor/table evidence. No new donor
identity, complete holder layout or runtime result is asserted.

| Consumer | Matched rows | Ordinary preview bytes |
| --- | ---: | ---: |
| HeroModeSpecialAbilityUpdate.cpp | 10 | 396 -> 396 |
| Rva00495801.cpp | 1 | 63 -> 63 |
| TeleportToCasterSpecialPower.cpp | 17 | 1,257 -> 1,257 |
| AIStructureCreepTactic.cpp | 52 | 4,226 -> 4,226 |

Verification:

- `find_declared_unmatched.py` passed before and after all four edits.
- `./build.sh` on the four original and final sources: 80/80 rows match;
  final literal checks pass (6 nonempty, 2 empty strings, 12 floats).
  See `before-build.log` and `after-build.log`.
- `object-diff.json`: all external definitions and undefined references are
  unchanged; 289/289 normalized COMDAT fingerprints and sizes are identical.
  Weak aliases are unchanged. No linker alias is removed; Rva00495801 gains
  only the seven already shared AsciiString aliases through the existing header.
  With zero removed providers, no other object loses a definition from this batch.
- `link.log`: four ordinary LINKS, 5,942 -> 5,942 authored bytes, index
  `f44cbcf5b0`, census 2026-11-05 15:19. This predicts preservation, not a real link.
- One `header_adopt_lane.py accept --class AICommandInterface` over all four
  final consumers passed and retired exactly four queue rows (`accept.log`).
  No manual queue deletion, pin, hatch, ledger or data-identity change.

The initial 17-file automatic adoption retained no source edits (`adopt.log`).
The other 13 files retain their queue rows and original sources. Recurring next
checks: reconcile embedded command members and canonical AIUpdate slot surfaces;
resolve field-renaming ambiguity (pathfinder's `locomotor`) and incomplete
canonical methods before retrying. SpecialAbilityUpdate/InitiateIntent and
StrafeAreaUpdate_update also hit preprocessing/header-layout prerequisites.
No repeated failed trial or handoff-only commit is proposed for those files.
The initial default pick, coord2d.cpp, already predicts LINKS for 1,112 bytes
on the current index; its stale missing-provider lead was released unchanged.

No source path moves, new unique matched bytes, census gain or game-run result
is claimed. Remaining classes and other AICommandInterface cohorts are outside
this bounded clearance.
