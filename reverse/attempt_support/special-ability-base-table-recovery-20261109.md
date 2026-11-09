# SpecialAbilityUpdate base-table recovery, 2026-11-09

## Correct the existing post-load placement

The native base constructor at RVA 0x0044EF5E and destructor at
0x00451F45 install the primary table at RVA 0x0083FBA8. Its slot 1
holds 0x00497805. That five-byte body jumps directly to
UpdateModule::loadPostProcess at 0x0058B03E. The former placement,
0x00483CEF, is another five-byte jump to 0x00497805, rather than the
address held in this table.

The existing ArrowStormUpdateBehaviorCtor.cpp emitter and the private
canonical base-destructor candidate both emit the same direct-jump
COMDAT, digest `4df555d0129b`. The 19:12 census index at `5b5011469d`
already contains this digest in five sources. This is an address repair
of the existing SpecialAbilityUpdate identity, not a new ArrowStorm
override or a new COMDAT variant.

`add_match.py --replace-existing --icf-owner` repointed only the existing
SpecialAbilityUpdate::loadPostProcess row to 0x00497805, retaining its
source and extent. BannerCarrierUpdate.cpp provides the existing matched
ICF owner at that address. The old 0x00483CEF address remains covered by
its placeholder and helper fold rows. The normal symbol map now contains
both addresses for this name, because the former address is a forwarding
jump to the corrected body.

Verification: normal build 12/12 bodies exact; check_csv passes;
link_check reads **LINKS, 233 -> 233 bytes**, against index `5b5011469d`.
No source paths, pins, compiler flags or extents changed.

## Remaining table work

The independently proved base secondary table at RVA 0x008552A4 is
36 bytes with nine native relocations. A private canonical destructor
candidate passes all five existing rows without extra symbol bindings.
Its publication and the eleven generic-array consumer references are
the next package. These facts do not clear the separate primary-table
getter ownership or any other derived-class bridge.

The inline canonical GetSnapshotName body is still represented by the
placeholder row at 0x0044F099 in ModuleNameGetters.cpp. Its supported
identity transfer needs an out-of-line emitter and the canonical-header
closure, currently 55 consumers before the two proposed new includes.
Do not copy a private canonical class or invent an emitter to avoid that
closure.


## Complete base secondary owner and caller closure

The final SpecialAbilityUpdateDtor.cpp includes the canonical class rather
than the partial private SpecialAbilityUpdate/one-slot interface. Three
unused auxiliary class views are removed too. The existing destructor body,
STLport declaration-only specializations and two destructor aliases are
unchanged. Its five existing code/funclet rows remain byte-exact without
extra symbol-map bindings.

The compiler emits the complete 36-byte SpecialPowerUpdateInterface table
at RVA 0x008552A4: all nine relocated native targets verify. The explicit
matched data row now names this base-class table in its actual destructor
emitter. Address, extent, section and matched status are unchanged. This is
a physical owner proved by the native base stores, not a borrowed derived
class identity. The raw data ledger and its diagnostic historical names
are unchanged.

The former strong array in GloriousChargeUpdate.cpp is removed, along
with its unused declaration and nine unused function declarations. All
ten ModuleUpdateDtors.cpp stores and the one SpecialDisguiseUpdateCtor.cpp
store now reference the same base compiler table directly. No new pin,
linker alias, source file or code-row move was introduced.

Private before/after verification: 56/56 existing rows over four sources;
all ten newly emitted canonical inline helpers also match independent
native targets. The getter's 21-byte SpecialAbilityUpdate string, including
its terminator, matches at native VA 0x00BF50D4. The producer's LinkGuard
reports no losses. The primary table resolves 22/23 ledger-named slots;
its exact but still placeholder-owned getter at 0x0044F099 remains a
separate identity prerequisite. The BehaviorModuleInterface table resolves
47/47 slots, the UpdateModule table 3/3, and the claimed secondary 9/9.
This does not certify every derived table or clear their bridges.

Normal verification: 56/56 bodies, three data rows, two strings and five
EH-bearing rows exact. The five affected units' own link_check verdicts
are LINKS, totaling 2,505 -> 2,505 bytes against index 5b5011469d.
find_declared_unmatched passes on all four modified sources; staged
data_check has zero findings. The owning header lane accepts the direct
canonical BehaviorModule include and retires two stale queue rows
(5,643 -> 5,641). Three Rva0029FB3BMember rows remain: that private list
view still supplies begin/end and manually models construction/destruction;
a header-only replacement has not been claimed as a fix.

A bounded native child reviewed all 35 inventoried local/parameter
bindings in the complete inspected sources. The parent scanned every
mapping and the resulting diff, retained the two uncertain meanings and
five pointer bindings the planner refused, and acknowledged the exact
proposal once. The supported scoped transaction applied 14 clear names in
one verification, preserving 21 names. The omitted comparison operand
`other` and qualified pointer `slot` were inspected and retained; the regex
inventory is not claimed to cover them.

Tooling compatibility audit: there are no Code path additions, deletions
or renames. Both old and new data-emitter paths remain tracked; the sole
changed path-valued record is the explicit verified data owner. Active
Code/tools/hooks/workflows contain no remaining old-array reference or
reference to the removed partial-interface table. Historical data-ledger
aliases remain diagnostic. No path consumer requires a rewrite. Carry
forward the earlier broad audit's unchanged AICowerState_onEnter.cpp
receipt gap to the next census; the five own verdicts above do not clear
that unrelated index limitation. Actual next-image selection and bridge
counts remain to be measured.
