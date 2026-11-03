### LINK-009: split-identity destructors; the alias route needs an admission path

**Status: The six original units link (census `73061d9452`); the remaining
split pairs are blocked on an identity merge or a maintainer admission decision.
Updated: 2026-10-27; inspected revision: `d16a31e4dc`.**

- **Evidence / scope:** constructors matched under one class name whose retail
  destructor is matched under a second, address-derived name, so the unit's
  `??1X` stays unresolved. Six units are affected, 661 authored bytes:
  GameSpyInfoCtor.cpp 280 B (`??1GameSpyInfo`), ExperienceTrackerAutoResolve.cpp
  113 B, Rva0022BD9ASubsystem.cpp 67 B, Rva0022C0CDSubsystemCtor.cpp 81 B,
  Rva0022BE0FSubsystemCtor.cpp 65 B and Rva0022BD25SubsystemCtor.cpp 55 B.
  Retail proves each pair: the unit's constructor installs a vtable whose slot 0
  deleting destructor calls the matched body, and two pairs are additionally
  anchored by address adjacency (`0x0041EFFF` + 67 = `0x0041F042`;
  `0x0041F913` + 55 = `0x0041F94A`). Banked detail and the per-class table:
  [split-identity handoff](../../reverse/attempt_support/split-identity-dtors-20261024/readme.md).
- **Completed:** a full-form `/alternatename` trial on all six units re-verified
  28/28 rows and linked `LINKED 0 -> 661` bytes at census index 2026-10-24 10:28
  (`2fbdec0868`). It was reverted: the current rules forbid adding
  `/alternatename` by hand, hatch counts may rise only through an admitted tool,
  and the counter's own `--allow`/`--admit` is hand-adding. No admission tool
  covers this hatch, so the evidence is preserved as an attempt, not a repair.
- **Completed (2026-10-26, agent b1):** a placeholder-to-placeholder pair needs no
  name decision. `Rva000647B5Ctor.cpp`'s ctor 0x000647B5 and the rowed dtor
  0x000647D4 store the same vptrs (0xBC5A5C/0xBC5A24; slot 0 is
  `??_GRva000647D4` 0x00064809), so the ctor class became `Rva000647D4` on
  `LocomotorDerivedDtors.cpp`'s view (two alternatenames dropped): link_check
  0 -> 25 B LINKS, factory 0x00042036 and the dtor unit still LINK. Two more
  pairs found, not applied: `WeaponStore` (ctor 0x002CC20E, table 0x00C02114,
  dtor `Rva002CCD56` 0x002CCD56; Weapon.cpp's present-unmatched `~WeaponStore`
  would also go; links 0 -> 47 B, patch kept outside the tree) needs the same
  placeholder-to-real admission as LINK-063; `Rva006DE1A0Finish.cpp` (table
  0x00CEB150 slot 14 is `??_GRva006DE2B0`) needs its four caller units and the
  `??3Rva006DE1A0` ICF pin moved. `T1Base_005F3750` is not a pair: its
  `??_G` 0x003AE8D5 is ICF-shared with a different class (table 0x00C1D55C).
- **Remaining / next check:** choose an admissible route. Preferred is an
  identity merge of the placeholder destructor class into the class the
  constructor/vtable prove, sharing one class view among every unit that emits
  the vtable; that is still blocked on `rename.py` support for a
  placeholder-to-real merge and on the class-view/COMDAT cases recorded in the
  handoff (GameLogic/SubsystemInterface slots, the ExperienceTrackerXfer vtable
  COMDAT, BaseHeightMapRenderObjClass and GlobalWeatherSystem split identities). Otherwise a maintainer decision is needed for
  a scoped admission path. Do not repeat the unchanged alias trial.
- **Clearance / census confirmation:** pending; no census change is claimed and
  the alias trial was not published.

