### Proxy and object-creation canonical Module factory views (2026-10-30)

Cleared only for the two related factory units: GateProxy retains allocation
0x50/Module+4 and ObjectCreationUpgrade retains 0x30/Module+8. Use canonical
Module8, adjust only opaque padding and select the native Snapshot name-slot
mode. Four declaration-only roles make each partial view concrete. Native
constructors and tables independently establish both offsets and slot2 names.
Each 65-byte factory/EH passes; every non-debug section, definition, relocation
and unresolved-name set is conserved with SafeSEH indices resolved. No table,
thunk, alias or implementation is added. The owning tool retires two Module
keys; previews preserve LINKS/65 bytes each against `ccafe54d1d`. Static key,
nonvirtual name and complete-hierarchy debts remain; no census gain is claimed.
[GateProxy evidence](../../reverse/attempt_support/module-gate-proxy-factory-20261030/README.md),
[ObjectCreationUpgrade evidence](../../reverse/attempt_support/module-object-creation-factory-20261030/README.md).
