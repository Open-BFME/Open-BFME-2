# P32: LivingWorldRegionEffects initializer order, TU evidence and the approval gap (2026-11-07)

Merge lane 2 (seat5), route 1 of crash-triage packet P32. Base 7fd11cc6a2. Nothing in the map,
ledger or sources changed. The map figures come from `tu_map` rebuilt in memory, and the signals
from `tools/tu_evidence.py --write/--validate`. Addresses are RVAs (image base 0x00400000).

## Answer

The initializers, the table fill and the block registration belong to one retail object: the
LivingWorldRegionEffects code at 0x003EE84A..0x003EF5DA. A merge would fix the boot order, but no
supported route can approve any of the initializers. `tools/tu_evidence.py`'s I signal (the
`.CRT$XCU` order) predicts nothing, and no other signal reaches `.text$yc`. tu_skeleton moves only
approved rows, so steps 2 and 3 are blocked on tooling.

## Target facts

- The dynamic initializers 0x007AF8CD..0x007AFC25 form one contiguous run, with other units'
  initializers on both sides:
  - 0x007AF8CD constructs the global at 0x00E02E50 and registers its atexit;
  - 0x007AF8E3..0x007AF9BB are the nine 27-byte AsciiString constructors for 0x00E02E64..0x00E02E84
    ('BordersEffect' .. 'UnifiedEffect'), each with an atexit;
  - 0x007AF9D6 is `initializeRegionEffectFields` (571 B), which fills table entries
    0x00DC1518..0x00DC15B4;
  - 0x007AFC11 (21 B) does `mov eax,[0x00DDF578]; mov [0x00DC14B8],eax;
    mov [0x00DDF578],0x00DC14B8`, linking the BlockParse node 0x00DC14B8 onto
    theBlockParseList. Per packet P32, that node is the `LivingWorldRegionEffects` block
    (table 0x00DC14BC -> parseLivingWorldRegionEffectsDefinition 0x003EF467).
- The .bss globals 0x00E02E50 and 0x00E02E64..0x00E02E84 are adjacent, so they belong to one
  object's data.
- In the map rebuilt in memory, 0x003EE84A..0x003EF2FF is approved as the provisional TU
  `Code/GameEngine/Source/Common/LivingWorldRegionEffectsManager.cpp` (N group; the
  LivingWorldRegionEffectsManager ctor is at 0x003EEAFB). Most rows of Rva003EE900Forward.cpp
  and Rva003EE980Forward.cpp are already in it. 0x003EF323..0x003EF5DA have no TU, including
  the parser 0x003EF467 and Rva0022B0B8Subsystem's ctor 0x003EF5A3 and dtor 0x003EF36E.
- None of the eleven initializers (0x007AF8CD..0x007AFC11) has a TU. `tu_evidence.py --source`
  emits no signal for Rva003EE746ColorProvider.cpp, Rva003EE900Forward.cpp or Rva003EE980Forward.cpp.

## Donor fact (WorldBuilder; names a file, proves no placement)

- worldbuilder.exe pushes `C:\Projects\bfme2\Code\GameEngine\Source\GameClient\LivingWorld\LivingWorldRegionEffectsManager.cpp`
  (offset 0x01AB8FF0; `reverse/worldbuilder_source_paths.csv`). `name_lane.py consolidate`
  (build/consolidation/seat5_p32) lists it as a retail path. The map's provisional TU spells it
  under `Common/`, which is the naming hint of the files' current directory.

## Structural inference

- MSVC emits a TU's dynamic initializers in definition order and lists them in `.CRT$XCU` in
  object order. So once the strings, `initializeRegionEffectFields` and the block link are one
  unit (in that order), the image runs the strings before the table fill, as retail does.
  Today they are three objects sorted by path.

## The gap (for a tooling seat)

1. **No signal places a `.CRT$XCU` initializer.** `tu_evidence.py --validate` at this base shows
   I with 0 predictions of 9,917 tests, proposal-only. Its docstring says so: "I still predicts
   nothing: its 1,166 `.CRT$XCU` functions sit in their own region at the end of .text and none
   is anchored."
   - E, P and T are the only promoted signals, and none reaches `.text$yc`.
   - Initializers have no class, so they have no N hint; C cannot bracket them, because their
     neighbours are other units' initializers.
