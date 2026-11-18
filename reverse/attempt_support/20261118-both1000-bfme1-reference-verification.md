# BFME1 upstream input verification

At unchanged BFME2 source revision `08319aab75c0d9862a84bee3d1f03bdcf94afd65`, the normal full native byte
gate passes with committed reference `946f3c05a1b1e60448734e874a8f47f8017cfdb9` and staged candidate `f956f041626b7cdedec401bbe55282ccee1a3fe8`.
The first unstaged checkout trial was correctly refused by the native pin guard;
the original reference was restored and its full gate passed again. The candidate
gitlink was then staged normally and its full gate passed. No verifier, dependency
fallback, baseline, donor source or compiler override was changed.

All 1000 original/adopted source pairs are also independently re-probed under the
new reference in their actual source filenames. Whole runtime/relocation/data/
directive/external/weak-binding inventories, class and enum contracts and exact
primitive pointer-binding/sizeof witnesses agree; diagnostic runtime equals the
current ordinary native object. Real include receipts identify resolved headers.
The native diagnostic compiler writes only private outputs, never build/match.

The clean donor checkout is initialized without recursion. This check, the
reference update and failed setup trial count zero source tasks and zero new
function bytes, measured LINKED bytes, memory/FPS/crash or runtime improvements.
