### LINK-233: Vector3 aggregate construction emits an extra provider

Status: Blocked; original source and owning header key preserved.
The product TU's two black values use aggregate initialization, which is
incompatible with the registered constructor-bearing Vector3 header. Direct
zero-float construction fixes C2552 and preserves every old matched body,
but emits an extra `??0Vector3@@QAE@MMM@Z` COMDAT. Its target ownership or
safe provider suppression has not been established. No shared header, pin,
alias, baseline or constructor identity is changed to force acceptance.

[Native boundary and retained candidate](../../reverse/attempt_support/vector3-aggregate-prerequisite-20261104-1242.md).
No debt retirement, native coverage or full-image/runtime proof is claimed.
