# AptValue bridge cohort recheck

The picker serves fourteen bridged tables in AptValue.cpp, led by RVA
0x008EA228. The current ordinary baseline passes 35/35 rows, sixteen string
references and its emitted EH children. find_declared_unmatched is clear.

The source's RvaAptValueBase and Rva006D6360Base are short constructor views,
while retail's underlying AptValue hierarchy has fifteen virtual slots.
Rva006DE2B0 also declares its slot-7/8 overrides under placeholder signatures.
No class or source change was applied during this recheck.

The November 16 undefined-defaults handoff now reports all seven methods
landed. They are present in the current tree. The November 2 LINK-177
IsGarbageCollected/RegisterReferences naming prerequisite is also superseded:
both the canonical AptValue.h and AptObject/AptScriptFunction.h now use those
names in slots 12/13. Neither historical obstacle should be repeated as a
current missing definition.

AptScriptFunction.h still redeclares the registered AptValue class instead
of including AptValue.h. Only AptValue.cpp and AptArrayConstructor.cpp use its
protected mnValueData spelling; the canonical header calls that word field04.
The previous header-adoption probes are preserved in
aptvalue-root-reconcile-20261104.md and
00706a40-aptboolean-header-adoption-20261114.md. The later probe passed
569/570 rows and failed _createObject at 0x00706A40 on a constant-register
swap in its Date branch. This recheck did not repeat that experiment.

Claims for AptActionInterpreter.cpp and 0x00706A40 were refused because
another worker holds them. Since the known adoption repair needs that unit,
the header experiment was deferred and its unused claims released. No shared
header was modified while that consumer was held. A future attempt must
acquire the consumer and its body, revalidate the prior mismatch on the then
current source, and use normal byte checks before adopting the root header.
