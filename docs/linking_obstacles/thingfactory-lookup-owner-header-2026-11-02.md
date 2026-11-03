### ThingFactory lookup owner header (2026-11-02)

Rva002D06CAGet.cpp now defines its three real factory methods against the
unchanged canonical header. The old1B m_table only supplied a receiver
address; the methods now view opaque field14 through their existing lookup
receiver. All three bodies/relocations (38+32+5B) stay identical, with no
data, tables, new providers or lifetime assumption. Normal/strict and
scoped LINKS75B checks pass; owning acceptance retires one factory header
key. Forty-one entries remain. Evidence:
reverse/attempt_support/factory-lookup-header-20261102/.
The preceding award push's wider audit remains INCONCLUSIVE against the
older984a4cdc4d index, first lacking0CreateAHeroManager21FE49.cpp's receipt.
Its shadow static-guard wrong-name finding atA02F94 is an unchanged old
definition (all21 data definitions compare equal), retained for data cleanup.
