### Timing-log ThingFactory interface (2026-11-02)

Rva0023C641Write.cpp adopts the unchanged canonical factory header through
its existing public firstTemplate accessor, preserving the native+0x0C read
and all three rows (542B). All five prior complete code and five data
definitions stay exact; no factory/base table is introduced. Normal/strict
and scoped LINKS checks pass; owning acceptance retires one header key.
The remaining43 factory users retain their original views pending base,
method, lifetime or member-pointer prerequisites; no shared header changed.
Evidence: reverse/attempt_support/thingfactory-timing-header-20261102/.
