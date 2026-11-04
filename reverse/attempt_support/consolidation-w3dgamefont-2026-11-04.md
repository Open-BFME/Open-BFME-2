# W3DGameFont consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameFont.cpp`; `consolidation_queue.py --check-tu` passed. A fresh GUI-scoped planner and its `--check` passed. The plan had 17 approved rows, three pull donors and no mixed or refused files.

The merge dry run accepted no donors. `W3DFontLibraryDestructor.cpp` was rejected because `W3DFontLibrary::~W3DFontLibrary` already has a body in the composed TU. `W3DFontLibraryLoadFontData.cpp` was rejected because `GameFont::m_pointSize` and `m_nameData` are absent from the class view; the tool recommends reconciling `BfmePod4` and `W3DFontLibrary`. No changes or claims were made. No source reduction or identity/link progress is claimed.
