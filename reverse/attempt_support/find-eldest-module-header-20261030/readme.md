# findEldest canonical Module base

The queued private `Module` definition in CreateObjectDieFindEldest.cpp includes
a module-specific interface at `+0x0C`. The canonical base occupies eight bytes
and does not define that derived interface or its accessor. This is a source
view/header prerequisite, not a missing native callback.

Keep the canonical base and express the observed interface in an address-named
partial derived view with a four-byte gap. Access that view directly. Native
`004859C9` adds `0x0C` to the returned module pointer, loads the interface vtable
and calls slot `0xA0` with no stack arguments. The returned pointer's first
unsigned word participates in the minimum test. These accesses prove the
offsets and ABI; the view does not claim the complete module identity, original
inheritance or actual data-member relationship. An existing analogous partial
canonical-Module view appears in ScriptActions_rva003C3175.cpp.

Private before/after objects retain the complete 72-byte callback and both
symbolic call relocations identically. No new code definition is emitted.
Only the former four-byte inline getInterface accessor disappears; it has
debug-only incoming relocations and no executable reference in the published
index. The actual strict object reproduces the private candidate.
[Native instructions and object proof](proof.json).

Literal build.sh, frozen-definition and strict preparation pass. The owning
`header_adopt_lane.py accept --class Module` test passes and retires exactly
one header queue entry. Before and accepted-current previews retain LINKS/72
authored bytes against `ccafe54d1d`. No shared header, row, pin, alias, hatch,
source path or other debt register changes. The broader CreateObjectDie merge
still needs its existing Object access, GameLogic, Xfer and BitFlags view
reconciliations; this commit does not claim that merge or a new census gain.

Ready-batch audit: INCONCLUSIVE on older `ccafe54d1d` versus outgoing base
`bea01c68bb` and the missing current CreateAHeroManager consumer receipt.
Carry the removed getter and affected consumers into the next scheduled
census; no full consumer selection/loss clearance is inferred.
