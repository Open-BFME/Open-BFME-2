# Player ScienceType provider cleanup, 2026-10-30

Declare the existing const ScienceType allocator and vector push_back before
Player instantiates them. Their exact names already have real definitions in
FXShaderParameterBinderInit.cpp and PlayerAddScience.cpp. The allocator is
28 bytes (RET8); push_back is the 49-byte rowed owner at RVA 2E01C6 (RET4).
No new name, alias, pin, layout, header, build flag or source path is needed.

Private original/corrected Player probes preserve all eleven matched rows.
Only the divergent 26-byte allocator and 58-byte push_back definitions vanish;
no definition is added. Every retained external code body and symbolic
relocation is identical. The inserted #line preserves following diagnostics.
The actual strict-current object must reproduce this same comparison.

The two unchanged provider sources are compiled only into private scratch
objects. All eight of their rows match retail, including their applicable EH
graphs. The coherent three-unit preview removes both named blockers from
Player and conserves the providers' existing LINKS verdicts. Player remains
unlinked on other causes, so this is partial linking cleanup with no claimed
headline/census gain. `proof.json` records the bounded comparisons and scope.
This publishes the completed small final batch of this Player provider pass.

## Remaining whole-file obstacles

The const ScienceType `_M_allocate_and_copy<PBW>` has no exact native provider:
Player's 110-byte and ThingFactory's 143-byte copies are nonnative. The 45-byte
31B9EB owner uses Rva0031B9EBElement, while ScienceVectorReserve's mutable PAW
specialization has a different mangling. A pin does not supply a definition;
do not replace this body with a declaration or add an alias to conceal it.

The hasUpgradeComplete QAE spelling is pinned to 2AB87D, whose 23-byte current
owner is the const QBE placeholder rva002AB87D. Removing the donor body alone
would leave the QAE name unresolved. Reconcile its name/signature and target
upgrade layout against that owner first. Player also retains independent
unresolved names and bitset::set conflicts. These are not declared repaired.

The earlier BitFlags repair landed as 1fdb9073a6. Shadow identity divergences
outside these two removed definitions remain unchanged; no baseline is edited.
Broader outgoing-consumer verification retains the old published-index and
missing current-consumer qualification. Census confirmation is still pending.
