# AIGateUpdate constructor/destructor view reconciliation

2026-11-05, seat codexb5; prerequisite to the approved AIGateUpdate TU merge.

Target evidence: `vftable_map.py --va 0x00C56480` identifies 13 primary
slots installed by the destructor at RVA 0x004B0802. Slot 4 points to the
existing getModuleNameKey row at RVA 0x004B087C. Constructor/destructor views
previously left that slot abstract; both now declare that existing override.
Their current COFF tables agree in all 13 relocation targets. This is slot
parity evidence, not proof that all other virtual slots already match retail.

The constructor adopts the existing seed's field view: pointer +0x20,
unsigned +0x24, counters +0x28/+0x2c, bool +0x30 and byte +0x31. These names
come from the existing seed; this change asserts no new donor-derived names.
The destructor uses the same first two fields. Matched native zero stores
and destructor ID access retain their bytes. All three link-wide constructor
aliases remain present, unchanged.

Normal build: 5/5 constructor/destructor rows exact, including the parent
whose emitted funclet label is renumbered and verified at RVA 0x0078E77E.
Declared-unmatched passes. Current-object link preview preserves all 522
bytes across seed/constructor/destructor. The supported TU dry run now
accepts these three sources (12 rows) together. Trigger's inherited data
view and ModuleData class/struct spelling remain a separate prerequisite;
mixed donors are excluded. No source paths moved in this prerequisite.
