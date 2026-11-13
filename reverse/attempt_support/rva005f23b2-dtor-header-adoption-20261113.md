# Rva005F23B2Dtor.cpp and Rva005F23B2.h (2026-11-13)

24c7254157 gave the header 24 opaque bytes and adopted it in StrategicInGameUI.cpp (five includers
122/122 matched, link_check 5 of 5). Rva005F23B2Dtor.cpp, the destructor's own unit, stays queued:

- `header_adopt_lane.py adopt --class Rva005F23B2 ... Rva005F23B2Dtor.cpp`: "field renames:
  Rva005F23B2::m_list00 (+0x0, 16 bytes) has no canonical field of that offset and size".
- The destructor 0x005F23B2 (/EHs, funclets 0x007A4E94 and 0x007A4E9C) relies on two destructible
  members: the +0 list (begin/end/cap/index, inline `free` of begin) and the +0x10 `Rva005F20C5`
  (destructor row 0x005F21F8). Opaque storage cannot express those unwind states.
- `Rva005F20C5` has no header and three differing private views: Rva005F20C5.cpp (node pointer +
  count, `erase`), RvaTreeDtorFamily.cpp (`RvaTreeFamilyHolder m_header; int m_flag`), and this unit
  (`void *m_head00; int m_flag04`).

Next: one shared header for Rva005F20C5 covering those three units, then typed fields in
Rva005F23B2.h (list at +0, tree at +0x10) and rerun adopt/accept on Rva005F23B2Dtor.cpp and the
five current includers. Not tried here.
