# Foundation Thing/Matrix3D ownership prerequisites

No combined source or shared-header change is retained. Only the independent
Module adoption proceeds. Foundation's Thing and Matrix3D queue keys remain.

Canonical Thing ends at +0x60, while this unit's private base ends at +0x44.
The private combined probe removes the overlapping Object padding and retains
all existing offsets. The canonical Matrix3D storage header also needs the
already-owned `float Get_Z_Rotation() const` declaration: the complete existing
eight-byte owner is at 0x00712020 in matrix3d.cpp. The unapplied API patch is
included as evidence, not a source change or retirement. The read-only include
graph inspection reached 428 existing sources, approximately 429 with this
consumer; no full gate was run for that unapplied header.

Replacing seven inline getTemplate calls with direct public m_template access
changes the 1,174-byte constructor to 1,172 bytes: the compiler combines two
kind-69/68 byte tests into one word load and AH tests. Retaining the existing
inline `Thing::getTemplate` outside the canonical declaration restores every
owned byte. That private combined candidate passes all five rows and EXACT EH;
all 26 prior definitions survive after the Module getter's access spelling is
normalized, plus the exact existing 34-byte ATL compiler iterator.

The retained Thing getter is four bytes, `8B 41 04 C3`, with no relocations.
Other observed Thing.cpp, WorkerAIUpdateCtor and BuildAssistant providers have
identical copies; it is not a sole-provider issue. No native RVA or dead-strip
proof for this getter is established. Raw executable references exist elsewhere
even though the index's admitted-reference graph has no incoming edges, so that
graph must not be described as proof that the getter is globally unused.

With the getter honestly annotated, the real row-owning source preflight
refuses `Thing::getTemplate` as unrowed. The source was automatically restored
byte for byte; no header, marker, pin or whitelist was changed. Do not rely on
the stale constructor annotation at the file's top: without a correct getter
annotation the scanner can misattribute this new out-of-class definition to
construct. That is not an ownership remedy.

Next establish the getter's legitimate source/row or retail-dead-strip status,
or find an exact inline source shape that uses the canonical declaration
without introducing an unowned definition. Then add the existing rotation API,
run the required shared-header checks, and retire both keys via acceptance.
