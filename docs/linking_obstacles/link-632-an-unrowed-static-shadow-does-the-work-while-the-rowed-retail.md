### LINK-632: an unrowed static shadow does the work while the rowed retail body sits unreachable

**Status: Open (check gap). Updated: 2026-11-08; inspected revision: f0d7034d24 (crash-triage seat2, P33). Family:
[LINK-630](link-630-a-byte-matched-row-whose-calls-bind-to-local-unrowed-comdats.md).**

- **Gap:** a unit can define an unrowed copy of a function whose retail-exact body is rowed in a different unit. When
  both copies have internal linkage (file `static`), the link never sees a duplicate (each object resolves the name to
  its own copy), so the real link's duplicate count stays 0, the byte gate verifies only the rowed copy, and the image
  runs the unrowed one. The rowed body is present but reachable only through its keep-alive anchor.
  `tools/find_declared_unmatched.py` also misses it: it counts a definition as matched when its *name* has a row in any
  unit, so GameWindowManagerScript.cpp reported "35 matched rows, 1 unclaimed definition" while it defined 13 shadows.
- **Case (P33, crash):** GameWindowManagerScript.cpp's `.wnd` keyword table (`_gameWindowFieldList`, retail
  0x009BE198) bound 13 keywords to the unit's own Zero Hour-shaped static parsers (`parseName`, `parseStatus`,
  `parseStyle`, `parseComboBoxData`, `parseSliderData`, `parseRadioButtonData`, `parseTooltipDelay`,
  `parseTextColor`, `parseStaticTextData`, `parseTextEntryData`, `parseTabControlData`, `parseDrawData`,
  `parseImageOffset`). Their retail bodies are rowed as file-statics with anchors in
  `GameWindowManagerScript_parse*.cpp`, `GameWindowManagerScript_parseStatusStyle.cpp` and
  `GameWindowManagerScriptDrawData.cpp` (`parseDrawData` was external but still shadowed). COFF: both copies of each
  name are storage class 3 (static), COMDAT `NODUPLICATES`. The shadow `parseStaticTextData` writes Zero Hour's 16-byte
  `TextData` (leftMargin/topMargin = 7 at +8/+0xC) into retail's 8-byte static-text template (getDataTemplate static,
  retail 0x00E01364), overrunning the next template, entryData (0x00E0136C); getDataTemplate (retail-exact) clears only
  the first 4 bytes, so `gogoGadgetTextEntry` dereferences entryData->sText = 7 (receipt
  2026-11-08T020044Z-boot_smoke-1d06e62134b7, InGameUI::createControlBar).
- **Repair (P33):** delete the 13 shadows from GameWindowManagerScript.cpp (its external declarations stay) and give the
  rowed definitions external linkage (drop `static` and the anchors), so the table binds to them; no rows move (only
  parseName and parseDrawData have approved TU GameWindowManagerScript.cpp; the lasting form is one TU in retail order).
- **Proposed check:** for every function an object *defines* (any storage class), look up its decorated name in
  `reverse/functions.csv`; if the name has a row whose source is a *different* unit, flag "definition shadows the rowed
  body in <unit>". This catches static shadows (this case) and external duplicates alike. As a lighter form,
  `find_declared_unmatched.py` should judge definitions per object (a name rowed elsewhere is unclaimed here), and a
  rowed function whose only reference in the linked image is its own anchor (a dead retail body) is a second signal.
