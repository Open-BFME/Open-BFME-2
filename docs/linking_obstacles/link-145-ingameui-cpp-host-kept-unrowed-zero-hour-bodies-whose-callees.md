### LINK-145: InGameUI.cpp host kept unrowed Zero Hour bodies whose callees BFME 2 does not provide (2026-10-29)

Status: partly repaired; the host does not link yet. Census 2026-10-29 15:08 at
85f6b7f40c: `GameClient/InGameUI.cpp` (2 rows, 55 B) linked=no with five
unresolved names (`UpdateDiplomacyBriefingText(AsciiString, Bool)`,
`WindowLayout::destroyWindows`, `MemoryPool::freeBlock`, `UnicodeString::set`,
`GameLogic::setGamePaused(Bool, Bool)`), three COMDAT losers and one wrong
selected copy (`WindowLayout::runInit`). Five of the six link-regression
decisions of the merge-all run are InGameUI donors that wait for this host.
- **Cause:** none of these names has a row or a pin under that spelling. BFME 2's
  wide string is `StringBase<unsigned short>` (`UnicodeString::set` is rowed as
  `?set@?$StringBase@G@@QAEXABV1@@Z` at 0x00037150), its pool API is
  `MemoryPool::_Allocate`/`_Free`, and no row names the other three. All of
  them are called only from Zero Hour bodies the host compiles without rows.
- **Completed:** the bodies of `InGameUI::popupMessage` (both overloads) and
  `InGameUI::clearPopupMessageData` are dropped. The link index shows no other
  object touching any of the three names. That removes four of the five
  unresolved names and the wrong `runInit` selection. `./build.sh`: 2/2 rows exact;
  `link_check.py`: still does not link, LINKED 0 -> 0.
- **Remaining / next check:** `MemoryPool::freeBlock` comes from the Zero Hour pool
  deletes inlined into `InGameUI::clearWorldAnimations`. That body is also the only
  emitter of the host's row `??_GWorldAnimationData@@QAEPAXI@Z` (0x007593F0, 25 B;
  retail has no call or data reference to it). Dropping the body therefore fails
  that row; it stays until the row has another emitter or the BFME 2 body is
  recovered (lead decision: no body without retail bytes; the row, placed by a
  masked .text search with no retail call or data reference, goes to the
  maintainers to confirm or retire). The three COMDAT losers (`MemoryPoolObject::deleteInstance`,
  `BitFlags<116>` default ctor, `less<AsciiString>::operator()`) are Zero Hour
  template copies that differ from the first copy in link order. They come from
  further unrowed bodies (for example `removeNamedTimer` and `clearFloatingText`
  call `deleteInstance`). A texture.cpp-style removal of those bodies, each
  checked for other consumers, is the next step.
- **Step 2 (2026-10-29):** the object's only references to the three COMDAT
  losers are their own `.debug$F` records; no host code calls them. A
  declaration-only `less<AsciiString>::operator()` specialization (the
  existing `bfme link decl-only` block) stops that copy: 2/2 rows and both
  data rows exact. The same form for `BitFlags<KINDOF_COUNT>::BitFlags()` does
  not compile here, and `MemoryPoolObject::deleteInstance` is not a template,
  so those two copies and `freeBlock` remain; the host still does not link.
- **Clearance:** none. No census-linked byte gained or lost.
- **Census confirmation:** not applicable yet.
