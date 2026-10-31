# Native vector range destroy (2026-10-31)

At fab59430af, stlport_vector_rva004f77e0_dtor.cpp has a 63-byte exact destructor at 0x5EC919 but no definition for its already-pinned _Destroy<Rva004F77E0Element*> at 0x5F97BC. The old 2026-10-20 attempt failed because StrategicVeterancyAutoResolveCtor supplied a wrong copy. The current constructor no longer emits that helper; this is a new implementation trial, not repetition of the old declaration-only/alias workaround.

Reuse the existing TreeHintRef forwarder's clean C++ pattern: call the already-owned 27-byte Rva004F72EDDestroy with the observed two range pointers plus an unused false-type tag argument. The complete new forwarder is 24 native bytes including the actual call relocation. All seven existing external definitions/relocations, the 63-byte destructor and its EXACT EH graph remain unchanged. The element name stays an address-derived structural view; no original identity is inferred from the fold.

Official add_match.py admission verifies the ICF twin against the existing _Destroy<TreeHintRef00217D4C*> owner at 0x5F97BC. No new pin, alias, hatch, source path or TU-map entry is added. Strict preparation passes three rows across the destructor and actual 27-byte loop provider. Six shadow identity references are five owner plus one EH, zero wrong.

Current three-unit preview against d249ce458a: destructor LINKS 0 -> 87 (63-byte primary plus already-owned 24-byte fold); range loop retains 27, StrategicVeterancy constructor retains 375. Total 402 -> 489. The additional fold row is not unique coverage or a separate global linked-byte gain. At most the previously blocked 63-byte destructor is newly predicted linking; census confirmation remains pending. The underlying range loop still owns its existing release call at 0x5F8FCC.

Publication carry-forward: tokenizer fab59430af landed first attempt in 45.7 seconds. Its batch audit remains INCONCLUSIVE because index d249ce458a predates e1719086f7 and affected Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry that scope and this destroy/provider/constructor cohort into the next scheduled census. No maintainer-only runner was started.
