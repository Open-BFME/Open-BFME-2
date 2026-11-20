# SpawnedModelConditionCreate primary slot bindings

Inspected 2026-11-20 at `f1627ab62ad`. The compiler emits a 48-byte table for retail RVA `0x007EFA7C`. Its slot 1 now names `SpawnedModelConditionCreate::loadPostProcess`. The five-byte override forwards to the existing `CreateModule::loadPostProcess` at `0x0058B03E` and matches retail `0x00497805` with the existing `BattlePlanUpdate.cpp` ICF owner. The constructor and all five previous rows still pass the ordinary scoped build.

Slot 2 needs the existing six-byte getter at `0x00250A93` in `SubsystemNameGetters.cpp`. The documented same-class `rename.py function --to-class` route refuses at the class-registration gate before it reaches the Snapshot getter proof. `SpawnedModelConditionCreate` has no registered header. Preserve the getter's source placement, which `tu_map.csv` lists as proposed.

Slot 3 needs the existing five-byte row at `0x003A44DA` in `VslotSmallBodiesAJ.cpp`, a tail call to `CreateModule::xfer` at `0x004B8D4E`. The scoped trial matched both forwarding rows and all previous rows. The single native table occurrence supports moving the existing slot-3 row's ownership rather than retaining a second spelling. That move also requires the registered class and slot approval. The diagnostic slot-3 changes were restored.

The bridge remains open until a published real link clears the complete table.
