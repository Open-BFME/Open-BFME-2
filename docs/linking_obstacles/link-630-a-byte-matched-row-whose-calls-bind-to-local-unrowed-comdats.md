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

**2026-11-08, crash-triage seat2 (P31): a second live case, a heap overrun.** The rowed
`??4?$list@URva00289FBCRecord@@...` (0x00289FBC, ExperienceLevelSystem.cpp) is byte-identical to retail, but its
calls bind to that unit's own `list<Rva00289FBCRecord>::insert`/`_M_create_node` COMDATs, compiled from an opaque
element view of a vptr and one char (8 bytes, so 16-byte nodes). Retail's callees are the rowed `list<BfmePod264>`
chain 0x00289F46 -> 0x00289ED7 -> `_M_create_node` 0x00289EB2, which allocates 0x110 (links + the 0x108-byte
experience level). The unit's forced `_Construct<Rva00289FBCRecord>` forwards to `_Construct<BfmePod264>`, so every
`ExperienceLevelStore::AddExperienceLevel` that assigns a new one-item list copies 0x108 bytes into a 16-byte node.
- Runtime: the AV stack capture (e20616cbfd) on test-only image 05d517395d shows the general allocator following a
  free-list link overwritten with `MenG` (`ExperienceLevel MenGenericLevel1`, ini.big:64012) under
  `friend_parseExperienceLevelDefinition` -> `AddExperienceLevel` -> `list<Rva00289FBCRecord>::operator=` -> insert.
- Interim fix 3c1ac4bfce: the view carries retail's 0x108-byte extent (vptr + `char bytes[0x104]`), so the local
  COMDATs size nodes correctly; 53/53 exact, link_check LINKS 3,152 -> 3,152. The lasting fix is one element type for
  both spellings, through the same code-identity respell route as P29.
- Like P29, the shadow code-identity gate is the check that sees this shape; until it is enforced, a byte-matched
  container member whose callees bind to local COMDATs of a differently sized placeholder element is the pattern to
  sweep for.
