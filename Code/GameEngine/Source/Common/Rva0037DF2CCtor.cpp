// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0037DF2C@@QAE@XZ @0x0037DF2C (97B).
// Ctor with vtable 0x00BDF158 at +0x0, AsciiString at +0x4 from TheEmptyString
// 0x00DE0878 via pinned StringBase copy 0x000365F0, float 0 at +0x8 via xorps
// plus movss, int 0 at +0xC, 0x80-byte block at +0x10 via inline helper ctor
// calling rowed clear80 0x001EAE6F, int 0 at +0x90, struct at +0x94 via rowed
// zeroing ctor 0x004E04FD. Empty base with inline ctor plus declared-only dtor
// arms EH state 0 before first member call per ModuleData precedent. Flags add
// /EHsc for EH prolog plus /arch:SSE for movss to sibling /O1 /DNDEBUG /MD.
// Callers at 0x001EC15F 0x001EC3FA 0x001EC491 0x001ECD05 0x0040C354.
#include <string.h>
#include "ascii_string.h"
extern const void *const g_00BDF158[];
class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper() { clear80(); }
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};
class Rva004E04FD
{
public:
	Rva004E04FD();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
};
class Rva0037DF2C : public EmptyBase
{
public:
	Rva0037DF2C();
private:
	unsigned int m_vtable;
	AsciiString m_s04;
	float m_f08;
	int m_c0C;
	Rva001EAE6FHelper m_h10;
	int m_90;
	Rva004E04FD m_94;
};
Rva0037DF2C::Rva0037DF2C() : m_vtable((unsigned int)g_00BDF158), m_s04(AsciiString::TheEmptyString), m_f08(0.0f), m_c0C(0), m_90(0)
{
}
