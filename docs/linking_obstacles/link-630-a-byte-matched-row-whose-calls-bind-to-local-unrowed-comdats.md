### LINK-630: a byte-matched row whose calls bind to local unrowed COMDATs instead of retail's callee rows passes the gate

**Status: Open. Updated: 2026-11-07; inspected revision: d88c3448da (crash-triage seat2, P29).**

- **Gap (code-identity check):** the byte gate passes a row whose bytes match retail while its call
  relocations bind to its own unit's unrowed COMDATs instead of the rows retail's callees are.
  `tools/code_identity_gate.py` sees it (class `wrong`), but it runs in shadow and the finding is not in
  `reverse/code_identity_baseline.tsv`, so nothing refused the row or queued it for repair. This is the
  wrong-binding case the code-identity flip to `enforce` would refuse; until then such rows only show up
  as runtime crashes. Related family: [LINK-064](link-064-placeholder-element-names-that-hide-the-retail-element-of.md)
  (placeholder element names that hide the retail element of STL families).
- **Case (P29, crash):** `??4?$_Rb_tree@URva002D07F4Element@@U?$pair@$$CBURva002D07F4Element@@H@_STL@@...`
  (0x002D07F4, 115 B) and its 18 B `??4?$map@URva002D07F4Element@@...` wrapper 0x002D0B36, rowed in
  `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva002D07F4.cpp` with a 2-byte placeholder key.
  - Target facts (baselines game.dat): 0x002D07F4 calls 0x002572AE and 0x002D0326, the rowed `clear` and
    `_M_copy` of `_Rb_tree<BfmeStringRecord002CF550,...,_Identity,...>` (ModuleFactory.cpp,
    OwnedRecord900TreeCopy.cpp); 0x002D0B36 calls 0x002D07F4; `ThingTemplate::operator=` 0x002D1101 calls
    0x002D07F4 at 0x002D1395 for member +0x388, the UnitSpecificSounds set (`Rva0033DC9CParse`,
    ThingTemplateFieldTable.cpp). Inference: 0x002D07F4 is the 12-byte string-record set's `operator=`.
  - `code_identity_gate.py --staged` on the unit: both calls `wrong` (it binds its own
    `_Rb_tree<Rva002D07F4Element...>::clear` and `::_M_copy` for 0x002572AE / 0x002D0326); neither is
    registered.
  - Runtime: ThingTemplateAssignment.cpp types member +0x388 as that tree, so a ChildObject's `copyFrom`
    builds the child's set from 8-byte-element nodes (the AsciiString pointer copied without a reference,
    the record's +8 owner word unset) and the UnitSpecificSounds parser's `clear()` crashes in the folded
    AsciiString `releaseBuffer`: receipt `2026-11-07T222226Z-boot_smoke-0a2b402a6b72` (image 4d314dc87c =
    master d88c3448da + P16 test anchor).
- **Repair route (blocked):** respell both rows to the `BfmeStringRecord002CF550` set, move them to their
  approved TU `Code/GameEngine/Source/Common/Thing/ThingFactory.cpp`, and retype ThingTemplateAssignment.cpp's
  +0x388 view member. No tool route exists: `rename.py function --respell` refuses operator and template
  rows ("rename its class instead"), a class rename or fold cannot turn a map-shaped
  `pair<const K,int>`/`_Select1st` tree into a `set`/`_Identity` one, and no `--basis` kind covers retail
  callee identity. Recorded as a false reject in `reverse/re_attempts.log` at 0x002D07F4.
- **Next useful check:** with a code-identity respell mode (proven by the retail callee rows), rerun the
  combined test (master + P16 anchor); the receipt should get past ChildObject parsing of templates whose
  parent carries UnitSpecificSounds. Also worth a sweep: other `code_identity_gate` `wrong` findings on
  byte-matched rows that the baseline does not hold.
