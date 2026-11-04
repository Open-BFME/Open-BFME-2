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

#### Shared declaration prerequisite repaired, 2026-11-04

The canonical guard header now declares the existing native unlock provider as
bool, matching dx8wrapper.cpp at0x00120F50. Its6 current consumers retain125
function/EH rows and complete non-debug sections; only the already same-address
callee spelling changes in7 code instances. No pin or alias changes. Header
adoption of further private guard copies is now testable. No TU merge or
full-image link is established by this prerequisite.
[Native scope and byte evidence](../../reverse/attempt_support/device-guard-contract-20261104-0110.md).


#### Seventeen private guard copies retired, 2026-11-04

After that shared prerequisite,17 independent sources adopt the registered
BFMEDX8DeviceLock header, including DynamicIBAccessWriteLock.cpp. Native
acceptance retires exactly17 header keys; all129 existing code/EH rows
and complete non-debug sections remain. The23-source canonical-header closure
has normal byte verification and strict current receipts. The older
reference/shims/indexbuffercount/dx8indexbuffer.h still declares void unlock
and a private guard; it is outside this changed header's dependency graph.
No seed/donor composition or TU merge is claimed. That shim and any remaining
DynamicIBAccessClass view remain explicit prerequisites; the broader obstacle
stays open. [Batch evidence](../../reverse/attempt_support/device-guard-batch-20261104-0110.md).


#### Outgoing native batch audit

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 94ebe7b612cfa4a6ac16f8d37ea28a8598edc437; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 2 source object(s) lack current receipts; first: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
```

Inconclusive cases are carried forward to the next maintainer census. They
are unverified consumers, not evidence of a clean complete-image link.


#### Native audit after search-inventory receipt refresh

The first audit above preceded refreshing two root-search inventories after
new proof files were created. All actual recorded dependencies stayed exact.
Reprepare only W3DBridgeBuffer.cpp and FXShaderGeometry.cpp via the supported
strict-current mode, with normal byte gates. The broader native result now is:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 94ebe7b612cfa4a6ac16f8d37ea28a8598edc437; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

This supersedes the earlier two-own-source receipt gap; any remaining affected
consumer gap still stays unverified and is carried to the next census.
