### Special-power view-object ObjectModule adoption (2026-10-31)

SpecialPowerModuleCreateViewObject includes the existing ObjectModule header
and uses the canonical protected data/object getters. All four rows and the
complete EH graph remain exact. Ten retained external code definitions and
all main-body relocations are identical; only two debug-referenced private
getter copies give way to the canonical getters. Both objects keep the same
S1 static guard and key name, and both shadow data checks have zero findings:
the earlier guard-name failure is not reproduced by this variant. Strict
preparation and the owning acceptance tool pass, retiring one header key.
No shared header, pin, alias, row, flag, path or guard-name change is made.
The bounded linking prediction and full consumer-selection/census checks
remain separate; the other ObjectModule/Xfer prerequisites remain open.
[Controls, prior verdict and scope](../../reverse/attempt_support/view-object-objectmodule-20261031.md).

Prepublication audit at base `277f1f4d4e`: INCONCLUSIVE on index `3c7a254a38`
and the missing current receipt for affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. Carry that
consumer and the removed/canonical getter selections into the scheduled
census; the one-key acceptance does not clear the full consumer-loss scope.
