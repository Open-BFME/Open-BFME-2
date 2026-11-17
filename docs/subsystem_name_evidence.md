# Subsystem names from the retail initSubsystem literals (proposal, nothing landed)

Status: proposal; nothing here is renamed. Checked against master at a4df5d39
(2026-11-17). Every rename below needs `./build.sh`, and the four globals also need
the gate change proposed below. Addresses are 1.06 RVAs unless marked VA (image base
0x00400000).

## Target facts

`GameEngine::init` (0x0022E2E4) calls `initSubsystem<T>(global, AsciiString(literal),
new C, xfer)` 90 times, each as `push literal; call AsciiString ctor; push &global; call
initSubsystem<T>` (at 76 of them an EH-state byte store follows the first push).
GameEngineInit.cpp writes the same 90 literals in the same order. Four globals carry a
name that differs from their literal; the file counts are files under `Code/`:

| current name (data_ledger) | retail literal (VA) | literal push | global | call -> `initSubsystem<T>` |
|---|---|---|---|---|
| `TheParticleSystemManager` (owned, 81 files) | TheFXParticleSystemManager (0x00BE7F88) | 0x0022EB03 | 0x009FDD04 | 0x0022EB12 -> 0x0022A3EC |
| `g_bfmeAptWindowManager` (provisional, 348 files) | TheAptPlayer (0x00BE7CFC) | 0x0022F1C2 | 0x009FE4CC | 0x0022F1D1 -> 0x0022AF59 |
| `TheCampaignManager` (owned, 48 files) | TheLivingWorldCampaignManager (0x00BE7AEC) | 0x0022F80D | 0x00A02D6C | 0x0022F820 -> 0x0022BADC |
| `TheTriggerManager` (owned, 34 files) | TheFireLogicSystem (0x00BE7AC4) | 0x0022F89B | 0x009FEC68 | 0x0022F8AE -> 0x0022BBC6 |

A fifth textual difference is not one: `TheHeroManager` (GameEngineInit.cpp:856) is a
`#define` view of the owned `TheCreateAHeroManager`. None of the four names has a
`name_basis.csv` record.

Other retail data:

- `Data\INI\Default\SubsystemLegend.ini` (ini.big of a 1.06 install, 9,807 bytes)
  documents its key as "this string is keyed to arg 1 in initSubsystem()". It has
  `LoadSubsystem` blocks for TheFXParticleSystemManager, TheLivingWorldCampaignManager
  and TheFireLogicSystem, and one for TheParticleSystemManager that no code registers.
- "TheTriggerManager", "TheCampaignManager" and "TheParticleSystemManager" occur neither
  in game.dat nor in worldbuilder.exe.
- `GameEngine::init` has the same 90 literals, in the same order and call shape, in an
  unprotected copy of the 1.00 game.dat and in RotWK 2.01's game.dat (whose layout the
  1.09 and RotWK 2.02 fan patches keep). RotWK 2.01 has four more such sites in
  another function: TheGlobalLanguageData and TheGameText, twice.

### WorldBuilder asserts spell three of the four variables

worldbuilder.exe (the baseline file) registers the same literals with its own globals,
and its asserts test those globals under the literal's spelling:

| literal | WB literal push -> global (VA) | assert text and function |
|---|---|---|
| TheFireLogicSystem | 0x00DD1F7B -> 0x0225B518 | "!(!TheFireLogicSystem)" in FireLogicSystem::parseINI |
| TheLivingWorldCampaignManager | 0x00DD1E23 -> 0x0225F6FC | "!(TheLivingWorldCampaignManager == 0)" in AptLivingWorldWindow::SelectCampaign; "!(!TheLivingWorldCampaignManager)" in AptMainMenu::OnTutorial and AptStrategicPlayerStatus::AptStrategicPlayerStatus; "TheLivingWorldCampaignManager != NULL" in StrategicInGameUI::GetArmySummary |
| TheAptPlayer | 0x00DD0ECB -> 0x0225AD9C | "TheAptPlayer != NULL", 266 pushes |
| TheFXParticleSystemManager | 0x00DCFE07 -> 0x0225A2E0 | none |

Every push of those assert texts comes within 0x60 bytes after a `cmp [global],0` on the
registered global. An assert expression is EA source text, so for three of the four the
variable's spelling is EA's own. Pairing a WorldBuilder global with the 1.06 global rests
on the shared literal. TheFXParticleSystemManager has no assert and stays an inference.

### Six placeholder classes: the GetSnapshotName literal

The constructor each of these registrations calls installs a Snapshot table whose slot 2
(the `GetSnapshotName` slot, as in `FireLogicSystem`) is a 6-byte `mov eax, literal; ret`:

