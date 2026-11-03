# ObjectCreationUpgrade canonical base-header debt closure

Dtor, loadPostProcess and update already derive from canonical UpdateModule,
which imports canonical BehaviorModule and BehaviorModuleInterface. Make that
base dependency explicit by including BehaviorModule.h immediately after
UpdateModule.h, preserving the initial Snapshot configuration and every body.
The owning header_adopt_lane accept operation passes for all three classes in
all three files and retires nine stale header-queue records. No queue entry
is deleted by hand. The first transitive-only attempt was correctly refused
by the owning tool's direct-include prerequisite.

Normal builds preserve all seven current rows, including update's EH funclet
and handler. Strict reusable receipts also pass. No source path, row, pin,
class layout or vtable declaration changes. This is debt retirement through
its owning tool; census and whole-image/runtime behavior remain separate.
