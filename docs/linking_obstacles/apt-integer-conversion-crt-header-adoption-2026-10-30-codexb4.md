### Apt integer conversion CRT header adoption (2026-10-30, codexb4)

`AptValueToIntegerBFME2.cpp` now takes `atoi` and `strtol` from the toolchain's
`stdlib.h`. The per-body retail check identifies direct calls to the existing
import thunks at RVAs `0x00629838` and `0x00629ABA`; the header's `_CRTIMP`
guard preserves that ABI. The 250-byte row still byte-verifies, all non-debug
object sections and external symbol records are identical, strict preparation
passes, and ordinary preview retains LINKS, 250 -> 250 authored bytes against
index `85f6b7f40c`.
The owning header scan reports clean and removes only this file's queue row,
retiring both local CRT declarations.

The six-source outgoing batch audit remains INCONCLUSIVE: the index predates
base `6fe1089c24`, and earlier providers `AptPlayerStatusDtor.cpp` and
`LinearCampaignManager.cpp` lack current strict receipts. Carry those providers
and affected consumers into the next scheduled census; no census gain is
claimed. [Target facts and checks](../../reverse/attempt_support/apt-integer-crt-headers-20261030-codexb4.md).
