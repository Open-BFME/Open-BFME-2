# Independent private OrCondition audit

Scripts retains all23 external code definitions byte-for-byte and relocation-for-relocation; two retained EH graphs are identical, one obsolete36B pool-helper graph disappears.

Scripts initialized arrays and all unrelated initialized data are unchanged; intended deltas are Or table8->4, removal of MPO table8 and pool-only OrCondition literal12.

Two4B Or pool BSS statics are removed with their sole indexed helper/EH closure; no external indexed consumers exist.

MPO helper/table providers remain selected earlier in current PartitionManager and are identical. The OrCondition literal retains an identical current ScriptWriteDataChunk provider.

Ctor anchor initialized pointer bytes/binding are unchanged; its anonymous namespace salt differs only because of private source paths. Or table changes public_E to protected_E.

Rva scalar-delete28 and its4B table disappear: coordinate retirement against the existing replacement28 row in Scripts, as current ledger records. This is not silently approved row loss.

EH method: Compare complete initialized EH sections recursively through local COFF referents: raw bytes with relocation fields masked, relocation offsets/types/addends, external symbol identities, and recursively referenced local section bodies. Compiler $L/$T spellings are not treated as identities. Code references remain checked symbolically.

Limits: This audits captured private pairs; it does not assert all current working-tree sources equal those snapshots. Cross-unit closure uses the saved census cohort. Post-index whole-tree consumer safety remains for normal gates/census. No claim of canonical original OrCondition naming or original donor inheritance is made.
