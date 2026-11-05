# WindowLayout consolidation prerequisites, 2026-11-05

Inspected revision: `006a74b68c`. No game source, ledger row, alias or register
was changed. The supported planner surveyed `Code/GameEngine/Source/GameClient/GUI/`;
its queue identifies three rows each in WindowLayout.cpp, window_layout.cpp and
BfmeQuickMatchScreenBaseDefaultCtor.cpp, plus two mixed sources that stay put.
Both donors pass find_declared_unmatched before any edit.

`tu_skeleton.py --merge Code/GameEngine/Source/GameClient/GUI/WindowLayout.cpp
--dry-run` accepted no donor and exited 2:

- `window_layout.cpp`: C2011 GameWindow redefinition from WindowLayout.h:19,
  followed by missing winSetPrevInLayout and other chain accessors. The seed
  already includes canonical Bfme2GameWindow.h; WindowLayout.h defines its own
  incompatible GameWindow view. The canonical header does not declare those
  layout-chain methods. This requires coherent header reconciliation before
  merging; changing the seed alone does not supply the missing methods.
- `BfmeQuickMatchScreenBaseDefaultCtor.cpp`: link guard reports unresolved
  `?slot7@BfmeQuickMatchScreenBase@@UAEXPAVGameWindow@@@Z` and first COMDAT
  `??_7BfmeQuickMatchScreenBase@@6B@`. All three original units are census-linked.
  The seed declares virtual slots 7 and 8 that the default-ctor view lacks;
  composing it makes the constructor emit a broader vtable. A union of the
  declarations alone therefore cannot establish provider closure.

`tu_views.py ... --dry-run` proposes the union of BfmeQuickMatchScreenBase's
views and notes GameWindow* versus void* for the head at +8. It was not applied:
the proposal does not solve either measured blocker.

The dry-run claim check for class:GameWindow is held through live fleet claims
for BehaviorModuleInterface, GameWindowManager, GeometryInfo, InGameUI,
RenderStateStruct and Vector4 (StarkillerHDX@fleet). No foreign scope was edited.
Six existing /alternatename directives remain in window_layout.cpp; none was
removed, renamed or treated as dead. No hatch or debt is retired.

Next: acquire the canonical header/class consumer scope, reconcile the legacy
WindowLayout header with GameWindow's real shared declaration and preserve its
chain-call bindings, then rerun the merge. Separately establish target-backed
vtable provider identities before absorbing the default constructor. Keep both
mixed sources outside this mechanical merge. No source reduction, new byte
coverage, link gain or census confirmation is claimed.
