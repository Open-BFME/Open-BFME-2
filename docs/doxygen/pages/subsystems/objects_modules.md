# Game objects and their modules {#sub_objects_modules}

This subsystem is the simulated game world at the level of single
entities: every unit, hero, horde, building and projectile is an `Object`.
An `Object` carries identity, position, team and status, but nearly all of
its behaviour lives in its modules, a null-terminated array built from its
template. Each module type is a C++ class that the module factory knows by
name, and each module instance is configured by a module data object that
the INI loader fills from the `Object` block of a thing template. The
same few base classes (update, body, contain, die, damage, collide, create,
special power and upgrade modules) therefore describe hundreds of unit
types, which is why most game rules can be changed in data.

Its API group is \ref grp_objects_modules. Templates and the module
factory are on \ref sub_rts_model; weapons, armor, upgrades and special
powers as definitions are on \ref page_core_frameworks.

## Where it lives {#sub_objects_modules_where}

All paths are under `Code/GameEngine/Source/GameLogic/`.

| Path | What is there |
|---|---|
| `Object/` (top level) | `Object` itself, weapons and weapon sets, armor, locomotors, object creation lists, the experience and firing trackers, ghost objects and the Create-a-Hero system; also the partition manager, which \ref sub_gamelogic_map covers |
| `Object/Update/` | update modules, the largest family: `AIUpdateInterface` and its `Update/AIUpdate/` subclasses (`DozerAIUpdate`, `WorkerAIUpdate`, `HordeAIUpdate`, `GiantBirdAIUpdate` and others), `SpecialAbilityUpdate`, `ProductionUpdate`, `StealthUpdate`, `StructureToppleUpdate`, `Update/DockUpdate/` |
| `Object/Behavior/` | modules that are not one plain family, often several at once: `SlowDeathBehavior`, `SpawnBehavior`, `BridgeBehavior`, `CastleBehavior`, `GateOpenAndCloseBehavior`, `PhysicsBehavior` |
| `Object/Body/` | body modules (health and damage state): `ActiveBody`, `StructureBody`, `ImmortalBody`, `HighlanderBody`, `DetachableRiderBody` |
| `Object/Contain/` | contain modules: `OpenContain`, `GarrisonContain`, `TransportContain`, `TunnelContain`, `CaveContain`, `SiegeEngineContain`; the horde family (`HordeContain` and its relatives; most files sit directly in `Contain/`, though retail's assert paths put the ones they name in `Contain/HordeContain/`) |
| `Object/Die/`, `Damage/`, `Collide/`, `Create/` | event modules: `FXListDie`, `CreateCrateDie`, `CrushDie`; `TransitionDamageFX`, `BoneFXDamage`, `CallHelpOnDamage`; the crate collides, `SquishCollide`, `FireWeaponCollide`; `GrantUpgradeCreate`, `SupplyCenterCreate` |
| `Object/SpecialPower/`, `Upgrade/` | `SpecialPowerModule` and its subclasses (`OCLSpecialPower`, `ElvenWoodSpecialPower` and many more); upgrade modules (`ArmorUpgrade`, `CommandSetUpgrade`, `SubObjectsUpgrade`) |
| `Object/Helper/` | built-in helper modules that `Object::Object` creates without INI (some only for certain templates): `ObjectSMCHelper`, `ObjectRecoveryHelper`, `ObjectRepulsorHelper`, `ObjectDefectionHelper`, `ObjectWeaponStatusHelper`; the firing tracker, created the same way, is in `Object/` itself |
| `Object/WeaponEffects/` | weapon effect nuggets |
| `Module/`, `Thing/` | a few stray rows, mostly memory-pool name keys; neither directory is in Zero Hour's layout or in retail's assert paths, so these rows may move |

Retail assert paths confirm the original layout, including
`Contain/HordeContain/`, `Update/AIUpdate/`, `Update/DockUpdate/` and
`WeaponEffects/`. Most of the several thousand source files here hold one
or a few functions. `reverse/tu_map.csv` proposes the original translation
units they belong to (a few hundred, such as `Object.cpp` or
`OpenContain.cpp`); many of those assignments are still proposals and some
rows have none yet, so search by class or function name
(\ref page_reading_code).

## Key pieces {#sub_objects_modules_pieces}

- **Object.** `Object` derives from `Thing`. It holds its template, team,
  status and disabled flags, transform and geometry, the module array, and
  pointers it caches while building that array: the body, the contain
  module, the AI update interface and the physics module.
- **Behavior modules.** Every logic module is a `BehaviorModule`. Its typed
  queries (`getBody`, `getContain`, `getAIUpdateInterface` and others)
  return an interface or null, so one class can play several roles:
  `SlowDeathBehavior`, for example, is registered with both the update and
  the die interface. Each module keeps a pointer to its object and to its
  module data; the module data's tag name (the `ModuleTag_...` in INI)
  identifies the module within its object.
- **Module data.** A module data class builds its INI field table in a
  static `buildFieldParse`, starting from its base class's table.
  `HordeContainModuleData`, for example, chains onto
  `TransportContainModuleData`, so a horde accepts every transport field
  plus its own (\ref sub_ini).
- **Update modules.** `UpdateModule` adds a wake frame, a slot in one of
  `GameLogic`'s schedule lists and `UpdateModule::getUpdatePhase`, which
  picks the list (by default list 2, which runs in logic phase 5).
  `update` returns how many logic frames to sleep.
- **Helper modules.** `Object::Object` creates up to seven built-in
  modules before the template's own, under fixed tags such as
  `ModuleTag_SMCHelper`, `ModuleTag_RecoveryHelper`,
  `ModuleTag_DefectionHelper` and `ModuleTag_FiringTrackerHelper`; some
  only when the template or the AI settings call for them.
- **Hordes.** A horde is one `Object` whose contain module, `HordeContain`
  or a subclass, holds the individual soldiers as contained objects. It
  derives from the transport container, reads per-rank entries, a
  banner-carrier position and split results from its INI block, can
  compute the average position of its members, and picks a melee
  behaviour by name. Related containers cover siege engines, garrisoned
  hordes, horse hordes and the "slaughter" containers.

## Lifecycle {#sub_objects_modules_lifecycle}

1. **Create.** The thing factory (Zero Hour: `ThingFactory::newObject`)
   picks a build variation with the logic random generator and has
   `GameLogic::friend_createObject` construct the object. `Object::Object`
   resolves the template's final override, creates the helper modules,
   then each module the template lists through `ModuleFactory::newModule`,
   and calls every module's `onObjectCreated`. Near the end it adds the
   object to the radar and calls `GameLogic::registerObject`. The factory
   then calls each create module's `onCreate`.
2. **Schedule.** `GameLogic::registerObject` links the object into the
   object list and the id lookup, and puts each update module either in
   the list its `getUpdatePhase` names or, if it sleeps forever, in the
   sleeping list. A module with no wake frame yet is due at once.
3. **Update.** Logic phases 3 to 6 run the four lists (list 0 split over
   phases 3 and 4, lists 1 and 2 in phase 5, list 3 in phase 6). A module
   runs when its wake frame has come; on a disabled object it runs only if
   `getDisabledTypesToProcess` covers one of the object's disabled types,
   and the default covers none. On an object that
   `GameLogic::destroyObject` has already marked, a due module is not run
   but put to sleep forever. The result becomes the next wake frame, and
   modules that sleep forever move to the sleeping list.
   `UpdateModule::setWakeFrame` and `GameLogic::friend_awakenUpdateModule`
   reschedule a module from outside its own update, moving a sleeping one
   back into its list. \ref page_frame_loop has the whole phase table.
4. **Events.** Damage enters through `Object::attemptDamage`;
   `Object::onDie` walks the die modules; contain and collide modules react
   to entering, leaving and contact. `Object::updateUpgradeModules` offers
   each upgrade module that has not yet fired the upgrades its object can
   use, and `UpgradeMux::attemptUpgrade` applies the upgrade when the
   module's `wouldUpgrade` accepts them.
5. **Destroy.** `GameLogic::destroyObject` calls every destroy interface's
   `onDestroy`, marks the object, stops its AI path, queues it for
   deletion and calls `Object::onDestroy`. The queue is emptied in logic
   phase 5.
6. **Save and checksum.** `Object::xfer` writes a version, the template
   name and id, the object's own state, a module count and each module as
   a block named `BehaviorModule` keyed by its tag, followed by the rest
   of the object's state, among it the experience tracker and the
   special-power bits. Many of these trailing fields were added in later
   versions of the block and are read only when the saved version has
   them. On load a block whose tag the object no longer has is skipped.
   `GameLogic::getCRC` normally runs the objects through the same
   function with a checksum writer. A
   reduced "light CRC" mode sends only a subset of the object's state
   (among it the template name and id, status, upgrades, health, producer
   and builder, AI goal and weapons), skips the transform, and returns
   before the team, drawable and module blocks. The periodic multiplayer
   checksum that `GameLogic::update` sends uses this light mode unless the
   deep-CRC switch is on (\ref sub_save_load_crc).

## How it connects {#sub_objects_modules_connects}

- **Templates** (\ref sub_rts_model): thing templates list the modules,
  the module factory creates them, and players and teams own objects.
- **Game logic** (\ref sub_gamelogic_map): `GameLogic` creates, schedules,
  updates and destroys objects; the partition manager answers spatial
  queries.
- **AI** (\ref sub_ai_pathfinding): `AIUpdateInterface` and its subclasses
  run the AI state machines and drive locomotors through the pathfinder.
- **Client** (\ref sub_gameclient): each object is bound to a client
  `Drawable` (`Object::friend_bindToDrawable`), which draws it. Zero Hour:
  the drawable owns the draw and client-update modules.
- **Scripts** (\ref sub_scripting): map scripts and Lua query and command
  objects.
- **Saving and memory** (\ref sub_save_load_crc, \ref sub_memory): objects
  and modules are snapshots, and module classes are allocated from
  per-class named memory pools.

## BFME 2 and Zero Hour {#sub_objects_modules_zh}

The object and module architecture is Zero Hour's (`GameLogic/Object/`
and `Include/GameLogic/Module/` in the reference tree), reached through
BFME 1. Differences seen in BFME 2's bodies:

