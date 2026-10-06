// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005C663C@@UAE@XZ @ 0x005C66A8 72B
// Dtor of Rva005C663C: derived vtable 0x00C74914 via virtual, DeleteButtonFlash
// on AsciiString at +8, releaseBuffer, then base vtable g_00BC6F20 via novtable
// base explicit store. Evidence: two [this] stores; Delete 0x003FED32 and
// releaseBuffer 0x00036410 rowed; layout (+4 int, +8 string, +C/+10 floats)
// matches rowed ctor 0x005C663C and neighbour Rva005C6599; caller 0x005C670F.
#include "ascii_string.h"

void __cdecl Rva003FED32DeleteButtonFlash(void **pp);
extern const void *const g_00BC6F20[];

class __declspec(novtable) RvaBase
{
public:
	RvaBase() : m_4(0) {}
	virtual ~RvaBase() { *(const void **)this = g_00BC6F20; }
	int m_4;
};

class Rva005C663C : public RvaBase
{
public:
	virtual ~Rva005C663C();
private:
	AsciiString m_8;
	float m_C;
	float m_10;
};

Rva005C663C::~Rva005C663C()
{
	Rva003FED32DeleteButtonFlash((void **)&m_8);
}
