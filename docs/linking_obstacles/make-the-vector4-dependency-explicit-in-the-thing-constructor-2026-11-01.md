### Make the Vector4 dependency explicit in the Thing constructor (2026-11-01)

The Thing constructor now explicitly includes the registered Vector4 header it already received transitively. Complete byte/frozen/EH/strict checks retain all existing code/relocations, and owning acceptance retires one header key. No new census or runtime gain is claimed. Separately, Drawable retirement is deferred: original and direct-include controls both lose the current census prediction through an unresolved existing OpaqueRefCounted release provider; original restored and no queue override (reverse/attempt_support/drawable-vector4-dependency-block-20261101.md).
[Evidence](../../reverse/attempt_support/thing-vector4-stale-key-20261101.md).
