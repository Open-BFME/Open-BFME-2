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
