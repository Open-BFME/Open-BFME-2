### LINK-053: unmatched light persistence factory instantiates missing donor interfaces
Status: Cleared in ordinary-preview scope; census confirmation pending. Updated: 2026-10-26; inspected revision: 896af21680.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WW3D2/light.cpp`; unresolved `PersistFactoryClass` constructor/destructor and `SaveLoadSystemClass::Register_Pointer`; current index `d1f046749a`. Raw evidence: `build/link-report.md` and `build/link-worker-20261026/`.
Completed: removed the unrowed Light factory instance, its Load/Save bodies and the unmatched `LightClass::Get_Factory` accessor. The existing `LightPersistFactoryClass::Chunk_ID` definition remains under its own name as an ordinary out-of-class member and byte-matches all six retail bytes. Three present-unmatched markers disappear. No row, pin, alias, storage substitute or code-generation flag changes.
Verification: final build verifies 40/40 rows across all 20 assigned units; changed-source frozen, EH, data, ledger and pin checks pass. The final expanded ordinary preview reports light LINKS; the 46-unit before/after intersection gains no blocker. Exact-name source search and all available cached census objects find no other light-factory consumer; 517 indexed object files are absent locally, so this is bounded evidence, not whole-game closure.
Remaining / next check: carry the removed-provider audit and the retained six-byte accessor into the next scheduled census; missing cached objects prevent a complete object-level consumer claim.
Clearance: cleared in ordinary-preview scope; census confirmation pending.
Census confirmation: awaiting the next normal census; no headline change claimed.

**Persistence-remnant follow-up (2026-10-26, inspected `ff45f96b14`):**
[Paired object evidence](../../reverse/attempt_support/light-persistence-followup-20261026/readme.md)
confirms the factory was already absent, but the donor `LightClass::Save`
and `LightClass::Load` bodies remained. Removed those two bodies and retired
their two unmatched exemptions. The complete six-byte `Chunk_ID` row stays
exact and the actual before/after objects both preview LINKS. The removed
methods have no indexed incoming edge from an outside provider; the third
removed definition has another provider. No retained COMDAT digest changes
or newly wrong selected provider appears. `Load_W3D` and `Save_W3D` remain
separate debt. This follow-up claims zero new linked bytes; census confirmation
remains pending.

**W3D-remnant follow-up (2026-10-27, inspected `7ed44e8ffd`):**
[Paired object evidence](../../reverse/attempt_support/light-w3d-cleanup-20261027/readme.md)
checks the remaining donor `LightClass::Load_W3D` and `Save_W3D` bodies.
Neither has a source caller or an indexed incoming edge from an outside
provider. Removed both bodies and their two unmatched exemptions; the six-byte
`Chunk_ID` remains exact. Both actual objects preview LINKS. The removed
emissions have either another indexed provider or no outside incoming edge;
no retained COMDAT changes or selected provider becomes wrong. Keep the
optimization anchor: its removal changed the retained `??_H` helper from the
34-byte retail body to a wrong 50-byte body. This retires two exemptions,
adds zero linked bytes and still awaits scheduled census confirmation.
