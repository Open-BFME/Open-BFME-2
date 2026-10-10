// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?AddCreateAHeroSpecialPowerUpgrade@Object@@QAEXPAVRva004B555F@@@Z retail 0x002972DE 130B
// Chain from 0x004B555F; unused name copy plus Science dedup at this+0x4A4 via rowed push_back.
// Evidence: callers plus rowed 0x004B555F 0x000365F0 0x00036410 0x002E01C6 plus prev 0x00295A0F next 0x00297360.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Rva004B555F
{
public:
	const AsciiString &rva004B555F();
};

struct Rva004B555FHolder
{
	char m_pad[4];
	ScienceType m_science;
};

class Object
{
public:
	void AddCreateAHeroSpecialPowerUpgrade(Rva004B555F *arg);
private:
	char m_pad[0x4A4];
	_STL::vector<ScienceType> m_sciences;
};

void Object::AddCreateAHeroSpecialPowerUpgrade(Rva004B555F *arg)
{
	if (!arg)
		return;
	AsciiString name = arg->rva004B555F();
	ScienceType science = *(ScienceType *)(*(unsigned int *)((char *)arg + 4) + 4);
	unsigned char needPush = 1;
	unsigned int i = 0;
	while (needPush) {
		if (i >= m_sciences.size())
			break;
		if (m_sciences[i] == science)
			needPush = 0;
		++i;
	}
	if (needPush)
		m_sciences.push_back(science);
}
