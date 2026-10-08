# OpenContain restoration

The complete existing OpenContain.cpp and served WB 0119BC70 body were read.
WB independently identifies LoadPostProcess. ZH and the clean BFME1 donor at
34f59164 provide the restoration purpose; the existing lower-case source
spelling is retained. The donor's per-rider enclosure query is replaced by
the native routine's enclosing-container walk before the rider loop.

Native 00463C6E..00463D58 establishes owner +8, lists +54/+74, the secondary
interface at +20, its slot 44, Object's containing-owner +274 and containment
module +250, and primary slot 24 with two trailing zero arguments. Those
arguments and the mask's application type remain unnamed. Word 1 bit 29 is
tested. The existing native secondary vtable 8433B0 slot 44 points to 462CE1;
that provider copies exactly 16 bytes through the rowed 2CF108 copy constructor
and returns the supplied buffer. This corroborates the mask storage and ABI.

The first isolated body copied the returned mask to a named local, causing
a shorter direct stack-byte test. Testing the returned temporary directly
reproduces the native EAX load/shift/test. The whole source uses O1 with its
existing G7/SSE flags. All four matched home rows pass the normal byte gate,
including the three pre-existing template bodies. The routine's compiled
235th alignment byte is also equal to retail. No pins, aliases, optimization
pragmas, emitted instructions or naked bodies were added. Existing actual
XferException, list, lookup and UpdateModule providers are reused.

The whole-source placement sweep reports zero additional bodies or pins.
This records scoped byte/relocation verification, not a fresh link census or
runtime result; the private source class still carries the reference layout
for its remaining unmatched methods, while this routine uses the explicitly
measured native view.
