# InGameUI outgoing audit follow-up (2026-11-04)

The fleet publisher rebased the cleanup onto `0302488aea`, producing
`3595b6fc6d`. Its InGameUI source diff is unchanged from the handed-off commit.
The ordinary byte gate was rerun after that rebase: both code rows and both data
rows pass; the frozen-file check also passes (41 unclaimed definitions).

A separate outgoing audit of that single commit, with the host listed as
byte-verified, returned exit 2 both before and after the fresh gate:

```
link batch audit: INCONCLUSIVE baseline: index at a62ac1c10b, outgoing base HEAD^; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 1 source object(s) lack current receipts; first: Code/GameEngine/Source/GameClient/InGameUI.cpp
```

This is unverified link evidence, not a passing regression audit. The ordinary
byte gate accepts dependency-hash receipts; `link_census.object_current` also
requires the include-search inventory or a witnessed census compile. Repeating
the ordinary gate did not supply that stronger receipt. No receipt or check was
edited, and no census or smoke run was started.

Carry the removed-provider scope from the
[cleanup audit](ingameui-donor-prune-20261104-codex5.md) into the next scheduled
census: the two donor roots, their helper closure, the surviving pair-destructor
providers, and `MemoryPoolObject::deleteInstance` in Player/WeaponSet. Confirm
there is no loss of previously linking consumers. The host still awaits the
`BitFlags<116>` repair and the merge guard's `Drawable::isSelected` conflict.
