# Byte-fill provider repair

PartitionManager's O2 byte-vector insertion emitted competing non-retail unsigned-byte fill/fill_n bodies. The current retail owner is ByteFillNO1.cpp; Rva000AD9ABFinish.cpp uses its fill at 0x000ABC25. A declaration of the already rowed vector<unsigned char>::_M_fill_insert specialization makes the consumer use the established 0x000AFE9F provider. No renamed template, new address pin, alternate name, helper, or synthetic caller is introduced.

Removing the local insertion emission also suppresses allocator<unsigned char>::allocate. Its existing row at 0x000073E0 belongs to PartitionManager and matches all 27 retail bytes. Explicitly instantiate that actual STLport member to retain the existing owner; the normal eight-body gate verifies it together with all seven siblings. There is no data anchor.

## Evidence

Both original and repaired PartitionManager pass 8/8 under the same normal tool-selected profile. Explicit three-peer link checks refresh the current PartitionManager, Rva000AD9ABFinish and ByteFillNO1 objects in memory over the witnessed 62ab434507 index. Original: 0/3 LINK. Repaired: grid owner LINKS449 and byte-fill owner LINKS60, +509 existing bytes. The control records the remaining PartitionManager blockers; its unrelated unresolved/COMDAT/selected debt remains, and the whole PartitionManager unit does not link. This is a scoped improvement over an older witnessed global census, not a claim that the whole current ledger links.

The relevant reference reviewed is Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da. Its PartitionManager linking repair 339ecb08099e41519d1cfae61ca3881ccbd5bd85 deletes three wrong ZH bodies; that is a related owner-reconciliation lead but does not repair this BFME2-specific byte-vector optimization delta. Actual BFME2 library names, native allocator extent and unchanged body/provider checks establish this repair. The new terrain lead 0x000ADCE3 remains separate unfinished recovery work.

No new unique C++ bytes and no hatch growth. Sources and all control outputs are listed in control.json; no census or gate baseline is edited.