| placeholder | ctor | Snapshot table (VA) | slot 2 | literal |
|---|---|---|---|---|
| `Rva002A8F24` (registered, 145 files) | 0x002A9725 | 0x00BFDB84 | 0x002A92E4 | SkirmishAIManager |
| `Rva003B923B` | 0x003B90DB | 0x00C1FAF4 | 0x003B9124 | LivingWorldCampaignManager |
| `Rva00426713` | 0x00426713 | 0x00C3C3F8 | 0x00426737 | MissionObjectiveTracker |
| `Rva00355B61` | 0x00355B61 | 0x00C14E04 | 0x00354EF6 | AiOrdersManager |
| `Rva001ED41B` | 0x001ED3C0 | 0x00BDF260 | 0x001EAE69 | LinearCampaignManager |
| `Rva0041497D` | 0x0041497D | 0x00C3A0AC | 0x0041431F | ScoredKillEvaAnnouncerController |
| control: `FireLogicSystem` | 0x00286EC8 | 0x00BFB7AC | 0x00286F81 | FireLogicSystem |

Control: of the ledger's 184 `GetSnapshotName` rows that are such a getter on a named
class, 182 return the class's own name; the other two are
`FXParticleSystem::ParticleSystemInfo` ("FXParticleSystemInfo") and `S3Money` ("Money").
Some of those names were taken from the literal, but the classes named from Zero Hour
(`Eva`, `SidesList`, `PlayerList`, `TerrainLogic`, `Drawable`, `AI`, `GameState`) were
not. The 1.00 and RotWK 2.01 images return the same six literals from slot 2 of a table
their code installs.

## Inferences (hints, not proof)

- TheFXParticleSystemManager names its global by convention only. Zero Hour's 44
  `initSubsystem(TheX, "TheX", ...)` calls all pass the global's own name
  (GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp), and so do 86 of the 90
  here. WorldBuilder's function-name strings call the class
  `FXParticleSystem::ParticleSystemManager`.
- A literal "TheX" is only a hint for a class `X`: Zero Hour's TheAudio is an
  `AudioManager`. The slot-2 literal is the class-level evidence, and under
  docs/naming.md it is still a `string-hint`, so the six class names belong to the
  inferred lane.
- `Rva002872BA` and `Rva00E02D6C`, the declared types of `TheTriggerManager` and
  `TheCampaignManager`, install no table of their own. The objects stored are a
  `FireLogicSystem` and a `Rva003B923B` (GameEngineInit.cpp:842, :840).
- The 37 `RvaXXXXXXXXSubsystem` types in GameEngineInit.cpp are the `T` of each
  `initSubsystem<T>`. They should follow their global's class and not get names of
  their own.

## What `tools/rename.py` refuses today (`--dry-run`)

- `global --name TheTriggerManager --new TheFireLogicSystem --basis canonical:string`
  (or `canonical:assert`): "a real name that name_basis.csv does not record as
  inferred; a canonical name may replace only a placeholder or an inferred name". The
  same for `TheCampaignManager` and `TheParticleSystemManager`. With `--basis inferred`:
  "a real name, not a placeholder". Both canonical kinds also need a string that
  reverse/string_xrefs.tsv ties to a function's own address, and it holds none of the
  90 literals.
- `global --name g_bfmeAptWindowManager`: "no reverse/data_rows.csv row names" it. Its
  data_ledger row is `provisional`, with the alias `TheRva00222A8BTarget`. The owner
  comes first.
- `class --fold Rva003B923B --into LivingWorldCampaignManager` and `--fold Rva00355B61
  --into AiOrdersManager`: refused. The placeholder's rows install the table
  (`??_7Rva003B923B@@6BSubsystemInterface@@@`) and no row is a virtual method of the
  registered header class.
- `class --fold Rva002872BA` and `--fold Rva00E02D6C`: "installs no vftable retail shows
  as its own".

## Proposal: `canonical:subsystem`

A gate change (`Verifier-Change:`), shaped like `canonical:iniblock`:

1. A tool reads game.dat and writes `reverse/subsystem_registrations.tsv`, one row per
   registration in `GameEngine::init`: literal, literal VA, call RVA, global RVA and
   `initSubsystem<T>` RVA. That is 90 rows.
2. `rename.py global --basis canonical:subsystem --evidence 0x<call rva>` accepts only
   when exactly one row has that call, the global's address and a literal equal to the
   new name. Like `iniblock_contradiction`, it may then replace a real name that has no
   canonical record; the "placeholder or inferred" rule stays as it is otherwise.
3. Globals only. Classes stay on the inferred lane.
4. Tests on a fixture tree: accept a placeholder and an unrecorded real name; refuse a
   canonical name, a literal mismatch and a wrong call RVA.

The evidence is split per name on purpose: a maintainer may prefer a narrower route
for the three assert-backed names, or to leave TheFXParticleSystemManager alone.

## What it would unblock (each step needs `./build.sh`)

1. The four global renames; the widest, `TheParticleSystemManager`, touches 81 files.
2. Retyping `TheTriggerManager` to `FireLogicSystem` and `TheCampaignManager` to
   `Rva003B923B`.
3. The six class names, through the inferred lane. `LivingWorldCampaignManager` and
   `AiOrdersManager` already have registered headers, so those two reconcile a
   placeholder with an existing class. The other four names are already spelled in
   the tree too, as unregistered views or forward declarations.
4. The owner of `g_bfmeAptWindowManager` (type `BfmeAptWindowManager`, beside the
   registered `AptPlayer` class).
