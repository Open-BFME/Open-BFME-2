# FX event concrete primary interfaces

Served file: Common/VectorDeletingDtorsV06.cpp, four rowed deleting helpers.
Targets: LifeEvent primary RVA81C2F4 and TerrainCollision primary RVA81C314.
Native sequences are [3AB899,3AB991,3AD9BB,56435C] and
[3AB946,3AB9C8,3ADA36,56499B]. Their last two slots are the real exported
ConcreteModuleTemplate::createModule and Life/TerrainModuleTemplate::writeINI,
not CategoryModuleInfo::getClass. That getter belongs to the secondary table.
The old FX_MODULE_TEMPLATE_SLOTS inference must not be used for these targets.

The original V06 primary views had deletion and clone only. Restore the typed
factory and writer interface while retaining V06's declaration-only destructor
view, needed by its rowed vector-deleting helper emission. The two peer emitter
units now share fixed-KEY/NAME category-8 specializations. Only class parameters
are deduced: VC7.1 does not select the fully reference-deducing partial form here.
Declarations remain at the original event-tag sites to retain initialization
order. Factories' existing Terrain novtable full specialization remains and
adds its real typed factory declaration. No common runtime-module inheritance
or original pure-interface return type was invented.

All five emitted primary copies are sixteen bytes and match every native slot:
three Life copies and two Terrain copies. There are 999 COMDATs before and after;
only these five table copies change and 994 other fingerprints remain identical.
Independent review also compared full section graphs: no sections added/removed,
only those five change; 1,520 other graphs match after compiler-label and SafeSEH
symbol-index normalization. Weak sets, defined-symbol graphs, initializer and
local-static guard names remain unchanged. Only the expected factory/writer
references are added. Sizes0x24/0x28 and the secondary/info tables stay exact.

Final ./build.sh:310/310 code rows plus42/42 data rows. EH:58EXACT graphs.
Strict preparation:three explicit safe current sources, no other compilation
scope and no census/index/status update. Scoped preview:all3LINKS with
8143/8143 census-linked bytes preserved against aa7acf764d. It is not whole-game
closure. No bridge queue/data-ledger row was deleted; await the next published
real-link receipt for authoritative retirement.

## Preserved unsuccessful hypotheses

A V06-only correct table change still lost166 census bytes against short peer
copies, establishing the coherent three-emitter scope. A shared partial that
also deduced reference arguments produced V06 C2027 and abstract peer classes.
Explicit full-class/inline-constructor trials hit VC7.1 C1001 at
string_base.h:171 (msc1.cpp:2701). Fixing the real KEY/NAME references and
deducing only class types compiled. Using that peer implicit-destructor view
also in V06 emitted a competing Terrain destructor; an attempted shared
explicit destructor plus Life novtable factory view then lost Life_G and
changed Terrain_G to an imported call (2/310 failures). Restoring the existing
emitter-specific destructor declarations preserves every row and closes the
cohort preview. Failed sources/headers/logs remain in build/root-fx-*-failed-*;
verdicts were recorded through re_log.py. No refused source is retained.

## Remaining scope

The Category8 base's own retail table at7BB59C has deletion plus three pure
slots; its complete common runtime return-base interface remains unrecovered.
This cohort does not emit that base table. Other categories and the separate
FX DefaultModuleKey/Name guard-export debt are unchanged. The served V06 file
has no queued header-adoption pairs. Peer header-adoption work remains separate.
