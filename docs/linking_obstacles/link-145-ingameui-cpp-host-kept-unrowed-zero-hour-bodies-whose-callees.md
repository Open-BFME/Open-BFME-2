### LINK-145: InGameUI.cpp host kept unrowed Zero Hour bodies whose callees BFME 2 does not provide (2026-10-29)

Status: host blockers cleared in the 2026-11-05 scoped preview; census confirmation and guarded donor merges remain pending. Census 2026-10-29 15:08 at
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

- **2026-11-04 prerequisite cleanup:** removed unused donor `removeNamedTimer` / `clearFloatingText` bodies and the host's conflicting `deleteInstance` copy; four rows stay exact, preview blockers 2 -> 1, LINKED 0 -> 0. Next: `BitFlags<116>` and the merge guard's `Drawable::isSelected` conflict; [provider audit and handoff](../../reverse/attempt_support/ingameui-donor-prune-20261104-codex5.md).
- **Outgoing audit follow-up:** byte gate passes after the fleet rebase, but the batch link audit is inconclusive (older index; host lacks census-grade receipt); carry provider/consumer checks into the next scheduled census: [evidence](../../reverse/attempt_support/ingameui-link-audit-followup-20261104-codex5.md).

- **2026-11-05 selector-emitter cleanup:** removed four unused donor selectors and their private callback; both conflicting `BitFlags<116>` / `Drawable::isSelected` copies disappear, all four rows stay exact, host preview now LINKS (predicted 55 B). Next: scheduled census confirmation and a fresh guarded merge pass; [provider audit and scope](../../reverse/attempt_support/ingameui-bitflags-prune-20261105-codexb.md).

- **2026-11-07 host cleanup and current merge boundary:** three stale,
  non-emitting scrolling/selecting definitions and the unused struct-Coord2D
  setScrollAmount body are removed. The class-Coord2D owner is unchanged;
  no signature respell is inferred from a source-name hit. All eight code and
  two data rows remain exact; 102 simple external code comparisons and CRT
  order are preserved, with only the unused U setter definition removed.
  Four live unmatched hatches retire. The current 114-donor trial accepts none:
  the host's no-/O override rejects or mismatches most donors before composition,
  and canonical/private header boundaries remain. A private /O1 /Ot host passes
  all eight rows and LinkGuard; applying it needs the full repository gate and
  another guarded merge trial. Existing expireHint/resetIdleWorker ABI leads
  remain separate. [Proof and scope](../../reverse/attempt_support/ingameui-host-prune-20261107/README.md).

  Donor cleanup published as 5d3b84e454: outgoing eight code/two data rows pass,
  preserving the 244-byte ordinary preview. Broader audit is INCONCLUSIVE:
  index 9c81acd297 versus base 6d6c5630213a285ffa0ce942d40737d8ffefabee;
  the host lacks a current audit receipt. Carry selection into the next census.

- **Same pass, optimized-host prerequisite:** the owning flag tool records
  /O1 /Ot /G7 /arch:SSE. All eight native rows still match; /Ot keeps the
  scalar wrapper's 25-byte add-ESP form instead of the regional 23-byte pop-ECX
  form. Private LinkGuard passes, all seven prior strict borrowed-owner twins
  remain matching, and CRT order is equal. The override remains necessary.
  A new donor trial and actual image/census evidence remain required.
  [Compiler and provider proof](../../reverse/attempt_support/ingameui-optimized-host-20261107/README.md).

- **Same pass, concrete list-constructor boundary:** the optimized trial still
  accepts no donor. The 0x002A1B07 constructor's only mismatch is a call to the
  out-of-line list constructor (0x00239CB7), replacing retail's direct call to
  _List_base (0x00239BB0). Restoring the ordinary inline list constructor after
  its existing provider declarations preserves all eight host rows and admits
  the unchanged donor in a private nine-row LinkGuard trial. All 105 external
  code definitions, seven prior strict borrowed-owner twins and CRT order are
  preserved. No member/base lifetime substitution is applied. Supported merge
  and publication verification remain pending.
  [Binding proof and scope](../../reverse/attempt_support/ingameui-list-constructor-20261107/README.md).

- **2026-11-08 donor-provider prerequisite:** Rva002A1B07Ctor.cpp keeps
  declarations for its existing shared pool and lifetime providers, removing
  the unused private pool view and seven duplicate helper emissions. Its
  22-byte row remains exact; all four surviving external code definitions
  retain bytes, flags and relocations. The normal two-source build passes
  nine code and two data rows. The final composition still needs provider
  selection checks, including its out-of-line list-constructor copy.

- **2026-11-08 supported merge verified:** the cleaned 0x002A1B07 donor is
  absorbed into InGameUI.cpp: nine code/two data rows remain exact, one source
  file is removed, and the combined 266-byte preview is conserved. The indexed
  first list-constructor provider remains retail's 18-byte GameLogicDispatch
  copy ahead of the host's differing 19-byte copy. Seven prior strict host
  provider twins and CRT order are preserved. The source-path, register,
  header/MS-header and EH audit passes within its stated scope. The remaining
  113 donors retain flag/header blockers; publication audit and new census
  confirmation remain pending.
  [Consolidation audit](../../reverse/attempt_support/ingameui-list-constructor-20261107/consolidation-audit.md).

  Publication: the four-commit batch landed at 2c603d524d on 2026-11-08,
  first attempt in 28.0 seconds. Pre-push reverified nine code and two data
  rows, scoped DIR32, EH and converged-data checks. The broader batch audit
  is INCONCLUSIVE: index 9c81acd297 versus outgoing base
  6b4cb578294968b2de232ab02a81048dcfc8b23e, with two source objects lacking
  current receipts (first InGameUI.cpp). Carry these missing receipts and
  provider selection into the next census; no real-image clearance is claimed.
