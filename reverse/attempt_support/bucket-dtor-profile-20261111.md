## Bucket deleting destructor at 0x00148AFD (2026-11-11)

Real-link run 43001023175 refused slot 0 of the Bucket table at 0x007D3564.
MSVC 7.1 compiled the unchanged BucketDtor.cpp into two scratch objects. With
the effective region profile (-O2 -arch:SSE -G7), the deleting destructor is
30 bytes, aligned to 16. Changing only the effective optimization to -O1
produces the verified NameKeyGenerator.obj COMDAT exactly: 28 bytes, alignment
1, REL32 Bucket::~Bucket at +4 and global operator delete at +17. The byte
after the delete call changes from add esp,4 to pop ecx.

Adding /O1 to the source directive alone cannot select that profile.
flag_defaults.py propose Code/GameEngine/Source/Common/BucketDtor.cpp reported
that the region default keeps every row. Its only assigned row is the 14-byte
ordinary destructor at 0x00148B19. The failing deleting destructor belongs to
NameKeyGenerator.cpp. A tooling repair could compare the selected provider of
a verified COMDAT when evaluating profile proposals. A regression test should
also reject a candidate with different relocations. The TU map approves no move
for either row. No override was added and the trial directive was reverted.