2. **Candidate anchors** (retail-only; each would need the 99% leave-one-out gate, the hold-out
   harness and a Verifier-Change promotion):
   - (a) A BlockParse-link initializer takes the TU of the parse callback its node names
     (0x007AFC11 -> node 0x00DC14B8 -> 0x003EF467). This needs the parser approved first;
     see gap 3.
   - (b) An atexit-paired global constructor takes the TU of the approved functions that
     reference the global it builds. The referencer vote measured 0.79-0.88 in the docstring,
     below the gate, so it would need restricting, for example to runs that an anchor of
     type (a) confirms.
   - (c) I then brackets the run between anchored initializers (GAPS["I"] = 0x40).
3. **The parser has no TU either.** The provisional group ends at 0x003EF2FF. C needs
   brackets that agree, and the next named rows (Rva0022B0B8Subsystem) do not hint at
   the same TU.
4. **TU name.** The approved path is provisional (`Common/`). WorldBuilder names
   `GameClient/LivingWorld/`. The W route anchors only where W names the path a row's own hint
   gives, so this remains a naming-lane step.

## Not done

No merge, move or row repoint: rows without an approved TU may not move (AGENTS.md). Triage's
test-only diag remains the interim.

## Merge plan addendum (crash triage, 2026-11-07)

The full retail order is in `~/bfme2-ops/swarm/packets.tsv` P32. It runs the eight string
initializers 0x007AF8E3..0x007AF9A0 (Rva003EE900Forward.cpp), then 0x007AF9BB
(Rva003EE980Forward.cpp), then 0x007AF9D6 `initializeRegionEffectFields`
(Rva003EE746ColorProvider.cpp).

Our `initializeRegionEffectFields` is an ordinary function. It reaches `.CRT$XCU` only through
the exit link's initializer bridge. When the merge becomes possible, it should do both of these:

- define the nine string globals in retail order, and after them make
  `initializeRegionEffectFields` a real dynamic initializer of the same TU (a file-scope
  initializer the compiler emits into `.CRT$XCU` right after the strings), byte-verified against
  0x007AF9D6;
- drop the bridge entry, which lowers the real link's `initializers_bridged` (G1 debt) by one.

Then check that the image's `.CRT$XCU` puts the strings first, using link_check, the census or
`tools/image_iso.py`'s initializer report.

## Tooling measurements and decision (2026-11-07)

Measured on the retail image with the map rebuilt in memory (base 7fd11cc6a2). Probe scripts
are on srv1 in `~/bfme2-ops/seat5-tools/build/blockparse_probe.py` and `blockparse_order.py`.

- **(a) The BlockParse-link rule fails its gate.**
  - The `.CRT$XCU` table holds 1,166 initializers. 130 of them link a BlockParse node onto
    theBlockParseList (one list head).
  - 69 of those nodes' parse callbacks have an approved TU. None of the 130 initializers has a TU
    of its own, so `--validate`'s leave-one-out over approved F/Z/S rows can never score the rule.
  - Retail-intrinsic check: `.CRT$XCU` and `.text` are both in object order. The 69 anchored links,
    sorted by table slot, keep the order of their TUs' `.text` spans in only 62 of 69 cases
    (0.8986). The seven out of order are ControlBar.cpp, CrateSystem.cpp, DamageFX.cpp,
    GlobalData.cpp, SpecialPower.cpp, Upgrade.cpp and Weapon.cpp.
- **(b) The parser has no route.** No signal reaches any row in 0x003EE600..0x003EF800 (no
  evidence row). Rva0022B0B8Subsystem (ctor 0x003EF5A3, vftable 0x00C363D8, built on
  SubsystemInterface) is not LivingWorldRegionEffectsManager (ctor 0x003EEAFB, vftable 0x00C363C8),
  so no class fold extends the provisional group over the parser. P32's own link 0x007AFC11 is
  therefore not anchored either.
- **(c) I bracketing cannot reach the strings.** Nothing anchors an initializer below them
  (0x007AF8CD is unanchored, and other units' initializers precede it).

Decision (orchestrator, 2026-11-07): no TU-approval exception for this run. The fix goes to the
Link lane: order the exit link's objects by retail's `.CRT$XCU` sequence, which fixes initializer
order in general.
