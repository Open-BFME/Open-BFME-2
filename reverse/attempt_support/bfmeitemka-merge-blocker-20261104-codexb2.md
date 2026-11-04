# BfmeItemKA unchanged merge dry run (2026-11-04)

The allocated `Code/GameEngine/Source/GameClient/BfmeItemKA.cpp` plan has 32
approved rows and 5 donor files. Dry run accepted none: `GameSubTitle.cpp`
redeclares `StringBase` and lacks `m_count`; `GameSubTitleDraw.cpp` lacks
`GameSubTitle::rva002600DC` and `m_startFrame`; the W5/W6 STL sweep donors fail
byte checks. LinkGuard confirmed the five units remain census-linked. Reconcile
the class views and recover the two exact STL bodies before retrying.
