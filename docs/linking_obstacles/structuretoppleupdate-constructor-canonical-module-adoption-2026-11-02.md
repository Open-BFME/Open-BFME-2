### StructureToppleUpdate constructor canonical module adoption (2026-11-02)

`Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCtor.cpp`
adopted canonical `UpdateModule.h` and canonical `DieModuleInterface.h` (retiring
one row from `reverse/header_queue.tsv`), removing private `BehaviorModuleBase`,
`BehaviorModuleOther`, `UpdateModule`, and `DieModuleInterface` view stubs.
Header inclusion order defined `UpdateModule.h` before `Geometry.h` with
guarded Snapshot macro alignment, ensuring `StructureToppleUpdate`'s vtables
(`??_7StructureToppleUpdate@@6BUpdateModule@@@`,
`??_7StructureToppleUpdate@@6BBehaviorModuleInterface@@@`, and
`??_7StructureToppleUpdate@@6BObjectModule@@@`) match the first copy in link
order from `Rva0024A797Grandchildren.cpp`. Byte-matched 3/3 (0x004A5556 ctor,
182B, exactly matched with EH funclet and handler), `tools/link_check.py`
confirms clean link (`0 -> 192 bytes`, +192 linked bytes gain).
