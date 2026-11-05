# CommandSet header adoption, 2026-11-05

Inspected source revision: `762117144a`. Owner: `yasinschroeder-codexb2`.
The existing canonical `GameClient/CommandSet.h` replaces private declarations
in the fifteen sources below; no canonical header, ledger identity or source
path changes. The constructor, destructor and setter definitions stay in place.
The removed class declarations contain no inline member bodies or data definitions;
no provider or `/alternatename` is removed.

Result: `header_adopt_lane.py accept --class CommandSet` accepts the fifteen-file
cohort and retires fifteen queue rows. The same source adaptations also accept
one CommandButton row (PlayerRva002AD1FD) and two Overridable rows (CommandSet.cpp
and CreateAHeroHero), through one owner-tool invocation per class: eighteen
header-queue rows retired in total.

The manual adaptations use the canonical special-power pointer at +0x44,
CommandSet's typed button array at +0x14 and members at +0x94/+0x98; the setter
preserves its existing integer ABI with a pointer cast. Exact bytes establish
compatibility for these bodies, not a new recovered field-name claim.

Verification: `./build.sh` over all fifteen sources passes 423/423 functions,
four data rows, 71 literals, ten empty-string references, 29 compiler float
literals and six named imports. Renumbered EH labels verify through parent EH
data. Declared-unmatched passes for every changed source; `check_csv.py` and
`git diff --check` pass. Final ordinary `link_check.py` reports all fifteen
LINKS, preserving 53,921 -> 53,921 bytes against the 2026-11-05 15:19 census at
`f44cbcf5b0`. This is a preview, not a new census or real-link measurement.
The publishing hook additionally audits affected consumers across the outgoing
batch; census confirmation remains pending because the index predates the base.

Remaining scope: ten CommandSet queue sources are unchanged. BuildAssistant's
needed-upgrades view, the large ControlBar/ReloadNotice views, AIPlayer codegen,
AIGroup/header dependencies and AutoAbility/ScriptActions prerequisites need
separate verified repairs. In ReloadNotice, preserve the private Overridable
inline providers until all-object consumers and their canonical owners are
resolved. This batch clears the CommandSet declaration prerequisite for
ControlBarCommand and ControlBarCommandSetCtor; it does not clear the broader
ControlBar consolidation obstacle.

Changed sources:

- `Code/GameEngine/Source/Common/RTS/ActionManagerSpecialPowerChecks.cpp`
- `Code/GameEngine/Source/Common/RTS/PlayerRva002AD1FD.cpp`
- `Code/GameEngine/Source/Common/Rva005DA6F3Ctor.cpp`
- `Code/GameEngine/Source/Common/System/SaveGame/CommandSet.cpp`
- `Code/GameEngine/Source/Common/System/SaveGame/CommandSet_SetCommandButton.cpp`
- `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommand.cpp`
- `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommandSetCtor.cpp`
- `Code/GameEngine/Source/GameClient/GUI/parseSpellIndex_Thunk.cpp`
- `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIPlanningPhaseBuildingSelectionCtor.cpp`
- `Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp`
- `Code/GameEngine/Source/GameLogic/Object/CreateAHeroHero.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp`
- `Code/GameEngine/Source/GameLogic/SkirmishAI/AIUpgrade/AIUnitUpgrader/AIUnitUpgrader.cpp`
- `Code/GameEngine/Source/GameLogic/SkirmishAI/AIUpgrade/AIUpgradeScienceBuilder/AIUpgradeScienceBuilder.cpp`
