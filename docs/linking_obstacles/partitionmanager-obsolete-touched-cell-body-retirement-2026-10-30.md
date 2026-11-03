### PartitionManager obsolete touched-cell body retirement (2026-10-30)

Cleared only for the unused donor updateCellsTouched copy: remove its 426-byte
definition, stale present-unmatched marker and false 0x0073AD90 pin. Its only
incoming relocation is debug-only; two accompanying GhostObject helper copies
are likewise debug-only and no other indexed object touches the three names.
The existing 37-byte friend facade and independently named 1,158-byte native
ShroudManager::Data::UpdateCellsTouched owner remain exact. All four Partition
rows and all 561 retained code bodies/relocations are unchanged; the sole
onPartitionCellChange reference disappears with the donor body. The hatch
tool retires exactly one marker and one pin. Other Partition unresolved names
remain; no recovered native coverage or census gain is claimed.
[Removal proof and target ownership](../../reverse/attempt_support/partition-unused-update-retirement-20261030/README.md).
