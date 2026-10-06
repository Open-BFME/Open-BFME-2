// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva00212ED3@@QAE@XZ, RVA 0x00212ED3, 503B. Non-virtual dtor draining
// AsciiString members plus vector<AsciiString> at +0x188 via rowed 0x0002CC70
// and 3 RefHolder members at +0x148/+0x14c/+0x150 via rowed Release_Ref
// 0x00050ED3; base AsciiString at +0. Callers include 0x0021468B in
// 0x00214405/691. Owner unproven so honest-address class Rva00212ED3.
#include "ascii_string.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva00212ED3Ref
{
	OpaqueRefCounted *m_ptr;
	~Rva00212ED3Ref()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
};

namespace _STL {
template <typename T> class allocator;
template <typename T, typename A = allocator<T> > class vector
{
public:
	~vector();
};
}

class Rva00212ED3 : public AsciiString
{
public:
	~Rva00212ED3();
private:
	char m_pad04[0x30];
	AsciiString m_34;
	char m_pad38[0x48];
	AsciiString m_80;
	AsciiString m_84;
	AsciiString m_88;
	AsciiString m_8c;
	AsciiString m_90;
	AsciiString m_94;
	AsciiString m_98;
	AsciiString m_9c;
	AsciiString m_a0;
	AsciiString m_a4;
	AsciiString m_a8;
	AsciiString m_ac;
	AsciiString m_b0;
	AsciiString m_b4;
	AsciiString m_b8;
	AsciiString m_bc;
	AsciiString m_c0;
	char m_padC4[0x50];
	AsciiString m_114;
	AsciiString m_118;
	AsciiString m_11c;
	char m_pad120[0x28];
	Rva00212ED3Ref m_148;
	Rva00212ED3Ref m_14c;
	Rva00212ED3Ref m_150;
	AsciiString m_154;
	AsciiString m_158;
	char m_pad160[0x20];
	AsciiString m_17c;
	AsciiString m_180;
	AsciiString m_184;
	_STL::vector<AsciiString> m_188;
};

Rva00212ED3::~Rva00212ED3() {}
