### LINK-664: a generated canonical header drops the contract's size, so template instances over the class use the wrong stride
Status: Open (one instance; the class, header and contract were held by another seat on 2026-11-12, see below).
Updated: 2026-11-12 (seat halilkkaya-lk105); base `54e2556eae9`, census `4ba87ee6df` (index `5e2fc81a04`).

**Problem.** `header_adopt_lane.py generate` writes only the contract's `fields`. Pad members of the private views
are not fields (`tu_views.is_pad`), and nothing pads the class out to the contract's `size`. A class whose views
were `vptr + char m_padNN[...]` is therefore generated as a 4-byte class, although the header's own comment says
`// sizeof 128 (majority)`. Code that a unit compiles against the header with `sizeof(X)` in it changes:
pointer strides in STL helpers (`_Destroy`, `__destroy_aux`, `__copy_ptrs`, vector growth), `new X[n]`, and
member offsets after an embedded `X`. Rowed bodies whose bytes change are caught by the byte gate. Unrowed COMDAT
instances are not, and link_check sees them only when another object holds a retail-equal copy.

**Instance.** "Register canonical Rva0032A3A9Element, adopt it in 3 units" (StarkillerHDX, before the 16:28
census) replaced `class Rva0032A3A9Element { virtual ~...(); char m_pad04[0x7C]; }` in SidesList.cpp,
Rva0032C84FMethod.cpp and stlport_destroy_0032B580.cpp with the generated header (contract size 128, header
size 4). SidesList.cpp instantiates `_Destroy` / `__destroy` / `__destroy_aux<Rva0032A3A9Element *>` from STLport.
Its `__destroy_aux` loop now steps `add esi, 4`; retail's 0x0032A3A9 steps `add esi, 80h` (index digest
17cf7f724eb5 at census 1380d51e2c, 315247501032 now). Its `_Destroy` COMDAT calls that instance, so it is no
longer equal to the rowed retail copy in stlport_destroy_0032B580.cpp. SidesList.cpp comes first in path order,
so a real link can keep the wrong-stride chain (a destroy loop that walks 128-byte elements 4 bytes at a time).
SidesList.cpp: census 2026-11-12 00:41 "yes", 2,346 B; census 16:28 "no" (loser
`??$_Destroy@PAVRva0032A3A9Element@@@_STL@@YAXPAVRva0032A3A9Element@@0@Z`).

**Scan of the other generated headers.** 23 registered generated headers (no bases) have a contract size larger
than their generated fields: Rva002B2405 (712 vs 68), Rva004B0303Base0 (136 vs 8), Rva0032A3A9Element (128 vs 4),
Rva0030BBE5 (104 vs 4), Rva003FAC3F (48 vs 4), Rva0039A245Base0 (48 vs 8), Rva0053FA0A, Rva006DB160,
Rva00452E00Primary, Rva00170EFENode (36 vs 16), Rva0028D891Owner, Rva003909FAObj, FreelistPool and ten that differ
by 4 bytes. In the index (5e2fc81a04), only Rva0032A3A9Element has a COMDAT with two different bodies. The other
classes' COMDATs (Rva00170EFEIter's constructor, Object::getPhysics, the Rva005E62F1 constructor, Rva0022CFE6's
_Destroy and famgenDelete) have one body each and do not depend on the size.

**Fix (not applied: file:SidesList.cpp was held by StarkillerHDX@fleet, and class:Rva0032A3A9Element, its header,
contract, Rva0032C84FMethod.cpp and stlport_destroy_0032B580.cpp by ancalgonn-swarm-waste).** Either the generated
header carries the contract's size, for example a tail pad up to `size` emitted by the generator, so SidesList.cpp's
instances return to retail's 0x80 stride. Or SidesList.cpp declares
`template <> void _STL::_Destroy<Rva0032A3A9Element *>(Rva0032A3A9Element *, Rva0032A3A9Element *);` ahead of
its first use and references the rowed 0x0032B580 instead of instantiating its own chain. The first fixes the
cause; the second only this unit.

**Tooling lead (not edited).** `header_adopt_lane.py generate` could emit a tail pad when the contract's size
exceeds the last field's end, or refuse to register such a header. `class_gate` could compare `sizeof` of the
generated class with the contract.