- **Scheduler.** Zero Hour keeps every update module in one priority
  queue (`m_sleepyUpdates`), ordered by wake frame and phase, and packs the
  phase into the low two bits of the wake frame. BFME 2, like BFME 1, keeps
  four phase lists plus a separate list of modules that sleep forever, and
  stores frame, list index and phase separately.
- **Helpers.** Zero Hour's object gets status-damage, subdual-damage and
  temporary-weapon-bonus helpers; BFME 2's constructor creates none of
  those and adds recovery and guarding helpers.
- **Disabled types.** BFME 2's disabled mask has 11 types; Zero Hour has 13.
- **Damage.** BFME 2's `Object::attemptDamage` can queue the damage on the
  object instead of applying it at once. Which damage takes that path,
  and where the queue is drained, is still being traced.
- **Upgrades.** Besides the player's and the object's own upgrades,
  BFME 2, like BFME 1, also offers an object's upgrade modules the
  upgrades of a linked castle object.
- **New module families.** None of these are in Zero Hour: the horde
  containers, castles and gates, detachable riders, the emotion tracker,
  the One Ring penalty, large-group bonus and audio, and attribute-modifier
  auras. All of them already exist in the Open-BFME-1 tree; Create-a-Hero
  has no counterpart there.
- **Rate.** Module timers count 5 Hz logic frames, against Zero Hour's 30.

