// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ??1Rva0031FAF0@@QAE@XZ, retail 0x0032002C, 105 bytes. Dtor of Rva0031FAF0: body calls clear 0x31FAF0 then destroys list at +0x170 and array at +0x158 and two AsciiStrings at +0xC/+0x0.
// Evidence: deleting-dtor caller at 0x0032013C; offsets match Rva0031FAF0 clear TU; callees rowed List_base 0x004EC395 vector-dtor 0x00629110 releaseBuffer 0x00036410.
#include "ascii_string.h"

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	private:
		void *m_header;
	};
	typedef _List_base<int, allocator<int> > ListBaseInt;
}

class Rva00200667
{
public:
	~Rva00200667();
private:
	void *m_header;
};

class Rva0031FAF0
{
public:
	void rva0031FAF0();
	~Rva0031FAF0();
private:
	AsciiString m_s0;
	int m_4;
	int m_8;
	AsciiString m_c;
	int m_10;
	int m_14;
	char m_pad18[0x1C];
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	int m_78;
	int m_7c;
	int m_80;
	int m_84;
	int m_88;
	int m_8c;
	int m_90;
	char m_pad94[0xBC];
	int m_150;
	int m_154;
	Rva00200667 m_lists[6];
	_STL::ListBaseInt m_list170;
};

Rva0031FAF0::~Rva0031FAF0()
{
	rva0031FAF0();
}
