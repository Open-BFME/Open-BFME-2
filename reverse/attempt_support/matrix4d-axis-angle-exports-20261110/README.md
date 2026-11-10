# Matrix4D axis-angle exports, LINK-018

Tested at 40649ef34a with the repository's MSVC 7.1 compiler and Snapshot.cpp flags. The attached patch applies to the approved TU. It keeps the existing x87 implementation in a shared force-inlined member, adds Set returning *this, and makes the constructor call the same member. It does not change Coord3D.

The two retail exports at RVA 0x00004079 are ordinal 285 (constructor) and ordinal 1391 (Set). In a scratch compile using the canonical Coord3D layout with the class key changed to class and public field access, the compiler defined both exact export names:

- ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
- ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z

The two COFF sections were each 357 bytes. Each had exactly one DIR32 relocation to __real@3f800000 at +0x1D. build.compile_function resolved both with no masked or unresolved operand. Each result matched the full retail body, SHA-256 3ef168049b60a10630ef0268d21c4b1370c95ae0caa6022f5b43a78b6cec9856. A control using the unchanged canonical struct emitted two exact bodies but spelled both parameters ABUCoord3D. Another control, calling ordinary out-of-line Set from the constructor, reproduced Set but failed the constructor byte check.

To repeat, use a scratch copy of Snapshot.cpp under build/, preserving the TU compiler flags and original include search path. Apply axis-angle.patch. For the class-key trial only, substitute the canonical header text at its include site with struct Coord3D changed to class Coord3D and an explicit public access label. Compile to a scratch object; check each named symbol against the existing 357-byte row. No class-key override belongs in the committed TU. After the coordinated Coord3D migration, verify all Snapshot rows, admit the folded Set row using the existing owner, and check both names in the real link.
