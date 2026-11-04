// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// ??0Rva007401F6@@QAE@XZ, retail 0x007401E5..0x007401F6 (17 B): the default
// constructor of the class whose rowed destructor (0x007401F6) and deleting
// destructor (0x00740226) sit right after it. Target facts: it stores the
// class vtable 0x00CF15E8 (the table whose first slot is ??_G 0x00740226),
// sets +4 to -1 and clears the string handle at +8. The inlined base
// constructor's own vptr store is dead and removed; it supplies the -1 at +4.
#include "ascii_string.h"
// Base of Rva007401F6: retail vtable 0x0083962C holds one slot (scalar
// deleting dtor 0x004102AB); ctor 0x00410297 stores -1 at +4 and the empty
// dtor 0x004102A4 only restores the vptr. Same view as Rva004103E7Finish.cpp.
class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_base((unsigned)-1) {}
	virtual ~Rva0045EF90Base() {}
protected:
	unsigned m_base;
};
class Xfer;
// Retail vtable 0x008F15E8: scalar deleting dtor 0x00740226, then __purecall
// in slots 1-3, which the W3DAptComponentView3D vtable 0x008F1600 fills
// (slot 1 0x007402C0, slot 3 0x00740BCD); slot 4 is its own SetLight.
// No user-declared destructor: retail's ~Rva007401F6 (0x007401F6, 48 B) is the
// compiler-generated one, which skips the derived vptr store a written
// destructor makes, then releases m_str08 and restores the base vtable.
class Rva007401F6 : public Rva0045EF90Base
{
public:
	Rva007401F6();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
private:
	AsciiString m_str08;
};
Rva007401F6::Rva007401F6()
{
}
