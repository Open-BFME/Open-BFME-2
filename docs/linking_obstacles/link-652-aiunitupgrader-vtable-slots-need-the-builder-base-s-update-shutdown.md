### LINK-652: AIUnitUpgrader vtable slots need the builder base's update/shutdown virtuals

Status: open (2026-11-09).

Target facts: retail table VA 0x00C70D38 (RVA 0x00870D38) is the Rva00506B1B
subobject table of `Rva005990DF` (at +0x0C; ctor 0x00598F3F, dtor 0x005990DF).
Slot 0 is the `??_E` adjustor 0x00598FAF, slot 1 is 0x00599264 (WB 0x01528530
`AIUnitUpgrader::update`, rowed `?update@Rva00599264@@QAEXXZ`), slot 2 is
0x0059904A (rowed `?shutdown@AIUnitUpgrader@@QAEXXZ` in
`Code/Libraries/Source/WWVegas/WWLib/AIUnitUpgrader_shutdown.cpp`). Both bodies
address fields relative to the +0x0C subobject, as an override introduced by
that base does. The real link bridges the table because AIUnitUpgrader.cpp's
private `Rva00506B1B` view has only the destructor slot
(`reverse/vtable_bridge_queue.tsv`: missing-source-slot 1 and 2).

Structural inference: `Rva005990DF` is retail's AIUnitUpgrader and the two
rows are its overrides of the canonical `Rva00506B1B` slots, which the header
spells `v1`/`v2` (AIWallBuilder's slot 1 is WB `AIWallBuilder::update`).

Prerequisite: one coordinated respell of the canonical base's `v1`/`v2` to the
real virtual names across every override (AIBaseBuilder 0x00506BDC/0x005071A1,
Rva0059A85C 0x0059A46F, AIWallBuilder's two alternatename slots, the other
Rva00506B1B users), then unify `Rva005990DF` with the `AIUnitUpgrader` view
(Register/UnRegister take the full object) and respell the two rows as its
virtual overrides. Respelling them `?v1@Rva005990DF@@UAEXXZ` instead would
overwrite the WB name `update`, and `rename.py function --virtual` cannot change
the class. Not attempted: no source change landed.
