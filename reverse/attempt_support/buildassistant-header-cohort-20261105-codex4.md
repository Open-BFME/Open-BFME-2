# BuildAssistant header adoption, 2026-11-05

Base: `bfd57880db9e672e72f575b14d81ef4dc568d91d`.
Claim owner: `yasinschroeder-codex4`.

Four units now include the existing canonical `BuildAssistantClass.h` instead
of declaration-only private views. The call mappings follow the existing
header's documented retail table at VA `0x00C1A088`: slot 20 is
`rva0039380F`, slot 21 is `rva0039321C`, slot 23 is `rva00391A70`, and
slot 24 is `canMakeUnit`. No new semantic names or header changes are made.

| Unit (under `Code/GameEngine/Source/`) | Runtime sections before/after | External definitions before/after | Link preview bytes before/after |
| --- | --- | --- | --- |
| `Common/System/BuildAssistantWallLocations.cpp` | 63 / 63 | 58 / 58 | 2,218 / 2,218 |
| `GameClient/GUI/ControlBar/ControlBarRappellerCount.cpp` | 63 / 63 | 51 / 51 | 4,725 / 4,725 |
| `GameClient/InGameUIHandleBuildPlacements.cpp` | 69 / 69 | 63 / 63 | 4,280 / 4,280 |
| `GameClient/MessageStream/PlaceEventTranslator.cpp` | 45 / 45 | 38 / 38 | 1,744 / 1,744 |

Verification:

- Normal `./build.sh` verifies originals and replacements. Final strict
  `link_check.py --prepare-current` verifies all 31/31 rows, 17 funclet pins,
  10 string literals and 24 compiler float literals with four reusable
  receipts. `find_declared_unmatched.py --fail` passes all four units.
- Original and replacement object graphs, captured with
  `class_cleanup.snapshot` and compared with `class_cleanup.same_runtime`,
  are equivalent in every unit. This covers all non-debug bytes and
  relocations, all 210 external definitions, COMDAT policies and weak
  bindings (the wall unit retains its two weak bindings). No provider or
  link-wide alias is removed. Only bijective section renumbering is allowed.
- One `header_adopt_lane.py accept --class BuildAssistant` over the four
  units passes and retires exactly their four queue rows.
- Ordinary current-object `link_check.py` reports LINKS for all four,
  preserving 12,967 / 12,967 census-linked bytes against the index at
  `f44cbcf5b0`, dated 2026-11-05 15:19. This is a preview, not a new census
  or evidence that the game runs. No real link or smoke runner was started.

Remaining cohort: the constructor/destructor and main implementation use
typed members where the canonical header currently declares opaque storage;
`GameEngineInit.cpp` also includes `spline_service.h`'s separate
`SubsystemInterface` definition. These existing queue items remain intact.

The AI wall caller exposes an additional signature disagreement (LINK-598).
`AIBuildableWallSegment::build` at RVA `0x00596D99` calls virtual slot 15
with a `Coord3D *` second argument. The canonical header declares that
parameter as `const ThingTemplate *`. Replacing its private view and using
`vslot15` fails C2664. No cast was added to conceal this disagreement.
The trial was restored byte-for-byte; all eleven original unit rows were
reverified. Establish the slot's native parameter contract before adoption.
