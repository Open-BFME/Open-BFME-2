### Index-buffer canonical prerequisites 20261103-1638

DynamicIBAccessWriteLock adopts IndexBufferClass and DX8IndexBufferClass.
Native acceptance retires exactly two header keys; existing338B and two EXACT
EH graphs remain. An unreferenced Add_Ref emission is removed without changing
other code. The scoped dated preview stays338->338B. No source merge occurs: a
void/bool mutex declaration still blocks composition; an affected shared-header
consumer is held elsewhere, so that repair remains open. The broad audit below
is carried forward as observed, not a full link or runtime result.

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 7bf014738c98432c9bd1037f5766ba501bc55bab; findings below are provisional since-index changes

link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

[Scoped evidence and remaining work](../../reverse/attempt_support/index-buffer-batch-20261103-1638.md).
