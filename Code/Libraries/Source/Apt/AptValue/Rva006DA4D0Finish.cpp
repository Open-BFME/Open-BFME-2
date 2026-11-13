// Native 6DA4D0/138 installs the AptArray-family table CEA778.
// This is distinct from AptValue constructors 6DCCC0/6DCD20 (CEAED0).
// Original class name is unknown; array offsets20/24/28 and calls are target facts.
// The rowed array-operation providers retain their older receiver spelling.
// This call-only declaration does not assert their private class layout.
// cl: /O2 /MD
#include <string.h>
class BfmeAptValue006DCD20 { public: void SetAt(int, BfmeAptValue006DCD20 *); };
#include "../../../../GameEngine/Include/Common/Rva006D9500.h"
// AptValue's AddRef/Release come first in these vtables, as in the five units
// (Rva006D6360Ctor.cpp, ...) that emit the same ??_7Rva006D6470Owner@@6B@.
class AptValue { public: virtual void AddRef(); virtual void Release(); };
class Rva006D6360 : public AptValue { public: Rva006D6360(int type, int size); virtual ~Rva006D6360(); char m_pad[0x18]; };
#include "../Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6470Owner : public Rva006D6360
{
public:
	Rva006D6470Owner(int type, int size) : Rva006D6360(type, size)
	{
		*(unsigned char *)&m_bits = 0;
		m_bits &= 0xFFFFFCFF;
	}
	virtual ~Rva006D6470Owner();
	unsigned int m_bits;
public:
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(p, size); }
};
class Rva006DA4D0 : public Rva006D6470Owner
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	Rva006DA4D0(int count, BfmeAptValue006DCD20 **pValues);
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};
Rva006DA4D0::Rva006DA4D0(int count, BfmeAptValue006DCD20 **pValues)
	: Rva006D6470Owner(0x16, count)
{
	mnCapacity = 0;
	m_data = 0;
	mnLength = count;
	reinterpret_cast<Rva006D9500 *>(this)->rva006D9500(count);
	for (int i = 0; i < mnLength; ++i)
		reinterpret_cast<BfmeAptValue006DCD20 *>(this)->SetAt(i, pValues[i]);
}
