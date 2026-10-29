# retail-truth-5 link order: names whose kept copy turns non-retail (LINK-135)

Seat halilkkaya-lk6, 2026-10-29, master `b740e71229`, census index
`d92e7e6635` (2026-10-28 15:58, retail-truth-4).

## Method

`rt5_sim.py` re-ranks every object of the census index by
`link_census.code_places` (retail-truth-5, 0d26afd6d2: an object goes by its
own unshared rows) computed from the census commit's own `functions.csv`, then
compares each COMDAT name's first copy (link.exe keeps it) with the census's.
The retail-truth-4 rule on the same ledger reproduces the index's object order
exactly, so the order model is the census's. `rt5_sim.txt` is its output.

## Result (upper bounds; other new conflicts are not re-judged)

* 10 names turn from a proven-wrong kept copy to a non-wrong one: 125
  census-unlinked units (271,771 B) were blocked only by those. This is the
  LINK-132/LINK-133 recovery the rule change was made for.
* 35 names turn the other way: 50 census-linked units (43,547 B) touch one.
  A retail-copy holder that sat early only through a shared (ICF) row moves
  back to its own code, and the next definer, early through its own unshared
  COMDAT row, holds a non-retail copy.

| Now-first provider (non-retail copy) | Names | Census-linked users |
| --- | ---: | ---: |
| `Common/System/SaveGame/CreateAHeroDataCopy.cpp` (`vector<AsciiString>` copy ctor) | 1 | 26 / 18,926 B |
| `GameClient/FXParticleSystemModules.cpp` (`ConcreteModuleClass::createTemplate`, `ConcreteModuleTemplate::clone`) | 25 | 3 / 8,121 B |
| `GameClient/GUI/GameWindowManager_registerTabList.cpp` (`list<GameWindow *>::erase`) | 1 | 4 / 3,042 B |
| `WWLib/stlport_deque_e12_new_elements.cpp` (`deque<BfmeE12>` `copy`, `erase`) | 2 | 2 / 3,003 B |
| `GameClient/GUI/FontLibraryInit.cpp` (`_Rb_tree<int, pair<const int, BfmePod52>>::insert_unique`) | 1 | 5 / 2,559 B |
| `GameLogic/Object/Contain/HordeContainRva00475F61.cpp` (`less<int>::operator()`) | 1 | 2 / 2,426 B |
| `WWLib/StlportVectorCopyCtorFamily.cpp` (`__uninitialized_copy<vector<BfmeE8>>`) | 1 | 2 / 2,266 B |
| `GameLogic/Object/Update/AIUpdate.cpp` (`allocator<_Rb_tree_node<pair<LocomotorSetType, ...>>>::allocate`) | 1 | 2 / 1,915 B |
| `Common/System/SaveGame/Rva0052CD81Finish.cpp` (`_Vector_base<SaveMapPreview>` ctor) | 1 | 2 / 682 B |
| `GameLogic/Object/ArmorHashtableRtsCtor.cpp` (`hashtable<ArmorTemplate>` dtor) | 1 | 2 / 607 B |

Repair per provider: stop the unit emitting the copy (a declaration-only
specialization where the unit calls the out-of-line body, as retail does) or
make the copy retail's; then the next definer in retail-truth-5 order, which
holds the retail copy, is kept. Verify by the unit's rows (`./build.sh`), its
`link_check` preview, and the first copy in this script's order.
Structural inference from the census index; no census confirmation claimed.

## Second class: keep_rule losers (`rt5_losers.py`)

Re-judging every multi-copy name's `keep_rule` under the same order (with the census's
referenced-name set; on the census order this reproduces the census's multi-copy losers
exactly) finds 9 census-linked units, 18,739 B, whose own copy newly loses: a name
without a retail address whose new first copy differs from theirs, or an unproven
copy that is now first and differs from the proven one. `rt5_losers.txt` lists them.

## Current-ledger preview (`rt5_lc.py`, halilkkaya-lk7, 2026-10-29)

`rt5_lc.py` runs `tools/link_check.py` on the census index permuted into retail-truth-5
order over the current ledger, so the checked units' current objects are judged in the
next census's order. At `6d854aae1c` plus the FX and deque repairs: of the 315 existing
census-unlinked units, 133 link (289,358 B) and 182 (48,307 B) do not, mostly on
unresolved names and private class views; FXParticleSystemModules.cpp, both deque<BfmeE12>
units and AIPlayerTeamBuild.cpp (with Player.cpp's current object) link; the class-view
cases `??_7ThingTemplate` and the `LivingWorldLogic` vtables remain.
