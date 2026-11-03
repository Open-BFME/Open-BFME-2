### LINK-026: a unit owns a Zero Hour field-parse table whose parsers BFME 2 rows under other names

**Status: Repair landed / awaiting census. Updated: 2026-10-26; inspected revision: 9f93879fe9.**

- **Evidence / affected units:** `ControlBarScheme_trolBarScheme_QAEXPAVControlBarSchemeAnimation_Z.cpp`
  (18 B, `ControlBarScheme::updateAnim`) owns `ControlBarSchemeManager::m_controlBarSchemeFieldParseTable`
  (data_ledger 0x0080CD88) but defined it from Zero Hour, so it referenced
  `ControlBarSchemeManager::parseImagePart/parseAnimatingPart`, which nothing defines. Retail's table
  (read from game.dat) points ImagePart at 0x00320158 and AnimatingPart at 0x003201A9, rowed as the
  placeholders `Rva00320158Parse` / `Rva003201A9Parse`; it also has BFME's ButtonBorderAlteredColor
  entry and different offsets from the Zero Hour `offsetof` values.
- **Completed:** b749c0bf05 writes retail's 68 entries (parsers by their rowed names, retail offsets).
  link_check (index 47e030bafc): the unit LINKS 0 -> 18 B; `ControlBarRva00320158.cpp`,
  `ControlBarRva003201A9.cpp`, `ConstIntGetters5Addr.cpp` and the newControlBarScheme unit still link.
- **Remaining / next check:** the same cause may sit in other Zero Hour-donor units whose owned
  table names an unrowed parser (`link_rank.py --near` U names `?parse*`): read the retail table and
  bind its entries to the rowed owners. Naming the two factories `parseImagePart`/`parseAnimatingPart`
  needs a signature change, which `rename.py` refuses; leave it to the naming lane.
- **Clearance:** current-object preview of this one unit only.
- **Census confirmation:** awaiting.
