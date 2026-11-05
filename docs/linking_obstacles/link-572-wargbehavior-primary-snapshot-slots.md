### LINK-572: WargBehavior primary table still lacks Snapshot overrides
Status: Open. Updated: 2026-11-05; inspected revision: a40a338ad9.
Evidence / completed: [canonical-view and merge prerequisite verification](../../reverse/attempt_support/wargbehavior-canonical-merge-20261105.md); constructor dummy tables replaced by compiler tables, canonical BehaviorModule header adoption accepted, byte and link previews pass.
Remaining / next check: recover primary VA 0x00C426E8 slots 1/2/3 (retail RVAs 0x0058B03E, 0x00460827, 0x004CE56D) and verify the folded destructor identity; current WargBehavior view emits __purecall for these Snapshot overrides.
Clearance: pending table-slot verification; body-byte/link previews do not clear this gap.
Census confirmation: none claimed.