**GlobalWeather current-owner audit (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`):** `GlobalWeatherSystemCtorDeferred.cpp` still has four unresolved names. Native primary table RVA 0x0080C734 slot zero reaches deleting destructor 0x0031861B, which calls the complete 110-byte destructor at 0x00318637. Both, plus the secondary thunk at 0x00318613, now have rows in `Code/GameEngine/Source/Common/Rva00318637Dtor.cpp` under `Rva00318637`; this is an existing split identity, not a needed destructor match. The constructor's element callbacks reach the ten-byte `IPEnumeration` constructor at 0x00318329 and the counted-reference destructor at 0x0010F149. The native cleanup at 0x0077A838 destroys member +0x20 through 0x0048BA39 (the rowed AsciiString/StringBase cleanup). Preserve their distinct lifetimes and resolve the identities through the naming lane. No source change, alias trial or pin was made. Raw proof: `build/c136-logic/weather-native.log`, `weather-owners.log`, `native-references.log` and the full report. Clearance and census confirmation remain pending.

**GlobalWeather string-member repair (2026-10-27, inspected `818311dee7`):**
[The bounded lifetime repair](../../reverse/attempt_support/weather-string-lifetime-20261027/readme.md)
replaces the constructor's opaque +0x20 handle with the existing AsciiString
type already used by its complete destructor. All five rows and the parent
EH graph remain exact. Against index `73061d9452`, the ordinary preview's
unresolved names drop from four to three, with no new COMDAT/selected-copy
blocker and no linked-byte gain. All 18 retained external COMDATs have identical
relocation-aware digests. WeatherData callback and complete-destructor identities
remain prerequisites. Generated unwind 0x0077A838 is held by another worker;
its row is untouched. Census confirmation remains pending.

**WeatherData constructor follow-up (2026-11-01, base97c10ba4d8):** native
array callback318329 and HasLightning/parseBool at field offset4 prove the
8-byte view has a bool. Its clean10-byte constructor now lives beside the
existing parent through add_match --icf-owner IPEnumeration:7/7 whole-source
rows and all parent EH cleanups pass; bounded strict preparation also passes.
No pin/hatch/path move or unique coverage is added. Index0d24c60eef preview
drops the constructor unresolved name, leaving only WeatherData's destructor
and GlobalWeatherSystem's split destructor identity. IPEnumeration stays LINKS10;
weather still0, so no linking gain or family clearance. The shared destructor
was held and is untouched. Carry changed provider consumers into the next census.
Evidence: `reverse/attempt_support/weather-data-constructor-link-20261101/readme.md`.
The source commit passes normal hooks (7/7; parent EH EXACT1). TU ownership's
A1 second-source finding at318329 remains visible; the ICF row does not retire
source-ownership debt or re-prove the older donor-derived IPEnumeration name.
The ordinary batch audit is INCONCLUSIVE (older0d24c60eef index; first strict
consumer receipt missing in Common/0CreateAHeroManager21FE49.cpp). Carry this
provider and its transitive consumer scope to the scheduled census.

**Native owner/table prerequisite (2026-11-01, base60e005e3d2):** constructor
and complete destructor install the same primary14-slot and Snapshot4-slot
native tables C0C734/C0C724. A private owner rename plus the existing14-slot
subsystem shim preserves the110B destructor and all eight family byte sequences
(one adjusted deleting-helper reference unresolved), but its tables and the
current constructor both replace six concrete native entries by __purecall.
Do not merge those agreeing incomplete views: primary slots1/9/10 must reach
B3FD0/3186A5/318768; Snapshot slots1/2/3 reach3187A0/31860D/3189AD. Existing
providers need real owner/override reconciliation; the3187A0 thunk adjusts-C
and forwards3184B8. The class-merge engine limitation is only one prerequisite,
not a reason to admit the incomplete table. Unchanged controls pass15/15;
old destructor preview LINKS146 and ctor stays0/U2. No Code/row/pin change or
clearance. [Native tables, emitted-table comparison and rejected candidate](../../reverse/attempt_support/globalweather-owner-native-20261101/readme.md).
**Reset callback follow-up:** a dedicated one-member view for3186A5 can join
GlobalWeatherSystem and become virtual with pad10->C; its private73B body is
exact/unresolved=false and emits no weather vtable. Unchanged control1/1 passes.
The native primary-slot owner operation is missing from rename.py; generic
naming approval/collision rules remain correct and untouched. Bank the candidate
until a narrowly proven mechanical identity operation exists, then apply the
normal virtual respell and constructor reset-slot repair with full audits.
[Candidate and admission boundary](../../reverse/attempt_support/weather-reset-owner-20261101/readme.md).

**Current-state audit (2026-10-27, seat halilkkaya-lk2, inspected `d16a31e4dc`, index `73061d9452`):**

- **Completed (census-confirmed):** the six units in the evidence above link in
  the census (`link_check.py`: 661 B, 668 B with current objects). 878194d833
  and 59267bce0d bound them; the bindings now come from respelled rows, not
  aliases. Of the wider handoff table, DozerAIUpdateCtor (8,003 B),
  WorkerAIUpdateCtor (4,736 B), BaseHeightMapConstructor (1,166 B) and
  ExperienceTrackerXfer_ExperienceTracker (208 B) also link. GameLogicInit.cpp
  links with current objects (0 -> 28,191 B, repaired by e40e476d69 through
  theLogicRandomLogFile, not a destructor merge) and awaits the census.
  Rva00415704Ctor.cpp links with current objects (0 -> 90 B, a83d26d19a).
- **Remaining, each needing a class merge that `rename.py class` refuses (it
  rejects a new name that already exists; `rename.py function` refuses special
  members; `add_match.py --replace-rva` takes scaffold rows only):**
  - `GlobalWeatherSystemCtorDeferred.cpp` (133 B): `??1GlobalWeatherSystem` is
    `??1Rva00318637` (table 0x00C0C734 slot 0 0x0031861B calls 0x00318637).
    Its other two names, `??0WeatherData`/`??1WeatherData`, are the ehvec
    callbacks 0x00318329 (rowed as the byte-identical `??0IPEnumeration`, which
    sits in the GlobalWeatherSystem block) and 0x0010F149; inline WWLib-style
    member bodies there would emit them without rows.
  - `WeaponStore.cpp` (47 B): `??1Rva002CCD56` is WeaponStore's destructor
    (table 0x00C02114 slot 0 0x002CD5E0); Weapon.cpp also defines a strong
    non-retail `??1WeaponStore@@UAE@XZ` and a second `??_7WeaponStore`, and
    WeaponStore.cpp declares the destructor protected with a fake
    `Rva002CC20EBase::unused` slot, so three views need one table.
  - `Rva006DE1A0Finish.cpp` (117 B): tables 0x00CEA228/0x00CEB150 share slot 0
    0x006DCAC0 and the unwind funclet 0x007A8DA0 jumps to 0x006D6340; an Apt
    class-family reconciliation, not a single pair.
  - New pair, `Scripts.cpp` (512 B): `??1OrCondition@@MAE@XZ` is
    `??1Rva003B262E@@MAE@XZ` (0x003B262E stores 0x00C1F3F4, the table the
    matched `??0OrCondition@@QAE@XZ` installs; slot 0 is 0x003B331E, which
    calls it). OrConditionCtor.cpp papers over the split with an
    `/alternatename`. Scripts.cpp has a second, independent blocker: its
    BFME 1 MemoryPoolObject view gives `??_7OrCondition@@6B@` a second slot
    (getObjectMemoryPool) that retail's one-slot table lacks, and all 13
    `??_7MemoryPoolObject@@6B@` copies share that two-slot shape.
  - New pair, `MultiplayerSettingsCtor.cpp` (159 B): the ledger rows
    `??1MultiplayerSettings@@QAE@XZ` (0x00381293) and
    `??_GMultiplayerSettings@@QAEPAXI@Z` (0x00381277) are non-virtual, but
    table 0x00C191B8, which the constructor installs, has 0x00381277 in slot 0
    and SubsystemSlot's destructor 0x00226CEB deletes the object through
    `call [eax]`: the destructor is virtual (UAE). The constructor's
    non-virtual SubsystemInterface view leaves `??1SubsystemInterface@@QAE@XZ`
    unresolved and stores the table through the address global `g_00C191B8`.
    Retail's 14 slots match subsystem_interface.h with init/reset/update
    overridden by empty bodies (0x000B3FD0).
- **Next check:** a maintainer decision or a `rename.py` merge mode for
  placeholder-to-real class merges unblocks GlobalWeather, WeaponStore and
  OrCondition; MultiplayerSettings needs the QAE -> UAE respell of its two rows
  (a signature change rename.py cannot express) plus the 14-slot view in the
  constructor. No source change, alias or pin was landed by this audit.

**MultiplayerSettings implicit-lifetime prerequisite (2026-10-30):** the
constructor adopts the seed's existing complete fourteen-slot subsystem
interface and real STL map view. Removing the explicit destructor declaration
lets the compiler emit the native virtual lifetime without a derived-vptr store.
Strict constructor preparation passes 1/1 and its ordinary preview clears
159 bytes against `12b9e7a7c0`. Private constructor/complete/delete bodies
159/83/28 are fully resolved exact, and both EH parents are EXACT. The old
non-virtual rows still need separately reviewable withdrawal and proper UAE
readmission, preserving all four destructor companions, plus supported TU
composition and outgoing consumer checks. This is not canonical-header adoption
or a census gain. [Native facts and scope](../../reverse/attempt_support/multiplayer-implicit-lifetime-20261030/readme.md).

The supported constructor merge now preserves all sixteen seed/constructor
rows and the data row; four EH graphs are EXACT. One approved donor file is
absorbed, with only the tool's one-row source repoint in the TU map. The actual
combined object retains exact native 159/83/28 lifetime bodies and both parent
EH graphs. Other allocator/template donors and the iterator-increment selection
refusal remain separate. The ready constructor move publishes with all existing
coverage retained; the old QAE lifetime admissions and their four companions
remain a separate correction. The path audit updates the live dependent-name
test to follow the constructor's ledger owner (regression passes), preserving
historical path mentions. Strict five-source preparation passes 404 rows and
three data rows, with 187 EXACT EH graphs and 5/5 LINKS. The seed's 746 authored
bytes include only 159 newly cleared by this repair; no historical 137-byte
difference is credited. The existing color-constructor AsciiString clear warning
has unchanged caller bytes/relocations and remains separate. Full consumer and
census confirmation remain pending.

The outgoing constructor-move audit additionally prepares GameEngineInit and
coord2d (154 rows plus one data row), covering 558 strict rows and four data
rows across seven sources in total. It remains INCONCLUSIVE on the older
index and missing current `Common/0CreateAHeroManager21FE49.cpp` consumer.
Carry the moved constructor, complete provider cohort and broader consumers
into the next scheduled census; no full-image loss/selection claim is made.

The constructor move lands at `33564ef244`. Its follow-up separately withdraws
the old QAE complete/deleting destructor and all four compiler companions
(six rows, 151 bytes), with tombstones and removal of their orphan views.
All sixteen retained approved-TU rows and the data row still verify. The same
TU already emits the correct UAE operations with exact parent EH graphs;
normal readmission must restore every withdrawn byte before this next batch
is published.

The separate lifetime correction now restores all six rows and 151 bytes through
normal admissions, one verified body per commit, under the correct UAE parent
in the approved seed. Native EH data proves all four companion placements.
The two obsolete lifetime sources are removed; supported metadata synchronization
repoints six source-column fields without changing TU approvals. Strict seven-
source preparation passes 564 rows and four data rows, with EXACT 191 EH graphs;
the bounded preview retains 7/7 LINKS for 33,891 authored bytes. This is source
recovery and identity repair with unchanged unique coverage, not a census gain.
The complete outgoing path audit finds only intentional historical mentions of
the retired paths. Broader consumer/census confirmation and the inherited
color-constructor binding warning remain open as recorded in the handoff.

**Multiplayer local optimization-debt follow-up (2026-10-30):** remove the
artificial unused array anchor and all four obsolete optimization overrides.
Private before/after verification preserves all 22 rows, five EXACT parent EH
graphs and all 30 retained external code bodies/relocations; only the unneeded
local vector-constructor iterator copy disappears. Its rowed native ATL owner
at `00001423/34` remains exact. Strict two-source preparation passes 23 rows and
one data row, retaining 2/2 LINKS for 891 authored bytes against `e1f7c1dd18`.
The owning counter retires exactly four pragma keys; unique coverage is kept.
Full consumer/census confirmation and the unchanged inherited binding warning
remain separate. [Scope and proof](../../reverse/attempt_support/multiplayer-vci-debt-20261030/readme.md).

**Multiplayer seed prerequisite (2026-10-28, inspected `d5843cec`, index
`d92e7e6635`):** MultiplayerSettings.cpp now uses the target 0xC4 layout,
complete 0x40-byte colors and native INI tables. Its two rows and singleton
remain exact; ordinary preview stays LINKS/97 bytes. Independent complete-table
and provider checks preserve the selected bindings, including the LINK-042
out-of-line pair-copy contract. The lifetime ABI repair, all three cleanup
parents (including newly rehomed 0x0077F308) and approved-TU composition remain
pending; this is not a census gain or clearance
of the constructor obstacle. [Evidence and remaining work](../../reverse/attempt_support/multiplayer-settings-layout-20261028.md).

**WeaponStore obsolete donor cleanup (2026-10-29, base `2f86c49f4552`):**
Weapon.cpp no longer emits its unrowed 145-byte Zero Hour destructor or its
24-byte table. One present-unmatched hatch retires; 24 scoped function rows,
ten data rows and the retail destructor's EH graph remain exact. With the
existing parseClearNuggets provider included, the six-unit preview preserves
1,045 authored LINKS bytes against index `85f6b7f40c`. The constructor's table
conflict disappears, but its protected destructor and fake base unused slot
remain unresolved. The native class/interface and admitted identity merge
prerequisites stay open; full consumer and census confirmation remain pending.
[Scope and provider audit](../../reverse/attempt_support/weaponstore-obsolete-destructor-20261029-codex4.md).
