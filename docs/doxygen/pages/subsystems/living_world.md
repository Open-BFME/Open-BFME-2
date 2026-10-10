# Living World: the War of the Ring campaign {#sub_living_world}

The Living World is BFME 2's strategic layer: a campaign map divided into
regions, with armies, buildings and build plots, campaign players, scripted
acts and a turn phase. A battle between armies is either fought as an
ordinary RTS game on a battle map or settled by the auto-resolve simulation,
and the result flows back into the campaign. Zero Hour has nothing like it;
BFME 1 has a smaller Living World that this one grew from.

The API group is \ref grp_living_world. Much of the code is matched but still
carries provisional names, so this page describes the data model and the
contracts between the parts rather than individual functions.

## Where it lives {#sub_living_world_where}

| Directory | What is there |
|---|---|
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/` | campaign logic: the logic root, regions, armies, players, battles, buildings and build plots, campaigns and acts, scenarios, the tutorial, save-game transfers |
| `.../System/LivingWorld/AutoResolve/` | the auto-resolve battle and its bonus tables |
| `Code/GameEngine/Source/GameLogic/System/` | the GameLogic battle hand-off files (`GameLogicLivingWorld*.cpp`) and `LinearCampaignManager.cpp` |
| `Code/GameEngine/Source/GameLogic/LivingWorld/` | INI parsers for act events and spline effects |
| `Code/GameEngine/Source/GameClient/LivingWorld/` | the client manager, map visuals, army lines, sounds and part of the eye tower |
| `Code/GameEngine/Source/GameClient/` | the rest of the eye tower (`LivingWorldEyeTower*.cpp`) |
| `.../GameClient/LivingWorld/InGameUI/` | the strategic in-game UI: selection, per-phase input, battle prompts |
| `Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/` | the strategic HUD's Apt movie clips, conflict results and veterancy display |
| `Code/GameEngine/Source/Common/` | the HUD's top-level callbacks (`StrategicHUD.cpp`), region connection parsing, and many address-named staging files |

Retail asserts name the original units
`GameLogic/System/LivingWorld/LivingWorldLogic.cpp`, `LivingWorldCampaign.cpp`,
`AutoResolve/LivingWorldAutoResolveBattle.cpp`,
`LivingWorldAISupport/LivingWorldAI.cpp`, `LivingWorldAIArmyMover.cpp` and
`LivingWorldAIInformation.cpp`, and
`GameClient/LivingWorld/LivingWorldEyeTower.cpp`. Many Living World bodies
still sit in address-named files elsewhere, so search the ledger by class
name rather than by directory.

## Key classes and singletons {#sub_living_world_classes}

The class names here are confirmed by retail strings: subsystem registration
names, the names objects report when saved, INI block keywords or assert
paths. The roles come from the reconstructed code; inferences are marked.

- **Logic root.** `LivingWorldLogic` (`TheLivingWorldLogic`) holds the
  region manager, the campaign players and their armies, region victory
  bookkeeping and the current turn phase, and saves them through a
  versioned state transfer.
- **Regions.** `LivingWorldRegionManager` holds the campaign's regions, its
  pending battles and the current battle. A `LivingWorldRegion` is one
  territory. A `LivingWorldRegionConnection` is one link to another region:
  a region name plus an optional list of detour points, built from either a
  `ConnectsTo` name or a `Connection` sub-block (`Region`, `DetourPoint`).
- **Players, armies, battles.** `LivingWorldPlayer` is a campaign player,
  `LivingWorldArmy` an army on the map and `LivingWorldBattle` a battle
  between armies.
- **Buildings.** `LivingWorldBuilding` templates
  (`TheLivingWorldBuildingTemplateStore`) are what a `LivingWorldBuildPlot`
  in a region can hold. A building's effects are *nuggets*; the kinds found
  so far are `LivingWorldBuildingNuggetSpawnArmy`, `...IncreaseCommandPoints`,
  `...StrengthenArmy` and `...UpgradeTroops`.
- **Campaigns.** `LivingWorldCampaignManager`
  (`TheLivingWorldCampaignManager`) keeps the campaigns parsed from
  `LivingWorldCampaign` blocks. Campaigns are
  scripted through *acts*, parsed by `ParseLivingWorldCampaignAct`
  (BFME 1: `Act` sub-blocks of `LivingWorldCampaign`).
  `LinearCampaignManager` (`TheLinearCampaignManager`, INI block
  `LinearCampaign`) saves the current linear campaign's name and difficulty;
  how its work divides with the Living World campaign manager is not yet
  reconstructed.
- **Auto-resolve.** `LivingWorldAutoResolveBattle` settles a battle without
  playing it. Its data are the `AutoResolve*` definitions, held in six stores
  (`TheLivingWorldAutoResolveArmorStore` and the weapon, body, leadership,
  combat-chain and handicap stores), and three schedule stores
  (reinforcement, resource bonus, science purchase point bonus).
- **Campaign AI** code lives under `LivingWorldAISupport/` (retail assert
  paths). A `LivingWorldAITemplate` block and
  `TheLivingWorldAITemplateStore` exist and are probably its data; how the
  two connect is not yet reconstructed.
- **Presentation.** `LivingWorldManager` (`TheLivingWorldManager`) is filed
  under `GameClient/LivingWorld` by WorldBuilder's source path, but it also
  holds settings and state that the campaign logic reads and saves (see
  \ref sub_living_world_remastering). `LivingWorldEyeTower` drives the eye
  tower, choosing at random among a list of points. `LivingWorldSound`,
  `LivingWorldAnimObject` and the icon blocks define map sounds, objects and
  icons. The HUD is an Apt movie driven by the `StrategicHUD` code (its
  nested class name comes from a WorldBuilder lead), which binds native
  callbacks for nine panels: end-turn button, new-turn indicator, palantir,
  checklist, stats display, selection details, radial menu, load dialog and
  help box (\ref sub_gui_apt).

## Lifecycle and entry points {#sub_living_world_entry}

| Stage | What happens |
|---|---|
| `GameEngine::init` | registers the Living World subsystems: the six auto-resolve stores; the player-template, AI-template and region-effects stores, `TheLivingWorldManager` and `TheLivingWorldLogic`; later `TheLinearCampaignManager`, `TheLivingWorldCampaignManager`, the building-template store and the three schedule stores. None is given fixed INI paths, so their startup data comes through the subsystem legend (\ref sub_ini). |
| A turn | the logic keeps the current turn phase, and army move requests are validated against it. Map scripts can be limited to some phases (\ref sub_scripting). |
| Battle start | a fought battle starts an RTS game. Outside a linear campaign, each map side whose player name matches a Living World battle entry gets that campaign player's id. |
| Battle end | game logic saves an army summary, collects every player's battle statistics into the current battle, then finds the winning participant through the victory conditions and records the winning side; finally it either ends the session or hands control back to `TheLivingWorldLogic`. |

The turn and battle rows are contracts. The functions behind them are
matched, but their names come from WorldBuilder leads and may change
(\ref page_reading_code).

## How it connects {#sub_living_world_connects}

- **Game logic and players** (\ref sub_gamelogic_map, \ref sub_rts_model):
  a battle is an ordinary game whose players carry a Living World player id,
  which links each game player to its campaign player.
- **Scripts** (\ref sub_scripting): `LIVING_WORLD_*` templates spawn, move
  and despawn campaign armies and bind player, region and army references;
  the `*DELAYED_CARRYOVER*` templates handle carry-over units.
- **Saves** (\ref sub_save_load_crc): regions, region connections, battles,
  buildings, build plots and the logic save through `Snapshot` transfers with
  their own versions, and ids are written through labelled helpers
  (`LivingWorldArmyID`, `LivingWorldBattleID`, `LivingWorldRegionID` and
  others). Retail holds four file-extension strings selected by a mode id
  (`.BfME2Campaign`, `.BfME2Skirmish`, `.BfME2WotR`, `.BfME2WotRMP`); by
  their names the WotR pair belongs to War of the Ring games, but which
  files use them is not yet reconstructed.
- **UI** (\ref sub_gui_apt): the HUD and its panels are Apt movies. The map
  preview, the LAN lobby (a `LanStrategic` mode) and the online shell (an
  `OnlineStrategic` screen) offer the mode; preferences and stats keep the
  chosen strategic scenario and auto-resolve wins and losses.
- **Rendering and audio** (\ref sub_w3d_rendering, \ref sub_audio): map
  visuals are W3D render objects, and map sound definitions come from
  `LivingWorldSound` blocks.

## BFME 2 compared with Zero Hour and BFME 1 {#sub_living_world_compare}

- **Zero Hour** has only a linear `CampaignManager`: a `Campaign` INI block
  listing `Mission`s, and no strategic map.
- **BFME 1** already has a Living World: Open-BFME-1 reconstructs its logic,
  region manager, campaign manager, path finder, eye tower and act parsers.
  Of BFME 2's Living World INI blocks, BFME 1's image registers
  `LivingWorldCampaign`, `LivingWorldRegionCampaign`, `LivingWorldMapInfo`,
  `LivingWorldObject`, `LivingWorldPlayerArmy`, `LivingWorldArmyIcon`,
  `LivingWorldAnimObject` and `LivingWorldSound`.
- **New in BFME 2's block list:** `LivingWorldBuilding`,
  `LivingWorldBuildingIcon`, `LivingWorldBuildPlotIcon`,
  `LivingWorldPlayerTemplate`, `LivingWorldAITemplate`,
  `LivingWorldRegionEffects`, `LinearCampaign`, `StrategicHUD`,
  `ArmySummaryDescription`, the seven `AutoResolve*` blocks and the two
  `LivingWorldAutoResolve*Bonus` schedules.
- **Acts changed.** BFME 2's act table adds `SpawnBuilding` and
  `SetPlayerControlOfArmy`, and lacks BFME 1's `DespawnArmy`,
  `ToggleArmyControl`, `RegionReinforcements`, `MergePlayerArmy` and
  `ModifyArmyEntry`.
- **Region links extended.** BFME 2 keeps BFME 1's `ConnectsTo` name list
  (each name becomes a connection) and adds a `Connection` sub-block that
  gives a `Region` and a list of `DetourPoint`s.

## Modding notes {#sub_living_world_modding}

- **Data-driven:** the INI blocks listed above. An act accepts `EnableRegion`,
  `ForceBattle`, `SpawnArmy`, `MoveArmy`, `SpawnBuilding`,
  `CallActSubroutine`, `JumpToAct`, `MoveCamera`, `SplineCamera`,
  `WorldText`, `AudioEvent`, `EndAct`, `UpdateAnimObject`, `EyeTowerPoints`
  and `SetPlayerControlOfArmy`. A `SpawnArmy` event takes `Icon`, `Banner`,
  `Position`, `InitialRegion`, `PlayerArmy`, `PalantirMovie`, `IconSize`,
  `SpawnForTemplates`, `ScriptingName`, `TooltipStringTag`, `IsCity`,
  `HeroTemplateName`, `MoveSpeed`, `BuildTime`, three `ConstructButton*`
  fields and `SpawnAtActStart`; without `MoveSpeed` it takes a default held
  by the Living World manager (5.0 when no manager exists). Open-BFME-1's
  `docs/ini_schema.md` gives the BFME 1 forms of the shared blocks.
- **Hard-coded:** the act event keywords, the nugget kinds and the HUD's
  panel set. Apt callbacks are bound by name (`_level<n>_On<Panel>Loaded`
  and similar), so a HUD movie that renames a panel loses its native
  handler.
- **Load rules:** a `LivingWorldBuilding` takes a quoted name, is refused if
  parsed before its template store exists, and cannot be redefined. The two
  bonus schedules throw an INI error when read outside the startup load (as
  reconstructed). An auto-resolve bonus table keys its entries by a unique
  `MinCount` and gives `Weapon`, `Armor` and `Experience` as percentages.
- **Lockstep and CRC:** the logic's state transfer also runs under CRC
  passes, skipping some fields there. The eye tower draws its random point
  from the logic random generator, not the client one (BFME 1 does the
  same), so changing how often it runs shifts that generator's sequence
  (\ref page_core_frameworks).
- **Saves:** Living World state is versioned per object, so new saved fields
  need a version bump to keep older saves loading. `GameState`'s
  save-path mapping recognises a `LivingWorldScripts` directory besides the
  map directories.

## Remastering notes {#sub_living_world_remastering}

- **Logic and presentation are separate subsystems, but coupled.** The
  campaign logic reads settings from `TheLivingWorldManager` (for example a
  spawned army's default move speed), calls it when a campaign starts and
  for region effects, and saves its state inside the logic's own save data
  (outside CRC passes).
  Parts of the logic also call the audio manager and the in-game UI
  directly. A replacement map renderer or UI must keep a compatible manager
  and its saved state, or move that state and those settings into the logic
  and put a new save version in place.
- **The HUD is Apt.** A replacement UI either hosts the shipped movies under
  the same callback names or reimplements the nine panels (\ref sub_gui_apt).
- **Files.** Saved map paths go through `GameState`'s portable-path mapping,
  which knows the `LivingWorldScripts` directory; a new data or save layout
  has to extend it (\ref sub_save_load_crc).

## State of the reconstruction {#sub_living_world_state}

Much of this subsystem is still provisional. Many method names,
`LivingWorldLogic`'s above all, are WorldBuilder leads rather than
confirmed. Many bodies sit in address-named staging files under `Common/`,
many files do not link yet, and most Living World classes still have only
per-file private views. Treat the class list above as stable and finer
detail as provisional. For the current state, search
`reverse/functions.csv`, `reverse/link_status.csv` and
`reverse/canonical_classes.csv` for `LivingWorld` and `Strategic`.

## Reading list {#sub_living_world_reading}

- Open-BFME-1: `game/GameEngine/Source/GameLogic/LivingWorld/`,
  `game/GameEngine/Source/GameLogic/System/LivingWorld/`,
  `game/GameEngine/Source/GameClient/LivingWorldEyeTower*.cpp` and
  `docs/ini_schema.md`.
- Zero Hour's linear campaign, for contrast:
  `GeneralsMD/Code/GameEngine/Source/GameClient/System/CampaignManager.cpp`
  under `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/`.
- \ref sub_scripting for the turn-phase gate on map scripts and the
  `LIVING_WORLD_*` templates.
