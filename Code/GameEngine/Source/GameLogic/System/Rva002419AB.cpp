// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

#include "ascii_string.h"

struct NoCaseTreeValue4;
namespace _STL { template<class First,class Second> struct pair; }
typedef _STL::pair<const AsciiString,NoCaseTreeValue4> NativeCountedStringPair;

// This 16-byte object is allocated by the target at 0x00240D8C. Its helper
// initializes a vtable-like word at +0 and an AsciiString at +8; the object
// identity is unresolved, so the type takes the address-derived name of the
// class whose vtable 0x00BEDC94 the 23FC98 constructor installs (its rowed
// dtor 0x0023FD06). That complete provider copies the eight-byte key/value pair
// at +8; the source pointer is passed through in the same single native stack slot.
class Rva0023FD06
{
private:
	void *m_vtable;

public:
	Rva0023FD06(const NativeCountedStringPair &value);
	int m_referenceCount;

private:
	char m_unknown_08[8];
};

class Rva002419ABOwner
{
private:
	Rva0023FD06 *m_value;

public:
	void *rva00240D8C(const AsciiString *value);
};

// The eight-byte (transition group name, frame) value the timed reverse
// 0x0023E323 consumes; GameLogic's load-screen stage 0x002423E3 passes it by
// value to build the callback for the event sequencer 0x003FE7E6.
#include "../../../Include/GameLogic/Rva0023E323.h"

class Rva00211E75Callback
{
public:
	Rva00211E75Callback(Rva0023E323 value);

private:
	Rva0023FD06 *m_value;
};

// ?rva00240D8C@Rva002419ABOwner@@QAEPAXPBVAsciiString@@@Z @ 0x00240D8C (73B):
// Ghidra boundary; caller 0x002419AB passes its local AsciiString by address.
// Retail allocates 16 bytes, initializes the object through 0x0023FC98, stores
// the pointer at this+0, increments its +4 count, and returns this. The object
// and operation remain address-derived.
void *Rva002419ABOwner::rva00240D8C(const AsciiString *value)
{
	m_value = new Rva0023FD06(*reinterpret_cast<const NativeCountedStringPair *>(value));
	if (m_value != 0)
		++m_value->m_referenceCount;
	return this;
}

// ??0Rva00211E75Callback@@QAE@VRva0023E323@@@Z @ 0x002419AB (55B): the
// callback's converting constructor from the by-value (group name, frame)
// value. It hands the value to 0x00240D8C, which allocates the 16-byte
// holder around it, and destroys the value's string at 0x00036410; the frame
// word travels in the same eight-byte argument.
Rva00211E75Callback::Rva00211E75Callback(Rva0023E323 value)
{
	((Rva002419ABOwner *)this)->rva00240D8C(&value.m_groupName);
}
