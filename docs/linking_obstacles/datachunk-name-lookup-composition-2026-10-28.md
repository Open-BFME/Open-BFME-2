### DataChunk name lookup composition (2026-10-28)

Status: bounded composition verified; external consumer selection unverified.
Inspected base: `72d1fadb45`; preview index: `14dc3d2467`.

The getName donor now shares the seed's private Mapping view and is absorbed
into DataChunk.cpp. All 32 destination rows remain exact; the 60 distinct
external COMDAT fingerprints equal the original two-object union, with no
external names added or removed. The merge guard passes, and ordinary preview
preserves the combined 1,110 authored bytes. SOURCE FILES falls by one; no new
census-linked bytes are claimed.

The batch audit is INCONCLUSIVE because the index predates the base and lacks
per-object consumer names. Carry this scope into the next normal census.
Ten rejected donors still need private-view/header reconciliation; eight mixed
sources remain satellites. [Verification, path audit and prerequisites](../../reverse/attempt_support/datachunk-getname-consolidation-20261028-codexb.md).
