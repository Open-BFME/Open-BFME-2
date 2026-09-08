# Compressed-animation array ownership

The retail `HCompressedAnimClass::Free` body at RVA `0x0018FE30` is 93 bytes. It releases two arrays, at object offsets `0x54` and `0x58`, then clears both pointers. The existing ancestor reconstruction released only the first array.

The first node is the already reconstructed `NodeCompressedMotionStruct`: stride 28, constructor `0x0018F680`, destructor `0x0018F6A0`. The second node has stride 24, constructor `0x0018F850` (22 bytes), and destructor `0x0018F870` (70 bytes). Its original source type name is not recovered; `BFME2CompressedMotionChannels` is an explicitly descriptive local name. It owns five polymorphic channel pointers followed by a visibility-channel pointer.

The compressed-animation loader independently establishes the second array. At VA `0x005901B0` it pushes destructor `0x0058F870`, then constructor `0x0058F850` at `0x005901B5`. It passes stride `0x18` at `0x005901BE` to the vector-construction helper, then stores the resulting array in object field `0x58` at `0x005901C8`. This is separate evidence from the cleanup body, whose two array destructors use strides `0x1C` and `0x18`.

The second-node destructor first releases its visibility channel through the existing `TimeCodedBitChannelClass` destructor at RVA `0x001960C0`. It then performs global deletion of each of the five polymorphic channels. Retail calls slot 1 with deleting flags zero, followed by global operator delete, including the null case. The local declaration labels unused slot 0 as unknown. It does not invent a method identity for that slot.

The dedicated translation unit uses `/G7`: this reproduces the retail loop increment and instruction scheduling, giving all 70 destructor bytes. The 22-byte constructor and 93-byte outer cleanup remain exact. Compile-time checks enforce the two node strides. Function sizes end at their complete RET instructions and exclude alignment.

The existing 84-byte vector deleting destructor at RVA `0x0018FB10` was labeled `MultiFixedPoolDecalSystemClass::LogicalDecalClass`, using a guessed destructor pin to `0x0018F870`. The independently established animation ownership refutes that identity. The row is replaced by the second animation-node deleting destructor, and the guessed decal pin is removed. This correction receives zero new-byte credit.

The new executable contribution is 22 + 70 + 93 = 185 bytes. The class prefix preceding `0x54` remains opaque in this narrowly scoped cleanup declaration; no unverified field meanings are claimed.
