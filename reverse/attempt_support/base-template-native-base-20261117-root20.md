# BaseTemplateLibrary constructor uses its real base lifetime

Inspected 13afb2e8202fbcd6ebcf632631b0689b7694501a on 2026-11-17. The claimed constructor `Rva0022BD9ASubsystem.cpp` now directly inherits the existing canonical SubsystemInterface with its native fourteen-slot surface. The manually constructed prefix and barrier-only fake destructor were removed. Native layout remains 0x34: 0x0C-byte base and two 20-byte tables at +0x0C/+0x20. No mapped-type identity or original class name is newly inferred.

The native constructor 0x0041EFFF remains 67 bytes; its handler remains 10 bytes. Its complete EH graph is EXACT. That graph independently places $L6060 at 0x00786CC7 and $L6061 at 0x00786CCF. With the actual base destructor at 0x001B4E74, add_match.py --replace-rva admitted the complete eight-byte $L6060 into the real parent, replacing gen_small's standalone generated harness. No generated source was edited and no pin/alias was added.

The eleven-byte member cleanup still cannot resolve the hash_map<int,Rva0041EFE0Element> destructor name to its native owner. Its add_match trial failed the ordinary byte check and restored the original generated row. Establishing the native mapped type/table lifetime is the next dependency; do not add a second named pin. The class-fold planner also refuses the existing shrink-only alternatename key linking the split constructor/destructor families. The alias and baseline are unchanged; their coherent retirement remains necessary before a supported fold.

The scoped preview retains 67/67 bytes and reports LINKS against index 0e4b2640a1, dated 2026-11-13. Its warning names 197 intervening source-path changes, so this is not current whole-link evidence. Native table 0x0083AF78 has fourteen ordinary subsystem slots; its init/post-process/reset/update and scalar lifetime still require the coherent class repair. No bridge is claimed retired.

Validation: final ordinary build covers the constructor, handler and recovered cleanup; the full parent EH graph is EXACT. Normal commit and push gates remain required. LINK-410 remains blocked for the previously documented composition and selected-COMDAT problems.