## Modding notes {#sub_objects_modules_modding}

- **Data-driven:** which modules a unit has, their tags and every field in
  their module data, including timings, weapons, horde ranks and melee
  behaviour, and upgrade triggers. \ref page_modding_modules has the INI
  rules.
- **Hard-coded:** the module classes themselves and each class's update
  list; the helper modules; the set of disabled types; and fixed name
  tables, such as the horde melee behaviours `Swarm`, `WaitForLeader`,
  `HoldGround` and `Amoeba`. `Object::Object` also looks up a few modules
  by their registered name (`PhysicsBehavior`, `StealthUpdate`,
  `SquishCollide`, `EmotionTrackerUpdate`) to cache them or set flags. New
  behaviour needs new code.
- **Save games:** module state is saved under its tag. Renaming a tag or
  removing a module makes old saves skip that state; a new module starts
  from its defaults. Each class versions its own block. `Object`'s own
  block grows the same way: new fields are appended and gated on its
  version number. On load, the shared version check throws on a block
  whose saved version is newer than the code supports or older than the
  earliest version it still accepts.
- **Multiplayer:** modules run in the logic, so every machine must have
  identical data, and any code change to a module must be identical too.
  Module code that needs randomness must use the logic random generator;
  objects are part of the logic CRC (\ref page_modding_rules,
  \ref sub_network).

## Remastering notes {#sub_objects_modules_remaster}

- The subsystem has no platform code of its own (no Direct3D or Win32
  calls), but it is not isolated from the client. Besides the bound
  `Drawable` and the audio manager (`TheAudio`), code in this subsystem
  calls client-side singletons directly: `TheInGameUI`,
  `TheParticleSystemManager`, `TheGameClient`, `TheTacticalView`,
  `TheEva`, and `TheDisplay`, which the partition manager uses for the
  shroud. Modules also trigger client FX lists. A replacement
  renderer or audio backend plugs in behind those client interfaces, not
  in module code (\ref sub_gameclient, \ref page_architecture_seams).
- Timers and sleeps are in logic frames, and INI durations are converted
  to frames at load. A different logic rate means re-deriving those
  conversions and breaks lockstep with retail clients
  (\ref page_frame_loop).
- No canonical header declares `Object` or the module base classes yet.
  Many source files declare their own partial view with the members they
  use, laid out for the 32-bit retail build, and others include one of
  several competing shim headers under `reference/shims/`. A port that
  changes pointer size or adds fields needs those reconciled into one set
  of headers first.

## State of the reconstruction {#sub_objects_modules_state}

This is one of the largest blocks of game code in the ledger. The ledger
records only byte-verified rows, so what varies is naming: most of its
bytes carry real names, and a substantial share, especially in the contain
modules and the top-level `Object` files, is still address-named. It is
also among the most actively edited directories, so expect names, private
views and file boundaries to keep changing. Class pages wait until
`Object` and the module bases have canonical headers. To list the rows,
run `rg ',Code/GameEngine/Source/GameLogic/Object/' reverse/functions.csv`.

## Reading list {#sub_objects_modules_reading}

- Zero Hour: `Code/GameEngine/Source/GameLogic/Object/` and
  `Code/GameEngine/Include/GameLogic/` (start with
  `Include/GameLogic/Object.h`, then `Module/BehaviorModule.h` and
  `Module/UpdateModule.h`) under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/`.
- BFME 1: `reference/open-bfme-1/docs/bfme_layouts.md` on how BFME moved
  class members from their Zero Hour offsets.
- `reverse/module_factory_registrations.csv`: every registered module
  name with its type and interface mask.
