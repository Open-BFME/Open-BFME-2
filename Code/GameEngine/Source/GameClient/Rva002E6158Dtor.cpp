// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ??1Rva002E6158@@QAE@XZ 0x002E6158 44B
// Evidence: chain from 0x002E5E5A vector dtor; scalar dtor over +4 Rva002E5791 array via delete[] then +8 trivial array via vector delete; callers 0x002E6415 0x002E6551 0x002E6303.
#include "ascii_string.h"
#include "unicode_string.h"
void operator delete[](void *p);

class Rva002E5791
{
public:
	~Rva002E5791();

private:
	StringBase<char> m_narrow;
	StringBase<unsigned short> m_wide;
};

class Rva002E6158
{
public:
	~Rva002E6158();

private:
	int m_unk00;
	Rva002E5791 *m_array;
	char *m_other;
};

Rva002E6158::~Rva002E6158()
{
	if (m_array)
	{
		delete[] m_array;
		m_array = 0;
	}
	if (m_other)
	{
		delete[] m_other;
		m_other = 0;
	}
	m_unk00 = 0;
}
