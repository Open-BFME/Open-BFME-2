// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -EHsc -MD
// stlport
// ??1ControlBarScheme@@QAE@XZ, retail 0x0032002C, 105 bytes. Dtor of ControlBarScheme: body calls reset 0x31FAF0 then destroys list at +0x170 and array at +0x158 and two AsciiStrings at +0xC/+0x0.
// Evidence: deleting-dtor caller at 0x0032013C; offsets match the ControlBarScheme reset TU (Rva0031FAF0.cpp); callees rowed List_base 0x004EC395 vector-dtor 0x00629110 releaseBuffer 0x00036410.
#include "ascii_string.h"

#include <list>

// The list teardown stays the rowed STLport int-list body at 0x004EC395
// (clear 0x0023DAA5 then free), so the member teardown is declared here.
namespace _STL { template <> _List_base<int, allocator<int> >::~_List_base(); }

class Rva00200667 : public _STL::_List_base<int, _STL::allocator<int> >
{
public:
	~Rva00200667() {}
};

class ControlBarScheme
{
public:
	void reset();
	~ControlBarScheme();
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
	// Native EH calls the complete five-byte list wrapper at200667;
	// the normal path inlines it and calls the23-byte base at4EC395.
	// The node payload is not established by these destruction paths.
	Rva00200667 m_list170;
};

ControlBarScheme::~ControlBarScheme()
{
	reset();
}
