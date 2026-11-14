### LINK-674: PlaceEventTranslator::translateGameMessage's spill slots flip with every Player.h change; TU recovery first

Status: Open (TU-recovery prerequisite). Opened 2026-11-14 by the waste lane (`ancalgonn-swarm-waste`); inspected
revision `7dfc096d04e`.

**Symptom.** `PlaceEventTranslator::translateGameMessage` (retail RVA 0x0043218A, 1,701 bytes, in
`Code/GameEngine/Source/GameClient/MessageStream/PlaceEventTranslator.cpp`) byte-matches or not depending on the
declarations its unit sees. Every Player layout step so far has swapped two of its spill slots
(`pendingBuild`/`builderObj`, `[ebp-0x1C]`/`[ebp-0x20]`, at body offsets 0x25C, 0x2E7 and 0x477):

| step | Player.h change | unit fix that restored 7/7 |
|---|---|---|
| batch 1b (landed `e2836315d7e`) | embed Money at +0x90 | `e4c1775fa90` adopt the canonical `FreelistPool.h` |
| batch 2 (landed `f60df479d13`) | nine shape-agreed fields | `32f6d7ce25b` adopt the canonical `MiscAudioClass.h` |
| batch 3a (pending) | `UnicodeString` at +0x38 | candidate: adopt the canonical `ThingTemplate.h` (matches only with batch 3a applied) |

**Measured (target facts about this compiler, not about retail source).** The flip follows neither a member count nor
a struct count nor declaration position: with batch 2's Player.h, a throwaway struct of 1..16 int members before the
first include restores the match, while an empty struct, two one-member structs, a struct at the end of the file or an
enum do not, and with the unchanged Player.h a one-member struct breaks it. This is the declaration-hash effect
`docs/recipes.md` describes for optimized frame slots ("named locals take frame slots in name-hash order";
symbol-count sensitivity of MSVC 7.1's slot keys). Diagnosis scripts: `~/bfme2-ops/swarm/sweeps/waste/lane/shared/`
`p1b_pet*.sh`, `p2_pet*.sh`, `p3a_pet.sh`.

**Why it is a TU-recovery prerequisite.** The unit is a one-function-file reconstruction with private views of
canonical classes (`reverse/header_queue.tsv` still lists GameMessage, InGameUI, MessageStream, Mouse, View for it).
Its declaration set is an accident of which views it keeps, so any change to a header it includes (Player.h is
included for the single inline `getControllingPlayer()->getPlayerIndex()`) can move the slots. Retail compiled this
function in its own translation unit with that unit's real declaration set; recovering that TU (merging the unit into
its approved TU with its real headers) is the lasting fix. Until then each Player.h change needs a real declaration
change in this unit, found by trial, and the remaining adoptions need API changes (e.g. the canonical
`Mouse::rva001EDD80` takes `Rva001EDD80Pair*` where the unit passes `ICoord2D*`).

**Next useful check.** `python3 tools/tu_skeleton.py --plan` for the unit's approved TU (`reverse/tu_map.csv`), then a
merge that adopts the canonical GameMessage/MessageStream/InGameUI/Mouse/View headers; after it, re-run the Player
batch 3 steps against the merged TU and record whether the slots still flip.
