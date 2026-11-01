# qc-13 item 5310

All five undecided representation attributes resolved by hand as VPTR, rather than opaque scalar pointers: native ctor writes primary C58B10, secondary C58110 at +C, C58AC8 at +10, C58790 at +18, and C58AB8 at +1C after temporary C4EF80. Native factory allocates 20h. Raw table words and ctor/factory/xfer bytes attached; slot spelling is not inferred from ICF-selected ledger names. The unmodified tool contract is attached separately from manual decisions.

Remaining prerequisite is canonical UpgradeModule and Rva004B70F0Iface1C parent ABI/provider closure. No canonical registration exists for UpgradeModule; current ctor donor represents vptr stores with local dummy addresses whereas xfer donor has an unrelated one-slot base view. Merely sharing their spelling would alter emitted tables. The source and table provider closure must be established before replacing these views. No Code changes, guessed layout, default virtual fallback, hatches or aliases retained.

Evidence applies at base 79da60c9fb. Requires canonical UpgradeModule; native getter/profile closure must precede derived adoption. Full slots remain a separate prerequisite from the five now-resolved representation decisions.
