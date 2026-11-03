### TeamTemplateInfo destructor and deleter link predictions (2026-10-30, dd-32)

At base `a5c01ba2ba`, `tools/link_check.py
Code/GameEngine/Source/Common/RTS/TeamTemplateInfoDtor.cpp` reports
`LINKS LINKED 0 -> 236 bytes` against census index `85f6b7f40c`, and the
sibling `TeamTemplateInfoDeleter.cpp` links too. Both census rows still say
`linked=no, unresolved=1` because their sources changed after the 15:08 census;
the blocker was the `??1Rva0039EA9C@@QAE@XZ` provider now rowed in
`Common/RTS/Team.cpp`. No source change is needed; the next census records
`linked=yes`. The picker's `0x0039EAED` claim is released as census-awaiting.
